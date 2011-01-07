#include "Application/SimpleApplication.h"
#include "Graph/Light.hpp"
#include "Graph/Camera.hpp"
#include "Graph/RenderVisitor.hpp"
#include "MeshLoaders/MeshFileLoader.h"
#include "MeshLoaders/MeshLoaderObj.h"

class TestGraphApp : public SimpleApplication {
public:
   TestGraphApp( ) : SimpleApplication("TestGraph", 800, 600) { /* */ };

   void Init( Light* l, MeshFileLoader* mfl )
   {
      m = mfl->Load("Objects/cube.obj");
      g.SetMesh( m );
      
      M3DVector4f color;
      m3dLoadVector4( color, 0.0f, 1.0f, 0.0f, 1.0f );
      l->SetDiffuse( color );
      l->SetAmbient( color );

      M3DVector3f pos;
      m3dLoadVector3( pos, 0.0f, 0.0f, 10.0f );
      Node* n = l->GetByName("GlobalCamera");
      if (!n) {
         DLOG(ERROR) << "GlobalCamera not found!\n";
         exit( 1 );
      }
      c = dynamic_cast<Camera*>( n );
      if (!c) {
         DLOG(ERROR) << "Cast failed!\n";
         exit( 1 );
      }
      c->SetPosition( pos );
      c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);
      c->AddChild( &g );
     
   };

   void Render( RenderVisitor* r, Light* l)
   { 
      // DLOG(INFO) << "Render()\n";
      r->Traverse( l );
      // DLOG(INFO) << "End of Render()\n";
   };
   
   void Update( Light* l )
   {
      DLOG(INFO) << "Update()\n";
   };

   void Resize( int w, int h )
   {
      DLOG(INFO) << "Resize()\n";
   };

private:
   // Light l;
    Camera* c;
   Transform t;
   Mesh* m;
   Geometry g;
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
