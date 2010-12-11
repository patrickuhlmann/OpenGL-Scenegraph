#include "MeshLoaderObj.h"

using namespace std;

/**
 *	\brief Load a Mesh from a Obj file
 *	
 *	\param Name path to a file
 *  \return Mesh if successfull, 0 otherwise
 */
Mesh* MeshLoaderObj::Load(istream& Stream) {
	Mesh* M = new Mesh();

	string Definition;

	DLOG(INFO) << "Start reading Mesh" << endl;

	/* How we read it in: always process one line at a time. First we read the first string on the line. This indicates what type of definition we have. With the switch case we handle every single Definition (Vertices, Comments, Normals, etc.) and process it */
	while(!Stream.eof() && !Stream.bad()) {
		// When we have empty lines there are \r or \n or maybe \t or whitespaces
		while (Stream.peek() == '\r' || Stream.peek() == '\n' || Stream.peek() == '\t' || Stream.peek() == ' ')
			Stream.ignore(1);

		// Maybe we had some empty lines at the end
		if (Stream.eof())
			break;

		// Special case comments they don't need to have a whitespace after them so we need to handle them separately
		if (Stream.peek() == '#')
			Definition = "#";
		else
			getline(Stream, Definition, ' ');


		/* PROCESS LINES */

		// Comments -> Ignore
		if (Definition.compare("#") == 0) {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Comment - ignored" << endl;


		// Object Name
		// o object name
		} else if (Definition[0] == 'o') {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Object Name - ignored" << endl;


		// Group Name
		// g group name
		} else if (Definition[0] == 'g') {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Group Name - ignored" << endl;


		// Smooth Shading activate/deactivate
		// s 1
  		// s off
		} else if (Definition[0] == 's') {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Shading Properties - ignored" << endl;


		// Reference External Material File
		// mtllib [external .mtl file name]
		} else if (Definition.compare("mtllib") == 0) {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Reference to external Material file - ignored" << endl;


		// Material Group
		// usemtl [material name]
		} else if (Definition.compare("usemtl") == 0) {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Material Group Definition - ignored" << endl;


		// Vertices, with (x,y,z[,w]) coordinates, w is optional.
		// v 0.123 0.234 0.345 1.0
		} else if (Definition.compare("v") == 0) {
			float* v = new float[3];
			ReadVector4fTo3f(v, Stream, true, false);
			M->_vertices.push_back(v);
			DLOG(INFO) << "Found Vertex: " << v[0] << ", " << v[1] << ", " << v[2] << endl;


		// Texture coordinates, in (u,v[,w]) coordinates, w is optional.
		// vt 0.500 -1.352 [0.234]
		} else if (Definition.compare("vt") == 0) {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Texture Coordinate - ignored" << endl;


		// Normals in (x,y,z) form; normals might not be unit.
		// vn 0.707 0.000 0.707
		// ignore as we calculate them ourselves so they are in the right order and not for a point but for the whole triangle
		} else if (Definition.compare("vn") == 0) {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Normal - ignored" << endl;


		// Face Definitions 
		// f 1 2 3						-> Vertex index starting with 1, face can contain more than three elements!
		// f 3/1 4/2 5/3					-> Vertex/texture-coordinate
		// f 6/4/1 3/5/3 7/6/5			-> Vertex/texture-coordinate/normal
		// f v1//vn1 v2//vn2 v3//vn3	-> Vertex/normal
		} else if (Definition.compare("f") == 0) {
			Triangle t;
			ReadTriangle(&t, Stream);
			M->_triangles.push_back(t);
			DLOG(INFO) << "Found Face " << t.vert1 << ", " << t.vert2 << ", " << t.vert4 << endl;
			float* CalculatedNormal = new float[3];
			m3dFindNormal(CalculatedNormal, M->_vertices[t.vert1-1], M->_vertices[t.vert2-1], M->_vertices[t.vert4-1]);
			M->_normals.push_back(CalculatedNormal);
			DLOG(INFO) << "Calculated Normal " << CalculatedNormal[0] << ", " << CalculatedNormal[1] << ", " << CalculatedNormal[2] << endl;


		// any other keywords -> ignore them
		} else {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Unknown Definition a" << Definition << "a" << endl;
		}
	}




	// Add Color and Texture for all Vertices
	for (VertexIterator it = M->_vertices.begin(); it != M->_vertices.end(); ++it) {
		float* Color = new float[4];
		Color[0] = 0.5;
		Color[1] = 0.5;
		Color[2] = 0.5;
		Color[3] = 0.5;

		float* Texture = new float[2];
		Texture[0] = 0;
		Texture[1] = 0;

		M->_colors.push_back(Color);
		M->_textureCoords.push_back(Texture);
	}

	if (Stream.bad()) {
		DLOG(WARNING) << "Error reading in Mesh" << endl;
		return 0;
	} else {
		DLOG(INFO) << "Mesh Successfully read in" << endl;
		return M;
	}
}

/**
 *	\brief Check if this is a Obj file
 *
 *	\param Name path to a file
 *	\return true if it ends with .obj, false otherwise
 */
bool MeshLoaderObj::Accept(istream& Stream) {
	return true;
}

void MeshLoaderObj::ReadVector3f(float* v, istream& Stream) {
	Stream >> v[0];
	Stream >> v[1];
	Stream >> v[3];
}

void MeshLoaderObj::ReadVector4fTo3f(float* v, istream& Stream, bool OptionalW, bool OptionalWInBrackets) {
	// Read in x to z
	Stream >> v[0];
	Stream >> v[1];
	Stream >> v[2];

	// w is optional and if there it is in brackets
	float w;
	if (OptionalW && OptionalWInBrackets) {
		char c;
		Stream >> c;
		if (c != '[') {
			Stream.unget();
			w = 1.0f;
		} else {
			Stream >> w;
			Stream.ignore('\n');
		}
	// w is optional but if there has no brackets around
	} else if (OptionalW && !OptionalWInBrackets) {
		Stream >> w;
		if (Stream.fail()) {
			Stream.clear();
			w = 1.0f;
		}
	} else {
		Stream >> w;
	}

	// normalize so we don't need the 
	v[0] = v[0] / w;
	v[1] = v[1] / w;
	v[2] = v[2] / w;
}

//# Face Definitions 
// 1 2 3						-> Vertex index starting with 1, face can contain more than three elements!
// 3/1 4/2 5/3					-> Vertex/texture-coordinate
// 6/4/1 3/5/3 7/6/5			-> Vertex/texture-coordinate/normal
// v1//vn1 v2//vn2 v3//vn3		-> Vertex/normal
void MeshLoaderObj::ReadTriangle(Triangle* t, istream& Stream) {
	Stream >> t->vert1;
	Stream.ignore(INT_MAX, ' ');
	Stream >> t->vert2;
	Stream.ignore(INT_MAX, ' ');
	Stream >> t->vert4;

	// It is Vertex/Texture Vertex/Texture/Normal or Vertex/Normal Format
	if (Stream.peek() == '/') {
		int i;
		Stream.ignore(1);

		// Finish VertexNormal Format
		if (Stream.peek() == '/') {
			Stream.ignore(1);
			Stream >> i;
		// Finish Vertex/Texture
		} else {
			Stream >> i;
			// Finish Vertex/Texture/Normal
			if (Stream.peek() == '/') {
				Stream.ignore(1);
				Stream >> i;
			}
		}
	}

	// If there are spaces or tabs ignore them
	while (Stream.peek() == '\t' || Stream.peek() == ' ')
		Stream.ignore(1);

	if (Stream.peek() != '\n' && Stream.peek() != '\r') {
		DLOG(WARNING) << "Face is not a Triangle but has more elements!" << endl;
		Stream.ignore(INT_MAX, '\n');
	}
}
