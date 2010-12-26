#pragma once

#include "IMeshLoader.h"
#include "../Base/Mesh.hpp"
#include <glog/logging.h>
#include <istream>
#include <climits>
#include "../Include/math3d.h"
#include <glog/logging.h>
#include <list>
#include <limits.h>
#include <stdlib.h>

const double PI = 3.1415926;

using namespace std;

/**
 * \brief This class load a mesh in obj format from a stream. But it only loads the vertices and faces. It adds grey as color for all faces and adds texture coordinates (0, 0) for all faces */
class MeshLoaderObj : public IMeshLoader {
	private:
		void ReadVector3f(float* v, istream& Stream);
		void ReadVector4fTo3f(float* v, istream& Stream, bool OptionalW = true, bool OptionalWInBrackets = true);
		void ReadTriangle(Triangle* t, istream& Stream);
		bool Triangulate(vector<Triangle>& TList, istream& Stream, Mesh* M);
		bool IsPolygonConvex(vector<int>& VList, Mesh* M);

	public:
		virtual Mesh* Load(istream& Stream);
		virtual bool Accept(istream& Stream);
};
