#ifndef flair_utils_ByteArray_h
#define flair_utils_ByteArray_h

#include "flair/flair.h"
#include "flair/Object.h"
#include "flair/utils/IDataInput.h"
#include "flair/utils/IDataOutput.h"
#include "flair/utils/Endian.h"

namespace flair {
namespace utils {
   
   class ByteArray : public flair::Object, public IDataInput, public IDataOutput
   {
      friend class flair::allocator;
      
   protected:
      ByteArray();
      
   public:
      ~ByteArray();
      
   public:
      enum class Compression {
         DEFLATE,
         ZLIB,
         GZIP
      };
      
   // Properties
   public:
      size_t bytesAvailable() override;
      
      Endian endian() override;
      Endian endian(Endian value) override;
      
      size_t length();
      size_t length(size_t value);
      
      size_t position();
      size_t position(size_t value);
      
      
   // Methods
   public:
      size_t atomicCompareAndSwapIntAt(size_t byteIndex, size_t expectedValue, size_t newValue);
      
      size_t atomicCompareAndSwapLength(size_t expectedLength, size_t newLength);
      
      void clear();
      
      void compress(Compression algorithm = Compression::ZLIB);
      void uncompress(Compression algorithm = Compression::ZLIB);
      
      std::string toString() const override;
      flair::JSON toJSON() const;
      
      bool readBoolean() override;
      void writeBoolean(bool value) override;
      
      double readDouble() override;
      void writeDouble(double value) override;
      
      float readFloat() override;
      void writeFloat(float value) override;
      
      int8_t readByte() override;
      void writeByte(int8_t value) override;
      
      int16_t readShort() override;
      void writeShort(int16_t value) override;
      
      int32_t readInt() override;
      void writeInt(int32_t value) override;
      
      int64_t readLong() override;
      void writeLong(int64_t value) override;
      
      uint8_t readUnsignedByte() override;
      void writeUnsignedByte(uint8_t value) override;
      
      uint16_t readUnsignedShort() override;
      void writeUnsignedShort(uint16_t value) override;
      
      uint32_t readUnsignedInt() override;
      void writeUnsignedInt(uint32_t value) override;
      
      uint64_t readUnsignedLong() override;
      void writeUnsignedLong(uint64_t value) override;
      
      void readBytes(ByteArray & bytes, size_t offset = 0, size_t length = 0) override;
      void writeBytes(ByteArray & bytes, size_t offset = 0, size_t length = 0) override;
      
      void readBytes(uint8_t * bytes, size_t offset = 0, size_t length = 0) override;
      void writeBytes(uint8_t const* bytes, size_t offset = 0, size_t length = 0) override;
      
      std::string readMultiByte(size_t length, std::string charSet) override;
      void writeMultiByte(std::string value, std::string charSet) override;
      
      flair::JSON readObject() override;
      void writeObject(flair::JSON) override;
      
      std::string readUTF() override;
      void writeUTF(std::string value) override;
      
      std::string readUTFBytes(size_t length) override;
      void writeUTFBytes(std::string value) override;
      
   private:
      size_t _length;
      size_t _position;
      Endian _endian;
      
      static const size_t BLOCK_SIZE = 1024;
      size_t _byteArrayLength;
      uint8_t * _byteArray;
   };
   
}}

#endif
