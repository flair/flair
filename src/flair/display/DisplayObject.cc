#include "flair/display/DisplayObject.h"
#include "flair/display/DisplayObjectContainer.h"
#include "flair/display/Stage.h"

using flair::geom::Rectangle;
using flair::geom::Matrix;
using flair::geom::Point;

namespace flair {
   namespace display {
      
      DisplayObject::DisplayObject()
      {
         _stage = std::weak_ptr<Stage>();
         _parent = std::weak_ptr<DisplayObjectContainer>();
      }
      
      DisplayObject::~DisplayObject()
      {
         
      }
      
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
      
      const Rectangle* DisplayObject::bounds() const
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
      
      std::shared_ptr<Stage> DisplayObject::stage() const
      {
         if (_stage.expired()) {
            std::shared_ptr<Stage>();
         }

         return std::shared_ptr<Stage>(_stage);
      }
      
      std::shared_ptr<DisplayObjectContainer> DisplayObject::root() const
      {
         const DisplayObject* currentObject = this;
         while (currentObject->parent())
         {
            auto root = dynamic_cast<const Stage*>(currentObject->parent().get());
            if (root != nullptr) {
               return currentObject->parent();
            }
            else {
               currentObject = currentObject->parent().get();
            }
         }
         
         return std::shared_ptr<DisplayObjectContainer>();
      }
      
      std::shared_ptr<DisplayObjectContainer> DisplayObject::parent() const
      {
         if (_parent.expired()) {
            return std::shared_ptr<DisplayObjectContainer>();
         }

         return std::shared_ptr<DisplayObjectContainer>(_parent);
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
      
      Rectangle DisplayObject::getBounds(std::shared_ptr<DisplayObject> targetSpace, Rectangle* result) const
      {
         Rectangle r;
         return r;
      }
      
      Matrix DisplayObject::getTransformationMatrix(std::shared_ptr<DisplayObject> targetSpace, Matrix* result) const
      {
         Matrix m;
         return m;
      }
      
      Point DisplayObject::globalToLocal(Point localPoint, Point* result) const
      {
         Point p;
         return p;
      }
      
      std::shared_ptr<DisplayObject> DisplayObject::hitTest(Point localPoint, bool forTouch) const
      {
         return std::shared_ptr<DisplayObject>();
      }
      
      void DisplayObject::setParent(std::weak_ptr<DisplayObjectContainer> parent)
      {
         auto ancestor = dynamic_cast<const DisplayObject*>(parent.lock().get());
         while (ancestor != this && ancestor != nullptr) {
            ancestor = dynamic_cast<const DisplayObject*>(ancestor->parent().get());
         }
         
         if (ancestor == this) {
            throw std::invalid_argument("An object cannot be added as a child to itself or one of its children (or children's children, etc.)");
         }
         else {
            _parent = parent;
         }
      }
      
      void DisplayObject::render(RenderSupport* support, float parentAlpha)
      {
         
      }
      
   }
}
