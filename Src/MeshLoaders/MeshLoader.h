#pragma once

#include "../Base/Mesh.hpp"
#include <vector>
#include "IMeshLoader.h"
#include <istream>
#include <iostream>

using namespace std;

/** \brief This class provides methods to check if it can load a mesh from the stream and to load Meshs from a Stream. It delegates this to Loaders which are instances of IMeshLoader that can be added with AddMeshLoader
 */
class MeshLoader {
	protected:
		/**
		 *	\brief Vector of Loaders which will be used to try to load a stream (starting from index 0)
		 */
		vector<IMeshLoader*> Loaders;

	public:
                ~MeshLoader();
		virtual Mesh* Load(istream& Stream);
		virtual void AddMeshLoader(IMeshLoader* Loader);
};
