#include "MeshFileLoader.h"

Mesh* MeshFileLoader::Load(const string& FileName) {
	ifstream in(FileName.c_str());

	DLOG(INFO) << "Load Mesh: " << FileName << endl;
	DLOG(INFO) << "Stream Status " << in.good() << endl;
	DLOG(INFO) << "Stream EOF " << in.eof() << endl;
	Mesh* m = this->Load(in);

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
