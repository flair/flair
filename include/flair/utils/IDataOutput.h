#ifndef flair_utils_IDataOutput_h
#define flair_utils_IDataOutput_h

#include "flair/JSON.h"
#include "flair/utils/Endian.h"

#include <cstdint>
#include <string>

namespace flair {
namespace utils {
   
   class ByteArray;
   
   class IDataOutput
   {
   // Properties
   public:
      virtual Endian endian() = 0;
      virtual Endian endian(Endian value) = 0;
      
   // Methods
   public:
      virtual void writeBoolean(bool value) = 0;
      
      virtual void writeByte(int8_t value) = 0;
      
      virtual void writeBytes(ByteArray & bytes, size_t offset = 0, size_t length = 0) = 0;
      
      virtual void writeDouble(double value) = 0;
      
      virtual void writeFloat(float value) = 0;
      
      virtual void writeInt(int32_t value) = 0;
      
      virtual void writeLong(int64_t value) = 0;
      
      virtual void writeMultiByte(std::string value, std::string charSet) = 0;
      
      virtual void writeObject(flair::JSON) = 0;
      
      virtual void writeShort(int16_t value) = 0;
      
      virtual void writeUnsignedByte(uint8_t value) = 0;
      
      virtual void writeUnsignedInt(uint32_t value) = 0;
      
      virtual void writeUnsignedLong(uint64_t value) = 0;
      
      virtual void writeUnsignedShort(uint16_t value) = 0;
      
      virtual void writeUTF(std::string value) = 0;
      
      virtual void writeUTFBytes(std::string value) = 0;
   };

}}

#endif
