#include "gtest/gtest.h"
#include "Vertex.hpp"

TEST(Vertex, Default_builder){
	Point2D p(1,2);
	Vertex v;
	v.setPoint(p);
	EXPECT_EQ(v.getPoint(),p);
}

TEST(Vertex, parametrized_builder){
	Point2D p(1,2);
	Vertex v(p);
	v.setPoint(p);
	EXPECT_EQ(v.getPoint(),p);
}

TEST(Vertex, edges){
	Edge e1;
	Edge e2;
	Edge e3;
	Point2D p(1,2);
	Vertex v(p);
	EXPECT_EQ(v.getEdges().size(),0);
	v.addEdge(&e1);
	v.addEdge(&e1);
	EXPECT_EQ(v.getEdges().size(),1);
	EXPECT_EQ(v.getEdges()[0],&e1);
	v.addEdge(&e2);
	v.addEdge(&e3);
	v.addEdge(&e1);
	EXPECT_EQ(v.getEdges().size(),3);
	EXPECT_EQ(v.getEdges()[0],&e1);
	EXPECT_EQ(v.getEdges()[1],&e2);
	EXPECT_EQ(v.getEdges()[2],&e3);
	v.removeEdge(&e2);
	EXPECT_EQ(v.getEdges().size(),2);
	EXPECT_EQ(v.getEdges()[0],&e1);
	EXPECT_EQ(v.getEdges()[1],&e3);
}

TEST(Vertex, operators){
	Vertex v1(Point2D(1,1));
	Vertex v2(Point2D(2,2));
	EXPECT_TRUE(v1.getPoint()==Point2D(1,1));
	EXPECT_TRUE(v2.getPoint()==Point2D(2,2));
	EXPECT_FALSE(v1==v2);
	v1=v2;
	EXPECT_TRUE(v1.getPoint()==Point2D(2,2));
	EXPECT_TRUE(v2.getPoint()==Point2D(2,2));
	EXPECT_TRUE(v1==v2);
}


TEST(Vertex, more_operators){
	Vertex v1(Point2D(1,1));
	Vertex v2(Point2D(2,2));
	EXPECT_TRUE(v1.getPoint()==Point2D(1,1));
	EXPECT_TRUE(v2.getPoint()==Point2D(2,2));
	EXPECT_TRUE(v1!=v2);
	v1=v2;
	EXPECT_TRUE(v1.getPoint()==Point2D(2,2));
	EXPECT_TRUE(v2.getPoint()==Point2D(2,2));
	EXPECT_FALSE(v1!=v2);
}
