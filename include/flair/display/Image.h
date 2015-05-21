#ifndef flair_display_Image_h
#define flair_display_Image_h

#include "flair/flair.h"
#include "flair/display/DisplayObject.h"

namespace flair {
   namespace display {
      
      class Image : public DisplayObject
      {
         friend std::shared_ptr<Image> flair::create<Image>();
       
      protected:
         Image();
         
      public:
         virtual ~Image();
      };
      
   }
}

#endif
