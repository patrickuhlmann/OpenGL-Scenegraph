#pragma once

#include <vector>
#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include <glog/logging.h>

#ifdef MEMORY_CHECK_ACTIVE
	#include "../../Libs/nvwa-0.8.2/debug_new.h"
#endif

/** \brief Constant PI to 12 places to use in Calculations */
const double PI = 3.141592653589;

class Material;

using namespace std;

string IntegerToString(int x);

/** \brief Vector with 3 elements. These can be accessed with x,y and z or over an array. Furthermore you can get pointers to the data. */
union Vector3 {
	/** \brief Access to x, y and z coordinates */ 
	struct sComponents {
		float x;
		float y;
		float z;
	} Components;

	/** \brief Elements in Array: x, y, z */
	float Array[3];

	Vector3();
	Vector3(float x, float y, float z);

	Vector3(const Vector3& v);
	Vector3(Vector3*& v);

	const float* GetConstPointer() const;

	float* GetPointer();

	friend ostream& operator<<(ostream& out, const Vector3& v);
};

/** \brief Vector4 to store 3 coordinates and w or color information */
union Vector4 { 
	/** \brief Access to x, y and z coordinate and w */
	struct sComponents { 
		float x;
		float y;
		float z;
		float w;
	} Components;

	/** \brief Array containing one element for x, y, z and w */
	float Array[4];

	/** \brief Access to r, g, b and alpha value for a color */
	struct {
		float r;
		float g;
		float b;
		float a;
	} Color;

	Vector4();

	Vector4(float x, float y, float z, float w);

	Vector4(const Vector4& v);

	const float* GetConstPointer() const;

	float* GetPointer();

	friend ostream& operator<<(ostream& out, const Vector4& v);
};

/** Represents a triangle consisting of 3 vertices, 1 normal and material information. The class is designed for performance and to work together with Mesh. This means it is initialized with pointers to the Vertices and the Material but it does not release this memory at the end. This is supposed to be done from the Mesh class! */
struct Triangle {
	/** \brief First Vertex of the Triangle */
	const Vector3* Vertex1;
	/** \brief Second Vertex of the Triangle */
	const Vector3* Vertex2;
	/** \brief Third Vertex of the Triangle */
	const Vector3* Vertex3;
	/** \brief Normal of the Triangle */
	const Vector3 Normal;
	/** \brief Material to use for the Triangle */
	const Material* Mat;

	Triangle(const Vector3* V1, const Vector3* V2, const Vector3* V3, const Vector3& Normal, const Material* Mat);

	friend ostream& operator<<(ostream& out, const Triangle& t);
};

/** Represents a quad consisting of 4 vertices, 1 normal and material information. The class is designed for performance and to work together with Mesh. This means it is initialized with pointers to the Vertices and the Material but it does not release this memory at the end. This is supposed to be done from the Mesh class! */
struct Quad {
	/** \brief First Vertex of the Quad */
	const Vector3* Vertex1;
	/** \brief Second Vertex of the Quad */
	const Vector3* Vertex2;
	/** \brief Third Vertex of the Quad */
	const Vector3* Vertex3;
	/** \brief Forth Vertex of the Quad */
	const Vector3* Vertex4;
	/** \brief Normal of the Quad */
	const Vector3 Normal;
	/** \brief Material to use for the Quad */
	const Material* Mat;

	Quad(const Vector3* V1, const Vector3* V2, const Vector3* V3, const Vector3* V4, const Vector3& Normal, const Material* Mat);

	friend ostream& operator<<(ostream& out, const Quad& q);
};

/** Represents a polygon consisting as many vertices as we want, 1 normal and material information. The class is designed for performance and to work together with Mesh. This means it is initialized with pointers to the Vertices and the Material but it does not release this memory at the end. This is supposed to be done from the Mesh class! */
struct Polygon {
	/** \brief Array to the Vertices pointers for this polygon */
	Vector3** Vertices;
	/** \brief Normal for this Polygon */
	const Vector3 Normal;
	/** \brief Material for this Polygon */
	const Material* Mat;
	/** \brief Size of the Polygon (how many vertices) */
	const int Size;

	Polygon(vector<Vector3*>& Vertices, const Vector3& Normal, const Material* Mat);
	~Polygon();

	const Vector3* Get(int Index) const;
};
