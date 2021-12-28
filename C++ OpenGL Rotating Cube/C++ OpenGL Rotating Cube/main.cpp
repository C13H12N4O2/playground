#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

const int FPS = 60;

GLfloat currentAngleOfRotation = 0.0;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glutWireCube(1.0);
  glRotatef(currentAngleOfRotation, 0.0, 0.0, 0.0);
  glFlush();
}

void timer(int v) {
  currentAngleOfRotation += 1.0;
  if (currentAngleOfRotation > 360.0) {
    currentAngleOfRotation -= 360.0;
  }
  glutPostRedisplay();
  glutTimerFunc(1000/FPS, timer, v);
}

void init() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, 4.0 / 3.0, 1.0, 40.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Rotating Cube");
  glutDisplayFunc(display);
  init();
  glutTimerFunc(100, timer, 0);
  glutMainLoop();
}
