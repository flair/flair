#include "flair/system/LoaderContext.h"
#include "flair/internal/services/IWorkerService.h"

namespace flair {
namespace system {
   
   flair::internal::services::IWorkerService * LoaderContext::workerService = nullptr;
   
   LoaderContext::LoaderContext()
   {
      
   }
   
   LoaderContext::~LoaderContext()
   {
      
   }
   
   void LoaderContext::decode(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<utils::ByteArray>)> callback)
   {
      callback(bytes);
   }
   
   void LoaderContext::create(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<display::DisplayObject>)> callback)
   {
      callback(nullptr);
   }

}}
