#include "Mesh.hpp"

/**
 * \brief Create an empty mesh with the name Dummy
 */
Mesh::Mesh() : _name("Dummy") {}

/**
 * \brief Destructor frees all Vertices, Normals and TextureCoordinates
 */
Mesh::~Mesh() {
	for (VertexVector::iterator it = _vertices.begin(); it != _vertices.end(); ++it) {
		delete[] *it;
	}

	for (TextureCoordVector::iterator it = _textureCoords.begin(); it != _textureCoords.end(); ++it) {
		delete[] *it;
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

	/*for (MaterialVector::iterator it = _material.begin(); it != _material.end(); ++it) {
		delete (*it);
	}*/
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
 * \brief Get the TextureCoordinates at position i
 * \param i index of the TextureCoordinates
 * \return pointer to the TextureCoordinates (ST)
 */
const float* Mesh::GetTextureCoord( int i ) const {
	return _textureCoords.at(i);
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
