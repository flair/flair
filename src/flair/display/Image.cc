#include "flair/display/Image.h"

namespace flair {
   namespace display {
      
      Image::Image() : DisplayObject()
      {
         
      }
      
      Image::~Image()
      {
         
      }
      
      std::string Image::toString() const
      {
         return "[Image image]";
      }
      
   }
}