#pragma once

#include <vector>

typedef M3DVector3f Vertex;
typedef M3DVector3f Normal;
typedef M3DVector4f Color;
typedef int Triangle[3];

typedef vector< Vertex > VertexVector;
typedef vector< Normal > NormalVector;
typedef vector< Color > ColorVector;
typedef vector< Triangle > TriangleVector;

typedef VertexVector::  iterator VertexIterator;
typedef NormalVector::  iterator NormalIterator;
typedef ColorVector::   iterator ColorIterator;
typedef TriangleVector::iterator TriangleIterator;

class Mesh {
public: 
  // RAII should be done!
  Mesh( const char* file );
  
  VertexIterator GetVertexIterator();
  VertexIterator GetVertexIteratorEnd();

  NormalIterator GetNormalIterator();
  NormalIterator GetNormalIteratorEnd();

  ColorIterator GetColorIterator();
  ColorIterator GetColorIteratorEnd();

  TriangleIterator GetTriangleIterator();
  TriangleIterator GetTriangleIteratorEnd();

  const Vertex* GetTriangleVertices( const Triangle& );

  GLint GetVertexCount();

private:
  GLint          _nVertexCount;
  VertexVector   _vertices; // XYZ
  NormalVector   _normals;  // XYZ
  ColorVector    _colors;   // RGBA
  TriangleVector _triangles; 
};
