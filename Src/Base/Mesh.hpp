#pragma once

#include <vector>
#include "../Include/math3d.h"
#include "../Include/GL/glew.h"
#include <string>
#include "../Graph/Material.hpp"
#include "Triangle.h"
#include "Datatypes.h"

class MeshLoaderObj;

using namespace std;

typedef vector<float*> VertexVector;
typedef vector<Triangle*> TriangleVector;
typedef vector<QuadIndex*> QuadVector;
typedef vector<PolygonIndex*> PolygonVector;
typedef vector<float*> TextureCoordVector;
typedef vector<Material*> MaterialVector;

typedef TriangleVector::const_iterator TriangleIteratorConst;

/**
 * \brief Class to hold all data needed for a mesh. This includes: Vertices, Normals, Triangles, TextureCoordinates and Materials. It has as many Normals and Materials as Triangles and as many TextureCoordinates as Vertices
 */
class Mesh {
	public: 
		Mesh();
		~Mesh();

		const float* GetVertex(int i) const;
		const float* GetTextureCoord(int i) const;
		const Triangle* GetTriangle(int i) const;
		const QuadIndex* GetQuad(int i) const;
		const QuadIndex* GetQuadConcave(int i) const;
		const PolygonIndex* GetPolygon(int i) const;
		const PolygonIndex* GetPolygonConcave(int i) const;
		const Material* GetMaterial(int i) const;

		void Scale(float Factor);

		int GetVertexCount() const;
		int GetTriangleCount() const;
		int GetQuadCount() const;
		int GetQuadConcaveCount() const;
		int GetPolygonCount() const;
		int GetPolygonConcaveCount() const;

   		const string& GetName() const;

		TriangleIteratorConst GetTriangleIteratorConst() const;
		TriangleIteratorConst GetTriangleIteratorEndConst() const;

private:
	/** \brief Vector of Vertices (XYZ) */
	VertexVector   _vertices;
	/** \brief Triangles (Index of 3 Vertices) */
	TriangleVector _triangles;
	/** \brief Quad (Index of 4 Vertices) */
	QuadVector _quads;
	/** \brief Quad (Concave) (Index of 4 Vertices) */
	QuadVector _quadsConcave;
	/** \brief Polygon (Index of N Vertices) */
	PolygonVector _polygons;
	/** \brief Polygon (Convace) (Index of N Vertices) */
	PolygonVector _polygonsConcave;

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
