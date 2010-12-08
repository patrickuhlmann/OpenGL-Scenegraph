#include "Camera.hpp"


// default at origin, pointing at -Z and up is Y
// default frustum gives an orthographic projection matrix
Camera::Camera() {} 

Camera::Camera( const M3DVector3f pos, const M3DVector3f dir, Node* parent )
  : CompositeNode( parent )
{
  // UpVector is Y by default
  _frame.SetOrigin( pos );
  _frame.SetForwardVector( dir );
  _frame.GetCameraMatrix( _viewMatrix );
}

void Camera::Accept( NodeVisitor* visitor ) { visitor->VisitGroup( this ); }

// TODO: update frustum
void Camera::SetPosition( const 3DVector3f origin ) { _frame.SetOrigin( origin ); }

// TODO: update frustum
void Camera::LookAt( const M3DVector3f direction ) { _frame.SetForwardVector( direction ); }

// Assemble the view matrix and return a reference to it
// GLFrame doesn't return a matrix in its GetCameraMatrix method
// so therefore we update our own and return it so that the interface
// stays coherent
const M3DMatrix44f& Camera::GetViewMatrix() const 
{ 
  _frame.GetCameraMatrix( _viewMatrix );
  return _viewMatrix;
}

const M3DMatrix44f Camera::GetProjectionMatrix() const { _viewFrustum.GetProjectionMatrix(); }

void Camera::SetOrthographic(GLfloat xMin, GLfloat xMax, 
			     GLfloat yMin, GLfloat yMax,
			     GLfloat zMin, GLfloat zMax)
{ _viewFrustum.SetOrthoGraphic( xMin, xMax, yMin, yMax, zMin, zMax ); }

void Camera::SetPerspective(float fFov, float fAspect, float fNear, float fFar)
{ _viewFrustum.SetPerspective( fFov, fAspect, fNear, fFar ); }
