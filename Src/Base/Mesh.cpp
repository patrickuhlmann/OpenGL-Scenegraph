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

const Vertex* Mesh::GetVertex( int i ) const { return _vertices.at(i); }

const Vertex* Mesh::GetNormal( int i ) const { return _vertices.at(i); }


