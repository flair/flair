#ifndef flair_display_DisplayObject_h
#define flair_display_DisplayObject_h

#include <memory>
#include <string>

#include "flair/Object.h"
#include "flair/events/EventDispatcher.h"
#include "flair/display/RenderSupport.h"

#include "flair/geom/Matrix.h"
#include "flair/geom/Point.h"
#include "flair/geom/Rectangle.h"

namespace flair {
   namespace display {
      
      class Stage;
      class DisplayObjectContainer;
      
      class DisplayObject : public events::EventDispatcher
      {
         friend class DisplayObjectContainer;
         
      protected:
         DisplayObject();
         
      public:
         virtual ~DisplayObject() = 0;
         
         
      // Properties
      public:
         virtual std::string name() const;
         virtual std::string name(std::string name);
         
         virtual float alpha() const;
         virtual float alpha(float alpha);
         
         virtual const flair::geom::Rectangle bounds() const;
         virtual bool hasVisibleArea() const;
         
         virtual float height() const;
         virtual float height(float height);
         
         virtual float width() const;
         virtual float width(float width);
         
         virtual float x() const;
         virtual float x(float x);
         
         virtual float y() const;
         virtual float y(float y);
         
         virtual std::shared_ptr<Stage> stage() const;
         
         virtual const std::shared_ptr<DisplayObjectContainer> root() const;
         virtual const std::shared_ptr<DisplayObjectContainer> parent() const;
         
         virtual flair::geom::Matrix transformationMatrix() const;
         virtual flair::geom::Matrix transformationMatrix(flair::geom::Matrix m);
         
         virtual float pivotX() const;
         virtual float pivotX(float pivotX);
         
         virtual float rotation() const;
         virtual float rotation(float rotation);
         
         virtual float scaleX() const;
         virtual float scaleX(float scaleX);
         
         virtual float scaleY() const;
         virtual float scaleY(float scaleY);
         
         virtual float skewX() const;
         virtual float skewX(float skewX);
         
         virtual float skewY() const;
         virtual float skewY(float skewY);
         
         virtual bool touchable() const;
         virtual bool touchable(bool touchable);
         
         virtual bool visible() const;
         virtual bool visible(bool visible);
         
         
      // Methods
      public:
         virtual flair::geom::Rectangle getBounds(std::shared_ptr<DisplayObject> targetSpace) const;
         
         virtual flair::geom::Matrix getTransformationMatrix(std::shared_ptr<DisplayObject> targetSpace) const;
         
         virtual flair::geom::Point globalToLocal(flair::geom::Point localPoint) const;
         
         virtual std::shared_ptr<DisplayObject> hitTest(flair::geom::Point localPoint, bool forTouch = false) const;
         
         
      // Internal Methods
      protected:
         void setParent(std::shared_ptr<DisplayObjectContainer> parent);
         virtual void render(RenderSupport *support, float parentAlpha, geom::Matrix parentTransform);
         
         
      protected:
         std::string _name;
         
         float _alpha;
         
         flair::geom::Rectangle _bounds;
         bool _hasVisibleArea;
         
         float _height;
         float _width;
         float _x;
         float _y;
         
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
