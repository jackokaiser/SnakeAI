#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "apple.h"
#include "grid.h"
#include "snake.h"

#define LENGTH 10
#define WIDTH 10

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

#endif
