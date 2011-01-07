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

typedef TriangleVector::iterator TriangleIterator;
typedef TriangleVector::const_iterator TriangleIteratorConst;

/**
 * \brief Class to hold all data needed for a mesh. This includes: Vertices, Normals, Triangles, TextureCoordinates and Materials. It has as many Normals and Materials as Triangles and as many TextureCoordinates as Vertices
 */
class Mesh {
	public: 
		Mesh();

		const float* GetVertex(int i) const;
		const float* GetNormal(int i) const;
		const float* GetTextureCoord(int i) const;
		const Triangle GetTriangle(int i) const;
		const Material GetMaterial(int i) const;

   TriangleIterator GetTriangleIterator();
   TriangleIteratorConst GetTriangleIteratorConst() const;
   TriangleIterator GetTriangleIteratorEnd();
   TriangleIteratorConst GetTriangleIteratorEndConst() const;

   const string& GetName() const;

   int GetVertexCount() const;
   int GetTriangleCount() const;

private:
  VertexVector   _vertices;  // XYZ
  NormalVector   _normals;   // one normal per vertex
  TriangleVector _triangles; // indexes for vertex vector
  MaterialVector _material;  // for material
  TextureCoordVector  _textureCoords; // can be set to all zeroes by default
  string _name;	// name of the mesh for example name of the file where it was loaded from

friend class MeshLoaderObj;
friend class MeshFileLoader;
friend class TestMeshLoaders;
};
