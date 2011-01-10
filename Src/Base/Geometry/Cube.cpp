#include "Cube.h"

Cube::Cube(float Length) : Mesh() {
	Init(Length);
}

Cube::Cube(float Length, const string& Name) : Mesh(Name) {
	Init(Length);
}

void Cube::Init(float Length) {
	Material* Mat = new Material("CubeMat", Vector3(0, 1.0f, 0));
	Mat->SetDiffuse(Vector3(0, 0, 0.3f));
	_materials.insert(mmsm::value_type("CubeMat", Mat));

	// Texture?
	// Vertex Normals?

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
