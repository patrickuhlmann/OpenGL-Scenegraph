#include "Datatypes.h"

Vector3::Vector3() {
	Array[0] = 0;
	Array[1] = 0;
	Array[2] = 0;
}

Vector3::Vector3(float x, float y, float z) { 
	Array[0] = x;
	Array[1] = y;
	Array[2] = z;
}

Vector3::Vector3(const Vector3& v) {
	Array[0] = v.Array[0];
	Array[1] = v.Array[1];
	Array[2] = v.Array[2];
}

const float* Vector3::GetConstPointer() const {
	return Array;
}

float* Vector3::GetPointer() {
	return Array;
}

Vector4::Vector4() { 
	Array[0] = 0;
	Array[1] = 0;
	Array[2] = 0;
	Array[3] = 0;
}

Vector4::Vector4(float x, float y, float z, float w) { 
	Array[0] = x;
	Array[1] = y;
	Array[2] = z;
	Array[3] = w;
}

Vector4::Vector4(const Vector4& v) {
	Array[0] = v.Components.x;
	Array[1] = v.Components.y;
	Array[2] = v.Components.z;
	Array[3] = v.Components.w;
}

const float* Vector4::GetConstPointer() const {
	return Array;
}

float* Vector4::GetPointer() {
	return Array;
}

TriangleIndex::TriangleIndex(int V1, int V2, int V3) : Vertex1(V1), Vertex2(V2), Vertex3(V3) { };

//Triangle::Triangle(const Vector4& V1, const Vector4& V2, const Vector4& V3) : Vertex1(V1), Vertex2(V2), Vertex3(V3) { };

QuadIndex::QuadIndex(int V1, int V2, int V3, int V4) : Vertex1(V1), Vertex2(V2), Vertex3(V3), Vertex4(V4) { };

Quad::Quad(const Vector4& V1, const Vector4& V2, const Vector4& V3, const Vector4& V4) : Vertex1(V1), Vertex2(V2), Vertex3(V3), Vertex4(V4) { };

Polygon::Polygon(int Size) {
	Size = Size;
	Vertices = new Vector4*[Size];
}

void Polygon::Set(int Index, const Vector4& Vertex) {
	Vertices[Index] = new Vector4(Vertex);
}

const Vector4& Polygon::Get(int Index) const {
	return *Vertices[Index];
}

Polygon::~Polygon() {
	for (int i=0; i<Size; i++) {
		delete Vertices[i];
	}

	delete[] Vertices;
}

PolygonIndex::PolygonIndex(vector<int>& Indices) {
	Size = Indices.size();
	Vertices = new int[Size];
	for (int i=0; i<Indices.size(); i++) {
		Vertices[i] = Indices[i];
	}
}

const int PolygonIndex::Get(int Index) const {
	return Vertices[Index];
}

PolygonIndex::~PolygonIndex() {
	delete[] Vertices;
}

