#ifndef LANDSCAPE_H_
#define LANDSCAPE_H_

#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <cmath>
#include <cstdlib>
#include <memory>

class Landscape {
public:
  Landscape(int rows, int columns);
  
public:
  void generate(int x1, int y1, int x2, int y2, double rug);
  void drawTriangle(int x1, int z1, int x2, int z2, int x3, int z3);
  void vertex(double x, double z);
  void createSolidDisplayList();
  void createWireFrameDisplayList();
  void create(double rug);
  
public:
  double scale(double x) {
    return x * ((static_cast<double>(rand()) / RAND_MAX) - 0.5);
  }
  
  void draw() {
    glCallList(solidId);
  }
  
  void drawWireFrame() {
    glCallList(wireFrameId);
  }
  
public:
  int rows;
  int columns;
  double hightest;
  std::vector<std::vector<double>> d;
  int solidId;
  int wireFrameId;
  static double unused;
};

#endif
