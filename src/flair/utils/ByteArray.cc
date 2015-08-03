#include "flair/utils/ByteArray.h"

#include <ios>
#include <cassert>
#include <cstring>

namespace {
   bool isBigEndian = *(uint16_t *)"\0\xff" < 0x100;
}

namespace flair {
namespace utils {
   
   ByteArray::ByteArray() : _position(0), _length(0), _byteArrayLength(0), _byteArray(nullptr)
   {
      _endian = isBigEndian ? Endian::BIG_ENDIAN_ORDER : Endian::LITTLE_ENDIAN_ORDER;
      
      _byteArray = new uint8_t[BLOCK_SIZE];
      _byteArrayLength = BLOCK_SIZE;
   }
   
   ByteArray::~ByteArray()
   {
      delete[] _byteArray;
   }
   
   size_t ByteArray::bytesAvailable()
   {
      return (_length > _position ? _length - _position : 0);
   }
   
   Endian ByteArray::endian()
   {
      return _endian;
   }
   
   Endian ByteArray::endian(Endian value)
   {
      return _endian = value;
   }
   
   size_t ByteArray::length()
   {
      return _length;
   }
   
   size_t ByteArray::length(size_t value)
   {
      if (value == _length) return _length;
      if (value < _byteArrayLength) return _length = value;
      
      if (value >= _byteArrayLength) {
         size_t newLength = ((value / BLOCK_SIZE) + 1) * BLOCK_SIZE;
         uint8_t * newByteArray = new uint8_t[newLength];
         
         assert(newByteArray);
         if (!newByteArray) throw std::ios_base::failure("Out of Memory");
         
         std::memcpy(newByteArray, _byteArray, _length);
         std::memset(&newByteArray[_length], 0, (newLength - _length));
         
         delete[] _byteArray;
         _byteArray = newByteArray;
         
         _byteArrayLength = newLength;
         _length = value;
         
         return _length;
      }
      
      return _length;
   }
   
   size_t ByteArray::position()
   {
      return _position;
   }
   
   size_t ByteArray::position(size_t value)
   {
      return _position = value;
   }
   
   size_t ByteArray::atomicCompareAndSwapIntAt(size_t byteIndex, size_t expectedValue, size_t newValue)
   {
      // TODO: Atomic Ops
      return 0;
   }
   
   size_t ByteArray::atomicCompareAndSwapLength(size_t expectedLength, size_t newLength)
   {
      // TODO: Atomic Ops
      return 0;
   }
   
   void ByteArray::clear()
   {
      delete[] _byteArray;
      _byteArray = new uint8_t[BLOCK_SIZE];
      _byteArrayLength = BLOCK_SIZE;
      
      _length = 0;
      _position = 0;
   }
   
   void ByteArray::compress(Compression algorithm)
   {
      // TODO: Compression
   }
   
   void ByteArray::uncompress(Compression algorithm)
   {
      // TODO: Compression
   }
   
   std::string ByteArray::toString() const
   {
      return "";
   }
   
   flair::JSON ByteArray::toJSON() const
   {
      return JSON();
   }
   
   bool ByteArray::readBoolean()
   {
      assert(_position + sizeof(bool) <= _length);
      if (_position + sizeof(bool) > _length) throw std::ios_base::failure("EOF reached");
      
      bool value = *((bool*)&_byteArray[_position]);
      _position += sizeof(bool);
      
      return value;
   }
   
   void ByteArray::writeBoolean(bool value)
   {
      length(_position + sizeof(bool));
      
      *((bool*)&_byteArray[_position]) = value;
      _position += sizeof(bool);
   }
   
   double ByteArray::readDouble()
   {
      assert(_position + sizeof(double) <= _length);
      if (_position + sizeof(double) > _length) throw std::ios_base::failure("EOF reached");
      
      double value = *((double*)&_byteArray[_position]);
      _position += sizeof(double);
      
      return value;
   }
   
   void ByteArray::writeDouble(double value)
   {
      length(_position + sizeof(double));
      
      *((double*)&_byteArray[_position]) = value;
      _position += sizeof(double);
   }
   
   float ByteArray::readFloat()
   {
      assert(_position + sizeof(float) <= _length);
      if (_position + sizeof(float) > _length) throw std::ios_base::failure("EOF reached");
      
      float value = *((float*)&_byteArray[_position]);
      _position += sizeof(float);
      
      return value;
   }
   
   void ByteArray::writeFloat(float value)
   {
      length(_position + sizeof(float));
      
      *((float*)&_byteArray[_position]) = value;
      _position += sizeof(float);
   }
   
   int8_t ByteArray::readByte()
   {
      assert(_position + sizeof(int8_t) <= _length);
      if (_position + sizeof(int8_t) > _length) throw std::ios_base::failure("EOF reached");
      
      int8_t value = *((int8_t*)&_byteArray[_position]);
      _position += sizeof(int8_t);
      
      return value;
   }
   
   void ByteArray::writeByte(int8_t value)
   {
      length(_position + sizeof(int8_t));
      
      *((int8_t*)&_byteArray[_position]) = value;
      _position += sizeof(int8_t);
   }
   
   int16_t ByteArray::readShort()
   {
      assert(_position + sizeof(int16_t) <= _length);
      if (_position + sizeof(int16_t) > _length) throw std::ios_base::failure("EOF reached");
      
      int16_t value = *((int16_t*)&_byteArray[_position]);
      _position += sizeof(int16_t);
      
      return value;
   }
   
   void ByteArray::writeShort(int16_t value)
   {
      length(_position + sizeof(int16_t));
      
      *((int16_t*)&_byteArray[_position]) = value;
      _position += sizeof(int16_t);
   }
   
   int32_t ByteArray::readInt()
   {
      assert(_position + sizeof(int32_t) <= _length);
      if (_position + sizeof(int32_t) > _length) throw std::ios_base::failure("EOF reached");
      
      int32_t value = *((int32_t*)&_byteArray[_position]);
      _position += sizeof(int32_t);
      
      return value;
   }
   
   void ByteArray::writeInt(int32_t value)
   {
      length(_position + sizeof(int32_t));
      
      *((int32_t*)&_byteArray[_position]) = value;
      _position += sizeof(int32_t);
   }
   
   int64_t ByteArray::readLong()
   {
      assert(_position + sizeof(int64_t) <= _length);
      if (_position + sizeof(int64_t) > _length) throw std::ios_base::failure("EOF reached");
      
      int64_t value = *((int64_t*)&_byteArray[_position]);
      _position += sizeof(int64_t);
      
      return value;
   }
   
   void ByteArray::writeLong(int64_t value)
   {
      length(_position + sizeof(int64_t));
      
      *((int64_t*)&_byteArray[_position]) = value;
      _position += sizeof(int64_t);
   }
   
   uint8_t ByteArray::readUnsignedByte()
   {
      assert(_position + sizeof(uint8_t) <= _length);
      if (_position + sizeof(uint8_t) > _length) throw std::ios_base::failure("EOF reached");
      
      uint8_t value = *((uint8_t*)&_byteArray[_position]);
      _position += sizeof(uint8_t);
      
      return value;
   }
   
   void ByteArray::writeUnsignedByte(uint8_t value)
   {
      length(_position + sizeof(uint8_t));
      
      *((uint8_t*)&_byteArray[_position]) = value;
      _position += sizeof(uint8_t);

   }
   
   uint16_t ByteArray::readUnsignedShort()
   {
      assert(_position + sizeof(uint16_t) <= _length);
      if (_position + sizeof(uint16_t) > _length) throw std::ios_base::failure("EOF reached");
      
      uint16_t value = *((uint16_t*)&_byteArray[_position]);
      _position += sizeof(uint16_t);
      
      return value;
   }
   
   void ByteArray::writeUnsignedShort(uint16_t value)
   {
      length(_position + sizeof(uint16_t));
      
      *((uint16_t*)&_byteArray[_position]) = value;
      _position += sizeof(uint16_t);
   }
   
   uint32_t ByteArray::readUnsignedInt()
   {
      assert(_position + sizeof(uint32_t) <= _length);
      if (_position + sizeof(uint32_t) > _length) throw std::ios_base::failure("EOF reached");
      
      uint32_t value = *((uint32_t*)&_byteArray[_position]);
      _position += sizeof(uint32_t);
      
      return value;
   }
   
   void ByteArray::writeUnsignedInt(uint32_t value)
   {
      length(_position + sizeof(uint32_t));
      
      *((uint32_t*)&_byteArray[_position]) = value;
      _position += sizeof(uint32_t);
   }
   
   uint64_t ByteArray::readUnsignedLong()
   {
      assert(_position + sizeof(uint64_t) <= _length);
      if (_position + sizeof(uint64_t) > _length) throw std::ios_base::failure("EOF reached");
      
      uint64_t value = *((uint64_t*)&_byteArray[_position]);
      _position += sizeof(uint64_t);
      
      return value;
   }
   
   void ByteArray::writeUnsignedLong(uint64_t value)
   {
      length(_position + sizeof(uint64_t));
      
      *((uint64_t*)&_byteArray[_position]) = value;
      _position += sizeof(uint64_t);
   }
   
   void ByteArray::readBytes(ByteArray & bytes, size_t offset, size_t length)
   {
      // TODO: Bytes
   }
   
   void ByteArray::writeBytes(ByteArray & bytes, size_t offset , size_t length)
   {
      // TODO: Bytes
   }
   
   void ByteArray::readBytes(uint8_t * bytes, size_t offset, size_t length)
   {
      // TODO: Bytes
   }
   
   void ByteArray::writeBytes(uint8_t const* bytes, size_t offset, size_t length)
   {
      // TODO: Bytes
   }
   
   std::string ByteArray::readMultiByte(size_t length, std::string charSet)
   {
      // TODO: Strings
      return "";
   }
   
   void ByteArray::writeMultiByte(std::string value, std::string charSet)
   {
      // TODO: Strings
   }
   
   flair::JSON ByteArray::readObject()
   {
      // TODO: Object
      return JSON();
   }
   
   void ByteArray::writeObject(flair::JSON)
   {
      // TODO: Object
   }
   
   std::string ByteArray::readUTF()
   {
      // TODO: Strings
      return "";
   }
   
   void ByteArray::writeUTF(std::string value)
   {
      // TODO: Strings
   }
   
   std::string ByteArray::readUTFBytes(size_t length)
   {
      // TODO: Strings
      return "";
   }
   
   void ByteArray::writeUTFBytes(std::string value)
   {
      // TODO: Strings
   }
}}
