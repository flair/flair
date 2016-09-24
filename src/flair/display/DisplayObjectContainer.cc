#include "flair/display/DisplayObjectContainer.h"

#include <stdexcept>
#include <algorithm>

namespace flair {
   namespace display {
      
      DisplayObjectContainer::DisplayObjectContainer()
      {
         
      }
      
      DisplayObjectContainer::~DisplayObjectContainer()
      {
         
      }
      
      float DisplayObjectContainer::width() const
      {
         // TODO: Calculate bounds of children objects
         float width = _width;
         for (auto const& child : _children) { width = std::max(child->width(), _width); }
         return width * _scaleX;
      }
      
      float DisplayObjectContainer::height() const
      {
         // TODO: Calculate bounds of children objects
         float height = _height;
         for (auto const& child : _children) { height = std::max(child->height(), _height); }
         return height * _scaleY;
      }
      
      int DisplayObjectContainer::numChildren() const
      {
         return _children.size();
      }
      
      bool DisplayObjectContainer::contains(std::shared_ptr<DisplayObject> child)
      {
         auto it = std::find(_children.begin(), _children.end(), child);
         return it != _children.end();
      }
      
      std::shared_ptr<DisplayObject> DisplayObjectContainer::addChild(std::shared_ptr<DisplayObject> child)
      {
         return addChildAt(child, _children.size());
      }
      
      std::shared_ptr<DisplayObject> DisplayObjectContainer::addChildAt(std::shared_ptr<DisplayObject> child, int index)
      {
         if (index < 0 || index > _children.size()) throw std::out_of_range("Invalid child index");
         
         if (child->parent().get() == this)
         {
            setChildIndex(child, index);
         }
         else
         {
            std::shared_ptr<DisplayObjectContainer> parent = child->parent();
            if (parent) {
               parent->removeChild(child);
            }
            
            if (index == numChildren()) {
               _children.push_back(child);
            }
            else {
               _children.insert(_children.begin() + index, child);
            }

            child->setParent(std::dynamic_pointer_cast<DisplayObjectContainer>(shared_from_this()));
            //child.dispatchEventWith(Event.ADDED, true);

            if (stage())
            {
               auto container = std::dynamic_pointer_cast<DisplayObjectContainer>(child);
               if (container) {
                  //container.broadcastEventWith(Event.ADDED_TO_STAGE);
               }
               else {
                  //child.dispatchEventWith(Event.ADDED_TO_STAGE);
               }
            }
         }

         return child;
      }
      
      std::shared_ptr<DisplayObject> DisplayObjectContainer::getChildAt(int index) const
      {
         if (index < 0 || index >= _children.size()) throw std::out_of_range("Invalid child index");
         
         return _children[index];
      }
      
      std::shared_ptr<DisplayObject> DisplayObjectContainer::getChildByName(std::string name) const
      {
         for (auto child : _children) {
            if (name == child->name()) {
               return child;
            }
         }
         
         return std::shared_ptr<DisplayObject>();
      }
      
      int DisplayObjectContainer::getChildIndex(const std::shared_ptr<DisplayObject>& child) const
      {
         auto it = std::find(_children.begin(), _children.end(), child);
         if (it != _children.end()) return std::distance(_children.begin(), it);
         
         return -1;
      }
      
      void DisplayObjectContainer::setChildIndex(const std::shared_ptr<DisplayObject>& child, int index)
      {
         int oldIndex = getChildIndex(child);
         if (oldIndex == index) return;
         
         if (oldIndex == -1) throw std::invalid_argument("Not a child of this container");
         
         _children.erase(_children.begin() + oldIndex);
         _children.insert(_children.begin() + index, child);
      }
      
      std::shared_ptr<DisplayObject> DisplayObjectContainer::removeChild(std::shared_ptr<DisplayObject> child)
      {
         int childIndex = getChildIndex(child);
         if (childIndex != -1) removeChildAt(childIndex);

         return child;
      }
      
      std::shared_ptr<DisplayObject> DisplayObjectContainer::removeChildAt(int index)
      {
         if (index < 0 || index > _children.size()) throw std::out_of_range("Invalid child index");
         
         auto child = _children[index];
         //child.dispatchEventWith(Event.REMOVED, true);

         if (stage())
         {
            auto container = std::dynamic_pointer_cast<DisplayObjectContainer>(child);
            if (container) {
               //container.broadcastEventWith(Event.REMOVED_FROM_STAGE);
            }
            else {
               //child.dispatchEventWith(Event.REMOVED_FROM_STAGE);
            }
         }
         
         child->setParent(std::shared_ptr<DisplayObjectContainer>());
         auto it = std::find(_children.begin(), _children.end(), child); // index might have changed by event handler
         if (it != _children.end()) _children.erase(it);
         
         return child;
      }
      
      void DisplayObjectContainer::removeChildren(int beginIndex, int endIndex)
      {
         if (endIndex < 0 || endIndex >= _children.size()) endIndex = _children.size() - 1;
         
         for (int i = beginIndex; i <= endIndex; ++i) {
            removeChildAt(beginIndex);
         }
      }
      
      void DisplayObjectContainer::tick(float deltaSeconds)
      {
         for (auto child : _children) {
            auto animated = std::dynamic_pointer_cast<DisplayObjectContainer>(child);
            if (animated) animated->tick(deltaSeconds);
         }
      }
      
      void DisplayObjectContainer::render(RenderSupport *support, float parentAlpha, geom::Matrix parentTransform)
      {
         geom::Matrix transform = parentTransform * transformationMatrix();
         for (auto child : _children) {
            auto renderable = std::dynamic_pointer_cast<DisplayObject>(child);
            if (renderable) renderable->render(support, parentAlpha, transform);
         }
      }
      
   }
}
