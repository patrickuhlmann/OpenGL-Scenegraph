#include "Geometry.hpp"

Geometry::Geometry(Mesh* M, const string& Name) : CompositeNode(Name) {
	if (M == 0)
		DLOG(WARNING) << "Try to initialize Geometry with null pointer!" << endl;

	_mesh = M;
};

Geometry::~Geometry() {
	if (_mesh)
		delete _mesh;

	DLOG(INFO) << "~Geometry()\n";
};

void Geometry::Accept( NodeVisitor* visitor ) 
{
   DLOG(INFO) << "Geometry accepted visitor\n";
   visitor->VisitGeometry( this ); 
}

void Geometry::SetMesh( Mesh* mesh ) { _mesh = mesh; }

const Mesh* Geometry::GetMesh() const { return _mesh; }

void Geometry::SetState( const State& s ) { _state = s; }
