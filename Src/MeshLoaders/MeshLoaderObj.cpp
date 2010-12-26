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
		// Special case 2: only g without name is also valid
		else if (Stream.peek() == 'g')
			Definition = "g";
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
			DLOG(INFO) << "Found Vertex: " << v[0] << ", " << v[1] << ", " << v[2] << ", number: " << M->_vertices.size()-1 << endl;


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
			Triangle t(0,0,0);
			ReadTriangle(&t, Stream);
			// found a triangle
			if (t.vert1 != INT_MIN) {
				M->_triangles.push_back(t);
				DLOG(INFO) << "Found Face " << t.vert1 << ", " << t.vert2 << ", " << t.vert3 << endl;
				float* CalculatedNormal = new float[3];
				m3dFindNormal(CalculatedNormal, M->_vertices[t.vert1], M->_vertices[t.vert2], M->_vertices[t.vert3]);
				M->_normals.push_back(CalculatedNormal);
				DLOG(INFO) << "Calculated Normal " << CalculatedNormal[0] << ", " << CalculatedNormal[1] << ", " << CalculatedNormal[2] << endl;
			// It is something of higher order so we triangulate
			} else {
				vector<Triangle> TList;
				if (!Triangulate(TList, Stream, M)) {
					Stream.clear(ios::badbit);
				} else {
					// Add all Triangles
					for (int i=0; i<TList.size(); i++) {
						t = TList[i];
						DLOG(INFO) << "Found Face " << t.vert1 << ", " << t.vert2 << ", " << t.vert3 << endl;
						float* CalculatedNormal = new float[3];
						m3dFindNormal(CalculatedNormal, M->_vertices[t.vert1], M->_vertices[t.vert2], M->_vertices[t.vert3]);
						M->_normals.push_back(CalculatedNormal);
						DLOG(INFO) << "Calculated Normal " << CalculatedNormal[0] << ", " << CalculatedNormal[1] << ", " << CalculatedNormal[2] << endl;
					}
				}
			}
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

/**
 * \brief Reads in a Triangle. It accepts the following formats:\n
 *  1 2 3						-> Vertex index starting with 1, face can contain more than three elements!\n
 * 3/1 4/2 5/3					-> Vertex/texture-coordinate\n
 * 6/4/1 3/5/3 7/6/5			-> Vertex/texture-coordinate/normal\n
 * v1//vn1 v2//vn2 v3//vn3		-> Vertex/normal\n
 *
 * If it is not a triangle but something of a higher order we rollback the position in the stream to the beginning and
 * set the first entry of the triangle to INT_MIN
 *
 * \param Triangle where we should store the values
 * \param Stream where we read from
 */
void MeshLoaderObj::ReadTriangle(Triangle* t, istream& Stream) {
	int startpos = Stream.tellg();

	Stream >> t->vert1;
	Stream.ignore(INT_MAX, ' ');
	Stream >> t->vert2;
	Stream.ignore(INT_MAX, ' ');
	Stream >> t->vert3;

	// The Vertices Index in the file start with 1 in our array it starts with 0
	t->vert1--;
	t->vert2--;
	t->vert3--;

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
		DLOG(WARNING) << "Face is not a Triangle but has more elements: We do Triangulation" << endl;
		Stream.seekg(startpos, ios::beg);
		//Stream.ignore(INT_MAX, '\n');
		t->vert1 = INT_MIN;
	}
}

int Sign(float X){ return(X<0 ? -1 : 1); }

/** \brief One convexity test is to conceptually walk along the polygon edges and check if the sign of the change in x and y changes more than twice. If it does than the polygon is convex. That should also check for complex polygons as well.
 */
bool MeshLoaderObj::IsPolygonConvex(vector<int>& VList, Mesh* M) {
	// If less than 4 points it's always convex
	if (VList.size() < 4)
		return true;

	// count how many times the x or y signs are diffrent
	int XCh = 0;
	int YCh = 0;

DLOG(INFO) << "order: " << VList.size() << endl;

for (int i=0; i<VList.size(); i++) {
	DLOG(INFO) << "point: " << M->_vertices[VList[i]][0] << ", " << M->_vertices[VList[i]][1] << ", " << endl;
}

	// Vector from last to first point
	float* A = new float[2];
	A[0] = M->_vertices[VList[VList.size()-1]][0] - M->_vertices[VList[0]][0];
	A[1] = M->_vertices[VList[VList.size()-1]][1] - M->_vertices[VList[0]][1];

	float* B = new float[2];

	for(int i=0; i<VList.size()-1; ++i) {
		B[0] = M->_vertices[VList[i]][0] - M->_vertices[VList[i+1]][0];
		B[1] = M->_vertices[VList[i]][1] - M->_vertices[VList[i+1]][1];

		if (Sign(A[0]) != Sign(B[0]))
			++XCh;

		if (Sign(A[1]) != Sign(B[1])) 
			++YCh;

		A[0] = B[0];
		A[1] = B[1];
	}

	delete[] A;
	delete[] B;

DLOG(INFO) << "XCh: " << XCh << endl;
DLOG(INFO) << "YCh: " << YCh << endl;

	return (XCh <= 2 && YCh <= 2);
}

/** \brief Reads in a lot of points and creates triangles out of them. It only accepts the basic format (like 1 2 3 4 5 6 7) to specify polygons. 
 */
bool MeshLoaderObj::Triangulate(vector<Triangle>& TList, istream& Stream, Mesh* M) {
	// Read in all the Vertices Indexes
	vector<int> Vertices;
	int index;
	while (Stream.peek() != '\n') {
		Stream >> index;

		// Vertex index in file start with 1, array start with 0
		index--;

		Vertices.push_back(index);

		// if we have another than the simple format for faces we stop
		if (Stream.peek() == '/') {
			DLOG(WARNING) << "Triangulation only for simple Face List Format!" << endl;
			Stream.ignore(INT_MAX, '\n');
			return false;
		}

		while(Stream.peek() == ' ' || Stream.peek() == '\t' || Stream.peek() == '\r')
			Stream.ignore(1);
	}

	// If it is concave it's to hard
	if (!IsPolygonConvex(Vertices, M)) {
		DLOG(WARNING) << "Triangulation to hard it's concave!" << endl;
		return false;
	}

	DLOG(INFO) << "Triangulation for " << Vertices.size() << " points" << endl;

	// Triangulate by finding the highest y-Coordinate, it's two nearest neighbors and drawing the lines. We then add the triangle and remove the highest point. When we have only three points left they are the last triangle and we quit
	// TODO: normals correct?
	while (Vertices.size() > 3) {
		// find highest y-coordinate
		float* HighestY = M->_vertices[Vertices[0]];
		float HighestYIndex = 0;
		for (int i = 0; i<Vertices.size(); i++) {
			if (M->_vertices[Vertices[i]][1] > HighestY[1]) {
				HighestY = M->_vertices[Vertices[i]];
				HighestYIndex = i;
			}
		}

		// put highest point at the end
		Vertices.push_back(Vertices[HighestYIndex]);
		Vertices.erase(Vertices.begin()+HighestYIndex);
		HighestYIndex = Vertices.size()-1;

		// find two nearest points
		float* Near1 = M->_vertices[Vertices[0]];
		int Near1Index = 0;
		float Near1Distance = abs(HighestY[0]-Near1[0]) + abs(HighestY[1]-Near1[1]) + abs(HighestY[2]-Near1[2]);
		float* Near2 = M->_vertices[Vertices[1]];
		int Near2Index = 0;
		float Near2Distance = abs(HighestY[0]-Near2[0]) + abs(HighestY[1]-Near2[1]) + abs(HighestY[2]-Near2[2]);
		float* Candidate;
		float CandidateDistance;
		for (int i=2; i<Vertices.size(); i++) {
			Candidate = M->_vertices[Vertices[2]];
			CandidateDistance = abs(HighestY[0]-Candidate[0]) + abs(HighestY[1]-Candidate[1]) + abs(HighestY[2]-Candidate[2]);
			// It's the nearest -> replace near point that is further away
			if (CandidateDistance < Near1Distance && CandidateDistance < Near2Distance) {
				if (Near1Distance < Near2Distance) {
					Near2Index = i;
					Near2Distance = CandidateDistance;
				} else {
					Near1Index = i;
					Near1Distance = CandidateDistance;
				}
			// only nearer than near 1 so we replace that one
			} else if (CandidateDistance < Near1Distance) {
				Near1Index = i;
				Near1Distance = CandidateDistance;
			// only nearer than near 2 so we replace that one
			} else if (CandidateDistance < Near2Distance) {
				Near2Index = i;
				Near2Distance = CandidateDistance;
			}
		}

		// build triangle
		TList.push_back(Triangle(Vertices[HighestYIndex], Vertices[Near1Index], Vertices[Near2Index]));

		// remove highest point
		Vertices.erase(Vertices.begin()+HighestYIndex);
	}

	// Add the last triangle
	TList.push_back(Triangle(Vertices[0], Vertices[1], Vertices[2]));

	DLOG(INFO) << "Triangulation produced " << TList.size() << " triangles" << endl;

	return true;
}
