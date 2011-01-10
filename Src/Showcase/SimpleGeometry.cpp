#include "SimpleGeometry.h"

/**
 * \brief Just redirect to SimpleApplication Constructor and create a window with a width of 800 and height of 600 pixels
 */
SimpleGeometry::SimpleGeometry() : SimpleApplication("SimpleGeometry", 800, 600) {

}

void SimpleGeometry::Init( CompositeNode* l, MeshFileLoader* MeshLoader) {
	// Init Camera
	Camera* c = reinterpret_cast<Camera*>(l->GetByName("GlobalCamera"));
	M3DVector3f pos;
	m3dLoadVector3( pos, 0.0f, 0.0f, 10.0f );
    c->SetPosition( pos );
    c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);

	// Build Up Scenegraph
	c->AddChild(
		(new Transform(string("SphereTransform")))->AddChild(
			(new Geometry(new Sphere(1.0f, 100, 20), string("Sphere")))
	));
	c->AddChild(
		(new Transform(string("TorusTransform")))->AddChild(
			(new Geometry(new Torus(1.0f, 0.5f, 20, 20), string("Torus")))
	));
	c->AddChild(
		(new Transform(string("CubeTransform")))->AddChild(
			(new Geometry(new Cube(1.0f), string("Cube")))
	));

	Transform* t = reinterpret_cast<Transform*>(l->GetByName("TorusTransform"));
	t->Rotate(PI/8, 0, 1.0f, 0);
	t->Translate(-3.0f, 0.0f, 0.0f);

	t = reinterpret_cast<Transform*>(l->GetByName("CubeTransform"));
	t->Rotate(PI/8, 0, 1.0f, 0);
	t->Translate(3.0f, 0.0f, 0.0f);
}

void SimpleGeometry::Render(NodeVisitor* RenderVisitor, CompositeNode* l)
{ 
	RenderVisitor->Visit(l);
};

void SimpleGeometry::Shutdown()
{
};

int main(int argc, char *argv[]) {
	SimpleGeometry App;
	App.Start();
}
