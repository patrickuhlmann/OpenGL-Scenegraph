#pragma once

#include "NodeVisitor.hpp"
#include "../Include/GLMatrixStack.h"
#include "../Include/GLTriangleBatch.h"
#include "../Include/GLBatch.h" 
#include "../Include/GLGeometryTransform.h"
#include "../Include/GLShaderManager.h"
#include "Light.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"
#include "../Base/Mesh.hpp"
//#include "../Base/Convert.h"
#include "Camera.hpp"

/**
 * Renders a geometry using OpenGL 3 core.
 * The visitor collects transformations, state and light information
 * in the scene graph and applies them when rendering geometry nodes.
 *
 * @see NodeVisitor
 */
class RenderVisitor : public NodeVisitor {

public:

  /**
   * Create a RenderVisitor.
   * 
   * Loads both modelview and projection matrices with identity matrices.
   * The matrices gets loaded into at helper object, GLGeometryTransform.
   * The shader program manager gets initialized so that the stock 
   * programs are available.
   * You have to provide a GLShaderManager that has been initialized
   * and glew must also be initialized. 
   *
   * @see GLShaderManager
   * @param gm Pointer to a shadermanager object.
   */
  RenderVisitor( GLShaderManager* gm );
  
  /**
   * Get transformation data.
   *
   * @see Transform.
   * @param t Node to Visit
   */
  virtual void VisitTransform( Transform* t);

  /**
   * Render a geometry.
   *
   * The rendering is limited in functionality right now
   * since we only support one light and only the diffuse
   * version.
   *
   * @see Geometry
   * @param g Node to visit   
   */
  virtual void VisitGeometry( Geometry* );

  /**
   * Get information about lighting in the scene.
   *
   * @see Light
   * @param l Node to visit     
   */
  virtual void VisitLight( Light* l);

  /**
   * Get transformations for viewing space and projection.
   * Retrieve the view matrix and projection load them to
   * the matrix stacks. View and projection transforms aren't
   * accumulated.
   *
   * @see Camera
   * @param c Node to visit
   */
  virtual void VisitCamera( Camera* c );
  



  /**
   * Traverse a composite.
   * @param \c Node to Traverse
   * @see CompositeNode
   */
  virtual void Traverse( CompositeNode* c );


   void DrawOpenGL();
   
private:
   GLMatrixStack _modelViewMatrix;         /**< ModelView matrix stack */
  GLMatrixStack _projectionMatrix;        /**< Projection matrix stack */
  GLGeometryTransform _transformPipeline; /**< Helper object holding the matrices */
  GLShaderManager* _shaderManager;           /**< Helper object for managing shader programs */
  Light _light;                           /**< Reference to a single light. We only support
					       one light per scene right now */


};


