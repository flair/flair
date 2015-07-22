#ifndef flair_display_Stage_h
#define flair_display_Stage_h

#include "flair/flair.h"
#include "flair/display/DisplayObjectContainer.h"

namespace flair {
   namespace internal {
      class EventLoop;
   }
   
   namespace display {
      
      class Stage : public DisplayObjectContainer
      {
         friend class flair::allocator;
         
      protected:
         Stage();
         
      public:
         virtual ~Stage();
         
      // Methods
      public:
         
      // Internal
      public:
         void tick(float deltaSeconds) override;
         
      protected:
         internal::EventLoop *_eventLoop;
         
      };
   }
}

#endif
