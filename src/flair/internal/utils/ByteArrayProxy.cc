#include "flair/internal/utils/ByteArrayProxy.h"

namespace flair {
namespace internal {
namespace utils {
   
   ByteArrayProxy::ByteArrayProxy(std::shared_ptr<flair::utils::ByteArray> bytes) : byteArray(bytes)
   {
      
   }
   
   uint8_t const* ByteArrayProxy::bytes() const
   {
      return byteArray->_byteArray;
   }
   
   size_t ByteArrayProxy::length() const
   {
      return byteArray->_length;
   }

}}}
