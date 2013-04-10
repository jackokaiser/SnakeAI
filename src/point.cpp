#include "point.h"

Point::Point ( int xx, int yy):
  x(xx),y(yy) {}

Point::Point(const Point& rhs):
  x(rhs.x),y(rhs.y) {}

void Point::positive()
{
  if (this->x<0)
    this->x=-x;
  if (this->y<0)
    this->y=-y;
}

Point& Point::normalize()
{
  Point tmp(*this);
  tmp.positive();
  if (tmp.x>tmp.y)
    {
      this->x /= tmp.x;
      this->y = 0;
    }
  else 
    {
      this->x = 0;
      this->y /= tmp.y;
    }
  return *this;
}

unsigned int Point::manathan() const
{
  Point tmp(*this);
  tmp.positive();
  return tmp.x+tmp.y;
}

Point& Point::operator+= (const Point& rhs)
{
  this->x+=rhs.x;
  this->y+=rhs.y;
  return *this;
}

Point operator+ (const Point& lhs,const Point& rhs)
{
  Point p(lhs);
  return p+=rhs;
}

Point& Point::operator-= (const Point& rhs)
{
  this->x-=rhs.x;
  this->y-=rhs.y;
  return *this;

}

Point operator- (const Point& lhs,const Point& rhs)
{
  Point p(lhs);
  return p-=rhs;
}

std::ostream& operator<< (std::ostream& s,const Point& lhs)
{
  return (s<<"( "<<lhs.x<<" , "<<lhs.y<<" )");
}

bool Point::operator== (const Point& rhs)
{
  return ((rhs.x==this->x)&&(rhs.y==this->y));
}
