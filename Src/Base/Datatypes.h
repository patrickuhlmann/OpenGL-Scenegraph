#pragma once

#include <vector>
#include <istream>

#ifdef MEMORY_CHECK_ACTIVE
	#include "../../Libs/nvwa-0.8.2/debug_new.h"
#endif

const double PI = 3.141592653589;

class Material;

using namespace std;

union Vector3 { 
	struct sComponents {
		float x;
		float y;
		float z;
	} Components;

	float Array[3];

	Vector3();

	Vector3(float x, float y, float z);

	Vector3(const Vector3& v);
	Vector3(Vector3*& v);
	~Vector3();

	const float* GetConstPointer() const;

	float* GetPointer();

	friend ostream& operator<<(ostream& out, const Vector3& v);
};

union Vector4 { 
	struct sComponents { 
		float x;
		float y;
		float z;
		float w;
	} Components;

	float Array[4];

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

struct Triangle {
	const Vector3* Vertex1;
	const Vector3* Vertex2;
	const Vector3* Vertex3;
	const Vector3 Normal;
	const Material* Mat;

	Triangle(const Vector3* V1, const Vector3* V2, const Vector3* V3, const Vector3& Normal, const Material* Mat);
	~Triangle();

	friend ostream& operator<<(ostream& out, const Triangle& t);
};

struct Quad {
	const Vector3* Vertex1;
	const Vector3* Vertex2;
	const Vector3* Vertex3;
	const Vector3* Vertex4;
	const Vector3 Normal;
	const Material* Mat;

	Quad(const Vector3* V1, const Vector3* V2, const Vector3* V3, const Vector3* V4, const Vector3& Normal, const Material* Mat);
	~Quad();

	friend ostream& operator<<(ostream& out, const Quad& q);
};

struct Polygon {
	Vector3** Vertices;
	const Vector3 Normal;
	const Material* Mat;
	const int Size;

	Polygon(vector<Vector3*> Vertices, const Vector3& Normal, const Material* Mat);
	~Polygon();

	const Vector3* Get(int Index) const;
};
