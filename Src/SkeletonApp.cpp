#include "SkeletonApp.h"

/**
 * \brief Just redirect to SimpleApplication Constructor and create a window called Skeleton with a width of 800 and height of 600 pixels
 */
SkeletonApp::SkeletonApp() : SimpleApplication("Skeleton", 800, 600) {

}

void SkeletonApp::Init( Light* l, MeshFileLoader* MeshLoader) {
	//Mesh* M = MeshLoader->Load("Objects/humanoid_tri.obj");
	//Mesh* M = MeshLoader->Load("Objects/cube.obj");
	//Mesh* M = MeshLoader->Load("Objects/gourd.obj");
	//Mesh* M = MeshLoader->Load("Objects/icosahedron.obj");
	//Mesh* M = MeshLoader->Load("Objects/octahedron.obj");
	//Mesh* M = MeshLoader->Load("Objects/tetrahedron.obj");

	// Visible to big
	Mesh* M = MeshLoader->Load("Objects/rose+vase.obj");
	//Mesh* M = MeshLoader->Load("Objects/teapot.obj");

	// Invisible	
	// Mesh* M = MeshLoader->Load("Objects/dolphins.obj");


	M3DVector4f color;
	m3dLoadVector4( color, 0.0f, 1.0f, 0.0f, 1.0f );
	l->SetDiffuse( color );
	l->SetAmbient( color );

	M3DVector3f pos;
	m3dLoadVector3( pos, 0.0f, 0.0f, 100.0f );

	Camera* c = reinterpret_cast<Camera*>(l->GetByName("GlobalCamera"));
    c->SetPosition( pos );
    c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);
	c->AddChild(new Geometry(M));
}

void SkeletonApp::Render(NodeVisitor* RenderVisitor, Light* l)
{ 
	DLOG(INFO) << "Render()\n";
	RenderVisitor->Traverse(l);
	DLOG(INFO) << "End of Render()\n";
};

int main(int argc, char *argv[]) {
	SkeletonApp App;
	App.Start();
}
