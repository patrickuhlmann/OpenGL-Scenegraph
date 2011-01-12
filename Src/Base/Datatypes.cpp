#include "Datatypes.h"

/** \brief Convert an IntegerNumber to a string
 * \param x to convert
 */
string IntegerToString(int x) {
	ostringstream o;
	
	//if (!(o << x))
	//	throw BadConversion("IntegerToString failed for: " + x);
	o << x;
	
	return o.str();
}

/** \brief Outputs the Vector3 to a Stream. It prints each component of the vector */
ostream& operator<<(ostream& out, const Vector3& v) {
	return out << "(" << v.Components.x << ", " << v.Components.y << ", " << v.Components.z << ")" << endl;
}

/** \brief Initializes the Vector with all 0 */
Vector3::Vector3() {
	Array[0] = 0;
	Array[1] = 0;
	Array[2] = 0;
}

/** \brief Initializes the Vector with the arguments
  * \param x set the x coordinate
  * \param y set the y coordinate
  * \param z set the z coordinate
  */
Vector3::Vector3(float x, float y, float z) { 
	Array[0] = x;
	Array[1] = y;
	Array[2] = z;
}

/** \brief Copies the values from the vector given in the argument to itself
  * \param v to get the values from
  */
Vector3::Vector3(const Vector3& v) {
	Array[0] = v.Array[0];
	Array[1] = v.Array[1];
	Array[2] = v.Array[2];
}

/** \brief Copies the values from the vector given in the argumetn to itself
  * \param v to get the values from
  */
Vector3::Vector3(Vector3*& v) {
	Array[0] = v->Array[0];
	Array[1] = v->Array[1];
	Array[2] = v->Array[2];
}

const float* Vector3::GetConstPointer() const {
	return Array;
}

float* Vector3::GetPointer() {
	return Array;
}

ostream& operator<<(ostream& out, const Vector4& v) {
	return out << "(" << v.Array[0] << ", " << v.Array[1] << ", " << v.Array[2] << ", " << v.Array[3] << ")" << endl;
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

ostream& operator<<(ostream& out, const Triangle& t) {
	return out << *(t.Vertex1) << ", " << *(t.Vertex2) << ", " << *(t.Vertex3) << endl;
}

Triangle::Triangle(const Vector3* V1, const Vector3* V2, const Vector3* V3, const Vector3& Normal, const Material* Mat) : Vertex1(V1), Vertex2(V2), Vertex3(V3), Normal(Normal), Mat(Mat) { };

ostream& operator<<(ostream& out, const Quad& q) {
	return out << *(q.Vertex1) << ", " << *(q.Vertex2) << ", " << *(q.Vertex3) << ", " << *(q.Vertex4) << endl;
}

Quad::Quad(const Vector3* V1, const Vector3* V2, const Vector3* V3, const Vector3* V4, const Vector3& Normal, const Material* Mat) : Vertex1(V1), Vertex2(V2), Vertex3(V3), Vertex4(V4), Normal(Normal), Mat(Mat) { };

Polygon::Polygon(vector<Vector3*> Vertices, const Vector3& Normal, const Material* Mat) : Size(Vertices.size()), Normal(Normal), Mat(Mat) {
	this->Vertices = new Vector3*[Vertices.size()];
	for (int i=0; i<Vertices.size(); ++i) {
		this->Vertices[i] = Vertices[i];
	}
}

const Vector3* Polygon::Get(int Index) const {
	return Vertices[Index];
}

Polygon::~Polygon() {
	delete[] Vertices;
}
