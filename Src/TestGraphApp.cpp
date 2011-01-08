#include "Application/SimpleApplication.h"
#include "Graph/Light.hpp"
#include "Graph/Camera.hpp"
#include "Graph/RenderVisitorOpenGL1.hpp"
#include "MeshLoaders/MeshFileLoader.h"
#include "MeshLoaders/MeshLoaderObj.h"

class TestGraphApp : public SimpleApplication {
public:
   TestGraphApp( ) : SimpleApplication("TestGraph", 800, 600)
   { /* */ };

   void Init(CompositeNode* root, MeshFileLoader* MeshLoader )
   {
      glDisable(GL_CULL_FACE);
      // glEnable(GL_CULL_FACE);
      // glCullFace(GL_BACK);
      // m = mfl->Load("Objects/cube.obj");
      // g = new Geometry(m, "Geometry");
      // g->SetMesh( m );
      
      Mesh* Magnolia = MeshLoader->Load("Objects/magnolia.obj");
      Magnolia->Scale(0.03f);
      Mesh* Rose = MeshLoader->Load("Objects/rose+vase.obj");
      Rose->Scale(0.03f);
      //Mesh* Dolphins = MeshLoader->Load("Objects/dolphins.obj");
	//Dolphins->Scale(0.01f);
      Mesh* Skyscraper = MeshLoader->Load("Objects/skyscraper.obj");
      Skyscraper->Scale(0.04f);
      
        
      // M3DVector4f color;
      // m3dLoadVector4( color, 0.0f, 1.0f, 0.0f, 1.0f );
      // l->SetDiffuse( color );
      // l->SetAmbient( color );

        M3DVector3f pos;
        m3dLoadVector3( pos, 0.0f, 0.0f, 50.0f );
      // Node* n = l->GetByName("GlobalCamera");
      // if (!n) {
      //    DLOG(ERROR) << "GlobalCamera not found!\n";
      //    exit( 1 );
      // }
      // c = dynamic_cast<Camera*>( n );
      // if (!c) {
      //    DLOG(ERROR) << "Cast failed!\n";
      //    exit( 1 );
      // }
      // c->SetPosition( pos );
     // c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,800.0f);
       //_camera.AddChild( g );
       _camera.SetPosition( pos );
      // root->AddChild( &_
	M3DVector4f color;
	m3dLoadVector4( color, 0.0f, 1.0f, 0.0f, 1.0f );
	_light.SetDiffuse( color );
	_light.SetAmbient( color );

	// M3DVector3f pos;
	// m3dLoadVector3( pos, 0.0f, 0.0f, 10.0f );

	// Init Camera
    //     Camera* c = reinterpret_cast<Camera*>(l->GetByName("GlobalCamera"));
    // c->SetPosition( pos );
    // c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);

	// Build Up Scenegraph
	_camera.AddChild(
		(new Transform(string("MagnoliaTransform")))->AddChild(
			(new Geometry(Magnolia, string("Magnolia")))
	));
        _camera.AddChild(
		(new Transform(string("RoseTransform")))->AddChild(
			(new Geometry(Rose, "Rose")))
	);
        _camera.AddChild(
		(new Transform(string("SkyscraperTransform")))->AddChild(
			(new Geometry(Skyscraper, "Skyscraper")))
	);

	Transform* t = reinterpret_cast<Transform*>(root->GetByName("MagnoliaTransform"));
	t->Rotate(20.0f, 1.0f, 1.0f, 1.0f);
	t->Translate(-3.0f, 0.0f, 0.0f);

	t = reinterpret_cast<Transform*>(root->GetByName("RoseTransform"));
	t->Translate(2.0f, 0.0f, 0.0f);
	t->Rotate(20.0f, 1.0f, 1.0f, 1.0f);
	t->Scale(1.6f, 1.2f, 1.2f);

	t = reinterpret_cast<Transform*>(root->GetByName("SkyscraperTransform"));
	t->Rotate(50.0f, 1.0f, 1.0f, 1.0f);
   };

   void Render( NodeVisitor* r, CompositeNode* c)
   { 
      // DLOG(INFO) << "Render()\n";
      r->Traverse( c );
      // DLOG(INFO) << "End of Render()\n";
   };
   
   void Update( CompositeNode* c )
   {
      // DLOG(INFO) << "Update()\n";
   };

   void Resize( int w, int h )
   {
      // DLOG(INFO) << "Resize()\n";
   };

private:
   Transform* t;
   Mesh* m;
   Geometry* g;
   // RenderVisitor r;
};

int main( int argc, char** argv )
{
   TestGraphApp app;
   DLOG(INFO) << "TestGraphApp has been created\n";
   // app.Init();
   // DLOG(INFO) << "TestGraphApp has been initialized\n";
   app.Start();
   return 0;
}
