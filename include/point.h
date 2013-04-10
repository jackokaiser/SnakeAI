#ifndef MPOINT_DOT_H
#define MPOINT_DOT_H

#include <iostream>

class Point {

 public:
  Point( int xx, int yy);
  Point(const Point& rhs);
  inline Point(): x(0),y(0) {}
  int x;
  int y;

  void positive();
  Point& normalize();
  unsigned int manathan() const;

  Point& operator+= (const Point& rhs);
  friend Point operator+ (const Point& lhs,const Point& rhs);

  Point& operator-= (const Point& rhs);
  friend Point operator- (const Point& lhs,const Point& rhs);

  bool operator== (const Point& rhs);
  friend std::ostream& operator<< (std::ostream& s,const Point& lhs);

} ;



#endif
