// some snake logic function

#include <vector>
#include <algorithm>
#include <stdlib.h>

template <unsigned int L,unsigned int W>
Point Snake::dumbAI(const Grid<L,W>& g,const Apple& a)
{
  // compute vector to apple and normalize (4 possible vectors)
  Point vHtoA=(a-head).normalize();
  // new head pos is old one plus this vector
  head += vHtoA;
  return head;
}

template <unsigned int L,unsigned int W>
Point Snake::randomAI(const Grid<L,W>& g,const Apple& a)
{
  std::vector<Point> possibilities;
  possibilities.push_back(Point(1,0));
  possibilities.push_back(Point(0,1));
  possibilities.push_back(Point(-1,0));
  possibilities.push_back(Point(0,-1));

  unsigned int index=0;
  do
  {
    // select random 4-neighbors cell
    index=rand()%possibilities.size();
    // if not available, removes it from possibilities
    if(!g.isAvailable(possibilities[index]+head))
      possibilities.erase(possibilities.begin()+index);
    // else we've found our winner
    else
      break;

    if (possibilities.size()==1) 
      {
	std::cout<<"Damn, last chance is "<<possibilities[0]<<std::endl;
	// no more than 1 possibility
	index=0;
	break;
      }
  } while (true);

  return head+possibilities[index];
}

template <unsigned int L,unsigned int W>
Point Snake::lessDumbAI(const Grid<L,W>& g,const Apple& a)
{
  std::vector<Point> possibilities;
  possibilities.push_back(Point(1,0)+head-a);
  possibilities.push_back(Point(0,1)+head-a);
  possibilities.push_back(Point(-1,0)+head-a);
  possibilities.push_back(Point(0,-1)+head-a);

  Point ret;
  do {
    unsigned int minDist=possibilities[0].manathan();
    unsigned int index=0;
    ret=possibilities[0];
    for (unsigned int i=1;i<possibilities.size();i++)
      {
	if (possibilities[i].manathan()<minDist)
	  {
	    minDist=possibilities[i].manathan();
	    ret=possibilities[i];
	    index=i;
	  }
      }
    // find and erase that best solution from possibilities
    possibilities.erase(possibilities.begin()+index);
    // do it while there's more than 1 possibility and while the cell isn't available
  } while ((possibilities.size()!=1) && (!g.isAvailable(ret+a)));
  std::cout<<"selected "<<ret+a<<"possibilities "<<possibilities.size()<<std::endl;
    return ret+a;
}
