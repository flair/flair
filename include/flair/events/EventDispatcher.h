#ifndef flair_events_EventDispatcher_h
#define flair_events_EventDispatcher_h

#include "flair/flair.h"
#include "flair/Object.h"
#include "flair/events/IEventDispatcher.h"

#include <unordered_map>
#include <functional>

namespace flair {
   namespace events {
      
      class EventDispatcher : public Object, public IEventDispatcher
      {
         friend class flair::allocator;

      protected:
         EventDispatcher(std::shared_ptr<EventDispatcher> target = nullptr);
         
      public:
         virtual ~EventDispatcher();
         
      public:
         void addEventListener(std::string type, std::function<void(std::shared_ptr<Event>)> listener, bool useCapture = false, int priority = 0) override;
         
         template <class T>
         void addEventListener(std::string type, void (T::*listener)(std::shared_ptr<Event>), std::shared_ptr<T> const& instance, bool useCapture = false, int priority = 0, bool weakReference = false)
         {
            std::function<void(std::shared_ptr<Event>)> delegate;
            
            if (weakReference) {
               auto ptr = std::weak_ptr<T>(instance);
               delegate = [listener, ptr](std::shared_ptr<Event> event) { if (auto p = ptr.lock()) { ((*p).*listener)(event); } };
            }
            else {
               auto ptr = std::shared_ptr<T>(instance);
               delegate = [listener, ptr](std::shared_ptr<Event> event) { ((*ptr).*listener)(event); };
            }
            
            addEventListener(type, delegate, useCapture, priority);
         }
         
         template <class T, typename std::enable_if<std::is_base_of<Object, T>::value>::type* = nullptr>
         void addEventListener(std::string type, void (T::*listener)(std::shared_ptr<Event>), T* self, bool useCapture = false, int priority = 0, bool weakReference = false)
         {
            addEventListener(type, listener, self->template shared<T>(), useCapture, priority, weakReference);
         }
         
         bool dispatchEvent(std::shared_ptr<Event> event) override;
         
         bool hasEventListener(std::string) override;
         
         void removeEventListener(std::string type, std::function<void(std::shared_ptr<Event>)> listener, bool useCapture = false) override;
         
         bool willTrigger(std::string type) override;
         
      private:
         std::unordered_multimap<std::string, std::function<void(std::shared_ptr<Event>)>> listeners;
      };
      
      
   }
}

#endif
