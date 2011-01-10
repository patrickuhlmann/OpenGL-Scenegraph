#include "SkeletonApp.h"

/**
 * \brief Just redirect to SimpleApplication Constructor and create a window called Skeleton with a width of 800 and height of 600 pixels
 */
SkeletonApp::SkeletonApp() : SimpleApplication("Skeleton", 800, 600) {

}

void SkeletonApp::Init( CompositeNode* l, MeshFileLoader* MeshLoader) {

	// Init Camera
	Camera* c = reinterpret_cast<Camera*>(l->GetByName("GlobalCamera"));
	M3DVector3f pos;
	m3dLoadVector3( pos, 0.0f, 0.0f, 10.0f );
    c->SetPosition( pos );
    c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);

	/* ====
     * Problem Objects
     * ==== */

	// No Material?
	//Mesh* Flowers = MeshLoader->Load("Objects/flowers.obj");
	//Flowers->Scale(0.2f);

	// Invisible, Material?
	//Mesh* Trumpet = MeshLoader->Load("Objects/trumpet.obj");
	//Trumpet->Scale(0.1f);


	/* ====
     * Nice Objects with Material
     * ==== */

	Mesh* Rose = MeshLoader->Load("Objects/rose+vase.obj");
	Mesh* Soccerball = MeshLoader->Load("Objects/soccerball.obj");
	Mesh* Slotmachine = MeshLoader->Load("Objects/slot_machine.obj");
	Mesh* F16 = MeshLoader->Load("Objects/f-16.obj");
	Mesh* Shuttle = MeshLoader->Load("Objects/shuttle.obj");
	Mesh* Cessna = MeshLoader->Load("Objects/cessna.obj");

	//Mesh* Porsche = MeshLoader->Load("Objects/porsche.obj");
	//Porsche->Scale(0.1f);

	//Mesh* ViolinCase = MeshLoader->Load("Objects/violin_case.obj");

	//Mesh* Magnolia = MeshLoader->Load("Objects/magnolia.obj");
	//Magnolia->Scale(0.03f);
	//Mesh* Skyscraper = MeshLoader->Load("Objects/skyscraper.obj");
	//Skyscraper->Scale(0.04f);
	
	//Mesh* Sandal = MeshLoader->Load("Objects/sandal.obj");

	//Mesh* Lamp = MeshLoader->Load("Objects/lamp.obj");
	//Lamp->Scale(0.4f);

	//Mesh* PowerLines = MeshLoader->Load("Objects/power_lines.obj");
	//PowerLines->Scale(0.05f);

	/* ======
     * Boring Objects without Material
     * ====== */

	//Mesh* Humanoid = MeshLoader->Load("Objects/humanoid_tri.obj");
	//Humanoid->Scale(0.5f);
	//Mesh* Cube = MeshLoader->Load("Objects/cube.obj");
	//Mesh* Gourd = MeshLoader->Load("Objects/gourd.obj");*/
	//Mesh* M = MeshLoader->Load("Objects/icosahedron.obj");
	//Mesh* M = MeshLoader->Load("Objects/octahedron.obj");
	//Mesh* M = MeshLoader->Load("Objects/tetrahedron.obj");
	//Mesh* M = MeshLoader->Load("Objects/humanoid_quad.obj");
	//Mesh* Dolphins = MeshLoader->Load("Objects/dolphins.obj");
	//Dolphins->Scale(0.01f);
	//Mesh* Teapot = MeshLoader->Load("Objects/teapot.obj");
	//Teapot->Scale(0.05f);
	//Mesh* Al = MeshLoader->Load("Objects/al.obj");

	c->AddChild(
		(new Transform(string("SlotMachineTransform")))->AddChild(
			(new Geometry(Slotmachine, string("SlotMachine")))
	));
	c->AddChild(
		(new Transform(string("RoseTransform")))->AddChild(
			(new Geometry(Rose, "Rose")))
	);
	c->AddChild(
		(new Transform(string("SoccerballTransform")))->AddChild(
			(new Geometry(Soccerball, "Soccerball")))
	);
	c->AddChild(
		(new Transform(string("F16Transform")))->AddChild(
			(new Geometry(F16, "F16")))
	);
	c->AddChild(
		(new Transform(string("ShuttleTransform")))->AddChild(
			(new Geometry(Shuttle, "Shuttle")))
	);
	c->AddChild(
		(new Transform(string("CessnaTransform")))->AddChild(
			(new Geometry(Cessna, "Cessna")))
	);

	Transform* t = reinterpret_cast<Transform*>(l->GetByName("SlotMachineTransform"));
	t->Translate(-3.0f, 0.0f, 0.0f);
	t->Scale(0.1f, 0.1f, 0.1f);

	t = reinterpret_cast<Transform*>(l->GetByName("RoseTransform"));
	t->Translate(2.0f, 0.0f, 0.0f);
	t->Scale(0.02f, 0.02f, 0.02f);

	t = reinterpret_cast<Transform*>(l->GetByName("SoccerballTransform"));
	t->Scale(0.15f, 0.15f, 0.15f);

	t = reinterpret_cast<Transform*>(l->GetByName("F16Transform"));
	t->Translate(4.0f, 1.2f, 0.0f);
	t->Scale(0.4f, 0.4f, 0.4f);

	t = reinterpret_cast<Transform*>(l->GetByName("ShuttleTransform"));
	t->Translate(-3.5f, 2.3f, 0.0f);
	t->Scale(0.2f, 0.2f, 0.2f);

	t = reinterpret_cast<Transform*>(l->GetByName("CessnaTransform"));
	t->Translate(0.0f, 2.5f, 0.0f);
	t->Scale(0.05f, 0.05f, 0.05f);
}

void SkeletonApp::Render(NodeVisitor* RenderVisitor, CompositeNode* l)
{ 
	RenderVisitor->Visit(l);
};

void SkeletonApp::Shutdown()
{ 
};

int main(int argc, char *argv[]) {
	SkeletonApp App;
	App.Start();
}
