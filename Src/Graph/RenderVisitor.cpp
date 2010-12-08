#include "RenderVisitor.hpp"

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
  _modelViewMatrix.Push(); // save current matrix
  _modelViewMatrix.MultMatrix( t->GetMatrix() );

  Traverse( t );

  _modelViewMatrix.Pop(); // restore matrix
}

void RenderVisitor::VisitGeometry( Geometry* g ) 
{
  GLTriangleBatch triangles;
  Mesh* mesh = g->GetMesh();
  TriangleIterator it  = mesh->GetTriangleIterator();
  TriangleIterator end = mesh->GetTriangleIteratorEnd();

  triangles.BeginMesh( mesh->GetVertexCount() );
  
  while ( it != end ) {
    triangles.AddTriangle( mesh->GetTriangleVertices( (*it) ) );
  }
  // only support point light right now!
  _shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF
}

void RenderVisitor::VisitLight( Light* l )
{
  _light = *l;
  Traverse( l );
}

void RenderVisitor::VisitGroup( Group* g ) 
{
  _modelViewMatrix.Push(); // save current matrix
  _modelViewMatrix.MultMatrix( g->GetMatrix() );

  Traverse( g );

  _modelViewMatrix.Pop(); // restore matrix
}

void RenderVisitor::VisitCamera( Camera* c)
{
  _modelViewMatrix.Push();
  _projectionMatrix.Push();
  _modelViewMatrix.MultMatrix( c->GetViewMatrix() );
  _projectionMatrix.MultMatrix( c->GetProjectionMatrix() );

  Traverse( c );

  _modelViewMatrix.Pop();
  _projectionMatrix.Pop();
}
