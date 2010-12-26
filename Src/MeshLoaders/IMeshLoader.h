#pragma once

#include <istream>
class Mesh;

using namespace std;

/**
 * \brief Interface for a Mesh Loader Class. This class is able to load a Mesh from a accepted Fileformat and to return if we can load the fileformat from a stream
 */
class IMeshLoader {
	private:

	public:
		/**
		 *	\brief Load a Mesh from a stream
		 *	
		 *	\param Stream to read from
		 *  \return Mesh if successfull, 0 otherwise
		 */
		virtual Mesh* Load(istream& Stream) = 0;

		/**
		 *	\brief Check if we can load a mesh from a stream
		 *
		 *	\param Stream to read from
		 *	\return true if possible, false otherwise
		 */
		virtual bool Accept(istream& Stream) = 0;
};
