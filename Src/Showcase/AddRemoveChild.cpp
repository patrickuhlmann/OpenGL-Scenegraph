#include "AddRemoveChild.h"

/**
 * \brief Just redirect to SimpleApplication Constructor and create a window with a width of 800 and height of 600 pixels
 */
AddRemoveChild::AddRemoveChild() : SimpleApplication("ObjectLoader", 800, 600) {

}

void AddRemoveChild::Init( CompositeNode* l, MeshFileLoader* MeshLoader) {
	// Init Camera
	Camera* c = reinterpret_cast<Camera*>(l->GetByName("GlobalCamera"));
	M3DVector3f pos;
	m3dLoadVector3( pos, 0.0f, 0.0f, 10.0f );
    c->SetPosition( pos );
    c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);

	Increasing = true;
	ChildCount = 0;
}

void AddRemoveChild::Update(CompositeNode* RootNode) {
	// Every 10th frame
	if (this->FrameCounter % 10 != 0)
		return;

	// We already have 10 and want to delete from now on
	if (Increasing && ChildCount == 10) {
		Increasing = false;
		cout << "Delete Mode" << endl;
		cout.flush();
	// We still need to add more
	} else if (Increasing) {
		Transform* t = new Transform(string("Cube")+IntegerToString(ChildCount));
		t->AddChild(new Geometry(new Cube(0.05f)));
		t->Translate(ChildCount / 10.0f + 0.05 * ChildCount - 0.8, 0, 0);
		RootNode->AddChild(t);
		cout << "Added " << ChildCount << endl;
		cout.flush();
		RootNode->PrintWholeTree(cout);
		ChildCount++;
	// We arrived at zero and need to add again
	} else if (!Increasing && ChildCount == 0) {
		Increasing = true;
		cout << "Adding Mode" << endl;
		cout.flush();
	// We still need to remove more	
	} else {
		ChildCount--;
		RootNode->RemoveChild(string("Cube")+IntegerToString(ChildCount));
		cout << "Deleted " << ChildCount << endl;
		RootNode->PrintWholeTree(cout);
		cout.flush();
	}
}

void AddRemoveChild::Render(NodeVisitor* RenderVisitor, CompositeNode* l)
{ 
	RenderVisitor->Visit(l);
};

void AddRemoveChild::Shutdown()
{ 
};

int main(int argc, char *argv[]) {
	AddRemoveChild App;
	App.Start();
}
