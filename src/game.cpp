#include "game.h"
#include "cell.h"
#include <iostream>

Game::Game():
  lostPosition(Point(0,0)),
  lostCode(RUNNING),
  score(0),
  round(0)
{
  this->generateAppleOnGrid();
  this->grid[snake.getHead()]=Cell::SNAKE_HEAD;
}

void Game::log() const
{
  std::cout<<"Round: "<<round<<std::endl;
  std::cout<<"Game status: ";
  switch(lostCode)
    {
    case(RUNNING):
      std::cout<<"running";
      break;
    case(BITE_ITSELF):
      std::cout<<"bite itself in position"<<lostPosition;
      break;
    case(HIT_A_WALL):
      std::cout<<"hit a wall in position"<<lostPosition;
      break;
    }
  std::cout<<std::endl;
  std::cout<<"score: "<<score<<std::endl;
  std::cout<<"head: "<<snake.getHead()<<" apple: "<<apple<<std::endl;
}
void Game::generateAppleOnGrid()
{
  do {
    apple=Apple::createAppleRandom(grid.length,grid.width);
  } while (!(grid[apple]==Cell::NONE));
  grid[apple]=Cell::APPLE;
}


bool Game::update()
{
  round++;

  ////////////////:// NO GAME OVER: LET'S THE GAME CONTINUE !
  ////////////// TEST IF EAT AN APPLE ////////////////
  if(snake.getHead() == apple)
    {
      // increases snake's size
      snake.eatsApple();
      score++;

      // make a new apple
      generateAppleOnGrid();
    }


  /////////////////// UPDATE /////////////
  snake.update(grid,apple);




  ////////////////////////////// TEST IF LOST
  lostPosition=snake.getHead();
  if (!grid.isInFrame(snake.getHead()))
    {
      lostCode=HIT_A_WALL;
      return true;
    }
  else if (grid[snake.getHead()] == Cell::SNAKE_BODY)
    {
      lostCode=BITE_ITSELF;
      return true;
    }

  ////////////// update the grid
  Point* toRemove=snake.getPointToRemove();
  const Point* previousHead=snake.getPreviousHead();
  if (toRemove)
    grid[*toRemove]=Cell::NONE;
  if (previousHead)
    grid[*previousHead]=Cell::SNAKE_BODY;
  grid[snake.getHead()]=Cell::SNAKE_HEAD;


  // return round>20;
  return false;
}

void Game::display() const
{
  std::cout<<grid<<std::endl;
}


void Game::clear()
{
}

int main (int argc, char** argv)
{
  srand(3);
  Game theGame;
  bool gameOver=false;
  do {
    theGame.display();
    gameOver = theGame.update();
    theGame.log();
  } while (!gameOver);
  theGame.display();


  theGame.clear();
  return 0;
}
