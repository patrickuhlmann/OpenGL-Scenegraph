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
	
	// Simple
	//Mesh* m = l.Load("Objects/humanoid_tri.obj");
	//Mesh* m = l.Load("Objects/cube.obj");
	//Mesh* m = l.Load("Objects/gourd.obj");
	//Mesh* m = l.Load("Objects/icosahedron.obj");
	//Mesh* m = l.Load("Objects/octahedron.obj");
	//Mesh* m = l.Load("Objects/teapot.obj");
	Mesh* m = l.Load("Objects/tetrahedron.obj");
	//Mesh* m = l.Load("Objects/dolphins.obj");
	//Mesh* m = l.Load("Objects/rose+vase.obj");

	// Convex Triangulation
	//Mesh* m = l.Load("Objects/shuttle.obj");
	//Mesh* m = l.Load("Objects/humanoid_quad.obj");
	//Mesh* m = l.Load("Objects/power_lines.obj");
	//Mesh* m = l.Load("Objects/roi.obj");
	//Mesh* m = l.Load("Objects/soccerball.obj");

	// Has Concave Polygons
	//Mesh* m = l.Load("Objects/f-16.obj");
	//Mesh* m = l.Load("Objects/flowers.obj");
	//Mesh* m = l.Load("Objects/porsche.obj");
	//Mesh* m = l.Load("Objects/al.obj");
	//Mesh* m = l.Load("Objects/lamp.obj");
	//Mesh* m = l.Load("Objects/violin_case.obj");
	//Mesh* m = l.Load("Objects/trumpet.obj");
	//Mesh* m = l.Load("Objects/cessna.obj");
	//Mesh* m = l.Load("Objects/magnolia.obj");
	//Mesh* m = l.Load("Objects/slot_machine.obj");
	//Mesh* m = l.Load("Objects/skyscraper.obj");
	//Mesh* m = l.Load("Objects/sandal.obj");

	EXPECT_TRUE(m != 0);
}

TEST_F(TestMeshLoaders, test_TestMeshLoaderObjTetrahedron)
{
	MeshFileLoader l;
	l.AddMeshLoader(new MeshLoaderObj());
	Mesh* m = l.Load("Objects/tetrahedron.obj");

	// Test the Vertices
	const float* v = m->GetVertex(0);
	ASSERT_FLOAT_EQ(v[0], 1.00f);
	ASSERT_FLOAT_EQ(v[1], 1.00f);
	ASSERT_FLOAT_EQ(v[2], 1.00f);
	v = m->GetVertex(3);
	ASSERT_FLOAT_EQ(v[0], 1.00f);
	ASSERT_FLOAT_EQ(v[1], 1.00f);
	ASSERT_FLOAT_EQ(v[2], 2.00f);
	
	// Test the Triangles
	Triangle t = m->GetTriangle(0);
	EXPECT_EQ(t.vert1, 0);
	EXPECT_EQ(t.vert2, 2);
	EXPECT_EQ(t.vert3, 1);
	t = m->GetTriangle(3);
	EXPECT_EQ(t.vert1, 1);
	EXPECT_EQ(t.vert2, 2);
	EXPECT_EQ(t.vert3, 3);

	// Test the Normals
	const float* n = m->GetNormal(0);
	EXPECT_EQ(n[0], 0);
	EXPECT_EQ(n[1], 0);
	EXPECT_EQ(n[2], -1.0f);
	n = m->GetNormal(3);
	EXPECT_EQ(n[0], 1.0f);
	EXPECT_EQ(n[1], 1.0f);
	EXPECT_EQ(n[2], 1.0f);
	
	// Test the TextureCoord
	const float* c = m->GetTextureCoord(0);
	ASSERT_FLOAT_EQ(c[0], 0.00f);
	ASSERT_FLOAT_EQ(c[1], 0.00f);
	c = m->GetTextureCoord(3);
	ASSERT_FLOAT_EQ(c[0], 0.00f);
	ASSERT_FLOAT_EQ(c[1], 0.00f);
}

// Initialization and entry point
int main(int argc, char** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
