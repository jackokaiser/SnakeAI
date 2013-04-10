#include "snake.h"
#include "cell.h"

Snake::Snake():
  tail(std::queue<Point>()),
  head(Point(0,0)),
  length(3)
{
}



void Snake::eatsApple()
{
  length++;
}
