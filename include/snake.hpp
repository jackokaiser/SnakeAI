#include "cell.h"

template <unsigned int L,unsigned int W>
void Snake::update(Grid<L,W>& g,const Apple& a)
{

  if(length==tail.size())
    {
      // pop body and removes it from grid
      g[tail.front()]=Cell::NONE;
      tail.pop();
    }

  // add old head pos to the grid
  g[head]=Cell::SNAKE_BODY;
  tail.push(head);

  // compute the new head pos
  // head=dumbAI(g,a);
  head=lessDumbAI(g,a);
  // head=randomAI(g,a);
}
