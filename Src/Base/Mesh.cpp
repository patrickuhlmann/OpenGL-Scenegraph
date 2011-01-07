#include "Mesh.hpp"

/**
 * \brief Create an empty mesh with the name Dummy
 */
Mesh::Mesh() : _name("Dummy") {}

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

const Triangle Mesh::GetTriangle(int i) const {
	return _triangles.at(i);
}

const Material Mesh::GetMaterial(int i) const {
	return _material.at(i);
}


const string& Mesh::GetName() const {
	return _name;
}



int Mesh::GetVertexCount() const { return _vertices.size(); }

TriangleIterator Mesh::GetTriangleIterator() 
{ return _triangles.begin(); }

TriangleIterator Mesh::GetTriangleIteratorEnd()
{ return _triangles.end(); }

TriangleIteratorConst Mesh::GetTriangleIteratorConst() const
{ return _triangles.begin(); }

TriangleIteratorConst Mesh::GetTriangleIteratorEndConst() const
{ return _triangles.end(); }
