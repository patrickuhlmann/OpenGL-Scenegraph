#include "Application/SimpleApplication.h"
#include "Graph/Light.hpp"
#include "Graph/Camera.hpp"
#include "Graph/RenderVisitor.hpp"


class TestGraphApp : public SimpleApplication {
public:
   TestGraphApp() : SimpleApplication("TestGraph", 800, 600),
                    r( &ShaderManager )
   {};

   void Init()
   {
 DLOG(INFO) << "Called Init()\n";
      l.Add( &c );
      DLOG(INFO) << "Light added Camera\n";
      r.Traverse( &l );
      DLOG(INFO) << "RenderVisitor traversed Light\n";
   };

   void Render()
   {
      
   };
   
private:
   Light l;
   Camera c;
   RenderVisitor r;
};

int main( int argc, char** argv )
{
   TestGraphApp app;
   DLOG(INFO) << "TestGraphApp has been created\n";
   app.Init();
   DLOG(INFO) << "TestGraphApp has been initialized\n";
   app.Start();
   return 0;
}
