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
  bool gameOver=false;

  if(grid[snake.getHead()] == Cell::APPLE)
    {
      // remove apple from grid
      grid[apple]=Cell::NONE;
      // increases snake's size
      snake.eatsApple();
      score++;

      // make a new apple
      generateAppleOnGrid();
    }
  snake.update(grid,apple);


  // HIT A WALL TEST
  gameOver=(!grid.isInFrame(snake.getHead()));
  lostCode=((!lostCode)&&(gameOver)?2:lostCode);
  // BITE ITSELF TEST
  // if the snake collides it's lost
  // we must not test if the game is already lost (out of frame)
  gameOver=(gameOver?true:(grid[snake.getHead()] > Cell::APPLE));
  lostCode=gameOver;
  lostPosition=snake.getHead();
  return gameOver;
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
    gameOver = theGame.update();
    theGame.display();
    theGame.log();
  } while (!gameOver);

  theGame.clear();
  return 0;
}
