#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"
#include "apple.h"
#include "grid.h"

#include <queue>
#include <functional>
class Snake {
 private:
  std::queue<Point> tail;
  Point head;
  unsigned int length;

 public:

  Snake();
  void eatsApple();
  inline Point getHead() {return head;}


  template <unsigned int L,unsigned int W>
    void update(Grid<L,W>& g,const Apple& a);

  template <unsigned int L,unsigned int W>
    Point dumbAI(const Grid<L,W>& g,const Apple& a);

  template <unsigned int L,unsigned int W>
    Point lessDumbAI(const Grid<L,W>& g,const Apple& a);

  template <unsigned int L,unsigned int W>
    Point randomAI(const Grid<L,W>& g,const Apple& a);

};


#include "snakeAI.hpp"
#include "snake.hpp"

#endif
