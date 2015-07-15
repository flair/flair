#include "flair/events/EventDispatcher.h"


namespace flair {
   namespace events {
      
      EventDispatcher::EventDispatcher(std::shared_ptr<EventDispatcher> target)
      {
         
      }
      
      void EventDispatcher::addEventListener(std::string type, std::function<void(std::shared_ptr<Event>)> listener, bool useCapture, int priority, bool useWeakReference)
      {
         listeners.insert(std::make_pair(type, listener));
      }
      
      EventDispatcher::~EventDispatcher()
      {
         listeners.clear();
      }
      
      bool EventDispatcher::dispatchEvent(std::shared_ptr<Event> event)
      {
         bool dispatched = false;
         auto range = listeners.equal_range(event->type());
         for (auto it = range.first; it != range.second; ++it) {
            auto callable = it->second;
            callable(event);
            
            dispatched = true;
            //if (event->preventDefault()) dispatched = false;
         }
         
         return dispatched;
      }
      
      bool EventDispatcher::hasEventListener(std::string type)
      {
         auto range = listeners.equal_range(type);
         return range.first != range.second;
      }
      
      void EventDispatcher::removeEventListener(std::string type, std::function<void(std::shared_ptr<Event>)> listener, bool useCapture)
      {
         auto range = listeners.equal_range(type);
         for (auto it = range.first; it != range.second; ) {
            auto callable = it->second;
            bool isTarget = callable.target_type() == listener.target_type() && callable.target<void(std::shared_ptr<Event>)>() == listener.target<void(std::shared_ptr<Event>)>();
            it = isTarget ? listeners.erase(it) : ++it;
         }
      }
      
      bool EventDispatcher::willTrigger(std::string type)
      {
         // TODO: Need to inspect all child listeners queues to see if anyone in the event chain has a listener
         return false;
      }
   }
}
