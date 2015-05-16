#include <cmath>

#include "flair/geom/Matrix.h"
#include "flair/geom/Point.h"

namespace flair {
   namespace geom {
      
      Matrix::Matrix(float a, float b, float c, float d, float tx, float ty)
         : _a(a), _b(b), _c(c), _d(d), _tx(tx), _ty(ty), _u(0.0f), _v(0.0f), _w(1.0f) {};
      
      float Matrix::a() const
      {
         return _a;
      }
      
      float Matrix::a(float a)
      {
         return _a = a;
      }
      
      float Matrix::b() const
      {
         return _b;
      }
      
      float Matrix::b(float b)
      {
         return _b = b;
      }
      
      float Matrix::c() const
      {
         return _c;
      }
      
      float Matrix::c(float c)
      {
         return _c = c;
      }
      
      float Matrix::d() const
      {
         return _d;
      }
      
      float Matrix::d(float d)
      {
         return _d = d;
      }
      
      float Matrix::tx() const
      {
         return _tx;
      }
      
      float Matrix::tx(float tx)
      {
         return _tx = tx;
      }
      
      float Matrix::ty() const
      {
         return _ty;
      }
      
      float Matrix::ty(float ty)
      {
         return _ty = ty;
      }
      
      Point Matrix::deltaTransformPoint(const Point & p) const
      {
         float x = _a * p.x() + _c * p.y();
         float y = _b * p.x() + _d * p.y();
         
         return Point(x, y);
      }
      
      Point Matrix::transformPoint(const Point & p) const
      {
         float x = (_a * p.x() + _c * p.y()) + _tx;
         float y = (_b * p.x() + _d * p.y()) + _ty;
         
         return Point(x, y);
      }
      
      void Matrix::identity()
      {
         _a = 1.0f;
         _b = 0.0f;
         _u = 0.0f;
         
         _c = 0.0f;
         _d = 1.0f;
         _v = 0.0f;
         
         _tx = 0.0f;
         _ty = 0.0f;
         _w = 1.0f;
      }
      
      void Matrix::invert()
      {
         float det = _a * _d - _c * _b;
         float a = _a, b = _b, c = _c, d = _d, tx = _tx, ty = _ty;
         
         _a = d / det;
         _b = -b / det;
         _c = -c / det;
         _d = a / det;
         _tx = -(_a * tx + _c * ty);
         _ty = -(_b * tx + _d * ty);
      }
      
      void Matrix::rotate(float angle)
      {
         Matrix rotation(cosf(angle), sinf(angle), -sinf(angle), cosf(angle));
         *this = *this * rotation;
         
         // Apply the operation to the translation vector
         float x = _a * _tx + _c * _ty;
         float y = _b * _tx + _d * _ty;
         _tx = x;
         _ty = y;
      }
      
      void Matrix::scale(float x, float y)
      {
         Matrix scale(x, 0.0f, 0.0f, y);
         *this = *this * scale;
         
         // Apply the operation to the translation vector
         float tx = _a * _tx + _c * _ty;
         float ty = _b * _tx + _d * _ty;
         _tx = tx;
         _ty = ty;
      }
      
      void Matrix::translate(float x, float y)
      {
         _tx += x;
         _ty += y;
      }
      
      void Matrix::setTo(float a, float b, float c, float d, float tx, float ty)
      {
         _a = a;
         _b = b;
         _u = 0.0f;
         
         _c = c;
         _d = d;
         _v = 0.0f;
         
         _tx = tx;
         _ty = ty;
         _w = 1.0f;
      }
      
      Matrix & Matrix::operator=(Matrix rhs)
      {
         _a = rhs._a;
         _b = rhs._b;
         _u = rhs._u;
         
         _c = rhs._c;
         _d = rhs._d;
         _v = rhs._v;
         
         _tx = rhs._tx;
         _ty = rhs._ty;
         _w = rhs._w;
         
         return *this;
      }
      
      const Matrix Matrix::operator*(const Matrix & rhs) const
      {
         Matrix ret = *this;
         
         ret._a  = this->_a * rhs._a  + this->_c * rhs._b  + this->_tx * rhs._u;
         ret._c  = this->_a * rhs._c  + this->_c * rhs._d  + this->_tx * rhs._v;
         ret._tx = this->_a * rhs._tx + this->_c * rhs._ty + this->_tx * rhs._w;
         
         ret._b  = this->_b * rhs._a  + this->_d * rhs._b  + this->_ty * rhs._u;
         ret._d  = this->_b * rhs._c  + this->_d * rhs._d  + this->_ty * rhs._v;
         ret._ty = this->_b * rhs._tx + this->_d * rhs._ty + this->_ty * rhs._w;
         
         ret._u  = this->_u * rhs._a  + this->_v * rhs._b  + this->_w * rhs._u;
         ret._v  = this->_u * rhs._c  + this->_v * rhs._d  + this->_w * rhs._v;
         ret._w  = this->_u * rhs._tx + this->_v * rhs._ty + this->_w * rhs._w;
         
         return ret;
      }
   }
}
