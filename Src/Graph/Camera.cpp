#include "Camera.hpp"


// default at origin, pointing at -Z and up is Y
// default frustum gives an orthographic projection matrix
Camera::Camera() : CompositeNode() {
} 

// default at origin, pointing at -Z and up is Y
// default frustum gives an orthographic projection matrix
// named camera
Camera::Camera(string Name) : CompositeNode(Name) {
} 

Camera::Camera( const M3DVector3f pos, const M3DVector3f dir) : CompositeNode()
{
  _frame.SetOrigin( pos );
  _frame.SetForwardVector( dir );
  //_frame.GetCameraMatrix( _viewMatrix );
}

void Camera::Accept( NodeVisitor* visitor ) 
{ 
   visitor->VisitCamera( this ); 
}

// TODO: update frustum???
void Camera::SetPosition( const M3DVector3f origin ) 
{ 
   _frame.SetOrigin( origin ); 
   // _viewFrustum.Transform( _frame );
}

// TODO: update frustum???
void Camera::LookAt( const M3DVector3f direction ) 
{ 
   _frame.SetForwardVector( direction ); 
   //_viewFrustum.Transform( _frame );
}

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

void Camera::MoveForward( float delta )
{
   _frame.MoveForward( delta );
}

void Camera::MoveBackward( float delta )
{ _frame.MoveForward( -delta ); }

void Camera::MoveRight( float delta )
{ 
	_frame.MoveRight( delta );
}

void Camera::MoveLeft( float delta )
{ 
	_frame.MoveRight( -delta );
}

void Camera::MoveUp( float delta )
{ _frame.MoveUp( delta ); }

void Camera::MoveDown( float delta )
{ _frame.MoveUp( -delta ); }
   
void Camera::RotateWorld( float angle, float x, float y, float z )
{ _frame.RotateWorld( angle, x, y, z ); }
