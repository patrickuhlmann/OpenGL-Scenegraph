#include "MeshFileLoaderObj"

/**
 *	\brief Load a Mesh from a Obj file
 *	
 *	\param Name path to a file
 *  \return Mesh if successfull, 0 otherwise
 */
Mesh* MeshFileLoaderObj::Load(const istream& Stream) {
	return 0;
}

/**
 *	\brief Check if this is a Obj file
 *
 *	\param Name path to a file
 *	\return true if it ends with .obj, false otherwise
 */
bool MeshFileLoaderObj::AcceptFile(const istream& Stream) {
	return false;
}
