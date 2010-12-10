#include "MeshFileLoader.h"

Mesh* MeshFileLoader::Load(const string& Name) {
	ifstream in(Name);

	Mesh* m = this->Load(in);

	in.close();

	return m;
}
