#include "SkeletonApp.h"

/**
 * \brief Just redirect to SimpleApplication Constructor and create a window called Skeleton with a width of 800 and height of 600 pixels
 */
SkeletonApp::SkeletonApp() : SimpleApplication("Skeleton", 800, 600) {

}

void SkeletonApp::Init( CompositeNode* l, MeshFileLoader* MeshLoader) {
	/* ====
     * Problem Objects
     * ==== */

	//Mesh* Shuttle = MeshLoader->Load("Objects/shuttle.obj");
	//Shuttle->Scale(0.5f);

	//Mesh* ViolinCase = MeshLoader->Load("Objects/violin_case.obj");

	//Mesh* Cessna = MeshLoader->Load("Objects/cessna.obj");
	//Cessna->Scale(0.2f);

	//Mesh* F16 = MeshLoader->Load("Objects/f-16.obj");
	//F16->Scale(0.5f);

	//Mesh* Lamp = MeshLoader->Load("Objects/lamp.obj");
	//Lamp->Scale(0.4f);

	//Mesh* Porsche = MeshLoader->Load("Objects/porsche.obj");
	//Porsche->Scale(0.1f);

	//Mesh* PowerLines = MeshLoader->Load("Objects/power_lines.obj");
	//PowerLines->Scale(0.05f);

	//Mesh* Sandal = MeshLoader->Load("Objects/sandal.obj");

	//Mesh* SlotMachine = MeshLoader->Load("Objects/slot_machine.obj");
	//SlotMachine->Scale(0.2f);

	//Mesh* M = MeshLoader->Load("Objects/soccerball.obj");
	//M->Scale(0.2f);

	//Mesh* Al = MeshLoader->Load("Objects/al.obj");
	//Mesh* Flowers = MeshLoader->Load("Objects/flowers.obj");
	//Flowers->Scale(0.2f);

	// Invisible
	//Mesh* M = MeshLoader->Load("Objects/trumpet.obj");
	//M->Scale(0.1f);




	/* ====
     * Nice Objects with Material
     * ==== */

	Mesh* Magnolia = MeshLoader->Load("Objects/magnolia.obj");
	Magnolia->Scale(0.03f);
	Mesh* Rose = MeshLoader->Load("Objects/rose+vase.obj");
	Rose->Scale(0.03f);
	Mesh* Skyscraper = MeshLoader->Load("Objects/skyscraper.obj");
	Skyscraper->Scale(0.04f);



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

	M3DVector3f pos;
	m3dLoadVector3( pos, 0.0f, 0.0f, 10.0f );

	// Init Camera
	Camera* c = reinterpret_cast<Camera*>(l->GetByName("GlobalCamera"));
    c->SetPosition( pos );
    c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);

	// Build Up Scenegraph
	c->AddChild(
		(new Transform(string("MagnoliaTransform")))->AddChild(
			(new Geometry(Magnolia, string("Magnolia")))
	));
	c->AddChild(
		(new Transform(string("RoseTransform")))->AddChild(
			(new Geometry(Rose, "Rose")))
	);
	c->AddChild(
		(new Transform(string("SkyscraperTransform")))->AddChild(
			(new Geometry(Skyscraper, "Skyscraper")))
	);

	Transform* t = reinterpret_cast<Transform*>(l->GetByName("MagnoliaTransform"));
	t->Translate(-3.0f, 0.0f, 0.0f);

	t = reinterpret_cast<Transform*>(l->GetByName("RoseTransform"));
	t->Translate(2.0f, 0.0f, 0.0f);
	t->Scale(1.6f, 1.2f, 1.2f);

	t = reinterpret_cast<Transform*>(l->GetByName("SkyscraperTransform"));
}

void SkeletonApp::Render(NodeVisitor* RenderVisitor, CompositeNode* l)
{ 
	//DLOG(INFO) << "Render()\n";
	RenderVisitor->Traverse(l);
	//DLOG(INFO) << "End of Render()\n";
};

void SkeletonApp::Shutdown()
{ 
};

int main(int argc, char *argv[]) {
	SkeletonApp App;
	App.Start();
}
