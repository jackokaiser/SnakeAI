#include "cell.h"

template <unsigned int LL,unsigned int WW>
std::ostream& operator<<(std::ostream& s,const Grid<LL,WW>& g) 
{
  for (unsigned int i=0;i<g.length;i++)
    {
      for (unsigned int j=0;j<g.width;j++)
	{
	  s<<g.gameboard[i][j]<<" ";
	}
      s<<std::endl;
    }
  return s;
}

/* ctor */
template <unsigned int L,unsigned int W>
Grid<L,W>::Grid()
{
  clearGameboard();
}


template <unsigned int L,unsigned int W>
unsigned int& Grid<L,W>::operator[](const Point& p)
{
  if(isInFrame(p))
    return gameboard[p.x][p.y];
  else
    {
      std::cout<<"Grid::operator[] => point out of frame"<<std::endl;
      return gameboard[0][0];
    }
}

template <unsigned int L,unsigned int W>
unsigned int Grid<L,W>::operator[](const Point& p) const
{
  if(isInFrame(p))
    return gameboard[p.x][p.y];
  else
    {
      std::cout<<"Grid::operator[] => point out of frame"<<std::cout;
      return gameboard[0][0];
    }
}

template <unsigned int L,unsigned int W>
void Grid<L,W>::clearGameboard()
{
  for (unsigned int i=0;i<L;i++)
    {
      for (unsigned int j=0;j<W;j++)
	{
	  gameboard[i][j]=Cell::NONE;
	}
    }
}



template <unsigned int L,unsigned int W>
bool Grid<L,W>::isInFrame(const Point& p) const
{
  return ( (0 <= p.x ) && ((unsigned int)p.x < L) && (0 <= p.y ) && ((unsigned int)p.y < W) );
}

template <unsigned int L,unsigned int W>
bool Grid<L,W>::isAvailable(const Point& p) const
{
  return isInFrame(p) && (*this)[p]<=Cell::APPLE;
}

template <unsigned int L,unsigned int W>
std::vector<Point> Grid<L,W>::neighbors (const Point& p) const
{
  std::vector<Point> ret;
  Point n[] = {Point(0,1),Point(0,-1),Point(1,0),Point(-1,0)};
  for (unsigned int i=0;i<4;i++)
    {
      if (isAvailable(p-n[i]))
	ret.push_back(p-n[i]);
    }
  return ret;
}

template <unsigned int L,unsigned int W>
std::vector<Point> Grid<L,W>::allNeighbors (const Point& p) const
{
  std::vector<Point> ret;
  Point n[] = {Point(0,1),Point(0,-1),Point(1,0),Point(-1,0)};
  for (unsigned int i=0;i<4;i++)
    {
      if (isInFrame(p-n[i]))
	ret.push_back(p-n[i]);
    }
  return ret;
}
