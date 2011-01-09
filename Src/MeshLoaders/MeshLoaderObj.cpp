#include "MeshLoaderObj.h"

using namespace std;

/**
 * \brief Go through the whole string and remove all line breaks (n) and tabs (t)
 * \param str to go through
 */
void RemoveLineBreaks(string& str) {
	for (int i=0; i<str.size(); i++) {
		if (str[i] == '\t' || str[i] == '\n') {
			str.erase(i, 1);
			i--;
		}
	}
}

/**
 *	\brief Load a Mesh from a Obj file
 *	
 *	\param Stream to load a mesh from
 *  \return Mesh if successfull, 0 otherwise
 */
Mesh* MeshLoaderObj::Load(istream& Stream) {
	Mesh* M = new Mesh();

	string Definition;

	// Material initialize
	Material* Mat = new Material("Proto", Vector3(1.0f, 1.0f, 1.0f));
	Mat->SetTransparency(1.0f);
	M->_materials.insert(mmsm::value_type(string("Proto"), Mat));

	//DLOG(INFO) << "Start reading Mesh" << endl;

	/* How we read it in: always process one line at a time. First we read the first string on the line. This indicates what type of definition we have. With the switch case we handle every single Definition (Vertices, Comments, Normals, etc.) and process it */
	while(!Stream.eof() && Stream.good()) {
		// When we have empty lines there are \r or \n or maybe \t or whitespaces
		while (Stream.peek() == '\r' || Stream.peek() == '\n' || Stream.peek() == '\t' || Stream.peek() == ' ')
			Stream.ignore(1);

		// Maybe we had some empty lines at the end
		if (Stream.eof())
			break;

		// Special case comments they don't need to have a whitespace after them so we need to handle them separately
		if (Stream.peek() == '#')
			Definition = "#";

		// Special case 2: only g without name is also valid
		else if (Stream.peek() == 'g')
			Definition = "g";
		else
			getline(Stream, Definition, ' ');


		/* PROCESS LINES */

		// Comments -> Ignore
		if (Definition.compare("#") == 0) {
			Stream.ignore(INT_MAX, '\n');
			//DLOG(INFO) << "Found Comment - ignored" << endl;


		// Object Name
		// o object name
		} else if (Definition[0] == 'o') {
			Stream.ignore(INT_MAX, '\n');
			//DLOG(INFO) << "Found Object Name - ignored" << endl;


		// Group Name
		// g group name
		} else if (Definition[0] == 'g') {
			Stream.ignore(INT_MAX, '\n');
			//DLOG(INFO) << "Found Group Name - ignored" << endl;


		// Smooth Shading activate/deactivate
		// s 1
  		// s off
		} else if (Definition[0] == 's') {
			Stream.ignore(INT_MAX, '\n');
			//DLOG(INFO) << "Found Shading Properties - ignored" << endl;


		// Reference External Material File
		// mtllib [external .mtl file name]
		} else if (Definition.compare("mtllib") == 0) {
			string FileName;
			getline(Stream, FileName, '\n');
			//DLOG(INFO) << "Found Reference to external Material file: " << FileName << endl;
			ReadMaterialFile(M->_materials, FileName);

		// Material Group
		// usemtl [material name]
		} else if (Definition.compare("usemtl") == 0) {
			string MatName;
			getline(Stream, MatName, '\n');
			RemoveLineBreaks(MatName);
			mmsm::iterator it = M->_materials.find(MatName);
			if (it == M->_materials.end())
				DLOG(WARNING) << "Couldn't find a material in the material map: " << MatName << endl;
			else
				Mat = it->second;
			//DLOG(INFO) << "Apply Material: " << MatName << endl;
			

		// Vertices, with (x,y,z[,w]) coordinates, w is optional.
		// v 0.123 0.234 0.345 1.0
		} else if (Definition.compare("v") == 0) {
			Vector3* v = new Vector3();
			ReadVector4fTo3f(v->GetPointer(), Stream, true, false);
			M->_vertices.push_back(v);
			//DLOG(INFO) << "Found Vertex: " << *v << ", number: " << M->_vertices.size()-1 << endl;


		// Texture coordinates, in (u,v[,w]) coordinates, w is optional.
		// vt 0.500 -1.352 [0.234]
		} else if (Definition.compare("vt") == 0) {
			Stream.ignore(INT_MAX, '\n');
			//DLOG(INFO) << "Found Texture Coordinate - ignored" << endl;


		// Normals in (x,y,z) form; normals might not be unit.
		// vn 0.707 0.000 0.707
		// ignore as we calculate them ourselves so they are in the right order and not for a point but for the whole triangle
		} else if (Definition.compare("vn") == 0) {
			Stream.ignore(INT_MAX, '\n');
			//DLOG(INFO) << "Found Normal - ignored" << endl;


		// Face Definitions 
		// f 1 2 3						-> Vertex index starting with 1, face can contain more than three elements!
		// f 3/1 4/2 5/3					-> Vertex/texture-coordinate
		// f 6/4/1 3/5/3 7/6/5			-> Vertex/texture-coordinate/normal
		// f v1//vn1 v2//vn2 v3//vn3	-> Vertex/normal
		} else if (Definition.compare("f") == 0) {
			ReadFace(Stream, M, Mat);

		// any other keywords -> ignore them
		} else {
			Stream.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Unknown Definition " << Definition << endl;
		}
	}




	// Add Texture for all Vertices
	for (VertexVector::iterator it = M->_vertices.begin(); it != M->_vertices.end(); ++it) {
		float* Texture = new float[2];
		Texture[0] = 0;
		Texture[1] = 0;

		M->_textureCoords.push_back(Texture);
	}

	DLOG(INFO) << "Read in " << M->_vertices.size() << " Vertices" << endl;
	DLOG(INFO) << "Read in " << M->_triangles.size() << " Triangles" << endl;
	DLOG(INFO) << "Read in " << M->_quads.size() << " Quads" << endl;
	DLOG(INFO) << "Read in " << M->_polygons.size() << " Polygons" << endl;
	DLOG(INFO) << "Read in " << M->_quadsConcave.size() << " ConcaveQuads" << endl;
	DLOG(INFO) << "Read in " << M->_polygonsConcave.size() << " ConcavePolygons" << endl;
	DLOG(INFO) << "Read in " << M->_textureCoords.size() << " Texture Coordinates" << endl;

	if (Stream.bad()) {
		DLOG(WARNING) << "Error reading in Mesh" << endl;
		return 0;
	} else {
		DLOG(INFO) << "Mesh Successfully read in" << endl << endl << endl << endl;
		return M;
	}
}

/**
 * \brief Opens and Reads a Material File and places all material Information in the MaterialMap
 * \param MaterialMap where we place Material Information
 * \param FileName to read the material information from
 */
// TODO:
void MeshLoaderObj::ReadMaterialFile(mmsm& MaterialMap, string& FileName) {
	RemoveLineBreaks(FileName);
	ifstream In(FileName.c_str());

	DLOG(INFO) << "Load Material: " << FileName << endl;
	//DLOG(INFO) << "Stream Status " << In.good() << endl;

	string Definition;

	Material* Mat = new Material("Proto", Vector3( 0.2f, 0.2f, 0.2f));

	bool FirstMat = true;
	float r;
	float g;
	float b;

	while(!In.eof() && In.good()) {
		// When we have empty lines there are \r or \n or maybe \t or whitespaces
		while (In.peek() == '\r' || In.peek() == '\n' || In.peek() == '\t' || In.peek() == ' ')
			In.ignore(1);

		// Maybe we had some empty lines at the end
		if (In.eof())
			break;

		// Special case comments they don't need to have a whitespace after them so we need to handle them separately
		if (In.peek() == '#')
			Definition = "#";
		else
			getline(In, Definition, ' ');

		/* PROCESS LINES */

		// Start a new Material, Commit the Old One to the Map
		if (Definition.compare("newmtl") == 0) {
			if (!FirstMat)
				MaterialMap.insert(mmsm::value_type(Mat->_name, Mat));
			FirstMat = false;
			Mat = new Material("Proto", Vector3( 0.2f, 0.2f, 0.2f));
			getline(In, Mat->_name, '\n');
			RemoveLineBreaks(Mat->_name);
			//DLOG(INFO) << "Found Material: " << Mat._name << endl;


		// Found Ambient Color
		} else if (Definition.compare("Ka") == 0) {
			In >> r >> g >> b;
			Mat->SetAmbient(r, g, b);
			//DLOG(INFO) << "  Found Ambient Color (" << r << ", " << g << ", " << b << ")" << endl;
			In.ignore(INT_MAX, '\n');


		// Found Diffuse Color
		} else if (Definition.compare("Kd") == 0) {
			In >> r >> g >> b;
			Mat->SetDiffuse(r, g, b);
			//DLOG(INFO) << "  Found Diffuse Color (" << r << ", " << g << ", " << b << ")" << endl;
			In.ignore(INT_MAX, '\n');


		// Found Specular Color
		} else if (Definition.compare("Ks") == 0) {
			In >> r >> g >> b;
			Mat->SetSpecular(r, g, b, 0);
			//DLOG(INFO) << "  Found Specular Color (" << r << ", " << g << ", " << b << ")" << endl;
			In.ignore(INT_MAX, '\n');


		// Found Alpha
		} else if (Definition.compare("d") == 0 || Definition.compare("Tr") == 0) {
			In >> r;
			Mat->SetTransparency(r);
			//DLOG(INFO) << "  Found Alpha Value " << r << endl;
			In.ignore(INT_MAX, '\n');


		// Found Shininess
		} else if (Definition.compare("Ns") == 0) {
			In >> r;
			Mat->SetSpecular(Mat->GetSpecularLight(), r);
			//DLOG(INFO) << "  Found Shininess Value " << r << endl;
			In.ignore(INT_MAX, '\n');


		// Found Illumination Model
		} else if (Definition.compare("illum") == 0) {
			//DLOG(INFO) << "  Found Illumination Model - ignored " << endl;
			In.ignore(INT_MAX, '\n');

		// Found Texture Map for Ambient
		} else if (Definition.compare("map_Ka") == 0) {
			//DLOG(INFO) << "  Found Texture Map - ignored" << endl;
			In.ignore(INT_MAX, '\n');

		// Found Texture Map for Diffuse
		} else if (Definition.compare("map_Kd") == 0) {
			//DLOG(INFO) << "  Found Texture Map - ignored" << endl;
			In.ignore(INT_MAX, '\n');

		// Found Texture Map for Specular
		} else if (Definition.compare("map_Ks") == 0) {
			//DLOG(INFO) << "  Found Texture Map - ignored" << endl;
			In.ignore(INT_MAX, '\n');

		// Found Texture Map for Specular
		} else if (Definition.compare("map_Ns") == 0) {
			//DLOG(INFO) << "  Found Texture Map - ignored" << endl;
			In.ignore(INT_MAX, '\n');

		// Found Bump Texture Map
		} else if (Definition.compare("bump") == 0) {
			//DLOG(INFO) << "  Found Texture Map - ignored" << endl;
			In.ignore(INT_MAX, '\n');

		// Found Reflection Definition
		} else if (Definition.compare("sharpness") == 0) {
			//DLOG(INFO) << "  Found Texture Map - ignored" << endl;
			In.ignore(INT_MAX, '\n');


		// Found Comment
		} else if (Definition.compare("#") == 0) {
			//DLOG(INFO) << "  Found Comment - ignored" << endl;
			In.ignore(INT_MAX, '\n');


		// any other keywords -> ignore them
		} else {
			In.ignore(INT_MAX, '\n');
			DLOG(INFO) << "Found Unknown Definition " << Definition << endl;
		}
	}

	// Insert the last material as well
	if (!FirstMat)
		MaterialMap.insert(mmsm::value_type(Mat->_name, Mat));

	In.close();
}

/**
 *	\brief Check if this is a Obj file
 *
 *	\param Stream to read a object from
 *	\return true if it ends with .obj, false otherwise
 * TODO: just stupidly returns true
 */
bool MeshLoaderObj::Accept(istream& Stream) {
	return true;
}

/**
 * \brief Reads 3 float numbers from the stream an places them in the array v
 *
 * \param v must be a float array with 3 elements
 * \param Stream where we read from
 */
void MeshLoaderObj::ReadVector3f(float* v, istream& Stream) {
	Stream >> v[0];
	Stream >> v[1];
	Stream >> v[3];
}

/**
 * \brief If OptionalW is false we read in 4 floats. Otherwise we read in 3 floats and check if it is specified (either within or not within brackets) and try to read it. If it is not specified we just set it to 1.0f. At the end we normalize the x, y and z values and can therefore discard w anyway.
 *
 * \param v pointer to an float array with 3 elements
 * \param Stream where we read from
 * \param OptionalW if false we need to read in a w and normalize otherwise we try but set it to 1.0f if we can't find it
 * \param OptionalWInBrackets if true we try to read in in format [1.0] otherwise just format 1.0
 */
void MeshLoaderObj::ReadVector4fTo3f(float* v, istream& Stream, bool OptionalW, bool OptionalWInBrackets) {
	// Read in x to z
	Stream >> v[0];
	Stream >> v[1];
	Stream >> v[2];

	// w is optional and if it is there it has brackets around
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
	// w is optional but if there are no brackets around
	} else if (OptionalW && !OptionalWInBrackets) {
		Stream >> w;
		if (Stream.fail()) {
			Stream.clear();
			w = 1.0f;
		}
	} else {
		Stream >> w;
	}

	// normalize so we don't need the w
	v[0] = v[0] / w;
	v[1] = v[1] / w;
	v[2] = v[2] / w;
}

/** \brief Determines the sign of the argument
 * \param X to determine sign from
 * \return -1 if smaller than 0, 1 otherwise
 */
int Sign(float X){ return(X<0 ? -1 : 1); }

/** \brief One convexity test is to conceptually walk along the polygon edges and check if the sign of the change in x and y changes more than twice. If it does than the polygon is convex. That should also check for complex polygons as well.
 * \param VList List containing the Index of the Vertices
 * \param M Mesh containing the Vertices themselves
 */
bool MeshLoaderObj::IsPolygonConvex(vector<int>& VList, Mesh* M) {
	// If less than 4 points it's always convex
	if (VList.size() < 4)
		return true;

	// count how many times the x or y signs are diffrent
	int XCh = 0;
	int YCh = 0;

//DLOG(INFO) << "order: " << VList.size() << endl;

for (int i=0; i<VList.size(); i++) {
//	DLOG(INFO) << "point (" << VList[i] << "): " << M->_vertices[VList[i]][0] << ", " << M->_vertices[VList[i]][1] << ", " << endl;
}

	// Vector from last to first point
	float* A = new float[2];
	A[0] = M->_vertices[VList[VList.size()-1]]->Array[0] - M->_vertices[VList[0]]->Array[0];
	A[1] = M->_vertices[VList[VList.size()-1]]->Array[1] - M->_vertices[VList[0]]->Array[1];

	float* B = new float[2];

	for(int i=0; i<VList.size()-1; ++i) {
		B[0] = M->_vertices[VList[i]]->Array[0] - M->_vertices[VList[i+1]]->Array[0];
		B[1] = M->_vertices[VList[i]]->Array[1] - M->_vertices[VList[i+1]]->Array[1];

		if (Sign(A[0]) != Sign(B[0]))
			++XCh;

		if (Sign(A[1]) != Sign(B[1])) 
			++YCh;

		A[0] = B[0];
		A[1] = B[1];
	}

	delete[] A;
	delete[] B;

//DLOG(INFO) << "XCh: " << XCh << endl;
//DLOG(INFO) << "YCh: " << YCh << endl;

	return (XCh <= 2 && YCh <= 2);
}

void MeshLoaderObj::ReadFace(istream& Stream, Mesh* M, Material* Mat) {

	// Read in all the Vertices Indexes
	vector<int> Vertices;
	int index;
	while (Stream.peek() != '\n') {
		Stream >> index;

		// Vertex index in file start with 1, array start with 0
		index--;

		Vertices.push_back(index);

		// ignore texture coordinates etc.
		if (Stream.peek() == '/') {
			while (Stream.peek() != ' ' && Stream.peek() != '\n')
				Stream.ignore(1);
		}

		while(Stream.peek() == ' ' || Stream.peek() == '\t' || Stream.peek() == '\r')
			Stream.ignore(1);
	}

	Vector3* CalculatedNormal = new Vector3();
	m3dFindNormal(CalculatedNormal->GetPointer(), M->_vertices[Vertices[0]]->GetConstPointer(), M->_vertices[Vertices[1]]->GetConstPointer(), M->_vertices[Vertices[2]]->GetConstPointer());

	if (Vertices.size() == 3) {
		//DLOG(INFO) << "Found Triangle: (" << Vertices[0] << ", " << Vertices[1] << ", " << Vertices[2] << ")" << endl;
		M->_triangles.push_back(new Triangle(M->_vertices[Vertices[0]], M->_vertices[Vertices[1]], M->_vertices[Vertices[2]], CalculatedNormal, Mat));

	} else if (Vertices.size() == 4) {
		if (IsPolygonConvex(Vertices, M)) {
			//DLOG(INFO) << "Found Quad: (" << Vertices[0] << ", " << Vertices[1] << ", " << Vertices[2] << ", " << Vertices[3] << ")" << endl;
			M->_quads.push_back(new Quad(M->_vertices[Vertices[0]], M->_vertices[Vertices[1]], M->_vertices[Vertices[2]], M->_vertices[Vertices[3]], CalculatedNormal, Mat));
		} else
			M->_quadsConcave.push_back(new Quad(M->_vertices[Vertices[0]], M->_vertices[Vertices[1]], M->_vertices[Vertices[2]], M->_vertices[Vertices[3]], CalculatedNormal, Mat));
	} else {
		//DLOG(INFO) << "Found Polygon: (" << Vertices[0] << ", " << Vertices[1] << ", " << Vertices[2] << ", " << Vertices[3] << "..., order: " << Vertices.size() << ")" << endl;
		vector<Vector3*> VerticesRef;
		for (int i=0; i<Vertices.size(); ++i) {
			VerticesRef.push_back(M->_vertices[Vertices[i]]);
		}

		if (IsPolygonConvex(Vertices, M))
			M->_polygons.push_back(new Polygon(VerticesRef, CalculatedNormal, Mat));
		else
			M->_polygonsConcave.push_back(new Polygon(VerticesRef, CalculatedNormal, Mat));
	}
}
