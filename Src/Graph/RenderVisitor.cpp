#include "RenderVisitor.hpp"

void RenderVisitor::DrawOpenGL()
{
   DLOG(INFO) << "DrawOpenGL\n";

   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
   glLoadMatrixf( _projectionMatrix.GetMatrix() );


//   gluPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);
   //  glLoadIdentity();
   glLoadMatrixf( _modelViewMatrix.GetMatrix() );

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   

   glTranslatef(-1.5f,0.0f,-6.0f);	
   glBegin(GL_TRIANGLES);
   glVertex3f( 0.0f, 1.0f, 0.0f);	
   glVertex3f(-1.0f,-1.0f, 0.0f);	
   glVertex3f( 1.0f,-1.0f, 0.0f);	
   glEnd();

}

void CopyM3DVector3f(const float* source, M3DVector3f dest) {
	memcpy(dest, source, sizeof(M3DVector3f));
}

void CopyM3DVector2f(const float* source, M3DVector3f dest) {
	memcpy(dest, source, sizeof(M3DVector2f));
}


RenderVisitor::RenderVisitor( GLShaderManager* gm )
{
   _shaderManager = gm;
   _modelViewMatrix.LoadIdentity();
   _projectionMatrix.LoadIdentity();
   _transformPipeline.SetMatrixStacks( _modelViewMatrix, _projectionMatrix );
}

void RenderVisitor::Traverse( CompositeNode* c )
{
   DLOG(INFO) << "RenderVisitor about to traverse node\n";
  NodeIterator it  = c->GetNodeIterator();
  NodeIterator end = c->GetNodeIteratorEnd();

//   DLOG(INFO) << (c == 0) << endl;
// //  DLOG(INFO) << "Composite children count: " <<
  // c->GetChildrenCount() << endl;
  // DLOG(INFO) << "Composite name: " << c->GetName() << endl;
  

  // if (*it) 
  //    DLOG(INFO) << "NOT NULL\n";

  while ( it != end ) {
     (*it)->Accept( this );
     ++it;
  }
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

   // DrawOpenGL();
   // return;
   
   //  DLOG(INFO) << "RenderVisitor::VisitGeometry()\n";
  GLTriangleBatch triangles;
  const Mesh* mesh = g->GetMesh();

  TriangleIteratorConst it  = mesh->GetTriangleIteratorConst(); 
  TriangleIteratorConst end = mesh->GetTriangleIteratorEndConst();
  
  M3DVector3f lightPos;   // array of 3 float (not GLfloat)
  M3DVector4f color;      // array of 4 =||=

  // set light position and diffuse light color
  _light.GetDiffuse( color );
  _light.GetPosition( lightPos );

  // create a triangle mesh and give the initial size
  triangles.BeginMesh( mesh->GetVertexCount() );
  
  // DLOG(INFO) << "mesh->GetVertexCount() == " << mesh->GetVertexCount() << endl;

  M3DVector3f vertices[3];
  M3DVector3f normals[3];
  M3DVector2f texCoords[3];
  
  while ( it != end ) {


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
    
    // DLOG(INFO) << "vertices[0]: " << vertices[0] << endl;
    // DLOG(INFO) << "vertices[1]: " << vertices[1] << endl;
    // DLOG(INFO) << "vertices[2]: " << vertices[2] << endl;

    // DLOG(INFO) << "normals[0]: " << normals[0] << endl;
    // DLOG(INFO) << "normals[1]: " << normals[1] << endl;
    // DLOG(INFO) << "normals[2]: " << normals[2] << endl;

    // DLOG(INFO) << "texCoords[0]: " << texCoords[0] << endl;
    // DLOG(INFO) << "texCoords[0]: " << texCoords[1] << endl;
    // DLOG(INFO) << "texCoords[0]: " << texCoords[2] << endl;

    ++it;
  }

  triangles.End();

  // load shader program
  _shaderManager->UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF,
				_transformPipeline.GetModelViewMatrix(),
				_transformPipeline.GetProjectionMatrix(),
				lightPos, color);

  triangles.Draw();
//  DLOG(INFO) << "triangles has been drawn\n";
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
