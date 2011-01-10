#pragma once

#include "BaseApplication.h"
#include "../Graph/RenderVisitorOpenGL1.hpp"

#define STEP 1.0f    // amount to move
#define ANGLE 0.09f  // angle in radians almost 5 deg
/**
 * \brief This class can be used to develop simple applications. It has some lifecycle methods and simple keyhandling for example Esc to close the application
 */
class SimpleApplication : public BaseApplication {
  private:
   void HandleKeysSimple(enuKey Code);
   
  protected:
   
  public:
   SimpleApplication(string Title, int WindowWidth, int WindowHeight);
   virtual ~SimpleApplication();
   virtual void Init(CompositeNode* RootNode, MeshFileLoader* MeshLoader);
   virtual void Update(CompositeNode* RootNode);
   virtual void Render(NodeVisitor* RenderVisitor, CompositeNode* RootNode);
   virtual void Resize(int NewWidth, int NewHeight);
   virtual void HandleKeys(enuKey Code);
   static  void HandleKeysS(enuKey Code, int x, int y);
   virtual void Pause();
   virtual void Continue();
   virtual void Shutdown();
};
