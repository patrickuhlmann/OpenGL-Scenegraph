#include "ObjectsLoader.h"

/**
 * \brief Just redirect to SimpleApplication Constructor and create a window with a width of 800 and height of 600 pixels
 */
ObjectsLoader::ObjectsLoader() : SimpleApplication("ObjectLoader", 800, 600) {

}

void ObjectsLoader::Init( CompositeNode* l, MeshFileLoader* MeshLoader) {
	// Init Camera
	Camera* c = reinterpret_cast<Camera*>(l->GetByName("GlobalCamera"));
	M3DVector3f pos;
	m3dLoadVector3( pos, 0.0f, 0.0f, 10.0f );
    c->SetPosition( pos );
    c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);

	// Load some Meshes
	Mesh* Rose = MeshLoader->Load("Objects/rose+vase.obj");
	Mesh* Soccerball = MeshLoader->Load("Objects/soccerball.obj");
	Mesh* Slotmachine = MeshLoader->Load("Objects/slot_machine.obj");
	Mesh* F16 = MeshLoader->Load("Objects/f-16.obj");
	Mesh* Shuttle = MeshLoader->Load("Objects/shuttle.obj");
	Mesh* Cessna = MeshLoader->Load("Objects/cessna.obj");

	// Build up Scenegraph
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

void ObjectsLoader::Render(NodeVisitor* RenderVisitor, CompositeNode* l)
{ 
	RenderVisitor->Visit(l);
};

void ObjectsLoader::Shutdown()
{ 
};

int main(int argc, char *argv[]) {
	ObjectsLoader App;
	App.Start();
}
