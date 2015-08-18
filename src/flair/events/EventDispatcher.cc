#include "flair/events/EventDispatcher.h"

namespace flair {
   namespace events {
            
      EventDispatcher::EventDispatcher(std::shared_ptr<EventDispatcher> target)
      {
         
      }
      
      void EventDispatcher::addEventListener(std::string type, std::function<void(std::shared_ptr<Event>)> listener, bool useCapture, int32_t priority, bool once)
      {
         std::multimap<std::string, EventListener>::iterator hint = listeners.end();
         
         auto const& range = listeners.equal_range(type);
         for (auto it = range.first; it != range.second; ++it) {
            auto const& eventListener = it->second;
            if (isTarget(eventListener, listener, useCapture)) return;
            if (priority >= eventListener.priority) { hint = it; break; }
         }
         
         if (hint == listeners.end()) {
            listeners.insert(std::make_pair(type, EventListener(std::move(listener), useCapture, priority)));
         }
         else {
            listeners.insert(hint, std::make_pair(type, EventListener(std::move(listener), useCapture, priority)));
         }
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
            auto eventListener = it->second;
            eventListener.callback(event);
            
            dispatched = true;
            //if (event->preventDefault()) dispatched = false;
            
            if (eventListener.once) it = listeners.erase(it);
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
         auto const& range = listeners.equal_range(type);
         for (auto it = range.first; it != range.second; ) {
            auto const& eventListener = it->second;
            bool target = isTarget(eventListener, listener, useCapture);
            it = target ? listeners.erase(it) : ++it;
         }
      }
      
      bool EventDispatcher::willTrigger(std::string type)
      {
         // TODO: Need to inspect all child listeners queues to see if anyone in the event chain has a listener
         return false;
      }
      
      bool EventDispatcher::isTarget(EventListener const& targetListener, std::function<void(std::shared_ptr<Event>)> const& listener, bool useCapture)
      {
         return targetListener.useCapture == useCapture &&
                targetListener.callback.target_type() == listener.target_type() &&
                targetListener.callback.target<void(std::shared_ptr<Event>)>() == listener.target<void(std::shared_ptr<Event>)>();
      }
   }
}
