#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
  for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
    glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
    glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
  }
  glEnd();
  
  glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
    glColor3f(0, 1, 0); glVertex3f(1, 0, 1);
    glColor3f(0, 0, 1); glVertex3f(0, 0, -1.4);
    glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
  glEnd();
  
  glFlush();
}

void init() {
  glClearColor(0.1, 0.39, 0.88, 1.0);
  glColor3f(1.0, 1.0, 1.0);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-2, 2, -1.5, 1.5, 1, 40);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0, 0, -3);
  glRotatef(50, 1, 0, 0);
  glRotatef(70, 0, 1, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 800);
  glutCreateWindow("A Simple Tetrahedron");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
