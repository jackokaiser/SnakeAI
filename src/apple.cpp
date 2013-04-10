#include "apple.h"
#include <stdlib.h>

Apple::Apple(unsigned int xx,unsigned int yy):
  Point(xx,yy) {}

Apple Apple::createAppleRandom(unsigned int length,unsigned int width)
{
  return Apple(rand()%length,
	       rand()%width);
}
