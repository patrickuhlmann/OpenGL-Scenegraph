#include "SkeletonApp.h"

/**
 * \brief Just redirect to SimpleApplication Constructor and create a window called Skeleton with a width of 800 and height of 600 pixels
 */
SkeletonApp::SkeletonApp() : SimpleApplication("Skeleton", 800, 600) {

}

void SkeletonApp::Init( Light* l, MeshFileLoader* MeshLoader) {
	/* ====
     * Problem Objects
     * ==== */

	//Mesh* M = MeshLoader->Load("Objects/shuttle.obj");
	//M->Scale(0.5f);

	//Mesh* M = MeshLoader->Load("Objects/violin_case.obj");

	//Mesh* M = MeshLoader->Load("Objects/al.obj");

	//Mesh* M = MeshLoader->Load("Objects/cessna.obj");
	//M->Scale(0.2f);

	//Mesh* M = MeshLoader->Load("Objects/f-16.obj");
	//M->Scale(0.5f);

	//Mesh* M = MeshLoader->Load("Objects/flowers.obj");
	//M->Scale(0.2f);

	//Mesh* M = MeshLoader->Load("Objects/lamp.obj");
	//M->Scale(0.5f);

	// Holes?
	// Material?
	//Mesh* M = MeshLoader->Load("Objects/porsche.obj");
	//M->Scale(0.2f);

	// Holes?
	//Mesh* M = MeshLoader->Load("Objects/power_lines.obj");
	//M->Scale(0.05f);

	// Holes?
	//Mesh* M = MeshLoader->Load("Objects/sandal.obj");
	
	// Holes?, Material?
	//Mesh* M = MeshLoader->Load("Objects/slot_machine.obj");
	//M->Scale(0.2f);

	// Holes, Material?
	//Mesh* M = MeshLoader->Load("Objects/soccerball.obj");
	//M->Scale(0.2f);

	// Invisible
	//Mesh* M = MeshLoader->Load("Objects/trumpet.obj");
	//M->Scale(0.1f);




	/* ====
     * Nice Objects with Material
     * ==== */

	//Mesh* Magnolia = MeshLoader->Load("Objects/magnolia.obj");
	//Magnolia->Scale(0.05f);
	Mesh* Rose = MeshLoader->Load("Objects/rose+vase.obj");
	Rose->Scale(0.05f);
	//Mesh* Dolphins = MeshLoader->Load("Objects/dolphins.obj");
	//Dolphins->Scale(0.01f);
	//Mesh* M = MeshLoader->Load("Objects/skyscraper.obj");
	//M->Scale(0.1f);



	/* ======
     * Boring Objects without Material
     * ====== */

	/*Mesh* Humanoid = MeshLoader->Load("Objects/humanoid_tri.obj");
	Humanoid->Scale(0.5f);
	Mesh* Cube = MeshLoader->Load("Objects/cube.obj");
	Mesh* Gourd = MeshLoader->Load("Objects/gourd.obj");*/
	//Mesh* M = MeshLoader->Load("Objects/icosahedron.obj");
	//Mesh* M = MeshLoader->Load("Objects/octahedron.obj");
	//Mesh* M = MeshLoader->Load("Objects/tetrahedron.obj");
	//Mesh* M = MeshLoader->Load("Objects/humanoid_quad.obj");

	//Mesh* Teapot = MeshLoader->Load("Objects/teapot.obj");
	//Teapot->Scale(0.05f);

	
	


	M3DVector4f color;
	m3dLoadVector4( color, 0.0f, 1.0f, 0.0f, 1.0f );
	l->SetDiffuse( color );
	l->SetAmbient( color );

	M3DVector3f pos;
	m3dLoadVector3( pos, 0.0f, 0.0f, 10.0f );

	// Init Camera
	Camera* c = reinterpret_cast<Camera*>(l->GetByName("GlobalCamera"));
    c->SetPosition( pos );
    c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);

	c->AddChild(new Geometry(Rose));

	/*// Build Up Scenegraph
	c->AddChild(
		(new Transform(string("GourdTransform")))->AddChild(
			(new Geometry(Gourd, string("Gourd")))
	));
	c->AddChild(
		(new Transform(string("HumanoidTransform")))->AddChild(
			(new Geometry(Humanoid, "Humanoid")))
	);
	c->AddChild(
		(new Transform(string("CubeTransform")))->AddChild(
			(new Geometry(Cube, "Cube")))
	);

	Transform* t = reinterpret_cast<Transform*>(l->GetByName("HumanoidTransform"));
	t->Translate(-5.0f, 0.0f, 0.0f);

	t = reinterpret_cast<Transform*>(l->GetByName("CubeTransform"));
	t->Translate(2.0f, 0.0f, 0.0f);
	t->Scale(1.6f, 1.2f, 1.2f);

	t = reinterpret_cast<Transform*>(l->GetByName("GourdTransform"));
	t->Rotate(50.0f, 1.0f, 1.0f, 1.0f);*/
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
