#pragma once

#include "../Base/Mesh.hpp"
#include "MeshLoader.h"
#include <string>
#include <istream>
#include <fstream>
#include <glog/logging.h>
#include "../../Libs/nvwa-0.8.2/debug_new.h"

using namespace std;

/**
 *	\brief Can load Meshes from files
 */
class MeshFileLoader : public MeshLoader {
	private:

	public:
		virtual ~MeshFileLoader();
		virtual Mesh* Load(const string& FileName);
		virtual Mesh* Load(istream& Stream);		// inherited
};
