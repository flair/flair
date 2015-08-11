#include "flair/flair.h"
#include "flair/utils/ByteArray.h"
#include "gtest/gtest.h"

#include <cstdint>

namespace {
   using flair::utils::ByteArray;
   
   class ByteArrayTest : public ::testing::Test
   {
   protected:
      ByteArrayTest() {}
      virtual ~ByteArrayTest() {}
   };
   
   TEST_F(ByteArrayTest, ReadWriteIntrinsic)
   {
      auto bytes = flair::make_shared<ByteArray>();
      
      bytes->writeBoolean(true);
      bytes->writeByte(INT8_MIN);
      bytes->writeDouble(3333.3333333333333333);
      bytes->writeFloat(0.12345678f);
      bytes->writeInt(INT32_MIN);
      bytes->writeLong(INT64_MIN);
      bytes->writeShort(INT16_MIN);
      bytes->writeUnsignedByte(UINT8_MAX);
      bytes->writeUnsignedInt(UINT32_MAX);
      bytes->writeUnsignedLong(UINT64_MAX);
      bytes->writeUnsignedShort(UINT16_MAX);
      
      bytes->position(0);
      EXPECT_EQ(true, bytes->readBoolean());
      EXPECT_EQ(INT8_MIN, bytes->readByte());
      EXPECT_DOUBLE_EQ(3333.3333333333333333, bytes->readDouble());
      EXPECT_FLOAT_EQ(0.12345678f, bytes->readFloat());
      EXPECT_EQ(INT32_MIN, bytes->readInt());
      EXPECT_EQ(INT64_MIN, bytes->readLong());
      EXPECT_EQ(INT16_MIN, bytes->readShort());
      EXPECT_EQ(UINT8_MAX, bytes->readUnsignedByte());
      EXPECT_EQ(UINT32_MAX, bytes->readUnsignedInt());
      EXPECT_EQ(UINT64_MAX, bytes->readUnsignedLong());
      EXPECT_EQ(UINT16_MAX, bytes->readUnsignedShort());
   }
   
   TEST_F(ByteArrayTest, Resize)
   {
      auto bytes = flair::make_shared<ByteArray>();
      
      for (int i = 0; i < 2048; ++i)
      {
         bytes->writeLong( i % 2 ? INT64_MIN : INT64_MAX);
      }
      
      bytes->position(0);
      for (int i = 0; i < 2048; ++i)
      {
         EXPECT_EQ(i % 2 ? INT64_MIN : INT64_MAX, bytes->readLong());
      }
   }
   
   TEST_F(ByteArrayTest, CompressDeflate)
   {
      auto bytes = flair::make_shared<ByteArray>();
      bytes->writeInt(100);
      bytes->writeInt(200);
      bytes->writeBoolean(true);
      bytes->writeFloat(1234.12345f);
      
      bytes->compress(ByteArray::Compression::DEFLATE);
      bytes->uncompress(ByteArray::Compression::DEFLATE);
      
      EXPECT_EQ(100, bytes->readInt());
      EXPECT_EQ(200, bytes->readInt());
      EXPECT_EQ(true, bytes->readBoolean());
      EXPECT_FLOAT_EQ(1234.12345f, bytes->readFloat());
   }
   
   TEST_F(ByteArrayTest, CompressZlib)
   {
      auto bytes = flair::make_shared<ByteArray>();
      bytes->writeInt(100);
      bytes->writeInt(200);
      bytes->writeBoolean(true);
      bytes->writeFloat(1234.12345f);
      
      bytes->compress(ByteArray::Compression::ZLIB);
      bytes->uncompress(ByteArray::Compression::ZLIB);
      
      EXPECT_EQ(100, bytes->readInt());
      EXPECT_EQ(200, bytes->readInt());
      EXPECT_EQ(true, bytes->readBoolean());
      EXPECT_FLOAT_EQ(1234.12345f, bytes->readFloat());
   }
   
   TEST_F(ByteArrayTest, CompressGzip)
   {
      auto bytes = flair::make_shared<ByteArray>();
      bytes->writeInt(100);
      bytes->writeInt(200);
      bytes->writeBoolean(true);
      bytes->writeFloat(1234.12345f);
      
      bytes->compress(ByteArray::Compression::GZIP);
      bytes->uncompress(ByteArray::Compression::GZIP);
      
      EXPECT_EQ(100, bytes->readInt());
      EXPECT_EQ(200, bytes->readInt());
      EXPECT_EQ(true, bytes->readBoolean());
      EXPECT_FLOAT_EQ(1234.12345f, bytes->readFloat());
   }
   
   TEST_F(ByteArrayTest, CompressLarge)
   {
      auto bytes = flair::make_shared<ByteArray>();
      const size_t ITERATIONS = 1000000; // 4 * ITERAIONS = 4 MB

      for (int i = 0; i < ITERATIONS; ++i) {
         bytes->writeInt(i * 2);
      }

      bytes->compress(ByteArray::Compression::DEFLATE);
      bytes->uncompress(ByteArray::Compression::DEFLATE);
      
      for (int i = 0; i < ITERATIONS; ++i) {
         EXPECT_EQ(i * 2, bytes->readInt());
      }
      
      bytes->compress(ByteArray::Compression::ZLIB);
      bytes->uncompress(ByteArray::Compression::ZLIB);
      
      for (int i = 0; i < ITERATIONS; ++i) {
         EXPECT_EQ(i * 2, bytes->readInt());
      }
      
      bytes->compress(ByteArray::Compression::GZIP);
      bytes->uncompress(ByteArray::Compression::GZIP);
      
      for (int i = 0; i < ITERATIONS; ++i) {
         EXPECT_EQ(i * 2, bytes->readInt());
      }
   }

}
