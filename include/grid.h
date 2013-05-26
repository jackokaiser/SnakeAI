#ifndef GRID_H
#define GRID_H

#include "point.h"
#include <iostream>
#include <vector>

template <unsigned int L,unsigned int W>
class Grid 
{
 public:
  /* THE ENUM HACK: no additional date stored in the object */
  enum {length = L, width = W};
  
  Grid();

  /* the gameboard */
  unsigned int gameboard [L][W];

  /* fill grid with none */
  void clearGameboard();
  /* is point in frame */
  bool isInFrame(const Point& p) const;

  /* is point valid */
  bool isAvailable(const Point& p) const;

  std::vector<Point> neighbors (const Point& p) const;
  std::vector<Point> allNeighbors (const Point& p) const;

  unsigned int& operator[](const Point& p);
  unsigned int operator[](const Point& p) const;

  template <unsigned int LL,unsigned int WW>
    friend std::ostream& operator<<(std::ostream& s,const Grid<LL,WW>& g);
};

#include "grid.hpp"


#endif
