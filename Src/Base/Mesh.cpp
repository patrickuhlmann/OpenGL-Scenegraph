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

	for (NormalVector::iterator it = _normals.begin(); it != _normals.end(); ++it) {
		delete[] *it;	
	}

	for (TextureCoordVector::iterator it = _textureCoords.begin(); it != _textureCoords.end(); ++it) {
		delete[] *it;
	}
}

/**
 * \brief Get the Vertex at position i
 * \param i index of the Vertex to get
 * \return pointer to the vertex (XYZ)
 */
const float* Mesh::GetVertex( int i ) const {
	return _vertices.at(i);
}

/**
 * \brief Get the Normal at position i
 * \param i index of the Normal to get
 * \return pointer to the normal (XYZ)
 */
const float* Mesh::GetNormal( int i ) const {
	return _normals.at(i);
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
const Triangle& Mesh::GetTriangle(int i) const {
	return _triangles.at(i);
}

/**
 * \brief Get the Material at position i
 * \param i index of the Material
 * \return reference to the material
 */
const Material& Mesh::GetMaterial(int i) const {
	return _material.at(i);
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
