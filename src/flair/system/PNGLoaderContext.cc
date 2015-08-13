#include "flair/system/PNGLoaderContext.h"

namespace flair {
namespace system {
   
   PNGLoaderContext::PNGLoaderContext()
   {
      
   }
   
   PNGLoaderContext::~PNGLoaderContext()
   {
      
   }
   
   void PNGLoaderContext::decode(std::shared_ptr<utils::ByteArray> bytes, std::function<void(std::shared_ptr<utils::ByteArray>)> callback)
   {
      callback(bytes);
   }
   
}}
