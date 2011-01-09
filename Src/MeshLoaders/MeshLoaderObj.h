#pragma once

#include "IMeshLoader.h"
#include "../Base/Mesh.hpp"
#include <glog/logging.h>
#include <istream>
#include <fstream>
#include <climits>
#include "../Include/math3d.h"
#include <glog/logging.h>
#include <list>
#include <limits.h>
#include <stdlib.h>
#include <map>
#include "../Graph/Material.hpp"
#include <cmath>
#include "../Base/Datatypes.h"

#include <list>
#include <algorithm>

//#include "../../Libs/nvwa-0.8.2/debug_new.h"

const double PI = 3.1415926;

using namespace std;

typedef multimap<string, Material*> mmsm;

/**
 * \brief This class load a mesh in obj format from a stream. But it only loads the vertices and faces. It adds grey as color for all faces and adds texture coordinates (0, 0) for all faces */
class MeshLoaderObj : public IMeshLoader {
	private:
		void ReadFace(istream& Stream, Mesh* M, Material* Mat);
		void ReadVector3f(float* v, istream& Stream);
		void ReadVector4fTo3f(float* v, istream& Stream, bool OptionalW = true, bool OptionalWInBrackets = true);
		bool IsPolygonConvex(vector<int>& VList, Mesh* M);
		void ReadMaterialFile(mmsm& MaterialMap, string& FileName);

	public:
		virtual Mesh* Load(istream& Stream);
		virtual bool Accept(istream& Stream);
};
