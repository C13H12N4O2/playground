#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLubyte F[24] = {
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xff, 0x00,
  0xff, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xff, 0xc0,
  0xff, 0xc0,
};

GLubyte E[24] = {
  0xff, 0xc0,
  0xff, 0xc0,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xff, 0x00,
  0xff, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xff, 0xc0,
  0xff, 0xc0,
};

GLubyte H[24] = {
  0xc0, 0xc0,
  0xc0, 0xc0,
  0xc0, 0xc0,
  0xc0, 0xc0,
  0xc0, 0xc0,
  0xff, 0xc0,
  0xff, 0xc0,
  0xc0, 0xc0,
  0xc0, 0xc0,
  0xc0, 0xc0,
  0xc0, 0xc0,
  0xc0, 0xc0,
};

GLubyte I[24] = {
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
  0x0c, 0x00,
};

GLubyte L[24] = {
  0xff, 0xc0,
  0xff, 0xc0,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
  0xc0, 0x00,
};

void init() {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2i(20, 20);
  glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, F);
  glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, E);
  glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, H);
  glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, I);
  glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, L);
  glFlush();
}

void reshape(int w, int h) {
  glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, 0, h, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27: exit(0);
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(100, 100);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Fonts");
  init();
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutMainLoop();
}
