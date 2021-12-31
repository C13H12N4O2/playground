#include <Test_Framework/olc_net.h>

Game::Character::Snake snake;

enum class CustomMsgTypes : uint32_t {
  ServerAccept,
  ServerDeny,
  ServerPing,
  MessageAll,
  ServerMessage,
  GameData,
};

class CustomClient : public olc::net::client_interface<CustomMsgTypes> {
public:
  void PingServer() {
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::ServerPing;
    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
    msg << timeNow;
    Send(msg);
  }
  
  void GameData() {
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::GameData;
    msg << snake;
    Send(msg);
  }
};

CustomClient c;
GLfloat white[3] = { 1.0, 1.0, 1.0 };
GLfloat red[3] = { 1.0, 0.0, 0.0 };
GLfloat black[3] = { 0.0, 0.0, 0.0 };
GLfloat green[3] = { 0.0, 1.0, 0.0 };
GLuint fontOffset;
int n = 0;
bool status = false;

void makeRestarterFont(void) {
  GLuint i, j;
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  fontOffset = glGenLists(128);
  for (i = 0, j = 'A'; i != 26; ++i, ++j) {
    glNewList(fontOffset + j, GL_COMPILE);
    glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, olc::net::letters[i]);
    glEndList();
  }
  glNewList(fontOffset + ' ', GL_COMPILE);
  glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, olc::net::space);
  glEndList();
}

void printString(std::string s) {
  glPushAttrib(GL_LIST_BIT);
  glListBase(fontOffset);
  glCallLists(static_cast<GLsizei>(s.size()), GL_UNSIGNED_BYTE, reinterpret_cast<GLubyte *>(s.data()));
    glPopAttrib();
}

void ClientStatus() {
  glColor3fv(white);
  glRasterPos2i(20, 580);
  printString("CLIENT ");
  
  if (n < 50) {
    glColor3fv(red);
    glRasterPos2i(90, 580);
    status ? printString("ON") : printString("OFF");
  } else if (n == 100) {
    n = 0;
  }
  
  ++n;
}

void CheckClient() {
  if (c.IsConnected()) {
    if (!c.Incoming().empty()) {
      auto msg = c.Incoming().pop_front().msg;
      
      switch (msg.header.id) {
        case CustomMsgTypes::ServerAccept: {
          std::cout << "Server Accepted Connection\n";
          break;
        }
        case CustomMsgTypes::ServerPing: {
          std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
          std::chrono::system_clock::time_point timeThen;
          msg >> timeThen;
          std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
          break;
        }
        case CustomMsgTypes::ServerMessage: {
          uint32_t clientID;
          msg >> clientID;
          std::cout << "Hello from [" << clientID << "]\n";
          break;
        }
        case CustomMsgTypes::GameData: {
          Game::Character::Snake user;
          msg >> user;
          user.DrawSnake();
          break;
        }
      }
    }
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  ClientStatus();
  CheckClient();
  snake.DrawSnake();
  c.GameData();
  glFlush();
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27: exit(0);
  }
}

void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_F1: status = c.Connect("127.0.01", 60000); break;
    case GLUT_KEY_F2: c.Disconnect(); status = false; break;
    case GLUT_KEY_F3: c.PingServer(); break;
    case GLUT_KEY_UP: snake.posY++; break;
    case GLUT_KEY_DOWN: snake.posY--; break;
    case GLUT_KEY_RIGHT: snake.posX++; break;
    case GLUT_KEY_LEFT: snake.posX--; break;
  }
}

void init() {
  glShadeModel(GL_FLAT);
  makeRestarterFont();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Client");
  init();
  glutReshapeFunc(reshape);
  glutTimerFunc(0, timer, 0);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutMainLoop();
}
