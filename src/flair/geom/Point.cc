#include <cmath>

#include "flair/geom/Point.h"

namespace flair {
   namespace geom {
      
      Point::Point(float x, float y) : _x(x), _y(y) {}
      
      float Point::x() const
      {
         return _x;
      }
      
      float Point::x(float x)
      {
         return _x = x;
      }
      
      float Point::y() const
      {
         return _y;
      }
      
      float Point::y(float y)
      {
         return _y = y;
      }
      
      float Point::length() const
      {
         return sqrtf((_x * _x) + (_y * _y));
      }
      
      void Point::normalize(float scale)
      {
         float length = this->length();
         _x = (_x / length) * scale;
         _y = (_y / length) * scale;
         
      }
      
      void Point::offset(float dx, float dy)
      {
         _x += dx;
         _y += dy;
      }
      
      void Point::setTo(float x, float y)
      {
         _x = x;
         _y = y;
      }
      
      bool Point::operator==(const flair::geom::Point & rhs) const
      {
         return (this->_x == rhs._x && this->_y == rhs._y);
      }
      
      bool Point::operator!=(const flair::geom::Point & rhs) const
      {
         return !this->operator==(rhs);
      }
      
      Point & Point::operator=(Point rhs)
      {
         _x = rhs._x;
         _y = rhs._y;
         
         return *this;
      }
      
      Point & Point::operator+=(const Point & rhs)
      {
         _x += rhs._x;
         _y += rhs._y;
         
         return *this;
      }
      
      Point & Point::operator-=(const Point & rhs)
      {
         _x -= rhs._x;
         _y -= rhs._y;
         
         return *this;
      }
      
      const Point Point::operator*(float rhs) const
      {
         Point p = *this;
         p._x *= rhs;
         p._y *= rhs;
         
         return p;
      }
      
      const Point Point::operator/(float rhs) const
      {
         Point p = *this;
         p._x /= rhs;
         p._y /= rhs;
         
         return p;
      }
      
      float Point::distance(const Point & p1, const Point & p2)
      {
         return sqrtf( ((p2._x - p1._x)*(p2._x - p1._x)) + ((p2._y - p1._y)*(p2._y - p1._y)) );
      }
      
      Point Point::interpolate(const Point & p1, const Point & p2, float t)
      {
         t = t > 1.0f ? 1.0f : (t < 0.0f ? 0.0f : t);
         
         return (p1 * t) + (p2 * (1.0f - t));
      }
      
      Point Point::polar(float length, float angle)
      {
         return Point(length * cos(angle), length * sin(angle));
      }
   }
}

flair::geom::Point operator+(const flair::geom::Point & lhs, const flair::geom::Point & rhs)
{
   return flair::geom::Point(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

flair::geom::Point operator-(const flair::geom::Point & lhs, const flair::geom::Point & rhs)
{
   return flair::geom::Point(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

flair::geom::Point operator*(float lhs, const flair::geom::Point & rhs)
{
   return rhs * lhs;
}

flair::geom::Point operator/(float lhs, const flair::geom::Point & rhs)
{
   return rhs / lhs;
}

