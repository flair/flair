#ifndef flair_display_Stage_h
#define flair_display_Stage_h

#include "flair/flair.h"
#include "flair/display/DisplayObjectContainer.h"

namespace flair {
   namespace display {
      
      class Stage : public DisplayObjectContainer
      {
         friend std::shared_ptr<Stage> flair::create<Stage>();
         
      protected:
         Stage();
         
      public:
         virtual ~Stage();
      };
   }
}

#endif
