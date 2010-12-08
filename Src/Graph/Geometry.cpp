#include "Geometry.hpp"

Geometry::Geometry( Mesh* mesh, Node* parent )
  : Node( parent ), _mesh( mesh ), _dirty( false ) {}

void Geometry::Accept( NodeVisitor* visitor ) { visitor->VisitGeometry( this ); }

void Geometry::SetMesh( Mesh* mesh ) { _mesh = mesh; }
