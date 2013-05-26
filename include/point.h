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

  friend bool operator< (const Point& lhs,const Point& rhs);
  friend bool operator<= (const Point& lhs,const Point& rhs);

  friend bool operator== (const Point& lhs,const Point& rhs);
  friend std::ostream& operator<< (std::ostream& s,const Point& lhs);

  void operator() () const {};

} ;


namespace std {
  template <> struct hash<Point>
  {
    size_t operator()(const Point & x) const
    {
      return hash<int>()(x.x+x.y);
    }
  };
}


#endif
