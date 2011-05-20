#pragma once

#include "CompositeNode.hpp"
#include "../Include/GLFrame.h"
#include "../Include/GLFrustum.h"
#include <glog/logging.h>

/**
 * Camera class for easy handling of view space and projection.
 * The class wraps functionality for viewspace and projection
 * transformations. 
 * A frame handles the viewspace transformations and a frustum the
 * projection.
 * Every scene graph should have a default camera as it's root node
 * or at least above the geometry nodes to be rendered.
 */
class Camera : public CompositeNode {
public:

	Camera();
	Camera(string Name);
	Camera(const M3DVector3f Position, const M3DVector3f Direction);
	virtual ~Camera();

	virtual void Accept( NodeVisitor* Visitor );
	void SetPosition( const M3DVector3f Position );
	void LookAt( const M3DVector3f Point);

	void GetViewMatrix( M3DMatrix44f& ) const;
	void GetProjectionMatrix( M3DMatrix44f& );

	void SetOrthographic(GLfloat xMin, GLfloat xMax, 
		       GLfloat yMin, GLfloat yMax,
		       GLfloat zMin, GLfloat zMax);

   /** 
   * Set the perspective projection in the frustum.
   *
   * @param fFov field of vision.
   * @param fAspect aspect ratio.
   * @param fNear clipping plane.
   * @param fFar clipping plane.
   */
  void SetPerspective(GLfloat fFov, GLfloat fAspect, GLfloat fNear, GLfloat fFar);


   void MoveForward( float Delta );
   void MoveBackward( float Delta );

   void MoveRight( float Delta );
   void MoveLeft( float Delta );

   void MoveUp( float Delta );
   void MoveDown( float Delta );
   
   void RotateWorld( float Angle, float x, float y, float z );

private:
	/* \brief Handles Movement and Direction of the Camera */
	GLFrame      _frame;
	/* \brief Handles Projection */	
	GLFrustum    _viewFrustum;
};
