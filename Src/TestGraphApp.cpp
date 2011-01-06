#include "Application/SimpleApplication.h"
#include "Graph/Light.hpp"
#include "Graph/Camera.hpp"
#include "Graph/RenderVisitor.hpp"
#include "MeshLoaders/MeshFileLoader.h"
#include "MeshLoaders/MeshLoaderObj.h"

class TestGraphApp : public SimpleApplication {
public:
   TestGraphApp() : SimpleApplication("TestGraph", 800, 600),
                    r( &ShaderManager )
   {};

   void Init()
   {
      // Transform* t1 = new Transform();
      // Transform* t2 = new Transform();
      // Transform* t3 = new Transform();

      MeshFileLoader mfl;
      mfl.AddMeshLoader( new MeshLoaderObj() );
      m = mfl.Load("Objects/tetrahedron.obj");
      g.SetMesh( m );
      
      M3DVector4f amb;
      m3dLoadVector4( amb, 128.0f, 128.0f, 128.0f, 0.0f );
      l.SetAmbient( amb );

      M3DVector3f pos;
      m3dLoadVector3( pos, 0.0f, 0.0f, 4.0f );
      c.SetPosition( pos );
      
      l.Add( &c );
      // c.Add( t1 );
      // c.Add( t2 );
      // c.Add( t3 );
      c.Add( &g );
     
   };

   void Render()
   { 
      r.Traverse( &l );
   };
   
private:
   Light l;
   Camera c;
   Transform t;
   Mesh* m;
   Geometry g;
   RenderVisitor r;
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
