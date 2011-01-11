#include "Cube.h"

Material Cube::CubeMaterial = Material("CubeMat", Vector3(0, 1.0f, 0), Vector3(0, 0, 0.3f));

/** \brief Create a unnamed cube of the defined length placed at the origin of the coordinate system. The Material is Blue 
 * \param Length of the cube */
Cube::Cube(float Length) : Mesh() {
	Init(Length);
}

/** \brief Create a named cube of the defined length placed at the origin of the coordinate system
 * \param Length of the cube
 * \param Name of the cube
 */
Cube::Cube(float Length, const string& Name) : Mesh(Name) {
	Init(Length);
}

/** \brief Create a named cube of the defined length placed at the origin of the coordinate system
 * \param Length of the cube
 * \param Name of the cube
 */
Cube::Cube(float Length, const string& Name, const Material& Mat) : Mesh(Name) {
	Init(Length, Mat);
}

/** \brief Create a cube with a defined length and material
  * \param Length of the cube
  * \param material to use */
void Cube::Init(float Length, const Material& CMat) {
	Material* Mat = new Material(CMat);
	_materials.insert(mmsm::value_type("CubeMat", Mat));

    // Top
	_vertices.push_back(new Vector3(Length, Length, Length));
	_vertices.push_back(new Vector3(Length, Length, -Length));
	_vertices.push_back(new Vector3(-Length, Length, -Length));    
	_vertices.push_back(new Vector3(-Length, Length, Length));

	_quads.push_back(new Quad(_vertices[0], _vertices[1], _vertices[2], _vertices[3], Vector3(0, Length, 0), Mat));

    // Bottom
	_vertices.push_back(new Vector3(-Length, -Length, -Length));
	_vertices.push_back(new Vector3(Length, -Length, -Length));
	_vertices.push_back(new Vector3(Length, -Length, Length));
	_vertices.push_back(new Vector3(-Length, -Length, Length));

	_quads.push_back(new Quad(_vertices[7], _vertices[6], _vertices[5], _vertices[4], Vector3(0, -Length, 0), Mat));
    
    // Left side
	_quads.push_back(new Quad(_vertices[7], _vertices[3], _vertices[2], _vertices[4], Vector3(-Length, 0, 0), Mat));
    
    // Right side
	_quads.push_back(new Quad(_vertices[6], _vertices[5], _vertices[1], _vertices[0], Vector3(Length, 0, 0), Mat));

    // Front
	_quads.push_back(new Quad(_vertices[7], _vertices[6], _vertices[0], _vertices[3], Vector3(0, 0, Length), Mat));

    // Back
	_quads.push_back(new Quad(_vertices[1], _vertices[5], _vertices[4], _vertices[2], Vector3(0, 0, -Length), Mat));
}
