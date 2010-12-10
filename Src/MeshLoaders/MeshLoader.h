#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <vector>
#include "IMeshLoader.h"
#include <istream>
#include "../Base/Mesh.h"
#include <iostream>

using namespace std;

/*
 * \brief This class provides methods to check if it can load a mesh from the stream and to load Meshs from a Stream. It delegates this to Loaders which are instances of IMeshLoader that can be added with AddMeshLoader
 */
class MeshLoader {
	protected:
		/**
		 *	\brief Vector of Loaders which will be used to try to load a stream (starting from index 0)
		 */
		vector<IMeshLoader*> Loaders;

	public:
		virtual Mesh* Load(const istream& Stream);
		virtual void AddMeshLoader(IMeshLoader* Loader);
};

#endif
