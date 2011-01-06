#include "Geometry.hpp"

Geometry::Geometry() {};
//Geometry::Geometry( Mesh* mesh) : Node(), _mesh( mesh ) {}

Geometry::~Geometry() {};

void Geometry::Accept( NodeVisitor* visitor ) 
{
   DLOG(INFO) << "Geometry accepted visitor\n";
   visitor->VisitGeometry( this ); 
}

void Geometry::SetMesh( Mesh* mesh ) { _mesh = mesh; }

const Mesh* Geometry::GetMesh() const { return _mesh; }

void Geometry::SetState( const State& s ) { _state = s; }
