#include "RenderVisitorOpenGL1.hpp"

/**
 * \brief Initialize the ModelView and ProjectionMatrix with the Identity Matrix and initializes the Transformation Pipeline
 */
RenderVisitorOpenGL1::RenderVisitorOpenGL1()
{
	_modelViewMatrix.LoadIdentity();
	_projectionMatrix.LoadIdentity();
	_transformPipeline.SetMatrixStacks(_modelViewMatrix, _projectionMatrix );
}

/**
 * \brief Traverse the actual node. In this case it will be traversed recursively
 * \param c to traverse
 */
void RenderVisitorOpenGL1::Visit( Node* c )
{
	OpenGLDrawing::TriangleCounter = 0;
	OpenGLDrawing::QuadCounter = 0;
	OpenGLDrawing::PolygonCounter = 0;

	//DLOG(INFO) << "Traverse Node" << endl;

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);

	// Global Light
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	// ambient and diffuse depending on material color
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

	c->Accept(this);

	OpenGLDrawing::CheckOpenGLError();

	//DLOG(INFO) << "OpenGL drawed " << OpenGLDrawing::TriangleCounter << " Triangles, " << OpenGLDrawing::QuadCounter << " Quads and " << OpenGLDrawing::PolygonCounter << " polygons" << endl;
}

/**
 * \brief Traverse all childrens. In this case it will happen recursively in the depth
 * \param c to traverse
 */
void RenderVisitorOpenGL1::TraverseChildren(CompositeNode* c) {
	for (NodeIterator it = c->GetNodeIterator(); it != c->GetNodeIteratorEnd(); ++it) {
		(*it)->Accept(this);
	}
}

/** \brief Accept a light. As we only support one light for now we just set it as the active light
 * \param l which we traverse
 */
// TODO: transform light with the Viewspace/Projection Matrix!!!
void RenderVisitorOpenGL1::VisitLight( Light* l )
{
	// Set the State if not set or not OpenGL
	if (l->GetState() == 0) {
		State* LightState = new OpenGLState();
		LightState->Enable(GL_LIGHTING);
		LightState->Enable(GL_LIGHT0+l->GetLightNumber());
		// TODO: warning when to many lights!
		l->SetState(LightState);
	}

	// If the light was changed we need to define the new properties for the light
	if (l->IsChanged()) {
		int Number = l->GetLightNumber();

		glLightfv(GL_LIGHT0+Number, GL_POSITION, l->GetPosition().GetConstPointer());
		glLightfv(GL_LIGHT0+Number, GL_AMBIENT, l->GetAmbient().GetConstPointer());
		glLightfv(GL_LIGHT0+Number, GL_DIFFUSE, l->GetDiffuse().GetConstPointer());
		glLightfv(GL_LIGHT0+Number, GL_SPECULAR, l->GetSpecular().GetConstPointer());

		l->SetChanged(false);
	}

	if (l->GetState())
		l->GetState()->Apply();

	TraverseChildren(l);

	if (l->GetState())
		l->GetState()->Undo();
}

/**
* \brief Get transformations for viewing space and projection.
* Retrieve the view matrix and projection load them to
* the matrix stacks. View and projection transforms aren't
* accumulated.
*
* @see Camera
* @param c Node to visit
*/
void RenderVisitorOpenGL1::VisitCamera( Camera* c)
{
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

	// OpenGL Load Matrices/
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

/**
* \brief Render a geometry.
* \param g Node to visit   
*/
void RenderVisitorOpenGL1::VisitGeometry( Geometry* g ) 
{
	// Invisible -> don't draw
	if (!g->GetVisibility())
		return;

	// Apply a state
	if (g->GetState())
		g->GetState()->Apply();

	const Mesh* M = g->GetMesh();

	// TODO: use for_each to draw them
	for (int i=0; i<M->GetTriangleCount(); ++i) {
		const Triangle* T = M->GetTriangle(i);
		OpenGLDrawing::DrawTriangle(T);
	}
	// TODO: why is the above code faster than the one commented out?
	// OpenGLDrawing::DrawTriangles(M->GetTriangleVector());

	for (int i=0; i<M->GetQuadCount(); ++i) {
		const Quad* Q = M->GetQuad(i);
		OpenGLDrawing::DrawQuad(Q);
	}

	for (int i=0; i<M->GetPolygonCount(); ++i) {
		const Polygon* P = M->GetPolygon(i);
		OpenGLDrawing::DrawPolygon(P);
	}
	//DLOG(INFO) << "Drawed " << M->GetPolygonCount() << " Polygons" << endl;

	if (g->GetState())
		g->GetState()->Undo();
}

/**
* Get transformation data.
*/
void RenderVisitorOpenGL1::VisitTransform( Transform* t )
{
	// Save our viewspace matrix
	_modelViewMatrix.PushMatrix();

	// create the one containing the transformation
	_modelViewMatrix.MultMatrix( t->GetMatrix() );

	// load new matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf( _modelViewMatrix.GetMatrix() );

	TraverseChildren(t);

	// restore the old one
	_modelViewMatrix.PopMatrix();
}

/* \brief Just traverse the children */
void RenderVisitorOpenGL1::VisitGroup( Group* g ) {
	TraverseChildren(g);
}
