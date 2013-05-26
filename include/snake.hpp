#include "cell.h"

template <unsigned int L,unsigned int W>
void Snake::update(const Grid<L,W>& g,const Point& a)
{
  if (pointToRemove)
    delete pointToRemove;
  pointToRemove=NULL;
  if(length==tail.size())
    {
      // pop body
      pointToRemove=new Point();
      *pointToRemove=tail.back();
      tail.pop_back();
    }

  tail.push_front(head);

  // compute the new head pos
  // head=dumbAI(g,a);
  // head=lessDumbAI(g,a);
  // head=randomAI(g,a);
  head=aStar(g,a);
}
