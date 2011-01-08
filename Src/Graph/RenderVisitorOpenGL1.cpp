#include "RenderVisitorOpenGL1.hpp"

/**
 * \brief Initialize the ModelView and ProjectionMatrix with the Identity Matrix and initializes the Transformation Pipeline
 */
RenderVisitorOpenGL1::RenderVisitorOpenGL1()
{
	LightCounter = 0;
	_modelViewMatrix.LoadIdentity();
	_projectionMatrix.LoadIdentity();
	_transformPipeline.SetMatrixStacks(_modelViewMatrix, _projectionMatrix );
}

/**
 * \brief Traverse the actual node. In this case it will be traversed recursively
 * \param c to traverse
 */
void RenderVisitorOpenGL1::Traverse( CompositeNode* c )
{
	c->Accept(this);
}

/**
 * \brief Traverse all childrens. In this case it will happen recursively in the depth
 * \param c to traverse
 */
void RenderVisitorOpenGL1::TraverseChildren(CompositeNode* c) {
	NodeIterator it  = c->GetNodeIterator();
	NodeIterator end = c->GetNodeIteratorEnd();

	for (NodeIterator it = c->GetNodeIterator(); it != c->GetNodeIteratorEnd(); ++it) {
		(*it)->Accept(this);

		if (reinterpret_cast<CompositeNode*>(*it))
			Traverse(reinterpret_cast<CompositeNode*>(*it));
	}
}

/** \brief Accept a light. As we only support one light for now we just set it as the active light
 * \param l which we traverse
 */
void RenderVisitorOpenGL1::VisitLight( Light* l )
{
	DLOG(INFO) << "Ligth accepted visitor" << endl;

	glEnable(GL_LIGHTING);

	// Global Light
	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	// One Directional Light
	GLfloat ambientLight0[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv(GL_LIGHT0,GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);

	glEnable(GL_LIGHT0);
	GLfloat lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	
	// One Spot Light
	GLfloat lightPos1[] = { 0.0f, 0.0f, 75.0f, 1.0f };
	GLfloat specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat ambientLight1[] = { 0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat spotDir1[] = { 0.0f, 0.0f, -1.0f };

	glLightfv(GL_LIGHT1,GL_DIFFUSE,ambientLight1);
	glLightfv(GL_LIGHT1,GL_SPECULAR,specular1);
	glLightfv(GL_LIGHT1,GL_POSITION,lightPos1);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spotDir1);
	// Specific spot effects
	// Cut-off angle is 60 degrees
	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,60.0f);
	// Enable this light in particular
	glEnable(GL_LIGHT1);

	//_light = *l;
	TraverseChildren(l);
}

/**
* Get transformations for viewing space and projection.
* Retrieve the view matrix and projection load them to
* the matrix stacks. View and projection transforms aren't
* accumulated.
*
* @see Camera
* @param c Node to visit
*/
void RenderVisitorOpenGL1::VisitCamera( Camera* c)
{
	DLOG(INFO) << "Camera accepted visitor" << endl;

	// save current matrices
	_modelViewMatrix.PushMatrix();
	_projectionMatrix.PushMatrix();

	// retrieve view and projection matrices
	// maybe shouldn't accumulate them but replace current
	// matrices? Does it make sense to add transformations
	// for cameras?
	M3DMatrix44f matrix;
	c->GetViewMatrix(matrix);
	_modelViewMatrix.LoadMatrix( matrix );
	c->GetProjectionMatrix(matrix);
	_projectionMatrix.LoadMatrix( matrix );

	// OpenGL Load Matrices
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(_projectionMatrix.GetMatrix());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( _modelViewMatrix.GetMatrix() );

	TraverseChildren(c);

	_projectionMatrix.PopMatrix();
	_modelViewMatrix.PopMatrix();

	// Open GL Restore Matrices
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(_projectionMatrix.GetMatrix());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( _modelViewMatrix.GetMatrix() );
}

void CopyM3DVector3f(const float* source, M3DVector3f dest) {
	memcpy(dest, source, sizeof(M3DVector3f));
}

void CopyM3DVector2f(const float* source, M3DVector3f dest) {
	memcpy(dest, source, sizeof(M3DVector2f));
}

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
void RenderVisitorOpenGL1::VisitGeometry( Geometry* g ) 
{
	DLOG(INFO) << "Geometry accepted visitor" << endl;

	const Mesh* M = g->GetMesh();

	glShadeModel(GL_SMOOTH);

	int TriangleIndex = 0;
	for (TriangleIteratorConst it = M->GetTriangleIteratorConst(); it != M->GetTriangleIteratorEndConst(); ++it) {
		const float* Vertex1 = M->GetVertex((*it).vert1);
		const float* Vertex2 = M->GetVertex((*it).vert2);
		const float* Vertex3 = M->GetVertex((*it).vert3);
		const float* Normal = M->GetNormal(TriangleIndex);

		Material m = M->GetMaterial(TriangleIndex);
		const float* Color = m.GetAmbientLight();

		// ambient and diffuse depending on material color
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

		// for specular highlight
		glMaterialfv(GL_FRONT, GL_SPECULAR, m.GetSpecularLight());
		glMateriali(GL_FRONT,GL_SHININESS, m.GetShininess());

		OpenGLDrawing::DrawTriangle(Vertex1, Vertex2, Vertex3, Normal, Color);

		TriangleIndex++;
	}
}

/**
* Get transformation data.
*/
void RenderVisitorOpenGL1::VisitTransform( Transform* t )
{
	DLOG(INFO) << "Transform accepted visitor" << endl;
	_modelViewMatrix.PushMatrix(); // save current matrix
	_modelViewMatrix.MultMatrix( t->GetMatrix() );

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( _modelViewMatrix.GetMatrix() );

	TraverseChildren(t);

	_modelViewMatrix.PopMatrix(); // restore matrix
}
