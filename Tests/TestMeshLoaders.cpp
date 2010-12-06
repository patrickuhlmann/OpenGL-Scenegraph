#include "gtest/gtest.h"

using namespace std;

class TestMeshLoaders : public ::testing::Test {
public:
   TestMeshLoaders() {}
   
  // code called just before each test
  virtual void SetUp() {}
  
   // code called after each test
  virtual void TearDown() {} 

};

TEST_F(TestMeshLoaders, test_TestMeshLoaders)
{
    EXPECT_TRUE(false);
}

// Initialization and entry point
int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
