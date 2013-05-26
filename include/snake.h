#ifndef MY_SNAKE_DOT_H
#define MY_SNAKE_DOT_H

#include "point.h"
#include "apple.h"
#include "grid.h"

#include <queue>
#include <deque>
#include <functional>
class Snake {
 private:
  std::deque<Point> tail;
  Point head;
  unsigned int length;
  Point* pointToRemove;

 public:

  inline Snake():
  tail(std::deque<Point>()),
    head(Point(0,0)),
    length(3),
    pointToRemove(NULL)
      {}
  inline void eatsApple() {length++;} 
  inline Point getHead() const {return head;} 
  inline const Point* getPreviousHead() const
  {
    if (!tail.empty())
      return &(tail.front());
    else 
      return NULL;
  }
  inline Point* getPointToRemove() const
  {
    return pointToRemove;
  }


  template <unsigned int L,unsigned int W>
    void update(const Grid<L,W>& g,const Point& a);

  template <unsigned int L,unsigned int W>
    Point dumbAI(const Grid<L,W>& g,const Point& a);

  template <unsigned int L,unsigned int W>
    Point lessDumbAI(const Grid<L,W>& g,const Point& a);

  template <unsigned int L,unsigned int W>
    Point randomAI(const Grid<L,W>& g,const Point& a);


  template <unsigned int L,unsigned int W>
    Point aStar(const Grid<L,W>& g,const Point& a);
};





#include "snake.hpp"
#include "snakeAI.hpp"

#endif
