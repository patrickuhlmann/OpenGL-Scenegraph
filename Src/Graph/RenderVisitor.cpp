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
  Mesh* mesh = g->GetMesh(); // Should not be dependent upon Mesh???

  TriangleIterator it  = mesh->GetTriangleIterator(); 
  TriangleIterator end    = mesh->GetTriangleIteratorEnd();
  
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

    vertices[0] = mesh->GetVertex( (*it).vert1 );
    vertices[1] = mesh->GetVertex( (*it).vert2 );
    vertices[2] = mesh->GetVertex( (*it).vert3 );

    normals[0]  = mesh->GetNormal( (*it).vert1 );
    normals[1]  = mesh->GetNormal( (*it).vert2 );
    normals[2]  = mesh->GetNormal( (*it).vert3 );

    texCoords[0] = mesh->GetTextureCoord( (*it).vert1 );
    texCoords[1] = mesh->GetTextureCoord( (*it).vert2 );
    texCoords[2] = mesh->GetTextureCoord( (*it).vert3 );

    triangles.AddTriangle( vertices, normals, texCoords );
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

void RenderVisitor::VisitGroup( Group* g ) 
{
  _modelViewMatrix.Push(); // save current matrix
  _modelViewMatrix.MultMatrix( g->GetMatrix() );

  Traverse( g );

  _modelViewMatrix.Pop(); // restore matrix
}

void RenderVisitor::VisitCamera( Camera* c)
{
  // save current matrices
  _modelViewMatrix.Push();
  _projectionMatrix.Push();

  // retrieve view and projection matrices
  // maybe shouldn't accumulate them but replace current
  // matrices? Does it make sense to add transformations
  // for cameras?
  _modelViewMatrix.LoadMatrix( c->GetViewMatrix() );
  _projectionMatrix.LoadMatrix( c->GetProjectionMatrix() );

  Traverse( c );

  _modelViewMatrix.Pop();
  _projectionMatrix.Pop();
}
