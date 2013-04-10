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
      std::cout<<"Grid::operator[] => point out of frame"<<std::cout;
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
	  gameboard[i][j]=0;
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
