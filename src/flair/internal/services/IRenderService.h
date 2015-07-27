#ifndef flair_internal_services_IRenderService_h
#define flair_internal_services_IRenderService_h

#include "flair/internal/services/IWindowService.h"

namespace flair {
   namespace internal {
      namespace services {
         
         class IRenderService
         {
         // Properties
         public:
            
         // Methods
         public:
            virtual void create(IWindowService * window, bool vsync = true) = 0;
            
            virtual void clear() = 0;
            
            virtual void present() = 0;
         };
         
      }
   }
}

#endif
