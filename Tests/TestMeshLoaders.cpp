#include "gtest/gtest.h"
#include "../Src/MeshLoaders/MeshFileLoader.h"
#include "../Src/MeshLoaders/MeshLoaderObj.h"

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
	MeshFileLoader l;
	l.AddMeshLoader(new MeshLoaderObj());
	Mesh* m = l.Load("Objects/cube.obj");
	//Mesh* m = l.Load("Objects/gourd.obj");
	//Mesh* m = l.Load("Objects/icosahedron.obj");
	//Mesh* m = l.Load("Objects/magnolia.obj");
	//Mesh* m = l.Load("Objects/octahedron.obj");
	//Mesh* m = l.Load("Objects/pyramid.obj");
	//Mesh* m = l.Load("Objects/teapot.obj");
	//Mesh* m = l.Load("Objects/tetrahedron.obj");

    EXPECT_TRUE(true);
}

// Initialization and entry point
int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
