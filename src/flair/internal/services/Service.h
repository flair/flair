#ifndef flair_internal_services_Service_h
#define flair_internal_services_Service_h

#include "flair/internal/services/IGamepadService.h"
#include "flair/internal/services/IKeyboardService.h"
#include "flair/internal/services/IMouseService.h"
#include "flair/internal/services/ITouchService.h"
#include "flair/internal/services/IWindowService.h"
#include "flair/internal/services/IRenderService.h"

namespace flair {
namespace internal {
namespace services {

   struct Service
   {
      flair::internal::services::IGamepadService * gamepadService;
      flair::internal::services::IMouseService * mouseService;
      flair::internal::services::IKeyboardService * keyboardService;
      flair::internal::services::ITouchService * touchService;
      flair::internal::services::IWindowService * windowService;
      flair::internal::services::IRenderService * renderService;
   };
   
}}}

#endif
