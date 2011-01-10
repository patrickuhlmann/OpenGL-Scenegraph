#pragma once

#include <vector>
#include "../Include/math3d.h"
#include <string>
#include "../Graph/Material.hpp"
#include "Datatypes.h"
#include <map>

class MeshLoaderObj;

using namespace std;

typedef vector<Vector3*> VertexVector;
typedef vector<Triangle*> TriangleVector;
typedef vector<Quad*> QuadVector;
typedef vector<Polygon*> PolygonVector;
typedef vector<float*> TextureCoordVector;
typedef multimap<string, Material*> mmsm;

typedef TriangleVector::const_iterator TriangleIteratorConst;

/**
 * \brief Class to hold all data needed for a mesh. This includes: Vertices, Normals, Triangles, TextureCoordinates and Materials. It has as many Normals and Materials as Triangles and as many TextureCoordinates as Vertices
 */
class Mesh {
	public: 
		Mesh();
		~Mesh();

		const Vector3* GetVertex(int i) const;
		const float* GetTextureCoord(int i) const;
		const Triangle* GetTriangle(int i) const;
		const Quad* GetQuad(int i) const;
		const Quad* GetQuadConcave(int i) const;
		const Polygon* GetPolygon(int i) const;
		const Polygon* GetPolygonConcave(int i) const;

		void Scale(float Factor);

		const TriangleVector& GetTriangleVector() const;
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
	mmsm _materials;

	/** \brief Vector of TextureCoordinates, should be one per Vertex */
	TextureCoordVector  _textureCoords;
	/** \brief Name of the Mesh */
	string _name;

friend class MeshLoaderObj;
friend class MeshFileLoader;
friend class TestMeshLoaders;
};
