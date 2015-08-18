#ifndef flair_events_IEventDispatcher_h
#define flair_events_IEventDispatcher_h

#include <string>
#include <functional>

#include "flair/events/Event.h"

namespace flair {
   namespace events {
      
      class IEventDispatcher
      {
         // Methods
      public:
         virtual void addEventListener(std::string type, std::function<void(std::shared_ptr<Event>)> listener, bool useCapture = false, int32_t priority = 0, bool once = false) = 0;
         
         virtual bool dispatchEvent(std::shared_ptr<Event> event) = 0;
         
         virtual bool hasEventListener(std::string) = 0;
         
         virtual void removeEventListener(std::string type, std::function<void(std::shared_ptr<Event>)> listener, bool useCapture = false) = 0;
         
         virtual bool willTrigger(std::string type) = 0;
      };
      
   }
}

#endif
