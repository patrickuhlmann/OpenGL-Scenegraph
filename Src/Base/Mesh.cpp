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

const float* Mesh::GetNormal( int i ) const { return _vertices.at(i); }

const string& Mesh::GetName() const {
	return _name;
}

