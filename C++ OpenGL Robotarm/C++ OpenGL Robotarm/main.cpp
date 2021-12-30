#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static int shoulderAngle = 0, elbowAngle = 0;

void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_LEFT: { (elbowAngle += 5) %= 360; break; }
    case GLUT_KEY_RIGHT: { (elbowAngle -= 5) %= 360; break; }
    case GLUT_KEY_UP: { (shoulderAngle += 5) %= 360; break; }
    case GLUT_KEY_DOWN: { (shoulderAngle -= 5) %= 360; break; }
    default: { return; }
  }
  glutPostRedisplay();
}

void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
  glPushMatrix();
  glScalef(width, height, depth);
  glutWireCube(1.0);
  glPopMatrix();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glRotatef(static_cast<GLfloat>(shoulderAngle), 0.0, 0.0, 1.0);
  glTranslated(1.0, 0.0, 0.0);
  wireBox(2.0, 0.4, 1.0);
  glTranslated(1.0, 0.0, 0.0);
  glRotatef(static_cast<GLfloat>(elbowAngle), 0.0, 0.0, 1.0);
  glTranslatef(1.0, 0.0, 0.0);
  wireBox(2.0, 0.4, 1.0);
  glPopMatrix();
  glFlush();
}

void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 1.0, 20.0);
}

void init() {
  glShadeModel(GL_FLAT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1, 2, 8, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Robot Arm");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  init();
  glutMainLoop();
}
