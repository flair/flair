#include "flair/display/DisplayObject.h"

using flair::geom::Rectangle;
using flair::geom::Matrix;
using flair::geom::Point;

namespace flair {
   namespace display {
      
      std::string DisplayObject::name() const
      {
         return _name;
      }
      
      std::string DisplayObject::name(std::string name)
      {
         return _name = name;
      }
      
      float DisplayObject::alpha() const
      {
         return _alpha;
      }
      
      float DisplayObject::alpha(float alpha)
      {
         return _alpha = alpha;
      }
      
      const Rectangle * DisplayObject::bounds() const
      {
         return &_bounds;
      }
      
      bool DisplayObject::hasVisibleArea() const
      {
         return _hasVisibleArea;
      }
      
      float DisplayObject::height() const
      {
         return _height;
      }
      
      float DisplayObject::height(float height)
      {
         return _height = height;
      }
      
      float DisplayObject::width() const
      {
         return _width;
      }
      
      float DisplayObject::width(float width)
      {
         return _width = width;
      }
      
      float DisplayObject::x() const
      {
         return _x;
      }
      
      float DisplayObject::x(float x)
      {
         return _x = x;
      }
      
      float DisplayObject::y() const
      {
         return _y;
      }
      
      float DisplayObject::y(float y)
      {
         return _y = y;
      }
      
      Stage * DisplayObject::stage() const
      {
         return _stage;
      }
      
      DisplayObjectContainer * DisplayObject::root() const
      {
         return _root;
      }
      
      DisplayObjectContainer * DisplayObject::base() const
      {
         return _base;
      }
      
      DisplayObjectContainer * DisplayObject::parent() const
      {
         return _parent;
      }
      
      Matrix DisplayObject::transformationMatrix() const
      {
         return _transformationMatrix;
      }
      
      Matrix DisplayObject::transformationMatrix(Matrix m)
      {
         return _transformationMatrix = m;
      }
      
      float DisplayObject::pivotX() const
      {
         return _pivotX;
      }
      
      float DisplayObject::pivotX(float pivotX)
      {
         return _pivotY;
      }
      
      float DisplayObject::rotation() const
      {
         return _rotation;
      }
      
      float DisplayObject::rotation(float rotation)
      {
         return _rotation = rotation;
      }
      
      float DisplayObject::scaleX() const
      {
         return _scaleX;
      }
      
      float DisplayObject::scaleX(float scaleX)
      {
         return _scaleX = scaleX;
      }
      
      float DisplayObject::scaleY() const
      {
         return _scaleY;
      }
      
      float DisplayObject::scaleY(float scaleY)
      {
         return _scaleY = scaleY;
      }
      
      float DisplayObject::skewX() const
      {
         return _skewX;
      }
      
      float DisplayObject::skewX(float skewX)
      {
         return _skewX = skewX;
      }
      
      float DisplayObject::skewY() const
      {
         return _skewY;
      }
      
      float DisplayObject::skewY(float skewY)
      {
         return _skewY = skewY;
      }
      
      bool DisplayObject::touchable() const
      {
         return _touchable;
      }
      
      bool DisplayObject::touchable(bool touchable)
      {
         return _touchable = touchable;
      }
      
      bool DisplayObject::visible() const
      {
         return _visible;
      }
      
      bool DisplayObject::visible(bool visible)
      {
         return _visible = visible;
      }
      
      
      void DisplayObject::dispose()
      {
         
      }
      
      Rectangle DisplayObject::getBounds(DisplayObject targetSpace, Rectangle *result) const
      {
         Rectangle r;
         return r;
      }
      
      Matrix DisplayObject::getTransformationMatrix(DisplayObject targetSpace, Matrix *result) const
      {
         Matrix m;
         return m;
      }
      
      Point DisplayObject::globalToLocal(Point localPoint, Point *result) const
      {
         Point p;
         return p;
      }
      
      DisplayObject * DisplayObject::hitTest(Point localPoint, bool forTouch) const
      {
         return 0;
      }
      
      void DisplayObject::removeFromParent(bool dispose)
      {
         
      }
      
      void DisplayObject::render(RenderSupport *support, float parentAlpha)
      {
         
      }
      
   }
}
