#include "Geometry.hpp"

/** \brief Initializes a Geometry node visible with a mesh. The node will take the name of the mesh
  * \param M Mesh to use in this geometry node. It takes ownership of the mesh and takes care of deleting it at the end
 */
Geometry::Geometry(Mesh* M) : CompositeNode(M->GetName()), Visible(true), _state(0) {
	SetMesh(M);
};

/** \brief Initializes a Geometry node visible with a mesh and a name.
  * \param M Mesh to use in this geometry node. It takes ownership of the mesh and takes care of deleting it at the end
  * \param Name of the GeometryNode
  */
Geometry::Geometry(Mesh* M, const string& Name) : CompositeNode(Name), Visible(true), _state(0) {
	SetMesh(M);
};

/** \brief Destructor deletes mesh */
Geometry::~Geometry() {
	delete _mesh;
	delete _state;
};

/** \brief Accept method just calls VisitGeometry from Visitor
 * \param Visitor of the Node */
void Geometry::Accept( NodeVisitor* Visitor ) 
{
	Visitor->VisitGeometry( this ); 
}

/** \brief Set a new mesh for this Geometry object
  * \param M to set */
void Geometry::SetMesh( Mesh* M ) {
	if (M == 0)
		LOG(WARNING) << "Try to initialize Geometry with null pointer!" << endl;

	_mesh = M;
}


const Mesh* Geometry::GetMesh() const {
	return _mesh;
}

/** \brief Set a State for this Geometry. If there was an old state it will be removed. We take control over the state and free it at the end
  * \param s to use */
void Geometry::SetState(State* s) {
	delete _state;
	_state = s;
}

/** \brief Get the State for this Geometry. Can be zero! */
const State* Geometry::GetState() const {
	return _state;
}

/** \brief Decides if the object is visible or not
 * \param NewStatus is true -> is visible, otherwise not */
void Geometry::SetVisibility(bool NewStatus) {
	this->Visible = NewStatus;
}

/** \brief Check if the object is visible
  * \return true if visible, false otherwise */
bool Geometry::GetVisibility() const {
	return this->Visible;
}
