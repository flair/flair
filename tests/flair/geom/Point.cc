#include "flair/geom/Point.h"
#include "gtest/gtest.h"

namespace {
   using flair::geom::Point;
   
   class PointTest : public ::testing::Test
   {
   protected:
      PointTest() {}
      virtual ~PointTest() {}
   };
   
   
   TEST_F(PointTest, Length)
   {
      Point p(10, 10);
      float length = p.length();
      
      EXPECT_FLOAT_EQ(14.142136f, length);
   }
   
   
   TEST_F(PointTest, Normalize)
   {
      Point p(10, 10);
      p.normalize();
      
      EXPECT_FLOAT_EQ(0.707107f, p.x());
      EXPECT_FLOAT_EQ(0.707107f, p.y());
   }
   
   
   TEST_F(PointTest, Distance)
   {
      Point p1(10, 10);
      Point p2(324, 756);
      float distance = Point::distance(p1, p2);
      
      EXPECT_FLOAT_EQ(809.3899f, distance);
   }
   
   TEST_F(PointTest, Interpolate)
   {
      Point p1(10, 10);
      Point p2(324, 756);
      
      Point r = Point::interpolate(p1, p2, 0.0f);
      EXPECT_FLOAT_EQ(324, r.x());
      EXPECT_FLOAT_EQ(756, r.y());
      
      r = Point::interpolate(p1, p2, 0.123f);
      EXPECT_FLOAT_EQ(285.378, r.x());
      EXPECT_FLOAT_EQ(664.242, r.y());
      
      r = Point::interpolate(p1, p2, 0.78f);
      EXPECT_FLOAT_EQ(79.0800, r.x());
      EXPECT_FLOAT_EQ(174.12, r.y());
      
      r = Point::interpolate(p1, p2, 1.0f);
      EXPECT_FLOAT_EQ(10, r.x());
      EXPECT_FLOAT_EQ(10, r.y());
   }
   
   TEST_F(PointTest, Polar)
   {
      Point r = Point::polar(234.78f, 0.6789f);
      
      EXPECT_FLOAT_EQ(182.7208, r.x());
      EXPECT_FLOAT_EQ(147.4271, r.y());
   }
   
   TEST_F(PointTest, Operators)
   {
      Point p1(100, 100);
      Point p2(200, 200);
      Point p3 = p1;
      
      EXPECT_FALSE(p1 == p2);
      EXPECT_TRUE(p1 != p2);
      EXPECT_TRUE(p3 == p1);
   }
}
