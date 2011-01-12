#include "Mesh.hpp"

int Mesh::MeshCounter = 0;
NameSet Mesh::Names;

/** \brief Add the Name to the set of names
 * \return true if it was not there already, false otherwise */
bool Mesh::IsNameUnique(const string& Name) {
	NameSetPair Ret = Names.insert(Name);
	return Ret.second;
}

/**
 * \brief Create an empty mesh with a generated name Mesh + a counter. You get a warning to the console if there is already a mesh with the same name.
 */
Mesh::Mesh() : _name(string("Mesh"+IntegerToString(MeshCounter))) {
	if (!IsNameUnique(_name))
		DLOG(WARNING) << "Name " << _name << " is not unique!" << endl;
	
	MeshCounter++;
}

/**
 * \brief Create an empty mesh with a given name. You get a warning to the console if there is already a mesh with the same name.
 * \param Name of the Mesh
 */
Mesh::Mesh(const string& Name) : _name(Name) {
	if (!IsNameUnique(_name))
		DLOG(WARNING) << "Name " << _name << " is not unique!" << endl;

	MeshCounter++;
}

/**
 * \brief Destructor frees all Vertices, Triangles, Quads, Polygons and Materials. Removes the Name from the list
 */
Mesh::~Mesh() {
	DLOG(INFO) << "Started Deleting Mesh" << endl;

	for (VertexVector::iterator it = _vertices.begin(); it != _vertices.end(); ++it) {
		delete *it;
	}

	for (TriangleVector::iterator it = _triangles.begin(); it != _triangles.end(); ++it) {
		delete (*it);
	}

	for (QuadVector::iterator it = _quads.begin(); it != _quads.end(); ++it) {
		delete (*it);
	}

	for (QuadVector::iterator it = _quadsConcave.begin(); it != _quadsConcave.end(); ++it) {
		delete (*it);
	}

	for (PolygonVector::iterator it = _polygons.begin(); it != _polygons.end(); ++it) {
		delete (*it);
	}

	for (PolygonVector::iterator it = _polygonsConcave.begin(); it != _polygonsConcave.end(); ++it) {
		delete (*it);
	}

	for (mmsm::iterator it = _materials.begin(); it != _materials.end(); ++it) {
		delete ((*it).second);
	}

	Names.erase(this->_name);

	DLOG(INFO) << "Finished Deleting Mesh" << endl;
}

/** \brief Get the Vector containing all triangles */
const TriangleVector& Mesh::GetTriangleVector() const {
	return _triangles;
}

/**
 * \brief Get the Vertex at position i
 * \param i index of the Vertex to get
 * \return pointer to the vertex (XYZ)
 */
const Vector3* Mesh::GetVertex( int i ) const {
	return _vertices.at(i);
}

/**
 * \brief Get the Triangle at position i
 * \param i index of the Triangle
 * \return reference to the triangle
 */
const Triangle* Mesh::GetTriangle(int i) const {
	return _triangles.at(i);
}

/**
 * \brief Get the Quad at position i
 * \param i index of the Quad
 * \return reference to the quad
 */
const Quad* Mesh::GetQuad(int i) const {
	return _quads.at(i);
}

/**
 * \brief Get the Quad Concave at position i
 * \param i index of the Quad
 * \return reference to the quad
 */
const Quad* Mesh::GetQuadConcave(int i) const {
	return _quadsConcave.at(i);
}

/**
 * \brief Get the Polygon at position i
 * \param i index of the Quad
 * \return reference to the quad
 */
const Polygon* Mesh::GetPolygon(int i) const {
	return _polygons.at(i);
}

/**
 * \brief Get the Polygon Concave at position i
 * \param i index of the Quad
 * \return reference to the quad
 */
const Polygon* Mesh::GetPolygonConcave(int i) const {
	return _polygonsConcave.at(i);
}

/** \brief Scale the Mesh proportionaly by a defined factor. This operation will lead to information loss and is not revertible. Another possible way to scale a mesh is the call to Transform of a TransformNode containing a GeometryNode containing a Mesh
 * \param Factor to scale
 */
void Mesh::Scale(float Factor) {
	for (VertexVector::iterator it = _vertices.begin(); it != _vertices.end(); ++it) {
		(*it)->Array[0] = (*it)->Array[0] * Factor;
		(*it)->Array[1] = (*it)->Array[1] * Factor;
		(*it)->Array[2] = (*it)->Array[2] * Factor;
	}
}

/**
 * \brief Get the Number of Vertices in this Mesh
 * \return Number of Vertices
 */
int Mesh::GetVertexCount() const {
	return _vertices.size();
}

/**
 * \brief Get the Number of Triangles in this Mesh
 * \return Number of Triangles
 */
int Mesh::GetTriangleCount() const {
	return _triangles.size();
}

/**
 * \brief Get the Number of Quads in this Mesh
 * \return Number of Quads
 */
int Mesh::GetQuadCount() const {
	return _quads.size();
}

/**
 * \brief Get the Number of Concave Quads in this Mesh
 * \return Number of Quads
 */
int Mesh::GetQuadConcaveCount() const {
	return _quads.size();
}

/**
 * \brief Get the Number of Polygons in this Mesh
 * \return Number of Quads
 */
int Mesh::GetPolygonCount() const {
	return _polygons.size();
}

/**
 * \brief Get the Number of Concave Polygons in this Mesh
 * \return Number of Quads
 */
int Mesh::GetPolygonConcaveCount() const {
	return _polygonsConcave.size();
}

/**
 * \brief Get the Name of this Mesh
 * \return the Name
 */
const string& Mesh::GetName() const {
	return _name;
}

/**
 * \brief Get a Constant Triangle Iterator
 * \return iterator
 */
TriangleIteratorConst Mesh::GetTriangleIteratorConst() const
{
	return _triangles.begin();
}

/**
 * \brief Get a Constant Triangle Iterator pointing to the element after the last one
 * \return iterator
 */
TriangleIteratorConst Mesh::GetTriangleIteratorEndConst() const
{
	return _triangles.end();
}
