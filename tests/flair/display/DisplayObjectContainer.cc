#include "flair/display/DisplayObjectContainer.h"
#include "flair/display/Image.h"
#include "gtest/gtest.h"

namespace {
   using flair::display::Image;
   using flair::display::DisplayObjectContainer;
   using flair::display::DisplayObject;
   
   class DisplayObjectContainerTest : public ::testing::Test
   {
   protected:
      DisplayObjectContainerTest() {}
      virtual ~DisplayObjectContainerTest() {}
   };
   
   TEST_F(DisplayObjectContainerTest, AddChild)
   {
      Image* image = new Image();
      DisplayObjectContainer* container = new DisplayObjectContainer();
      
      auto child = container->addChild(image);
      EXPECT_EQ(child->parent(), container);
      EXPECT_EQ(container->numChildren(), 1);
      
      delete container;
   }
   
   TEST_F(DisplayObjectContainerTest, Contains)
   {
      Image* image = new Image();
      DisplayObjectContainer* container = new DisplayObjectContainer();
      
      auto child = container->addChild(image);
      EXPECT_TRUE(container->contains(child));
      
      delete container;
   }
}
