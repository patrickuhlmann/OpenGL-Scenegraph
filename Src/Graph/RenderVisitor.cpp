#include "RenderVisitor.hpp"

void CopyM3DVector3f(const float* source, M3DVector3f dest) {
	memcpy(dest, source, sizeof(M3DVector3f));
}

void CopyM3DVector2f(const float* source, M3DVector3f dest) {
	memcpy(dest, source, sizeof(M3DVector2f));
}


RenderVisitor::RenderVisitor()
{
  _shaderManager.InitializeStockShaders();
  _modelViewMatrix.LoadIdentity();
  _projectionMatrix.LoadIdentity();
  _transformPipeline.SetMatrixStacks( _modelViewMatrix, _projectionMatrix );
}

void RenderVisitor::Traverse( CompositeNode* c )
{
  NodeIterator it = c->GetNodeIterator();
  NodeIterator end = c->GetNodeIteratorEnd();

  while ( it != end ) 
    (*it)->Accept( this );
}

void RenderVisitor::VisitTransform( Transform* t )
{
  _modelViewMatrix.PushMatrix(); // save current matrix
  _modelViewMatrix.MultMatrix( t->GetMatrix() );

  Traverse( t );

  _modelViewMatrix.PopMatrix(); // restore matrix
}

void RenderVisitor::VisitGeometry( Geometry* g ) 
{
  GLTriangleBatch triangles;
  const Mesh* mesh = g->GetMesh(); // Should not be dependent upon Mesh???

  TriangleIteratorConst it  = mesh->GetTriangleIteratorConst(); 
  TriangleIteratorConst end    = mesh->GetTriangleIteratorEndConst();
  
  M3DVector3f lightPos;   // array of 3 float (not GLfloat)
  M3DVector4f color;      // array of 4 =||=

  // set light position and diffuse light color
  _light.GetDiffuse( color );
  _light.GetPosition( lightPos );

  // create a triangle mesh and give the initial size
  triangles.BeginMesh( mesh->GetVertexCount() );
  
  while ( it != end ) {
    M3DVector3f vertices[3];
    M3DVector3f normals[3];
    M3DVector2f texCoords[3];

    CopyM3DVector3f(mesh->GetVertex( (*it).vert1 ), vertices[0]);
    CopyM3DVector3f(mesh->GetVertex( (*it).vert2 ), vertices[1]);
    CopyM3DVector3f(mesh->GetVertex( (*it).vert3 ), vertices[2]);

    CopyM3DVector3f(mesh->GetNormal( (*it).vert1 ), normals[0]);
    CopyM3DVector3f(mesh->GetNormal( (*it).vert2 ), normals[1]);
    CopyM3DVector3f(mesh->GetNormal( (*it).vert3 ), normals[2]);

    CopyM3DVector2f(mesh->GetTextureCoord( (*it).vert1 ), texCoords[0]);
    CopyM3DVector2f(mesh->GetTextureCoord( (*it).vert2 ), texCoords[1]);
    CopyM3DVector2f(mesh->GetTextureCoord( (*it).vert3 ), texCoords[2]);

    triangles.AddTriangle( vertices, normals, texCoords );

	it++;
  }

  triangles.End();

  // load shader program
  _shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF,
				_transformPipeline.GetModelViewMatrix(),
				_transformPipeline.GetProjectionMatrix(),
				lightPos, color);

  triangles.Draw();
}

void RenderVisitor::VisitLight( Light* l )
{
  _light = *l; // maybe accumulate light in a vector?
  Traverse( l );
}

/* TODO: what is group?
void RenderVisitor::VisitGroup( Group* g ) 
{
  _modelViewMatrix.PushMatrix(); // save current matrix
  _modelViewMatrix.MultMatrix( g->GetMatrix() );

  Traverse( g );

  _modelViewMatrix.PopMatrix(); // restore matrix
}
*/

void RenderVisitor::VisitCamera( Camera* c)
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

  Traverse( c );

  _modelViewMatrix.PopMatrix();
  _projectionMatrix.PopMatrix();
}
