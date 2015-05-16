#ifndef flair_geom_Matrix_h
#define flair_geom_Matrix_h

namespace flair {
   namespace geom {
      
      class Point;
      
      class Matrix
      {
      public:
         Matrix(float a = 1.0f, float b = 0.0f, float c = 0.0f, float d = 1.0f, float tx = 0.0f, float ty = 0.0f);
         virtual ~Matrix() {};
         
      // Properties
      public:
         float a() const;
         float a(float a);
         
         float b() const;
         float b(float b);
         
         float c() const;
         float c(float c);
         
         float d() const;
         float d(float d);
         
         float tx() const;
         float tx(float tx);
         
         float ty() const;
         float ty(float ty);
         
      // Methods
      public:
         Point deltaTransformPoint(const Point & p) const;
         Point transformPoint(const Point & p) const;
         
         void identity();
         void invert();
         
         void rotate(float angle);
         void scale(float x, float y);
         void translate(float x, float y);
         
         void setTo(float a, float b, float c, float d, float tx, float ty);
         
      // Operators
      public:
         Matrix & operator=(Matrix rhs);
         const Matrix operator*(const Matrix & rhs) const;
         
      private:
         float _a;
         float _b;
         float _u;
         float _c;
         float _d;
         float _v;
         float _tx;
         float _ty;
         float _w;
      };
      
   }
}

#endif
