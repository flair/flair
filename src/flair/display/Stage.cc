#include "flair/display/Stage.h"
#include "flair/events/Event.h"
#include "flair/internal/EventLoop.h"

flair::internal::EventLoop* g_ActiveEventLoop = nullptr;

namespace {
   static unsigned int _fps = 0;
   static unsigned int _fpsCount = 0;
   static float _fpsInterval = 0.0f;
   
   void updateFps(float deltaSeconds)
   {
      _fpsCount++;
      if (_fpsInterval >= 1.0f) {
         _fps = _fpsCount;
         _fpsCount = 0;
         _fpsInterval = 0.0f;
         
         std::cout << "FPS: " << _fps << std::endl;
      }
      _fpsInterval += deltaSeconds;
   }
}

namespace flair {
   namespace display {
      
      using flair::events::Event;
      using flair::internal::EventLoop;
      
      Stage::Stage() : DisplayObjectContainer()
      {
         g_ActiveEventLoop = _eventLoop = new EventLoop();
         addEventListener(Event::DEACTIVATE, [&](std::shared_ptr<Event> e) {
            delete _eventLoop; g_ActiveEventLoop = _eventLoop = nullptr;
         });
      }
      
      Stage::~Stage()
      {
         delete _eventLoop;
      }
      
      void Stage::tick(float deltaSeconds)
      {
         g_ActiveEventLoop = _eventLoop;
         DisplayObjectContainer::tick(deltaSeconds);
         
         // TODO: Testing
         if (_eventLoop) _eventLoop->Enqueue();
         
         // TODO: Testing
         updateFps(deltaSeconds);
      }
      
   }
}