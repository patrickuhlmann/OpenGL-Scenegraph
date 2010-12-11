#pragma once

#include "../Base/Mesh.hpp"
#include "MeshLoader.h"
#include <string>
#include <istream>
#include <fstream>
#include <glog/logging.h>

using namespace std;

/**
 *	\brief Can load Meshes from files
 */
class MeshFileLoader : public MeshLoader {
	private:

	public:
		/**
		 * \brief Load the Mesh from the File
		 *
		 * \return Pointer to Mesh if successful, 0 otherwise
		 */
		virtual Mesh* Load(const string& FileName);
		virtual Mesh* Load(istream& Stream);		// inherited
};
