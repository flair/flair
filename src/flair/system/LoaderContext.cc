#include "flair/system/LoaderContext.h"

namespace flair {
namespace system {
   
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

}}
