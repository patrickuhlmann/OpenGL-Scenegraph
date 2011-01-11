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

  /**
   * Create a default camera a the origin, pointing down -z axis
   * and having the y axis as the up vector.
   * Default view frustum gives a orthographic projection matrix.
   */
  Camera();

  Camera(string Name);

  /**
   * Create a camera and initilize it with a position and
   * a direction and set a node as a parent.
   * The y axis will be used as up vector.
   *
   * @param pos the position of the camera.
   * @param dir the direction of the camera.
   */
  Camera( const M3DVector3f, const M3DVector3f);

   ~Camera() { DLOG(INFO) << "~Camera"; }

  /** Accept a visitor */
  virtual void Accept( NodeVisitor* );

  /** Set a new position */
  void SetPosition( const M3DVector3f );

  /** Set a new point to look at */
  void LookAt( const M3DVector3f );

  // void GetViewMatrix( const M3DMatrix44f m ) const;

  /**
   * Get the value of the view matrix.
   */
   void GetViewMatrix( M3DMatrix44f ) const;

   /** Get the value of the projection matrix */
  void GetProjectionMatrix( M3DMatrix44f );
  // const GLFrustum& GetViewFrustum() const;
  //void SetViewFrustum( GLFrustum& );

   /** 
   * Set the perspective projection in the frustum.
   *
   * @param fFov field of vision.
   * @param fAspect aspect ratio.
   * @param fNear clipping plane.
   * @param fFar clipping plane.
   */
  void SetPerspective(GLfloat fFov, GLfloat fAspect, GLfloat fNear, GLfloat fFar);

  /**
   * Set the orthographic projection of the frustum.
   * 
   * @param xMin minimum x.
   * @param xMax maximum x.
   * @param yMin minimum y.
   * @param yMax maximum y.
   * @param zMin minimum z.
   * @param zMax maximum z.
   */
  void SetOrthographic(GLfloat xMin, GLfloat xMax, 
		       GLfloat yMin, GLfloat yMax,
		       GLfloat zMin, GLfloat zMax);


   void MoveForward( float delta );

   void MoveBackward( float delta );

   void MoveRight( float delta );

   void MoveLeft( float delta );

   void MoveUp( float delta );

   void MoveDown( float delta );
   
   void RotateWorld( float angle, float x, float y, float z );

private:
  GLFrame      _frame;       /**< Handles movement and direction of camera */
  M3DMatrix44f _viewMatrix;  /**< Matrix is derived from the frame */
  GLFrustum    _viewFrustum; /**< Handles projection **/
};
