#ifndef APPLE_DOT_H
#define APPLE_DOT_H

#include "point.h"

class Apple : public Point
{

 public:
  /* add apple on the grid and returns it */
  static Apple createAppleRandom(unsigned int length,unsigned int width);
  Apple(unsigned int xx,unsigned int yy);
  inline Apple():Point() {}
};

#endif
