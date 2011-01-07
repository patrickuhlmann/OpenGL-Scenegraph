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
	_light = *l;
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

void DrawTriangle(const float* Vertex1, const float* Vertex2, const float* Vertex3, const float* RGBColor){
	glColor3f(RGBColor[0], RGBColor[1], RGBColor[2]);

	glBegin(GL_TRIANGLES);
			glVertex2f(Vertex1[0], Vertex1[1]);
 			glVertex2f(Vertex2[0], Vertex2[1]);
 			glVertex2f(Vertex3[0], Vertex3[1]);
	glEnd();
}

void DrawPoint(const float* Vertex, const float* RGBColor) {
	glColor3f(RGBColor[0], RGBColor[1], RGBColor[2]);

	glBegin(GL_POINTS);
		glVertex2f(Vertex[0], Vertex[1]);
	glEnd();
}

void DrawLine(const float* VertexStart, const float* VertexEnd, const float* RGBColor) {
	glColor3f(RGBColor[0], RGBColor[1], RGBColor[2]);

	glBegin(GL_LINES);
		glVertex2f(VertexStart[0], VertexStart[1]);
		glVertex2f(VertexEnd[0], VertexEnd[1]);
	glEnd();
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

		Material m = M->GetMaterial(TriangleIndex);
		const float* Color = m.GetAmbientLight();

		DrawTriangle(Vertex1, Vertex2, Vertex3, Color);

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
