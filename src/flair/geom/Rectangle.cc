#include <algorithm>

#include "flair/geom/Point.h"
#include "flair/geom/Rectangle.h"

namespace flair {
   namespace geom {
      
      Rectangle::Rectangle(float x, float y, float width, float height) : _x(x), _y(y), _width(width), _height(height) {}
      
      float Rectangle::x() const
      {
         return _x;
      }
      
      float Rectangle::x(float x)
      {
         return _x = x;
      }
      
      float Rectangle::y() const
      {
         return _y;
      }
      
      float Rectangle::y(float y)
      {
         return _y = y;
      }
      
      float Rectangle::width() const
      {
         return _width;
      }
      
      float Rectangle::width(float width)
      {
         return _width = width;
      }
      
      float Rectangle::height() const
      {
         return _height;
      }
      
      float Rectangle::height(float height)
      {
         return _height = height;
      }
      
      float Rectangle::top() const
      {
         return _y;
      }
      
      float Rectangle::top(float top)
      {
         return _y = top;
      }
      
      float Rectangle::bottom() const
      {
         return _y + _height;
      }
      
      float Rectangle::bottom(float bottom)
      {
         _height = bottom - _y;
         return _y + _height;
      }
      
      float Rectangle::left() const
      {
         return _x;
      }
      
      float Rectangle::left(float left)
      {
         return _x = left;
      }
      
      float Rectangle::right() const
      {
         return _x + _width;
      }
      
      float Rectangle::right(float right)
      {
         _width = right - _x;
         return _x + _width;
      }
      
      Point Rectangle::topLeft() const
      {
         return Point(_x, _y);
      }
      
      Point Rectangle::topLeft(Point topLeft)
      {
         _x = topLeft.x();
         _y = topLeft.y();
         return topLeft;
      }
      
      Point Rectangle::bottomRight() const
      {
         return Point(_x + _width, _y + _height);
      }
      
      Point Rectangle::botomRight(Point bottomRight)
      {
         _width = bottomRight.x() - _x;
         _height = bottomRight.y() - _y;
         return Point(_x + _width, _y + _height);
      }
      
      Point Rectangle::size() const
      {
         return Point(_width, _height);
      }
      
      Point Rectangle::size(Point size)
      {
         _width = size.x();
         _height = size.y();
         return Point(_width, _height);
      }
      
      bool Rectangle::contains(float x, float y) const
      {
         return x >= _x && y >= _y && x <= (_x + _width) && y <= (_y + _height);
      }
      
      bool Rectangle::containsPoint(const Point & p) const
      {
         return contains(p.x(), p.y());
      }
      
      bool Rectangle::containsRect(const Rectangle & r) const
      {
         float xA = r.x();
         float yA = r.y();
         float xB = r.left();
         float yB = r.bottom();
         
         return xA >= _x && yA >= _y && xA <= (_x + _width) && yA <= (_y + _height) &&
         xB >= _x && yB >= _y && xB <= (_x + _width) && yB <= (_y + _height);
      }
      
      void Rectangle::inflate(float x, float y)
      {
         _x -= x;
         _width += 2 * x;
         _y -= y;
         _height += 2 * y;
      }
      
      void Rectangle::inflatePoint(const Point & p)
      {
         inflate(p.x(), p.y());
      }
      
      Rectangle Rectangle::intersection(const Rectangle & toInstersect) const
      {
         float xmin = std::max(this->_x, toInstersect._x);
         float xmax1 = this->_x + this->_width;
         float xmax2 = toInstersect._x + toInstersect._width;
         float xmax = std::min(xmax1, xmax2);
         if (xmax > xmin) {
            float ymin = std::max(this->_y, toInstersect._y);
            float ymax1 = this->_y + toInstersect._height;
            float ymax2 = toInstersect._y + toInstersect._height;
            float ymax = std::min(ymax1, ymax2);
            if (ymax > ymin) {
               return Rectangle(xmin, ymin, xmax - xmin, ymax - ymin);
            }
         }
         
         return Rectangle();
      }
      
      bool Rectangle::intersects(const Rectangle & toIntersect) const
      {
         return (this->left() < toIntersect.right() && toIntersect.left() < this->right() && this->top() < toIntersect.bottom() && toIntersect.top() < this->bottom());
      }
      
      bool Rectangle::isEmpty() const
      {
         return (_x == 0.0f && _y == 0.0f && _width == 0.0f && _height == 0.0f);
      }
      
      void Rectangle::offset(float x, float y)
      {
         _x += x;
         _y += y;
      }
      
      void Rectangle::offsetPoint(const Point & p)
      {
         _x = p.x();
         _y = p.y();
      }
      
      void Rectangle::setEmpty()
      {
         _x = 0.0f;
         _y = 0.0f;
         _width = 0.0f;
         _height = 0.0f;
      }
      
      void Rectangle::setTo(float x, float y, float width, float height)
      {
         _x = x;
         _y = y;
         _width = width;
         _height = height;
      }
      
      Rectangle Rectangle::merge(const Rectangle & toUnion) const
      {
         Rectangle ret = *this;
         if (toUnion._width == 0 || toUnion._height == 0) return ret;
         
         ret._x = std::min(_x, toUnion._x);
         ret._y = std::min(_y, toUnion._y);
         ret._width = std::max(_x +_width, toUnion._x + toUnion._width) - ret._x;
         ret._height = std::max(_y +_height, toUnion._y + toUnion._height) - ret._y;
         
         return ret;
      }
      
      Rectangle & Rectangle::operator=(Rectangle rhs)
      {
         this->_x = rhs._x;
         this->_y = rhs._y;
         this->_width = rhs._width;
         this->_height = rhs._height;
         
         return *this;
      }
      
      bool Rectangle::operator==(const flair::geom::Rectangle & rhs) const
      {
         return ( this->_x == rhs._x && this->_y == rhs._y && this->_width == rhs._width && this->_height == rhs._height );
      }
      
      bool Rectangle::operator!=(const flair::geom::Rectangle & rhs) const
      {
         return !this->operator==(rhs);
      }
   }
}
