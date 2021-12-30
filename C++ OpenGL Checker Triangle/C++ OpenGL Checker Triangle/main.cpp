#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>

#define red { 0xff, 0x00, 0x00 }
#define yellow { 0xff, 0xff, 0x00 }
#define magenta { 0xff, 0, 0xff }
GLubyte textrue[][3] = {
  red, yellow,
  yellow, red,
};

void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80, static_cast<GLfloat>(width / height), 1, 40);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, textrue);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5, 1.0); glVertex2f(-3, 3);
    glTexCoord2f(0.0, 0.0); glVertex2f(-3, 0);
    glTexCoord2f(1.0, 0.0); glVertex2f(0, 0);
  
    glTexCoord2f(4, 8); glVertex2f(3, 3);
    glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
    glTexCoord2f(8, 0.0); glVertex2f(3, 0);
  
    glTexCoord2f(5, 5); glVertex2f(0, 0);
    glTexCoord2f(0.0, 0.0); glVertex2f(-1.5, -3);
    glTexCoord2f(4, 0.0); glVertex2f(1.5, -3);
  glEnd();
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(520, 390);
  glutCreateWindow("Textured Triangles");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}
