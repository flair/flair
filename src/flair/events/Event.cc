#include "flair/events/Event.h"

namespace flair {
   namespace events {
      
      Event::Event(const char* type, bool bubbles, bool cancelable) : _type(type), _bubbles(bubbles), _cancelable(cancelable)
      {
         
      }
      
      Event::~Event()
      {
         
      }
      
      bool Event::bubbles() const
      {
         return _bubbles;
      }
      
      bool Event::cancelable() const
      {
         return _cancelable;
      }
      
      std::shared_ptr<Object> Event::currentTarget() const
      {
         return nullptr;
      }
      
      unsigned int Event::eventPhase() const
      {
         return 0;
      }
      
      std::shared_ptr<Object> Event::target() const
      {
         return nullptr;
      }
      
      std::string Event::type() const
      {
         return _type;
      }
      
      std::shared_ptr<Event> Event::clone()
      {
         return flair::make_shared<Event>(_type.c_str(), _bubbles, _cancelable);
      }
      
      std::string Event::toString() const
      {
         return "[flair.events.Event Event]";
      }
      
      const char* Event::ACTIVATE = "activate";
      const char* Event::ADDED = "added";
      const char* Event::ADDED_TO_STAGE = "addedToStage";
      const char* Event::BROWSER_ZOOM_CHANGE = "browserZoomChange";
      const char* Event::CANCEL = "cancel";
      const char* Event::CHANGE = "change";
      const char* Event::CHANNEL_MESSAGE = "channelMessage";
      const char* Event::CHANNEL_STATE = "channelState";
      const char* Event::CLEAR = "clear";
      const char* Event::CLOSE = "close";
      const char* Event::CLOSING = "closing";
      const char* Event::COMPLETE = "complete";
      const char* Event::CONNECT = "connect";
      const char* Event::CONTEXT3D_CREATE = "context3DCreate";
      const char* Event::COPY = "copy";
      const char* Event::CUT = "cut";
      const char* Event::DEACTIVATE = "deactivate";
      const char* Event::DISPLAYING = "displaying";
      const char* Event::ENTER_FRAME = "enterFrame";
      const char* Event::ERROR = "error";
      const char* Event::EXIT_FRAME = "exitFrame";
      const char* Event::EXITING = "exiting";
      const char* Event::FRAME_CONSTRUCTED = "frameConstructed";
      const char* Event::FRAME_LABEL = "frameLabel";
      const char* Event::FULLSCREEN = "fullScreen";
      const char* Event::HTML_BOUNDS_CHANGE = "htmlBoundsChange";
      const char* Event::HTML_DOM_INITIALIZE = "htmlDOMInitialize";
      const char* Event::HTML_RENDER = "htmlRender";
      const char* Event::ID3 = "id3";
      const char* Event::INIT = "init";
      const char* Event::LOCATION_CHANGE = "locationChange";
      const char* Event::MOUSE_LEAVE = "mouseLeave";
      const char* Event::NETWORK_CHANGE = "networkChange";
      const char* Event::OPEN = "open";
      const char* Event::PASTE = "paste";
      const char* Event::PREPARING = "preparing";
      const char* Event::REMOVED = "removed";
      const char* Event::REMOVED_FROM_STAGE = "removedFromStage";
      const char* Event::RENDER = "render";
      const char* Event::RESIZE = "resize";
      const char* Event::SCROLL = "scroll";
      const char* Event::SELECT = "select";
      const char* Event::SELECT_ALL = "selectAll";
      const char* Event::SOUND_COMPLETE = "soundComplete";
      const char* Event::STANDARD_ERROR_CLOSE = "standardErrorClose";
      const char* Event::STANDARD_INPUT_CLOSE = "standardInputClose";
      const char* Event::STANDARD_OUTPUT_CLOSE = "standardOutputClose";
      const char* Event::SUSPEND = "suspend";
      const char* Event::TAB_CHILDREN_CHANGE = "tabChildrenChange";
      const char* Event::TAB_ENABLED_CHANGE = "tabEnabledChange";
      const char* Event::TAB_INDEX_CHANGE = "tabIndexChange";
      const char* Event::TEXT_INTERACTION_MODE_CHANGE = "textInteractionModeChange";
      const char* Event::TEXTURE_READY = "textureReady";
      const char* Event::UNLOAD = "unload";
      const char* Event::USER_IDLE = "userIdle";
      const char* Event::USER_PRESENT = "userPresent";
      const char* Event::VIDEO_FRAME = "videoFrame";
      const char* Event::WORKER_STATE = "workerState";
      
   }
}
