#pragma once

#include "net_common.h"
#include "net_client.h"

namespace Game {
namespace Character {
class Snake {
public:
  Snake() {
    
  }
  
  virtual ~Snake() {
    
  }
  
public:
  bool HasID() {
    return user != 0;
  }
  
  void DrawSnake() {
    glColor3f(0.0, 1.0, 0.0);
    glRectd(posX * 10, posY * 10, (posX + 1) * 10, (posY + 1) * 10);
  }
  
public:
  int posX = 30;
  int posY = 30;
  int user;
};
}
}
