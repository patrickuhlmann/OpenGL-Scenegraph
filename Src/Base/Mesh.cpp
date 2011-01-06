#include "Mesh.hpp"

Mesh::Mesh() {}
Mesh::Mesh( const char* file ) {}
  
/*Mesh::VertexIterator GetVertexIterator() {}
Mesh::VertexIterator GetVertexIteratorEnd() {}

Mesh::NormalIterator GetNormalIterator() {}
Mesh::NormalIterator GetNormalIteratorEnd() {}

Mesh::ColorIterator  GetColorIterator() {}
Mesh::ColorIterator  GetColorIteratorEnd() {}

Mesh::TextureIterator GetTextureCoordIterator() {}
Mesh::TextureIterator GetTextureCoordIteratorEnd() {}*/

const float* Mesh::GetVertex( int i ) const { return _vertices.at(i); }

const float* Mesh::GetNormal( int i ) const { return _normals.at(i); }

const string& Mesh::GetName() const {
	return _name;
}

const float* Mesh::GetTextureCoord( int i ) const { return _textureCoords.at(i); }

const Triangle Mesh::GetTriangle(int i) const { return _triangles.at(i); }

int Mesh::GetVertexCount() const { return _vertices.size(); }

TriangleIterator Mesh::GetTriangleIterator() 
{ return _triangles.begin(); }

TriangleIterator Mesh::GetTriangleIteratorEnd()
{ return _triangles.end(); }

TriangleIteratorConst Mesh::GetTriangleIteratorConst() const
{ return _triangles.begin(); }

TriangleIteratorConst Mesh::GetTriangleIteratorEndConst() const
{ return _triangles.end(); }
