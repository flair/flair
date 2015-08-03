#ifndef flair_events_Event_h
#define flair_events_Event_h

#include "flair/flair.h"
#include "flair/Object.h"

#include <string>
#include <memory>

namespace flair {
   namespace events {
      
      class Event : public Object
      {
         friend class flair::allocator;
         
      protected:
         Event(const char * type, bool bubbles = false, bool cancelable = false);
         
      public:
         virtual ~Event();
      
      
      // Events
      public:
         static const char* ACTIVATE;
         static const char* ADDED;
         static const char* ADDED_TO_STAGE;
         static const char* BROWSER_ZOOM_CHANGE;
         static const char* CANCEL;
         static const char* CHANGE;
         static const char* CHANNEL_MESSAGE;
         static const char* CHANNEL_STATE;
         static const char* CLEAR;
         static const char* CLOSE;
         static const char* CLOSING;
         static const char* COMPLETE;
         static const char* CONNECT;
         static const char* CONTEXT3D_CREATE;
         static const char* COPY;
         static const char* CUT;
         static const char* DEACTIVATE;
         static const char* DISPLAYING;
         static const char* ENTER_FRAME;
         static const char* ERROR;
         static const char* EXIT_FRAME;
         static const char* EXITING;
         static const char* FRAME_CONSTRUCTED;
         static const char* FRAME_LABEL;
         static const char* FULLSCREEN;
         static const char* HTML_BOUNDS_CHANGE;
         static const char* HTML_DOM_INITIALIZE;
         static const char* HTML_RENDER;
         static const char* ID3;
         static const char* INIT;
         static const char* LOCATION_CHANGE;
         static const char* MOUSE_LEAVE;
         static const char* NETWORK_CHANGE;
         static const char* OPEN;
         static const char* PASTE;
         static const char* PREPARING;
         static const char* REMOVED;
         static const char* REMOVED_FROM_STAGE;
         static const char* RENDER;
         static const char* RESIZE;
         static const char* SCROLL;
         static const char* SELECT;
         static const char* SELECT_ALL;
         static const char* SOUND_COMPLETE;
         static const char* STANDARD_ERROR_CLOSE;
         static const char* STANDARD_INPUT_CLOSE;
         static const char* STANDARD_OUTPUT_CLOSE;
         static const char* SUSPEND;
         static const char* TAB_CHILDREN_CHANGE;
         static const char* TAB_ENABLED_CHANGE;
         static const char* TAB_INDEX_CHANGE;
         static const char* TEXT_INTERACTION_MODE_CHANGE;
         static const char* TEXTURE_READY;
         static const char* UNLOAD;
         static const char* USER_IDLE;
         static const char* USER_PRESENT;
         static const char* VIDEO_FRAME;
         static const char* WORKER_STATE;
         
         
      // Properties
      public:
         bool bubbles() const;
         
         bool cancelable() const;

         std::shared_ptr<Object> currentTarget() const;

         unsigned int eventPhase() const;
         
         std::shared_ptr<Object> target() const;

         std::string type() const;
      
      
      // Methods
      public:
         virtual std::shared_ptr<Event> clone();
         
         std::string formatToString(std::string className, ...) const;
         
         bool isDefaultPrevented() const;
         
         void preventDefault();
         
         void stopImmediatePropagation();
         
         void stopPropagation();
         
         std::string toString() const override;
      
      
      protected:
         bool _bubbles;
         bool _cancelable;
         std::weak_ptr<Object> _currentTarget;
         unsigned int _eventPhase;
         std::weak_ptr<Object> _target;
         std::string _type;
         
         bool _preventDefault;
         bool _stopImmediatePropegation;
         bool _stopPropigation;
      };
      
   }
}

#endif
