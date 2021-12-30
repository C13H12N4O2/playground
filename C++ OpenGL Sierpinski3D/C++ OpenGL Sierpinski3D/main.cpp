#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>

struct Point {
  GLfloat x, y, z;
  Point(GLfloat x, GLfloat y, GLfloat z): x(x), y(y), z(z) {}
  Point midpoint(Point p) { return Point((x + p.x) / 2, (y + p.y) / 2, (z + p.z) / 2); }
};

void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0, GLfloat(w) / GLfloat(h), 10.0, 1500.0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void generateMorePoints() {
  static Point vertices[4] = {
    Point(-250, -225, -200),
    Point(-150, -225, -700),
    Point(250, -225, -275),
    Point(0, 450, -500)
  };
  static Point lastPoint = vertices[0];
  glBegin(GL_POINTS);
  for (int i = 0; i <= 500; ++i) {
    lastPoint = lastPoint.midpoint(vertices[rand() % 4]);
    GLfloat intensity = (700 + lastPoint.z) / 500.0;
    glColor3f(intensity, intensity, 0.25);
    glVertex3f(lastPoint.x, lastPoint.y, lastPoint.z);
  }
  glEnd();
  glFlush();
}

void init() {
  glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Sierpinski Tetrahedron");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(generateMorePoints);
  init();
  glutMainLoop();
}
