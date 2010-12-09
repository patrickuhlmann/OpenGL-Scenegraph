#include "Mesh.hpp"

Mesh::Mesh( const char* file ) {}
  
Mesh::VertexIterator GetVertexIterator() {}
Mesh::VertexIterator GetVertexIteratorEnd() {}

Mesh::NormalIterator GetNormalIterator() {}
Mesh::NormalIterator GetNormalIteratorEnd() {}

Mesh::ColorIterator  GetColorIterator() {}
Mesh::ColorIterator  GetColorIteratorEnd() {}

Mesh::TextureIterator GetTextureCoordIterator() {}
Mesh::TextureIterator GetTextureCoordIteratorEnd() {}

const Vertex& GetVertex( int i ) { return _vertices.at(i); }

const Vertex& GetNormal( int i ) { return _vertices.at(i); }


