#include "gtest/gtest.h"
#include "../Src/Graph/Node.hpp"

class DummyNode : public Node {
};

class TestNode : public ::testing::Test {
public:
   TestNode() {}
   
  // code called just before each test
  virtual void SetUp() {}
  
   // code called after each test
  virtual void TearDown() {} 
};

TEST_F(TestNode, test_TestNodeGetSetParent)
{
	Node* n = new DummyNode();
	Node* n2 = new DummyNode();

	// Parent 0 in beginning
	EXPECT_TRUE(n->GetParent() == 0);

	// Parent still 0 when setting itself as parent
	n->SetParent(n);
	EXPECT_TRUE(n->GetParent() == 0);

	// Parent n2 when setting n2
	n->SetParent(n2);
	EXPECT_TRUE(n->GetParent() == n2);

	delete n;
	delete n2;
}

TEST_F(TestNode, test_TestNodeGetSetName)
{
	Node* n = new DummyNode();

	// Name "" in the beginning
	EXPECT_EQ(n->GetName(), string(""));

	// Name changed to "Hallo"
	n->SetName(string("Hallo"));
	EXPECT_EQ(n->GetName(), string("Hallo"));

	delete n;
}

// Initialization and entry point
int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
