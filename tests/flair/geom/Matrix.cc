#include "flair/geom/Matrix.h"
#include "flair/geom/Point.h"
#include "flair/geom/Rectangle.h"
#include "gtest/gtest.h"

namespace {
   using flair::geom::Matrix;
   using flair::geom::Rectangle;
   using flair::geom::Point;
   
   class MatrixTest : public ::testing::Test
   {
   protected:
      MatrixTest() {}
      virtual ~MatrixTest() {}
   };
   
   TEST_F(MatrixTest, Translate)
   {
      Matrix a;
      a.translate(10, 10);
      a.translate(10, 10);
      
      EXPECT_FLOAT_EQ(20, a.tx());
      EXPECT_FLOAT_EQ(20, a.ty());
      
   }
   
   TEST_F(MatrixTest, Rotate)
   {
      Matrix a;
      a.translate(10, 10);
      a.rotate(2*3.14f);
      
      EXPECT_FLOAT_EQ( 0.999994926f, a.a());
      EXPECT_FLOAT_EQ(-0.003185092f, a.b());
      EXPECT_FLOAT_EQ( 0.003185092f, a.c());
      EXPECT_FLOAT_EQ( 0.999994926f, a.d());
      EXPECT_FLOAT_EQ(10.031802287f, a.tx());
      EXPECT_FLOAT_EQ( 9.968098625f, a.ty());
   }
   
   TEST_F(MatrixTest, Scale)
   {
      Matrix a;
      a.translate(10, 10);
      a.rotate(2*3.14f);
      a.scale(2.0f, 2.0f);
      
      EXPECT_FLOAT_EQ( 1.9999899f, a.a());
      EXPECT_FLOAT_EQ(-0.006370184f, a.b());
      EXPECT_FLOAT_EQ( 0.006370184f, a.c());
      EXPECT_FLOAT_EQ( 1.9999899f, a.d());
      EXPECT_FLOAT_EQ(20.126999f, a.tx());
      EXPECT_FLOAT_EQ(19.872192f, a.ty());
   }
   
   TEST_F(MatrixTest, TransformPoint)
   {
      Matrix a;
      a.translate(10, 10);
      a.rotate(2*3.14f);
      a.scale(2.0f, 2.0f);
      Point p = a.transformPoint(Point(20, 15));
      
      EXPECT_FLOAT_EQ(60.222351f, p.x());
      EXPECT_FLOAT_EQ(49.744637f, p.y());
   }
   
   TEST_F(MatrixTest, DeltaTransformPoint)
   {
      Matrix a;
      a.translate(10, 10);
      a.rotate(2*3.14f);
      a.scale(2.0f, 2.0f);
      Point p = a.deltaTransformPoint(Point(20, 15));
      
      EXPECT_FLOAT_EQ(40.0953561f, p.x());
      EXPECT_FLOAT_EQ(29.8724357f, p.y());
   }
   
   TEST_F(MatrixTest, Invert)
   {
      Matrix a;
      a.translate(10, 10);
      a.rotate(2*3.14f);
      a.scale(2.0f, 2.0f);
      
      EXPECT_FLOAT_EQ( 1.9999899f, a.a());
      EXPECT_FLOAT_EQ(-0.006370184f, a.b());
      EXPECT_FLOAT_EQ( 0.006370184f, a.c());
      EXPECT_FLOAT_EQ( 1.9999899f, a.d());
      EXPECT_FLOAT_EQ(20.126999f, a.tx());
      EXPECT_FLOAT_EQ(19.872192f, a.ty());
      
      a.invert();
      
      EXPECT_FLOAT_EQ(  0.4999974f, a.a());
      EXPECT_FLOAT_EQ(  0.001592546f, a.b());
      EXPECT_FLOAT_EQ( -0.001592546f, a.c());
      EXPECT_FLOAT_EQ(  0.4999974f, a.d());
      EXPECT_FLOAT_EQ(-10.031801f, a.tx());
      EXPECT_FLOAT_EQ(-9.9680986f, a.ty());
   }
}
