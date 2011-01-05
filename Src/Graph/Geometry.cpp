#include "Geometry.hpp"

Geometry::Geometry( Mesh* mesh) : Node(), _mesh( mesh ) {}

void Geometry::Accept( NodeVisitor* visitor ) { visitor->VisitGeometry( this ); }

void Geometry::SetMesh( Mesh* mesh ) { _mesh = mesh; }

const Mesh* Geometry::GetMesh() const { return _mesh; };

void Geometry::SetState( const State& s ) { _state = s; }
