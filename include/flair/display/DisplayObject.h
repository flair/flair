#ifndef flair_display_DisplayObject_h
#define flair_display_DisplayObject_h

#include <memory>
#include <string>

#include "flair/Object.h"
#include "flair/display/RenderSupport.h"

#include "flair/geom/Matrix.h"
#include "flair/geom/Point.h"
#include "flair/geom/Rectangle.h"

namespace flair {
   namespace display {
      
      class Stage;
      class DisplayObjectContainer;
      
      class DisplayObject : public Object
      {
         using Object::Object;
         friend class DisplayObjectContainer;
         
      public:
         DisplayObject();
         virtual ~DisplayObject() = 0;
         
         
      // Properties
      public:
         std::string name() const;
         std::string name(std::string name);
         
         float alpha() const;
         float alpha(float alpha);
         
         const flair::geom::Rectangle* bounds() const;
         bool hasVisibleArea() const;
         
         float height() const;
         float height(float height);
         
         float width() const;
         float width(float width);
         
         float x() const;
         float x(float x);
         
         float y() const;
         float y(float y);
         
         std::shared_ptr<Stage> stage() const;
         
         std::shared_ptr<DisplayObjectContainer> root() const;
         std::shared_ptr<DisplayObjectContainer> parent() const;
         
         flair::geom::Matrix transformationMatrix() const;
         flair::geom::Matrix transformationMatrix(flair::geom::Matrix m);
         
         float pivotX() const;
         float pivotX(float pivotX);
         
         float rotation() const;
         float rotation(float rotation);
         
         float scaleX() const;
         float scaleX(float scaleX);
         
         float scaleY() const;
         float scaleY(float scaleY);
         
         float skewX() const;
         float skewX(float skewX);
         
         float skewY() const;
         float skewY(float skewY);
         
         bool touchable() const;
         bool touchable(bool touchable);
         
         bool visible() const;
         bool visible(bool visible);
         
         
      // Methods
      public:
         flair::geom::Rectangle getBounds(std::shared_ptr<DisplayObject> targetSpace, flair::geom::Rectangle* result = 0) const;
         
         flair::geom::Matrix getTransformationMatrix(std::shared_ptr<DisplayObject> targetSpace, flair::geom::Matrix* result = 0) const;
         
         flair::geom::Point globalToLocal(flair::geom::Point localPoint, flair::geom::Point* result = 0) const;
         
         std::shared_ptr<DisplayObject> hitTest(flair::geom::Point localPoint, bool forTouch = false) const;
         
         
      // Internal Methods
      protected:
         void setParent(std::weak_ptr<DisplayObjectContainer> parent);
         void render(RenderSupport *support, float parentAlpha);
         
         
      protected:
         std::string _name;
         
         float _alpha;
         
         flair::geom::Rectangle _bounds;
         bool _hasVisibleArea;
         
         float _height;
         float _width;
         float _x;
         float _y;
         
         std::weak_ptr<Stage> _stage;
         std::weak_ptr<DisplayObjectContainer> _parent;
         
         flair::geom::Matrix _transformationMatrix;
         float _pivotX;
         float _pivotY;
         float _rotation;
         float _scaleX;
         float _scaleY;
         float _skewX;
         float _skewY;
         
         bool _touchable;
         bool _visible;
      };
      
   }
}

#endif
