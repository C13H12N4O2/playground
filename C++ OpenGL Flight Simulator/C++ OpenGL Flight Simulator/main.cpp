#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "cockpit.h"
#include "landscape.h"

Landscape landscape(200, 143);
static bool wireframe = false;

void newLandscape() {
  static double rug = static_cast<double>(rand()) / RAND_MAX;
  landscape.create(rug);
}

static Ship theShip(Point(60, 40, 220));
static Cockpit cockpit(theShip);

void keyboard(unsigned char key, int, int) {
  const double deltaSpeed = 0.01;
  const double angle = 0.02;
  switch (key) {
    case '8': theShip.setSpeed(theShip.getSpeed() + deltaSpeed); break;
    case 'm': theShip.setSpeed(theShip.getSpeed() - deltaSpeed); break;
    case 'w': wireframe = !wireframe; break;
    case 'r': newLandscape();
    case 'j': theShip.roll(angle); break;
    case 'l': theShip.roll(-angle); break;
    case 'h': theShip.yaw(angle); break;
    case ';': theShip.yaw(-angle); break;
    case 'i': theShip.pitch(-angle); break;
    case 'k': theShip.pitch(angle); break;
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  wireframe ? landscape.drawWireFrame() : landscape.draw();
  cockpit.draw();
  glFlush();
  glutSwapBuffers();
}

void timer(int v) {
  theShip.fly();
  Point eye(theShip.getPosition());
  Point at(theShip.getPosition() + theShip.getDirection());
  Vector up(theShip.getVectical());
  glLoadIdentity();
  gluLookAt(eye.x, eye.y, eye.z, at.x, at.y, at.z, up.i, up.j, up.k);
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, v);
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, static_cast<GLfixed>(w) / static_cast<GLfloat>(h), 0.05, 300.0);
  glMatrixMode(GL_MODELVIEW);
}

void init() {
  srand(9903);
  glEnable(GL_DEPTH_TEST);
  newLandscape();
  cockpit.create();
  GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat dark[] = { 0.2, 0.15, 0.2, 1.0 };
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat direction[] = { 0.2, 1.0, 0.5, 0.0 };
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);
  
  glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glLightfv(GL_LIGHT0, GL_POSITION, direction);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void writeHelpToConsole() {
  std::cout << "j/l - roll left / right\n";
  std::cout << "i/k - pitch down / up\n";
  std::cout << "h/; - yaw left / right\n";
  std::cout << "8/m - speed up / slow donw\n";
  std::cout << "w - toggle wireframe mode\n";
  std::cout << "r - generate a new landscape\n";
}

int main(int argc, char** argv) {
  writeHelpToConsole();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(780, 500);
  glutCreateWindow("Simple Flight");
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
}
