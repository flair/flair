#ifndef flair_geom_Point_h
#define flair_geom_Point_h

namespace flair {
   namespace geom {
      
      class Point
      {
      public:
         Point(float x = 0.0f, float y = 0.0f);
         virtual ~Point() {};
         
      // Properties
      public:
         float x() const;
         float x(float x);
         
         float y() const;
         float y(float y);
         
         float length() const;
         
      // Methods
      public:
         void normalize(float scale = 1.0f);
         void offset(float dx, float dy);
         void setTo(float x, float y);
         
      // Static Methods
      public:
         static float distance(const Point & p1, const Point & p2);
         static Point interpolate(const Point & p1, const Point & p2, float t);
         static Point polar(float length, float angle);
         
      // Operators
      public:
         bool operator==(const Point & rhs) const;
         bool operator!=(const Point & rhs) const;
         Point & operator=(Point rhs);
         Point & operator+=(const Point & rhs);
         Point & operator-=(const Point & rhs);
         const Point operator*(float rhs) const;
         const Point operator/(float rhs) const;
         
      protected:
         float _x;
         float _y;
      };
   }
}

flair::geom::Point operator+(const flair::geom::Point & lhs, const flair::geom::Point & rhs);
flair::geom::Point operator-(const flair::geom::Point & lhs, const flair::geom::Point & rhs);
flair::geom::Point operator*(float lhs, const flair::geom::Point & rhs);
flair::geom::Point operator/(float lhs, const flair::geom::Point & rhs);

#endif
