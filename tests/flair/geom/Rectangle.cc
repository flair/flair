#include "flair/geom/Point.h"
#include "flair/geom/Rectangle.h"
#include "gtest/gtest.h"

namespace {
   using flair::geom::Rectangle;
   using flair::geom::Point;
   
   class RectangleTest : public ::testing::Test
   {
   protected:
      RectangleTest() {}
      virtual ~RectangleTest() {}
   };
   
   TEST_F(RectangleTest, Dimensions)
   {
      Rectangle r(25, -6, 30, 32);
      EXPECT_FLOAT_EQ(25, r.x());
      EXPECT_FLOAT_EQ(-6, r.y());
      EXPECT_FLOAT_EQ(30, r.width());
      EXPECT_FLOAT_EQ(32, r.height());
      EXPECT_FLOAT_EQ(-6, r.top());
      EXPECT_FLOAT_EQ(26, r.bottom());
      EXPECT_FLOAT_EQ(25, r.left());
      EXPECT_FLOAT_EQ(55, r.right());
      
      Point s = r.size();
      EXPECT_FLOAT_EQ(30, s.x());
      EXPECT_FLOAT_EQ(32, s.y());
   }
   
   TEST_F(RectangleTest, Inflate)
   {
      Rectangle r(25, -6, 30, 32);
      r.inflate(30, 10);
      
      EXPECT_FLOAT_EQ(-5, r.x());
      EXPECT_FLOAT_EQ(-16, r.y());
      EXPECT_FLOAT_EQ(90, r.width());
      EXPECT_FLOAT_EQ(52, r.height());
      
      Rectangle r2(25, -6, 30, 32);
      r2.inflatePoint(Point(30, 10));
      
      EXPECT_FLOAT_EQ(-5, r2.x());
      EXPECT_FLOAT_EQ(-16, r2.y());
      EXPECT_FLOAT_EQ(90, r2.width());
      EXPECT_FLOAT_EQ(52, r2.height());
   }
   
   TEST_F(RectangleTest, Intersection)
   {
      Rectangle r1(10, 10, 10, 10);
      Rectangle r2(15, 15, 10, 10);
      Rectangle r3(20, 10, 10, 10);
      
      EXPECT_EQ(true, r1.intersects(r1));
      EXPECT_EQ(true, r1.intersects(r2));
      EXPECT_EQ(false, r1.intersects(r3));
      
      Rectangle r1i(10, 10, 10, 10);
      Rectangle r2i(15, 15, 5, 5);
      Rectangle r3i(0, 0, 0, 0);
      
      Rectangle r1result = r1.intersection(r1);
      EXPECT_FLOAT_EQ(r1i.top(), r1result.top());
      EXPECT_FLOAT_EQ(r1i.left(), r1result.left());
      EXPECT_FLOAT_EQ(r1i.width(), r1result.width());
      EXPECT_FLOAT_EQ(r1i.height(), r1result.height());
      
      Rectangle r2result = r1.intersection(r2);
      EXPECT_FLOAT_EQ(r2i.top(), r2result.top());
      EXPECT_FLOAT_EQ(r2i.left(), r2result.left());
      EXPECT_FLOAT_EQ(r2i.width(), r2result.width());
      EXPECT_FLOAT_EQ(r2i.height(), r2result.height());
      
      Rectangle r3result = r1.intersection(r3);
      EXPECT_FLOAT_EQ(r3i.top(), r3result.top());
      EXPECT_FLOAT_EQ(r3i.left(), r3result.left());
      EXPECT_FLOAT_EQ(r3i.width(), r3result.width());
      EXPECT_FLOAT_EQ(r3i.height(), r3result.height());
   }
   
   TEST_F(RectangleTest, Merge)
   {
      Rectangle r1(10, 10, 10, 10);
      Rectangle r2(15, 15, 10, 10);
      Rectangle r3(100, 100, 50, 0);
      
      Rectangle expected(10, 10, 15, 15);
      Rectangle result = r1.merge(r2);
      EXPECT_FLOAT_EQ(expected.top(), result.top());
      EXPECT_FLOAT_EQ(expected.left(), result.left());
      EXPECT_FLOAT_EQ(expected.width(), result.width());
      EXPECT_FLOAT_EQ(expected.height(), result.height());
      
      // Test ignore rectangles with a width of height of 0
      expected.setTo(10, 10, 10, 10);
      result = r1.merge(r3);
      EXPECT_FLOAT_EQ(expected.top(), result.top());
      EXPECT_FLOAT_EQ(expected.left(), result.left());
      EXPECT_FLOAT_EQ(expected.width(), result.width());
      EXPECT_FLOAT_EQ(expected.height(), result.height());
   }
   
   TEST_F(RectangleTest, Contains)
   {
      Rectangle r1(10, 10, 10, 10);
      Rectangle r2(15, 15, 10, 10);
      Rectangle r3(100, 100, 50, 0);
      Rectangle r4(15, 15, 5, 5);
      
      EXPECT_TRUE(r1.containsRect(r1));
      EXPECT_FALSE(r1.containsRect(r2));
      EXPECT_FALSE(r1.containsRect(r3));
      EXPECT_TRUE(r1.containsRect(r4));
      
      EXPECT_TRUE(r1.containsPoint(Point(15, 15)));
      EXPECT_FALSE(r1.containsPoint(Point(-15, 15)));
      EXPECT_FALSE(r1.containsPoint(Point(15, 30)));
      
      EXPECT_TRUE(r1.contains(15, 15));
      EXPECT_FALSE(r1.contains(-15, 15));
      EXPECT_FALSE(r1.contains(15, 30));
   }
   
   TEST_F(RectangleTest, Operators)
   {
      Rectangle r1(100, 100, 50, 50);
      Rectangle r2(200, 200, 25, 25);
      Rectangle r3 = r1;
      
      EXPECT_FALSE(r1 == r2);
      EXPECT_TRUE(r1 != r2);
      EXPECT_TRUE(r3 == r1);
   }
}
