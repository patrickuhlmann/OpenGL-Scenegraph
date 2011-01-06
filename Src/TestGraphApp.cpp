#include "Application/SimpleApplication.h"

class TestGraphApp : public SimpleApplication {
pubic:
   TestGraphApp() : SimpleApplication("TestGraph", 800, 600)
   {};
};

int main( int argc, char** argv )
{
   TestGraphApp app;
   app.Start();
   return 0;
}
