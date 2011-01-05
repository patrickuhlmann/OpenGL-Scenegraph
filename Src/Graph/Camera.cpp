#include "Camera.hpp"


// default at origin, pointing at -Z and up is Y
// default frustum gives an orthographic projection matrix
Camera::Camera() {} 

Camera::Camera( const M3DVector3f pos, const M3DVector3f dir, Node* parent )
  : CompositeNode()
{
  _frame.SetOrigin( pos );
  _frame.SetForwardVector( dir );
  //_frame.GetCameraMatrix( _viewMatrix );
}

void Camera::Accept( NodeVisitor* visitor ) { visitor->VisitCamera( this ); }

// TODO: update frustum???
void Camera::SetPosition( const M3DVector3f origin ) { _frame.SetOrigin( origin ); }

// TODO: update frustum???
void Camera::LookAt( const M3DVector3f direction ) { _frame.SetForwardVector( direction ); }

void Camera::GetViewMatrix( M3DMatrix44f m ) const 
{ _frame.GetCameraMatrix( m ); }

void Camera::GetProjectionMatrix( M3DMatrix44f m )
{ 
   // Transform the frustum with the camera frame so that it 
   // is updated with the current position
   _viewFrustum.Transform( _frame );
   m3dCopyMatrix44( m, _viewFrustum.GetProjectionMatrix() ); 
}

void Camera::SetOrthographic(GLfloat xMin, GLfloat xMax, 
			     GLfloat yMin, GLfloat yMax,
			     GLfloat zMin, GLfloat zMax)
{ _viewFrustum.SetOrthographic( xMin, xMax, yMin, yMax, zMin, zMax ); }

void Camera::SetPerspective(GLfloat fFov, GLfloat fAspect, GLfloat fNear, GLfloat fFar)
{ _viewFrustum.SetPerspective( fFov, fAspect, fNear, fFar ); }
