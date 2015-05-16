#ifndef flair_geom_Rectangle_h
#define flair_geom_Rectangle_h

namespace flair {
   namespace geom {
      
      class Point;
      
      class Rectangle
      {
      public:
         Rectangle(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f);
         virtual ~Rectangle() {};
         
      // Properties
      public:
         float x() const;
         float x(float x);
         
         float y() const;
         float y(float y);
         
         float width() const;
         float width(float width);
         
         float height() const;
         float height(float height);
         
         float top() const;
         float top(float top);
         
         float bottom() const;
         float bottom(float bottom);
         
         float left() const;
         float left(float left);
         
         float right() const;
         float right(float right);
         
         Point topLeft() const;
         Point topLeft(Point topLeft);
         
         Point bottomRight() const;
         Point botomRight(Point bottomRight);
         
         Point size() const;
         Point size(Point size);
         
      // Methods
      public:
         bool contains(float x, float y) const;
         bool containsPoint(const Point & p) const;
         bool containsRect(const Rectangle & r) const;
         void inflate(float x, float y);
         void inflatePoint(const Point & p);
         Rectangle intersection(const Rectangle & toInstersect) const;
         bool intersects(const Rectangle & toIntersect) const;
         bool isEmpty() const;
         void offset(float x, float y);
         void offsetPoint(const Point & p);
         void setEmpty();
         void setTo(float x, float y, float width, float height);
         Rectangle merge(const Rectangle & toUnion) const; // union is a reserverd word
         
      // Operators
      public:
         Rectangle & operator=(Rectangle rhs);
         bool operator==(const Rectangle & lhs) const;
         bool operator!=(const Rectangle & lhs) const;
         
      protected:
         float _x;
         float _y;
         float _width;
         float _height;
         
      };
   }
}

#endif
