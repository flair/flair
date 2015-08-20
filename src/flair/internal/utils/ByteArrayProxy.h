#ifndef flair_internal_utils_ByteArrayProxy_h
#define flair_internal_utils_ByteArrayProxy_h

#include "flair/flair.h"
#include "flair/utils/ByteArray.h"

namespace flair {
namespace internal {
namespace utils {
   
   class ByteArrayProxy
   {
   public:
      ByteArrayProxy(std::shared_ptr<flair::utils::ByteArray> bytes);
      
   // Properties
   public:
      uint8_t const* bytes() const;
      
      size_t length() const;
      
   private:
      std::shared_ptr<flair::utils::ByteArray> byteArray;
   };
   
}}}

#endif
