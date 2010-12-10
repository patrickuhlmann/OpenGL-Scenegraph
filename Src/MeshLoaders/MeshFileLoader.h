#ifndef MESHFILELOADER_H
#define MESHFILELOADER_H

#include "../Base/Mesh.h"
#include "MeshLoader.h"
#include <string>

/**
 *	\brief Can load Meshes from files
 */
class IMeshFileLoader : protected MeshLoader() {
	private:

	public:
		/**
		 * \brief Load the Mesh from the File
		 *
		 * \return Pointer to Mesh if successful, 0 otherwise
		 */
		Mesh* Load(const string& FileName);
};

#endif MESHFILELOAADER_H
