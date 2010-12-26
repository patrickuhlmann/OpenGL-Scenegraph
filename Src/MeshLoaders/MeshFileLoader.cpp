#include "MeshFileLoader.h"

/**
 * \brief Load the Mesh from the File
 *
 * \return Pointer to Mesh if successful, 0 otherwise
 */
Mesh* MeshFileLoader::Load(const string& FileName) {
	ifstream in(FileName.c_str());

	DLOG(INFO) << "Load Mesh: " << FileName << endl;
	DLOG(INFO) << "Stream Status " << in.good() << endl;

	Mesh* m = this->Load(in);

	// if we have a valid mesh -> set it's name to the FileName which we loaded
	if (m != 0) {
		m->_name = FileName;
	}

	in.close();

	return m;
}

/**
 *	\brief Loads a Mesh from a Stream
 *
 *  The Method checks all added Loaders if they accept a stream
 *
 *	\param Stream to read from
 *  \return Pointer to Mesh if successful, 0 otherwise
 */
Mesh* MeshFileLoader::Load(istream& Stream) {
	for (vector<IMeshLoader*>::iterator it = this->Loaders.begin(); it != this->Loaders.end(); ++it) {
		if ((*it)->Accept(Stream))
			return (*it)->Load(Stream);
	}		

	cout << "Warning: MeshLoader couldn't load from stream" << endl;
	return 0;
}
