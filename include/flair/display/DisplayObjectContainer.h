#ifndef flair_display_DisplayObjectContainer_h
#define flair_display_DisplayObjectContainer_h

#include <memory>
#include <string>
#include <vector>
#include <limits>

#include "flair/display/DisplayObject.h"

namespace flair {
   namespace display {
      
      class DisplayObjectContainer : public DisplayObject
      {
      protected:
         DisplayObjectContainer();
         
      public:
         virtual ~DisplayObjectContainer() = 0;
         
      // Properties
      public:
         int numChildren() const;
         
      // Methods
      public:
         virtual bool contains(std::shared_ptr<DisplayObject> child);
         
         virtual std::shared_ptr<DisplayObject> addChild(std::shared_ptr<DisplayObject> child);
         virtual std::shared_ptr<DisplayObject> addChildAt(std::shared_ptr<DisplayObject> child, int index);
         
         virtual std::shared_ptr<DisplayObject> getChildAt(int index) const;
         virtual std::shared_ptr<DisplayObject> getChildByName(std::string name) const;
         
         virtual int getChildIndex(const std::shared_ptr<DisplayObject>& child) const;
         virtual void setChildIndex(const std::shared_ptr<DisplayObject>& child, int index);
         
         virtual std::shared_ptr<DisplayObject> removeChild(std::shared_ptr<DisplayObject> child);
         virtual std::shared_ptr<DisplayObject> removeChildAt(int index);
         virtual void removeChildren(int beginIndex = 0, int endIndex = std::numeric_limits<int>::max());
         
      // Internal
      public:
         virtual void tick(float deltaSeconds);
         void render(RenderSupport * support, float parentAlpha, geom::Matrix parentTransform) override;
         
      protected:
         std::vector<std::shared_ptr<DisplayObject>> _children;
      };
      
   }
}


#endif
