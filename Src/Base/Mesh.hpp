#pragma once

#include <vector>
#include "../Include/math3d.h"
#include "../Include/GL/glew.h"
#include <string>
#include "../Graph/Material.hpp"
#include "Triangle.h"

class MeshLoaderObj;

using namespace std;

typedef vector<float*> VertexVector;
typedef vector<float*> NormalVector;
typedef vector<Triangle> TriangleVector;
typedef vector<float*> TextureCoordVector;
typedef vector<Material> MaterialVector;

typedef TriangleVector::const_iterator TriangleIteratorConst;

/**
 * \brief Class to hold all data needed for a mesh. This includes: Vertices, Normals, Triangles, TextureCoordinates and Materials. It has as many Normals and Materials as Triangles and as many TextureCoordinates as Vertices
 */
class Mesh {
	public: 
		Mesh();
		~Mesh();

		const float* GetVertex(int i) const;
		const float* GetNormal(int i) const;
		const float* GetTextureCoord(int i) const;
		const Triangle& GetTriangle(int i) const;
		const Material& GetMaterial(int i) const;

		void Scale(float Factor);

		int GetVertexCount() const;
		int GetTriangleCount() const;

   		const string& GetName() const;

		TriangleIteratorConst GetTriangleIteratorConst() const;
		TriangleIteratorConst GetTriangleIteratorEndConst() const;

private:
	/** \brief Vector of Vertices (XYZ) */
	VertexVector   _vertices;
	/** \brief Vector of Normals (XYZ), should be one per Vertex */
	NormalVector   _normals;
	/** \brief Triangles (Index of 3 Vertices) */
	TriangleVector _triangles;
	/** \brief Vector of Materials, should be one per Triangle */
	MaterialVector _material;
	/** \brief Vector of TextureCoordinates, should be one per Vertex */
	TextureCoordVector  _textureCoords;
	/** \brief Name of the Mesh */
	string _name;

friend class MeshLoaderObj;
friend class MeshFileLoader;
friend class TestMeshLoaders;
};
