#include "Mesh.hpp"

  Mesh( const char* file );
  
  VertexIterator GetVertexIterator();
  VertexIterator GetVertexIteratorEnd();

  NormalIterator GetNormalIterator();
  NormalIterator GetNormalIteratorEnd();

  ColorIterator  GetColorIterator();
  ColorIterator  GetColorIteratorEnd();
