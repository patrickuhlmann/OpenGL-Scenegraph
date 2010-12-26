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

	// Has Concave Polygons -> cannot triangulate
	//Mesh* m = l.Load("Objects/lamp.obj");
	//Mesh* m = l.Load("Objects/violin_case.obj");
	//Mesh* m = l.Load("Objects/trumpet.obj");
	//Mesh* m = l.Load("Objects/cessna.obj");
	//Mesh* m = l.Load("Objects/magnolia.obj");
	//Mesh* m = l.Load("Objects/slot_machine.obj");
	//Mesh* m = l.Load("Objects/skyscraper.obj");
	//Mesh* m = l.Load("Objects/sandal.obj");

	// Triangulation
	//Mesh* m = l.Load("Objects/humanoid_quad.obj");
	Mesh* m = l.Load("Objects/shuttle.obj");
	//Mesh* m = l.Load("Objects/power_lines.obj");
	//Mesh* m = l.Load("Objects/roi.obj");
	
	// Simple
	//Mesh* m = l.Load("Objects/humanoid_tri.obj");
	//Mesh* m = l.Load("Objects/cube.obj");
	//Mesh* m = l.Load("Objects/gourd.obj");
	//Mesh* m = l.Load("Objects/icosahedron.obj");
	//Mesh* m = l.Load("Objects/octahedron.obj");
	//Mesh* m = l.Load("Objects/pyramid.obj");
	//Mesh* m = l.Load("Objects/teapot.obj");
	//Mesh* m = l.Load("Objects/tetrahedron.obj");

	EXPECT_TRUE(m != 0);
}

// Initialization and entry point
int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
