#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>

struct Point {
  GLfloat x, y;
  Point(GLfloat x = 0, GLfloat y = 0): x(x), y(y) {}
  Point midpoint(Point p) { return Point((x + p.x) / 2.0, (y + p.y) / 2.0); }
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  static Point vertices[] = { Point(0, 0), Point(200, 500), Point(500, 0) };
  static Point p = vertices[0];
  glBegin(GL_POINTS);
  for (int i = 0; i != 100000; ++i) {
    p = p.midpoint(vertices[rand() % 3]);
    glVertex2f(p.x, p.y);
  }
  glEnd();
  glFlush();
}

void init() {
  glClearColor(0.25, 0.0, 0.2, 1.0);
  glColor3f(0.6, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(40, 40);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Sierpinski Triangle");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
