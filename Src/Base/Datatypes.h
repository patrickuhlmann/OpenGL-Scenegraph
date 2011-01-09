#pragma once

#include <vector>

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

	const float* GetConstPointer() const;

	float* GetPointer();
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
};

struct TriangleIndex {
	int Vertex1;
	int Vertex2;
	int Vertex3;

	TriangleIndex(int V1, int V2, int V3);
};

/*struct Triangle {
	Vector4 Vertex1;
	Vector4 Vertex2;
	Vector4 Vertex3;

	Triangle(const Vector4& V1, const Vector4& V2, const Vector4& V3);
};*/

struct QuadIndex {
	int Vertex1;
	int Vertex2;
	int Vertex3;
	int Vertex4;

	QuadIndex(int V1, int V2, int V3, int V4);
};

struct Quad {
	Vector4 Vertex1;
	Vector4 Vertex2;
	Vector4 Vertex3;
	Vector4 Vertex4;

	Quad(const Vector4& V1, const Vector4& V2, const Vector4& V3, const Vector4& V4);
};

struct Polygon {
	Vector4** Vertices;
	int Size;

	Polygon(int Size);

	void Set(int Index, const Vector4& Vertex);

	const Vector4& Get(int Index) const;

	~Polygon();
};

struct PolygonIndex {
	int* Vertices;
	int Size;

	PolygonIndex(vector<int>& Indices);

	const int Get(int Index) const;

	~PolygonIndex();
};
