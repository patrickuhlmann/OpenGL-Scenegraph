#pragma once

#include "CompositeNode.hpp"
#include "include/GLTools/GLFrame.h"
#include "include/GLTools/GLFrustum.h"

class Camera : public CompositeNode {
public:
  Camera();
  Camera( const M3DVector3f, const M3DVector3f, Node* );

  virtual void Accept( NodeVisitor* );

  void SetPosition( const M3DVector3f );
  void LookAt( const M3DVector3f );

  // void GetViewMatrix( const M3DMatrix44f m ) const;
  const M3DMatrix44f& GetViewMatrix();
  const M3DMatrix44f& GetProjectionMatrix();
  // const GLFrustum& GetViewFrustum() const;
  //void SetViewFrustum( GLFrustum& );

  // Set projection
  void SetPerspective();
  void SetOrthographic();

private:
  GLFrame _frame;
  M3DMatrix44f _viewMatrix;
  GLFrustum _viewFrustum;
};
