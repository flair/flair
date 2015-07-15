#ifndef flair_events_EventDispatcher_h
#define flair_events_EventDispatcher_h

#include "flair/flair.h"
#include "flair/Object.h"
#include "flair/events/IEventDispatcher.h"

#include <unordered_map>

namespace flair {
   namespace events {
      
      class EventDispatcher : public Object, IEventDispatcher
      {
         friend std::shared_ptr<Event> flair::create<Event>(std::shared_ptr<EventDispatcher>);

      protected:
         EventDispatcher(std::shared_ptr<EventDispatcher> target = nullptr);
         
      public:
         virtual ~EventDispatcher();
         
      public:
         void addEventListener(std::string type, std::function<void(std::shared_ptr<Event>)> listener, bool useCapture = false, int priority = 0, bool useWeakReference = false) override;
         
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
