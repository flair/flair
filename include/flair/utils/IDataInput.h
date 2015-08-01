#ifndef flair_utils_IDataInput_h
#define flair_utils_IDataInput_h

#include "flair/JSON.h"
#include "flair/utils/Endian.h"

#include <cstdint>
#include <string>

namespace flair {
namespace utils {
   
   class ByteArray;
   
   class IDataInput
   {
   // Properties
   public:
      virtual size_t bytesAvailable() = 0;
      
      virtual Endian endian() = 0;
      virtual Endian endian(Endian value) = 0;
      
   // Methods
   public:
      virtual bool readBoolean() = 0;
      
      virtual int8_t readByte() = 0;
      
      virtual void readBytes(ByteArray & bytes, size_t offset = 0, size_t length = 0) = 0;
      
      virtual double readDouble() = 0;

      virtual float readFloat() = 0;
      
      virtual int32_t readInt() = 0;
      
      virtual int64_t readLong() = 0;
      
      virtual std::string readMultiByte(size_t length, std::string charSet) = 0;

      virtual flair::JSON readObject() = 0;
      
      virtual int16_t readShort() = 0;
      
      virtual uint8_t readUnsignedByte() = 0;
      
      virtual uint32_t readUnsignedInt() = 0;
      
      virtual uint64_t readUnsignedLong() = 0;
      
      virtual uint16_t readUnsignedShort() = 0;
      
      virtual std::string readUTF() = 0;
      
      virtual std::string readUTFBytes(size_t length) = 0;
   };
      
}}

#endif
