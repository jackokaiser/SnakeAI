// some snake logic function
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <deque>
#include <stdlib.h>
#include <utility>


template <unsigned int L,unsigned int W>
Point Snake::dumbAI(const Grid<L,W>& g,const Point& a)
{
  // compute vector to apple and normalize (4 possible vectors)
  Point vHtoA=(a-head).normalize();
  // new head pos is old one plus this vector
  head += vHtoA;
  return head;
}

template <unsigned int L,unsigned int W>
Point Snake::randomAI(const Grid<L,W>& g,const Point& a)
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
	  std::cout<<"Damn, last chance is "<<possibilities[0]+head<<std::endl;
	  // no more than 1 possibility
	  index=0;
	  break;
	}
    } while (true);

  return head+possibilities[index];
}

template <unsigned int L,unsigned int W>
Point Snake::lessDumbAI(const Grid<L,W>& g,const Point& a)
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


typedef std::pair<unsigned int, Point> heuristic;

template <unsigned int L,unsigned int W>
Point Snake::aStar(const Grid<L,W>& g,const Point& a)
{
  static std::vector<Point> path;
  static int position=-1;
  if (position==-1)
    {
      // std::cout<<"constructing new path.."<<std::endl;

      // new destination: we have to recompute the path
      path.clear();
      Point currentVertex;
      std::set<Point> closedSet;
      std::set<heuristic> openSet;
      openSet.insert(std::make_pair((a-head).manathan(),head));

      std::unordered_map<Point,unsigned int> g_score;
      std::unordered_map<Point,Point> came_from;

      // it takes max step to go to any point (init)
      for (unsigned int i=0;i<L;i++)
	for (unsigned int j=0;j<W;j++)
	  g_score[Point(i,j)]=L*W+1;
      // it takes 0 steps to go to start
      g_score[head]=0;
      // heuristic to the end

      while (!openSet.empty())
	{
	  ////////////
	  // looking for current
	  ////////////

	  currentVertex=std::get<1>(*(openSet.begin()));
	  ////////////
	  // the current node is found	
	  ////////////
	  if (currentVertex==a)
	    // over
	    {
	      // while current is in came from
	      // (while we aren't on the starting vertex)
	      while(came_from.find(currentVertex)!=came_from.end())
		{
		  path.push_back(currentVertex);
		  currentVertex=came_from[currentVertex];
		}
	      // our vector is in reverse order
	      position=path.size()-1;
	      // for (unsigned int i=0;i<path.size();i++)
	      // 	std::cout<<path[i] << " "<<std::endl;

	      // std::cout<<"miss, next "<<path[position]<<std::endl;
	      return path[position--];
	    }

	  ////////////
	  // update maps
	  ////////////
	  // remove the current node from openSet
	  openSet.erase(openSet.begin());
	  // add it to the closed set
	  closedSet.insert(currentVertex);

	  ////////////
	  // update g_score of neighbors
	  ////////////
	  // returns neighbors with respect to topology
	  std::vector<Point> adj=g.allNeighbors(currentVertex);
	  for (unsigned int i=0;i<adj.size();i++)
	    {
	      Point neighbor=adj[i];
	      std::deque<Point>::iterator found=std::find(tail.begin(),tail.end(),neighbor);
	      // if that's neighbor is in the queue, and if it won't get away until we arrive there
	      if (static_cast<unsigned int>((tail.end()-found))>(g_score[currentVertex])) {

		// std::cout<<"ignoring "<<neighbor<<"back index is "<<(tail.end()==found)<<" "<<g[neighbor]<<std::endl;
		continue;
	      }
	      if  (
		  // if the neighbors isn't in the closed set
		   (std::find(closedSet.begin(),closedSet.end(),neighbor)==closedSet.end())
		  &&
		  // and if the distance we're calculating is better than its one
		  (g_score[currentVertex]+1<g_score[neighbor])
		  )
		{
		  // coming from current
		  came_from[neighbor]=currentVertex;
		  // update distance
		  g_score[neighbor]=g_score[currentVertex]+1;
		  unsigned int f_score=g_score[neighbor]+(a-neighbor).manathan();
		  heuristic newpair=std::make_pair(f_score,neighbor);
		  if(std::find(openSet.begin(),openSet.end(),newpair)==openSet.end())
		    // add it in openset if not already inside
		    openSet.insert(newpair);
		}
	    }
	}
      // failed to find a path
      // no paths to goal: escape sequence
      std::cout<<"failed to construct path: escape random sequence"<<std::endl;
      return randomAI(g,a);
    }
  else
    {
      // position will be -1 by itself
      // std::cout<<"hit, next "<<path[position]<<std::endl;
      return path[position--];
    }
}
