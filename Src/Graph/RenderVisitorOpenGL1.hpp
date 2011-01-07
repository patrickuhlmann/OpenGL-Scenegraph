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
 * Renders a geometry using OpenGL 1 fixed pipeline
 * The visitor collects transformations, state and light information
 * in the scene graph and applies them when rendering geometry nodes.
 *
 * @see NodeVisitor
 */
class RenderVisitorOpenGL1 : public NodeVisitor {

public:
	RenderVisitorOpenGL1();
	virtual void Traverse( CompositeNode* c );
	virtual void TraverseChildren( CompositeNode* c );

	virtual void VisitLight( Light* l);
	virtual void VisitCamera( Camera* c );
	virtual void VisitGeometry( Geometry* );






  /**
   * Get transformation data.
   *
   * @see Transform.
   * @param t Node to Visit
   */
  virtual void VisitTransform( Transform* t);

   void DrawOpenGL();
   
private:
   GLMatrixStack _modelViewMatrix;         /**< ModelView matrix stack */
  GLMatrixStack _projectionMatrix;        /**< Projection matrix stack */
  GLGeometryTransform _transformPipeline; /**< Helper object holding the matrices */
  Light _light;                           /**< Reference to a single light. We only support
					       one light per scene right now */


};


