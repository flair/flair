#include "flair/display/Stage.h"
#include "flair/events/Event.h"

namespace {
   static unsigned int fps = 0;
   static unsigned int fpsCount = 0;
   static float fpsInterval = 0.0f;
   
   void updateFps(float deltaSeconds)
   {
      fpsCount++;
      if (fpsInterval >= 1.0f) {
         fps = fpsCount;
         fpsCount = 0;
         fpsInterval = 0.0f;
         
         std::cout << "FPS: " << fps << std::endl;
      }
      fpsInterval += deltaSeconds;
   }
}

namespace flair {
   namespace display {
      
      using flair::events::Event;
      
      Stage::Stage() : DisplayObjectContainer()
      {

      }
      
      Stage::~Stage()
      {
         
      }
      
      void Stage::tick(float deltaSeconds)
      {
         DisplayObjectContainer::tick(deltaSeconds);
         
         // TODO: Testing
         dispatchEvent(flair::make_shared<Event>(Event::ENTER_FRAME));
         
         // TODO: Testing
         updateFps(deltaSeconds);
      }
      
   }
}