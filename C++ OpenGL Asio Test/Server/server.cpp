#include <Test_Framework/olc_net.h>

enum class CustomMsgTypes : uint32_t {
  ServerAccept,
  ServerDeny,
  ServerPing,
  MessageAll,
  ServerMessage,
  GameData,
};

class CustomServer : public olc::net::server_interface<CustomMsgTypes> {
public:
  CustomServer(uint16_t nPort) : olc::net::server_interface<CustomMsgTypes>(nPort) {
  }
  
protected:
  Game::Character::Snake snake;
  
protected:
  virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client) {
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::ServerAccept;
    client->Send(msg);
    return true;
  }

  virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client) {
    std::cout << "Removing client [" << client->GetID() << "]\n";
  }
  
  virtual void OnMessage(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client, olc::net::message<CustomMsgTypes>& msg) {
    switch (msg.header.id) {
      case CustomMsgTypes::ServerPing: {
        std::cout << "[" << client->GetID() << "]: Server Ping\n";
        client->Send(msg);
        break;
      }
      case CustomMsgTypes::MessageAll: {
        std::cout << "[" << client->GetID() << "]: Message All\n";
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerMessage;
        msg << client->GetID();
        MessageAllClients(msg, client);
        break;
      }
      case CustomMsgTypes::GameData: {
        std::cout << "[" << client->GetID() << "]: Game Data\n";
        MessageGameData(msg, client);
        break;
      }
    }
  }
};

CustomServer server(60000);
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

void ServerStatus() {
  glColor3fv(white);
  glRasterPos2i(20, 580);
  printString("SERVER ");
  
  if (n < 50) {
    glColor3fv(red);
    glRasterPos2i(90, 580);
    status ? printString("ON") : printString("OFF");
  } else if (n == 100) {
    n = 0;
  }
  
  ++n;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  ServerStatus();
  glFlush();
  glutSwapBuffers();
  server.Update();
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
    case GLUT_KEY_UP: status = server.Start(); break;
    case GLUT_KEY_DOWN: server.Stop(); status = false; break;
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
  glutCreateWindow("Server");
  init();
  glutReshapeFunc(reshape);
  glutTimerFunc(0, timer, 0);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutMainLoop();
}
