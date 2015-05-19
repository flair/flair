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
      public:
         DisplayObjectContainer();
         virtual ~DisplayObjectContainer();
         
      // Properties
      public:
         int numChildren() const;
         
      // Methods
      public:
         bool contains(std::shared_ptr<DisplayObject> child);
         
         std::shared_ptr<DisplayObject> addChild(std::shared_ptr<DisplayObject> child);
         std::shared_ptr<DisplayObject> addChildAt(std::shared_ptr<DisplayObject> child, int index);
         
         std::shared_ptr<DisplayObject> getChildAt(int index) const;
         std::shared_ptr<DisplayObject> getChildByName(std::string name) const;
         
         int getChildIndex(const std::shared_ptr<DisplayObject>& child) const;
         void setChildIndex(const std::shared_ptr<DisplayObject>& child, int index);
         
         std::shared_ptr<DisplayObject> removeChild(std::shared_ptr<DisplayObject> child);
         std::shared_ptr<DisplayObject> removeChildAt(int index);
         void removeChildren(int beginIndex = 0, int endIndex = std::numeric_limits<int>::max());
         
      protected:
         std::shared_ptr<DisplayObjectContainer> base();
         
      protected:
         std::vector<std::shared_ptr<DisplayObject>> _children;
      };
      
   }
}


#endif
