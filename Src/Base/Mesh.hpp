#pragma once

#include <vector>
#include "../Include/math3d.h"
#include "../Include/GL/glew.h"
#include <string>
#include "../Graph/Material.hpp"

class MeshLoaderObj;

using namespace std;

struct Triangle {
	int vert1, vert2, vert3;

	Triangle(int v1, int v2, int v3) {
		vert1 = v1;
		vert2 = v2;
		vert3 = v3;
	}
};

typedef M3DVector4f Color;
typedef M3DVector2f TextureCoord;
//typedef int Triangle[3];

typedef vector<float*> VertexVector;
typedef vector<float*> NormalVector;
typedef vector<float*> ColorVector;
typedef vector<Triangle> TriangleVector;
typedef vector<float*> TextureCoordVector;
typedef vector<Material> MaterialVector;

typedef VertexVector::iterator VertexIterator;
typedef NormalVector::iterator NormalIterator;
typedef ColorVector::iterator ColorIterator;
typedef TriangleVector::iterator TriangleIterator;
typedef TextureCoordVector:: iterator TextureCoordIterator;
typedef MaterialVector::iterator MaterialIterator;

class Mesh {
public: 
  // RAII should be done!
  Mesh();
  Mesh( const char* file );
  
  VertexIterator GetVertexIterator();
  VertexIterator GetVertexIteratorEnd();

  NormalIterator GetNormalIterator();
  NormalIterator GetNormalIteratorEnd();

  ColorIterator GetColorIterator();
  ColorIterator GetColorIteratorEnd();

  TriangleIterator GetTriangleIterator();
  TriangleIterator GetTriangleIteratorEnd();

  TextureCoordIterator GetTextureCoordIterator();
  TextureCoordIterator GetTextureCoordIteratorEnd();

  const float* GetVertex( int ) const;
  const float* GetNormal( int ) const;

  const string& GetName() const;

  GLint GetVertexCount() const;

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
