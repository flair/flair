#include "flair/display/Stage.h"
#include "flair/display/Image.h"
#include "flair/display/Sprite.h"
#include "gtest/gtest.h"

namespace {
   using flair::display::Image;
   using flair::display::Stage;
   using flair::display::Sprite;
   using flair::display::DisplayObject;
   
   class DisplayObjectContainerTest : public ::testing::Test
   {
   protected:
      DisplayObjectContainerTest() {}
      virtual ~DisplayObjectContainerTest() {}
   };
   
   TEST_F(DisplayObjectContainerTest, AddChild)
   {
      auto image = flair::make_shared<Image>();
      auto stage = flair::make_shared<Stage>();
      
      auto child = stage->addChild(image);
      EXPECT_EQ(child->parent(), stage);
      EXPECT_EQ(stage->numChildren(), 1);
   }
   
   TEST_F(DisplayObjectContainerTest, Contains)
   {
      auto image = flair::make_shared<Image>();
      auto stage = flair::make_shared<Stage>();
      
      auto child = stage->addChild(image);
      EXPECT_TRUE(stage->contains(child));
   }
   
   TEST_F(DisplayObjectContainerTest, Inheritance)
   {
      class CustomStage : public Stage
      {
         friend std::shared_ptr<CustomStage> flair::make_shared<CustomStage>();
         
      protected:
         CustomStage() : Stage() {};
         
      public:
         virtual ~CustomStage() {}
      };
      
      auto image = flair::make_shared<Image>();
      auto stage = flair::make_shared<CustomStage>();
      auto sprite = flair::make_shared<Sprite>();
      
      auto child = stage->addChild(image);
      EXPECT_TRUE(stage->contains(child));
      
   }
}
