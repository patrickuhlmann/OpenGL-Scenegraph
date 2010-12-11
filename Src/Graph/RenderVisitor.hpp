#pragma once

#include "NodeVisitor.hpp"
#include "../Include/GLMatrixStack.h"
#include "../Include/GLTriangleBatch.h"
#include "../Include/GLGeometryTransform.h"
#include "../Include/GLShaderManager.h"
#include "Light.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"
#include "../Base/Mesh.hpp"

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
   * Create a default RenderVisitor.
   * 
   * Loads both modelview and projection matrices with identity matrices.
   * The matrices gets loaded into at helper object, GLGeometryTransform.
   * The shader program manager gets initialized so that the stock 
   * programs are available.
   */
  RenderVisitor();
  
  /**
   * Get transformation data.
   *
   * @see Transform.
   * @param Transform*
   */
  virtual void VisitTransform( Transform* );

  /**
   * Render a geometry.
   *
   * The rendering is limited in functionality right now
   * since we only support one light and only the diffuse
   * version.
   *
   * @see Transform
   * @param Geometry*    
   */
  virtual void VisitGeometry( Geometry* );

  /**
   * Get information about lighting in the scene.
   *
   * @see Light
   * @param Light*     
   */
  virtual void VisitLight( Light* );

  /**
   * Visit a group having a number of children.
   *
   * @see Group
   * @param Group*    
   */
  virtual void VisitGroup( Group* );

  /**
   * Get transformations for viewing space and projection.
   * Retrieve the view matrix and projection load them to
   * the matrix stacks. View and projection transforms aren't
   * accumulated.
   *
   * @see Camera
   * @param Camera*    
   */
  virtual void VisitCamera( Camera* );
  

private:

  /**
   * Traverse a composite.
   * @param CompositeNode*
   * @see CompositeNode
   */
  virtual void Traverse( CompositeNode* );

  GLMatrixStack _modelViewMatrix;         /**< ModelView matrix stack */
  GLMatrixStack _projectionMatrix;        /**< Projection matrix stack */
  GLGeometryTransform _transformPipeline; /**< Helper object holding the matrices */
  GLShaderManager _shaderManager;           /**< Helper object for managing shader programs */
  Light _light;                           /**< Reference to a single light. We only support
					       one light per scene right now */
};
