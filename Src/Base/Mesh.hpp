#pragma once

#include <glog/logging.h>
#include <vector>
#include "../Include/math3d.h"
#include <string>
#include "Material.hpp"
#include "Datatypes.h"
#include <map>
#include <set>

#ifdef MEMORY_CHECK_ACTIVE
	#include "../../Libs/nvwa-0.8.2/debug_new.h"
#endif

class MeshLoaderObj;

using namespace std;

typedef vector<Vector3*> VertexVector;
typedef vector<Triangle*> TriangleVector;
typedef vector<Quad*> QuadVector;
typedef vector<Polygon*> PolygonVector;
typedef vector<float*> TextureCoordVector;
typedef multimap<string, Material*> mmsm;
typedef TriangleVector::const_iterator TriangleIteratorConst;
typedef set<string> NameSet;
typedef pair<set<string>::iterator,bool> NameSetPair;

/**
 * \brief Class to hold all data needed for a mesh. This includes: Vertices, Triangles, Quads, Polygons and Materials. The Triangles, Quads and Polygons reference the Material and Vertices saved in this class
 */
class Mesh {
	public: 
		Mesh();
		Mesh(const string& Name);
		virtual ~Mesh();

		const Vector3* GetVertex(int i) const;
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

	protected:
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
		/** \brief Hold the Materials */
		mmsm _materials;

		/** \brief Name of the Mesh */
		string _name;

	private:
		/** \brief will be increased for every created mesh */
		static int MeshCounter;
		/** \brief hold the name of all created meshs */
		static NameSet Names;
		static bool IsNameUnique(const string& name);

friend class MeshLoaderObj;
friend class MeshFileLoader;
friend class TestMeshLoaders;
};
