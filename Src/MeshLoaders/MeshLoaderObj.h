#pragma once

#include "IMeshLoader.h"
#include "../Base/Mesh.hpp"
#include <glog/logging.h>
#include <istream>
#include <climits>
#include "../Include/math3d.h"
#include <glog/logging.h>

using namespace std;

class MeshLoaderObj : public IMeshLoader {
	private:
		void ReadVector3f(float* v, istream& Stream);
		void ReadVector4fTo3f(float* v, istream& Stream, bool OptionalW = true, bool OptionalWInBrackets = true);
		void ReadTriangle(Triangle* t, istream& Stream);

	public:
		virtual Mesh* Load(istream& Stream);
		virtual bool Accept(istream& Stream);
};
