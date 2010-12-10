#pragma once

#include <vector>
#include "../Include/math3d.h"
#include "../Include/GLTools/GL/glew.h"

class MeshLoaderObj;

using namespace std;

struct Triangle {
  int vert1, vert2, vert4;
};

typedef M3DVector3f Vertex;
typedef M3DVector3f Normal;
typedef M3DVector4f Color;
typedef M3DVector2f TextureCoord;
//typedef int Triangle[3];

typedef vector<Vertex*> VertexVector;
typedef vector<Normal*> NormalVector;
typedef vector<Color*> ColorVector;
typedef vector<Triangle> TriangleVector;
typedef vector<TextureCoord*> TextureCoordVector;

typedef VertexVector::iterator VertexIterator;
typedef NormalVector::iterator NormalIterator;
typedef ColorVector::iterator ColorIterator;
typedef TriangleVector::iterator TriangleIterator;
typedef TextureCoordVector:: iterator TextureCoordIterator;

class Mesh {
public: 
  // RAII should be done!
  Mesh();
  Mesh( const char* file );
  
  VertexIterator GetVertexIterator();
  VertexIterator GetVertexIteratorEnd();

  NormalIterator GetNormalIterator();
  NormalIterator GetNormalIteratorEnd();

  ColorIterator GetColorIterator();
  ColorIterator GetColorIteratorEnd();

  TriangleIterator GetTriangleIterator();
  TriangleIterator GetTriangleIteratorEnd();

  TextureCoordIterator GetTextureCoordIterator();
  TextureCoordIterator GetTextureCoordIteratorEnd();

  const Vertex* GetVertex( int ) const;
  const Vertex* GetNormal( int ) const;

  GLint GetVertexCount() const;

private:
  GLint          _nVertexCount;
  VertexVector   _vertices;  // XYZ
  NormalVector   _normals;   // one normal per vertex
  ColorVector    _colors;    // RGBA for each vertex
  TriangleVector _triangles; // indexes for vertex vector
  TextureCoordVector  _textureCoords; // can be set to all zeroes by default

friend class MeshLoaderObj;
};
