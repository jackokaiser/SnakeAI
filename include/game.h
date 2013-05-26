#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "apple.h"
#include "grid.h"
#include "snake.h"

#define LENGTH 5
#define WIDTH 5

class Game
{
 public:
  enum {
    RUNNING=0,
    BITE_ITSELF,
    HIT_A_WALL,
    WIN
  };
 private:
  Snake snake;
  Apple apple;
  Grid<LENGTH,WIDTH> grid;

  void generateAppleOnGrid();

  Point lostPosition;
  short int lostCode;
  unsigned int score;
  unsigned int round;
 public:

  Game();
  bool update();
  void display() const;
  void clear();
  void log() const;
};

int main (int argc, char** argv);

/* high level specialization */
namespace std {
  template <> 
    bool operator== (const pair<unsigned int,Point>& lhs, const pair<unsigned int,Point>& rhs)
    {
      // equal if points are the same
      return ((std::get<1>(lhs))==(std::get<1>(rhs)));
    }

  template <>
    bool operator< (const pair<unsigned int,Point>& lhs, const pair<unsigned int,Point>& rhs)
    {
      // inferior if distance is inferion
      return ((std::get<0>(lhs))<(std::get<0>(rhs)));
    }
}

#endif
