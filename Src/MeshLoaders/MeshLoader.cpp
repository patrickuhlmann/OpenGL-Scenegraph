#include "MeshLoader.h"

/**
 *	\brief Loads a Mesh from a Stream
 *
 *  The Method checks all added Loaders if they accept a stream
 *
 *	\param Stream to read from
 *  \return Pointer to Mesh if successful, 0 otherwise
 */
Mesh* MeshLoader::Load(const istream& Stream) {
	for (vector<IMeshLoader*>::iterator it = this->Loaders.begin(); it != this->Loaders.end(); ++it) {
		if ((*it)->Accept(Stream))
			return (*it)->Load(Stream);
	}		

	cout << "Warning: MeshLoader couldn't load from stream" << endl;
	return 0;
}

/**
 *	\brief Add a Loader to the internal list (will be used when trying to load meshes from a stream)
 *	
 *	\param Loader to add to list
 */
void MeshLoader::AddMeshLoader(IMeshLoader* Loader) {
	this->Loaders.push_back(Loader);
}
