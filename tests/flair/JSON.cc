#include "flair/flair.h"
#include "flair/JSON.h"
#include "gtest/gtest.h"

namespace {
   using flair::JSON;
   
   class JSONTest : public ::testing::Test
   {
   protected:
      JSONTest() {}
      virtual ~JSONTest() {}
   };
   
   TEST_F(JSONTest, Parse)
   {
      auto result = JSON::parse("{ \"hello\": \"world\" }");
      EXPECT_EQ(result["hello"].string_value(), "world");
   }
   
   TEST_F(JSONTest, Stringify)
   {
      auto object = JSON::Object {
         {"key1", "value1"},
         {"key2", false},
         {"key3", JSON::Array { 1, 2, 3 }}
      };
      
      auto result = JSON::stringify(object);
      EXPECT_EQ(result, "{\"key1\": \"value1\", \"key2\": false, \"key3\": [1, 2, 3]}");
   }
}
