#include "gtest/gtest.h"
#include "Tree.hpp"

TEST(Tree, Builder){
	Tree t;
	EXPECT_TRUE(t.getRoot()==NULL);
}

TEST(Tree, getSon_and_parent_empty){
	Tree t;
	EXPECT_TRUE(t.getParent(t.getRoot())==NULL);
	EXPECT_EQ(t.getSons(t.getRoot()).size(),0);
}

TEST(Tree, tree_build){
	Tree t;
	Point2D p0(0,0);
	Point2D p1(1,1);
	Point2D p2(2,2);
	Point2D p3(3,3);
	Point2D p4(4,4);
	Vertex* v0=new Vertex(p0);
	Vertex* v1=new Vertex(p1);
	Vertex* v2=new Vertex(p2);
	Vertex* v3=new Vertex(p3);
	Vertex* v4=new Vertex(p4);
	t.setRoot(v0);
	EXPECT_TRUE(t.getParent(t.getRoot())==NULL);
	EXPECT_EQ(t.getSons(t.getRoot()).size(),0);

	Edge* e0=new Edge(t.getRoot(), v1);
	t.getRoot()->addEdge(e0);
	v1->addEdge(e0);

	Edge* e1=new Edge(t.getRoot(), v2);
	t.getRoot()->addEdge(e1);
	v1->addEdge(e1);

	Edge* e2=new Edge(v2, v3);
	v2->addEdge(e2);
	v3->addEdge(e2);

	Edge* e3=new Edge(v2, v4);
	v2->addEdge(e3);
	v4->addEdge(e3);

	EXPECT_EQ(t.getSons(t.getRoot()).size(),2);

	Vertex* vaux;
	vaux=t.getSons(t.getRoot())[0];
	EXPECT_EQ(vaux,v1);
	vaux=t.getSons(t.getRoot())[1];
	EXPECT_EQ(vaux,v2);

	Vertex* vaux2;
	vaux2=t.getSons(vaux)[0];
	EXPECT_EQ(vaux2,v3);
	vaux2=t.getSons(vaux)[1];
	EXPECT_EQ(vaux2,v4);
}

TEST(Tree, getAllVertexes){
	Tree t;
	Point2D p0(0,0);
	Point2D p1(1,1);
	Point2D p2(2,2);
	Point2D p3(3,3);
	Point2D p4(4,4);
	Vertex* v0=new Vertex(p0);
	Vertex* v1=new Vertex(p1);
	Vertex* v2=new Vertex(p2);
	Vertex* v3=new Vertex(p3);
	Vertex* v4=new Vertex(p4);
	t.setRoot(v0);
	EXPECT_TRUE(t.getParent(t.getRoot())==NULL);
	EXPECT_EQ(t.getSons(t.getRoot()).size(),0);

	Edge* e0=new Edge(t.getRoot(), v1);
	t.getRoot()->addEdge(e0);
	v1->addEdge(e0);

	Edge* e1=new Edge(t.getRoot(), v2);
	t.getRoot()->addEdge(e1);
	v1->addEdge(e1);

	Edge* e2=new Edge(v2, v3);
	v2->addEdge(e2);
	v3->addEdge(e2);

	Edge* e3=new Edge(v2, v4);
	v2->addEdge(e3);
	v4->addEdge(e3);
	std::vector<Vertex*> list = t.getAllVertexes();
	EXPECT_EQ(list.size(),5);
	EXPECT_NE(list[0],v2);
	EXPECT_EQ(list[0],v0);
	EXPECT_EQ(list[1],v1);
	EXPECT_EQ(list[2],v2);
	EXPECT_EQ(list[3],v3);
	EXPECT_EQ(list[4],v4);
}

// TEST(Tree, print){
// 	Tree t;
// 	Point2D p0(0,0);
// 	Point2D p1(1,1);
// 	Point2D p2(2,2);
// 	Point2D p3(3,3);
// 	Point2D p4(4,4);
// 	Vertex* v0=new Vertex(p0);
// 	Vertex* v1=new Vertex(p1);
// 	Vertex* v2=new Vertex(p2);
// 	Vertex* v3=new Vertex(p3);
// 	Vertex* v4=new Vertex(p4);
// 	t.setRoot(v0);
// 	EXPECT_TRUE(t.getParent(t.getRoot())==NULL);
// 	EXPECT_EQ(t.getSons(t.getRoot()).size(),0);
//
// 	Edge* e0=new Edge(t.getRoot(), v1);
// 	t.getRoot()->addEdge(e0);
// 	v1->addEdge(e0);
//
// 	Edge* e1=new Edge(t.getRoot(), v2);
// 	t.getRoot()->addEdge(e1);
// 	v1->addEdge(e1);
//
// 	Edge* e2=new Edge(v2, v3);
// 	v2->addEdge(e2);
// 	v3->addEdge(e2);
//
// 	Edge* e3=new Edge(v2, v4);
// 	v2->addEdge(e3);
// 	v4->addEdge(e3);
//
// 	t.printTree();
// 	std::string response;
// 	std::cout << "is this ok? [y/n]\n\t-> ";
// 	std::cin >> response;
// 	EXPECT_EQ(response,"y");
// }
