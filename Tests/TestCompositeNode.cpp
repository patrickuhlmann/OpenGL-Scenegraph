#include "gtest/gtest.h"
#include "../Src/Graph/CompositeNode.hpp"

class DummyNode : public CompositeNode {
public:
	DummyNode() : CompositeNode() { }

	DummyNode(string name) : CompositeNode(name) {

	}
};

class TestCompositeNode : public ::testing::Test {
public:
   TestCompositeNode() {}
   
  // code called just before each test
  virtual void SetUp() {}
  
   // code called after each test
  virtual void TearDown() {} 
};

TEST_F(TestCompositeNode, test_TestAddRemoveChild)
{
	CompositeNode* n = new DummyNode();
	CompositeNode* n2 = new DummyNode();
	CompositeNode* n3 = new DummyNode();

	// Parent 0 in beginning
	EXPECT_TRUE(n2->GetParent() == 0);

	// n becomes parent of n2 if we add n2 as child to n
	n->AddChild(n2);
	EXPECT_TRUE(n2->GetParent() == n);

	// n3 becomes parent of n2 if we add n2 as child to n, n has it no longer as child
	n3->AddChild(n2);
	EXPECT_TRUE(n2->GetParent() == n3);
	EXPECT_TRUE(n3->GetChildrenCount() == 1);
	EXPECT_FALSE(n->Contains(n2));

	// n has no childs, if we remove n2 nothing happens
	n->RemoveChild(n2);
	EXPECT_TRUE(n2->GetParent() == n3);
	
	// if we remove n2 from n3 it has no more children
	n3->RemoveChild(n2);
	EXPECT_TRUE(n2->GetParent() == 0);
	EXPECT_TRUE(n3->GetChildrenCount() == 0);

	delete n;
	delete n2;
	delete n3;
}

TEST_F(TestCompositeNode, test_TestIterator)
{
	CompositeNode* n = new DummyNode();
	CompositeNode* n2 = new DummyNode();
	CompositeNode* n3 = new DummyNode();
	CompositeNode* n4 = new DummyNode();

	n->AddChild(n2);
	n->AddChild(n3);
	n->AddChild(n4);

	NodeIterator it = n->GetNodeIterator();
	EXPECT_TRUE(*it == n2);
	it++;
	EXPECT_TRUE(*it == n3);
	it++;
	EXPECT_TRUE(*it == n4);
	it++;
	EXPECT_TRUE(*it == *n->GetNodeIteratorEnd());

	delete n4;
	delete n3;
	delete n2;
	delete n;
}

TEST_F(TestCompositeNode, test_TestContains)
{
	CompositeNode* n = new DummyNode();
	CompositeNode* n2 = new DummyNode();
	CompositeNode* n3 = new DummyNode();

	n->AddChild(n2);

	EXPECT_TRUE(n->Contains(n2));
	EXPECT_FALSE(n->Contains(n3));

	delete n3;
	delete n2;
	delete n;
}

TEST_F(TestCompositeNode, test_TestGetChildrenCount)
{
	CompositeNode* n = new DummyNode();
	CompositeNode* n2 = new DummyNode();
	CompositeNode* n3 = new DummyNode();

	n->AddChild(n2);
	n->AddChild(n3);

	EXPECT_EQ(n->GetChildrenCount(), 2);
	EXPECT_EQ(n2->GetChildrenCount(), 0);

	delete n3;
	delete n2;
	delete n;
}

TEST_F(TestCompositeNode, test_TestGetByName)
{
	CompositeNode* n = new DummyNode(string("1"));
	CompositeNode* n2 = new DummyNode("2");
	CompositeNode* n3 = new DummyNode("3");

	n->AddChild(n2);
	n2->AddChild(n3);

	EXPECT_TRUE(n->GetByName("2") == n2);
	EXPECT_TRUE(n->GetByName("3") == n3);
	EXPECT_TRUE(n->GetByName("1") == n);
	EXPECT_TRUE(n2->GetByName("1") == 0);

	delete n3;
	delete n2;
	delete n;
}

// Initialization and entry point
int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
