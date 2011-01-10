#include "Geometry.hpp"

Geometry::Geometry(Mesh* M) : CompositeNode() {
	if (M == 0)
		DLOG(WARNING) << "Try to initialize Geometry with null pointer!" << endl;

	_mesh = M;
	Visible = true;
};

Geometry::Geometry(Mesh* M, const string& Name) : CompositeNode(Name) {
	if (M == 0)
		DLOG(WARNING) << "Try to initialize Geometry with null pointer!" << endl;

	_mesh = M;
	Visible = true;
};

Geometry::~Geometry() {
	delete _mesh;
	//delete _state;
};

void Geometry::Accept( NodeVisitor* visitor ) 
{
   visitor->VisitGeometry( this ); 
}

void Geometry::SetMesh( Mesh* mesh ) {
	_mesh = mesh;
}

const Mesh* Geometry::GetMesh() const {
	return _mesh;
}

/** \brief Set a State for this Geometry. If there was an old state it will be removed. We take control over the state and free it at the end
  * \param s to use */
void Geometry::SetState(State* s) {
	if (_state)
		delete _state;

	_state = s;
}

void Geometry::SetVisibility(bool NewStatus) {
	this->Visible = NewStatus;
}

bool Geometry::GetVisibility() const {
	return this->Visible;
}
