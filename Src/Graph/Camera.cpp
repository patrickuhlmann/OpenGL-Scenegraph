#include "Camera.hpp"

/**
 * \brief Creates a default camera a the origin, pointing down -z axis
 * and having the y axis as the up vector.
 * Default view frustum gives a orthographic projection matrix.
 */
Camera::Camera() : CompositeNode() {
} 

/**
 * \brief Creates a default named camera a the origin, pointing down -z axis
 * and having the y axis as the up vector.
 * Default view frustum gives a orthographic projection matrix.
 * \param Name of the camera
 */
Camera::Camera(string Name) : CompositeNode(Name) {
}

/**
 * \brief Creates a camera at a specified position, pointing in a specified direction
 * \param Position of the Camera (Viewspace)
 * \param Direction in which it is facing (Viewspace)
 */
Camera::Camera( const M3DVector3f Position, const M3DVector3f Direction) : CompositeNode()
{
	_frame.SetOrigin(Position);
	_frame.SetForwardVector(Direction);
}

/** \brief Empty Destructor
 */
Camera::~Camera() {
	DLOG(INFO) << "~Camera"; 
}

/** \brief Accept a visitor. It basically just calls the VisitCamera method 
 * \param Visitor of the Camera */
void Camera::Accept( NodeVisitor* Visitor ) 
{ 
   Visitor->VisitCamera( this ); 
}

/** \brief Repositionate the Camera (Viewspace)
 * \param Position
 */
void Camera::SetPosition( const M3DVector3f Position ) 
{ 
	_frame.SetOrigin(Position); 
}

/** \brief Let the camera look at a point (Direction), (Viewspace)
 * \param Point to look at */
void Camera::LookAt( const M3DVector3f Point ) 
{ 
	_frame.SetForwardVector( Point ); 
}

/** \brief Get the Viewspace Matrix
 * \param Matrix to store the Viewspace Matrix in */
void Camera::GetViewMatrix(M3DMatrix44f& Matrix ) const { 
	_frame.GetCameraMatrix(Matrix);
}

/** \brief Get the Projection Matrix. It includes updates from the Viewspace (Camerapositon and Direction)
 * \param Matrix to stroe the Projection Matrix in */
void Camera::GetProjectionMatrix(M3DMatrix44f& Matrix)
{ 
	// Transform the frustum with the camera frame so that it 
	// is updated with the current position
	_viewFrustum.Transform(_frame);
	m3dCopyMatrix44( Matrix, _viewFrustum.GetProjectionMatrix() ); 
}

/**
 * \brief Set the orthographic projection of the frustum.
 * \param xMin minimum x.
 * \param xMax maximum x.
 * \param yMin minimum y.
 * \param yMax maximum y.
 * \param zMin minimum z.
 * \param zMax maximum z.
 */
void Camera::SetOrthographic(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, GLfloat zMin, GLfloat zMax)
{
	_viewFrustum.SetOrthographic( xMin, xMax, yMin, yMax, zMin, zMax );
}

/** 
 * \brief Set the perspective projection in the frustum.
 * \param fFov field of vision.
 * \param fAspect aspect ratio.
 * \param fNear clipping plane.
 * \param fFar clipping plane.
 */
void Camera::SetPerspective(GLfloat fFov, GLfloat fAspect, GLfloat fNear, GLfloat fFar)
{
	_viewFrustum.SetPerspective( fFov, fAspect, fNear, fFar );
}

/** \brief Move the Camera delta in it's direction forward
 * \param Delta how much to move */
void Camera::MoveForward( float Delta )
{
   _frame.MoveForward( Delta );
}

/** \brief Move the Camera delta in the opposite direction of where it is facing
 * \param Delta how much to move */
void Camera::MoveBackward( float Delta )
{
	_frame.MoveForward( -Delta );
}

/** \brief Move the Camera to the right (90 degrees to the facing direction
 * \param Delta how much to move */
void Camera::MoveRight( float Delta )
{ 
	_frame.MoveRight( Delta );
}

/** \brief Move the Camera to the left (90 degrees to the facing direction
 * \param Delta how much to move */
void Camera::MoveLeft( float Delta )
{ 
	_frame.MoveRight( -Delta );
}

/** \brief Move the Camera up (90 degrees to the facing direction
 * \param Delta how much to move */
void Camera::MoveUp( float Delta )
{
	_frame.MoveUp( Delta );
}

/** \brief Move the Camera down (90 degrees to the facing direction
 * \param Delta how much to move */
void Camera::MoveDown( float Delta )
{
	_frame.MoveUp( -Delta ); }

/** \brief Rotate the World (turn camera) about an Angle around one or more axis
 * \param Angle in Radias
 * \param 1 if we want to turn around x, 0 otherwise
 * \param 1 if we want to turn around y, 0 otherwise
 * \param 1 if we want to turn around z, 0 otherwise
 */
void Camera::RotateWorld( float angle, float x, float y, float z )
{
	_frame.RotateWorld( angle, x, y, z );
}
