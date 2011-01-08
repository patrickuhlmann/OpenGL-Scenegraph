#pragma once

#include "NodeVisitor.hpp"
#include "../Include/GLMatrixStack.h"
#include "../Include/GLGeometryTransform.h"
#include "Light.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"
#include "../Base/Mesh.hpp"
#include "Camera.hpp"
#include "../OpenGLFixed/OpenGLDrawing.h"
#include <typeinfo>
#include "../OpenGLFixed/OpenGLState.h"
#include "Group.hpp"

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

protected:
	virtual void TraverseChildren( CompositeNode* c );

	virtual void VisitLight( Light* l);
	virtual void VisitCamera( Camera* c );
	virtual void VisitGeometry( Geometry* );
	virtual void VisitTransform( Transform* t);
	virtual void VisitGroup( Group* g );
private:
	/** \brief ModelView matrix stack */
	GLMatrixStack _modelViewMatrix;
	/** \brief Projection matrix stack */
	GLMatrixStack _projectionMatrix;
	/** \brief Helper for both the objects */
	GLGeometryTransform _transformPipeline;
	/** \brief Keeps track of how many lights we have */
	int LightCounter;
};


