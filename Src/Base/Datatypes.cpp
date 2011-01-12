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

/** \brief Outputs the Vector3 to a Stream. It prints each component of the vector
 * \param out stream to print to
 * \param v we want to print */
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

/** \brief Get a const pointer to the array of this Vector3 */
const float* Vector3::GetConstPointer() const {
	return Array;
}

/** \brief Get a regular pointer to the array of this Vector3 */
float* Vector3::GetPointer() {
	return Array;
}

/** \brief Output (print all components) of this Vector4
 * \param out stream to print to
 * \param v which we print out */
ostream& operator<<(ostream& out, const Vector4& v) {
	return out << "(" << v.Array[0] << ", " << v.Array[1] << ", " << v.Array[2] << ", " << v.Array[3] << ")" << endl;
}

/** \brief Initialize an empty Vector4. That means all elements are set to 0 */
Vector4::Vector4() { 
	Array[0] = 0;
	Array[1] = 0;
	Array[2] = 0;
	Array[3] = 0;
}

/** \brief Initialize an Vector4 with the arguments
  * \param x coordinate
  * \param y coordinate
  * \param z coordinate
  * \param w
  */
Vector4::Vector4(float x, float y, float z, float w) { 
	Array[0] = x;
	Array[1] = y;
	Array[2] = z;
	Array[3] = w;
}

/** \brief Copies all Components of the Vector given in the arguments. The values are completly independent of the original
 * \param v to copy the values from
 */
Vector4::Vector4(const Vector4& v) {
	Array[0] = v.Components.x;
	Array[1] = v.Components.y;
	Array[2] = v.Components.z;
	Array[3] = v.Components.w;
}

/** \brief Get a const pointer to the the array of this Vector4 */
const float* Vector4::GetConstPointer() const {
	return Array;
}

/** \brief Get a pointer to the array of this Vector4 */
float* Vector4::GetPointer() {
	return Array;
}

/** \brief Output the vertices of a Triangle to the stream
 * \param out stream to print to
 * \param t Triangle to print
 */
ostream& operator<<(ostream& out, const Triangle& t) {
	return out << *(t.Vertex1) << ", " << *(t.Vertex2) << ", " << *(t.Vertex3) << endl;
}

/** \brief Initialize the Triangle with the Vertices, Normal and Material
 * \param V1 first Vertex, note: we don't take ownership of the pointer and therefore do not free the memory at the end!
 * \param V2 second Vertex, note: we don't take ownership of the pointer and therefore do not free the memory at the end!
 * \param V3 third Vertex, note: we don't take ownership of the pointer and therefore do not free the memory at the end!
 * \þaram Normal
 * \param Mat to use for this triangle, note: we don't take ownership of the pointer and therefore do not free the memory at the end! */
Triangle::Triangle(const Vector3* V1, const Vector3* V2, const Vector3* V3, const Vector3& Normal, const Material* Mat) : Vertex1(V1), Vertex2(V2), Vertex3(V3), Normal(Normal), Mat(Mat) { };

/** \brief Output all the Vertices of a Quad
 * \param out stream to output to
 * \param q which we output
 */
ostream& operator<<(ostream& out, const Quad& q) {
	return out << *(q.Vertex1) << ", " << *(q.Vertex2) << ", " << *(q.Vertex3) << ", " << *(q.Vertex4) << endl;
}

/** \brief Initialize the Quad with the Vertices, Normal and Material
 * \param V1 first Vertex, note: we don't take ownership of the pointer and therefore do not free the memory at the end!
 * \param V2 second Vertex, note: we don't take ownership of the pointer and therefore do not free the memory at the end!
 * \param V3 third Vertex, note: we don't take ownership of the pointer and therefore do not free the memory at the end!
 * \param V4 third Vertex, note: we don't take ownership of the pointer and therefore do not free the memory at the end!
 * \þaram Normal
 * \param Mat to use for this quad, note: we don't take ownership of the pointer and therefore do not free the memory at the end! */
Quad::Quad(const Vector3* V1, const Vector3* V2, const Vector3* V3, const Vector3* V4, const Vector3& Normal, const Material* Mat) : Vertex1(V1), Vertex2(V2), Vertex3(V3), Vertex4(V4), Normal(Normal), Mat(Mat) { };

/** \brief Initialize the Quad with the Vertices, Normal and Material
 * \param Vertices vector containing lots of references to Vertices, note: we don't take ownership of the pointers and therefore do not free the memory at the end!
 * \þaram Normal
 * \param Mat to use for this polygon, note: we don't take ownership of the pointer and therefore do not free the memory at the end! */
Polygon::Polygon(vector<Vector3*>& Vertices, const Vector3& Normal, const Material* Mat) : Size(Vertices.size()), Normal(Normal), Mat(Mat) {
	if (Vertices.size() <= 4)
		DLOG(WARNING) << "Polygon initialized which could also be a Triangle or a Quad" << endl;

	this->Vertices = new Vector3*[Vertices.size()];
	for (int i=0; i<Vertices.size(); ++i) {
		this->Vertices[i] = Vertices[i];
	}
}

/** \brief Return a Vertex of this polygon identified by the index
 * \param Index of the Vertex
 */
const Vector3* Polygon::Get(int Index) const {
	return Vertices[Index];
}

/** \brief Free the Array of Vertices, but not the Vertices themselfes! */
Polygon::~Polygon() {
	delete[] Vertices;
}
