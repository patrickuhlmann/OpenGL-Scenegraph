#pragma once

#include "../Mesh.hpp"
#include <string>

/** \brief Class to create a mesh cotaining a cube */
class Cube : public Mesh {
	private:
		void Init(float Length, const Material& CMat = CubeMaterial);
		/** \brief Holds a prototype material to use for cubes */
		static Material CubeMaterial;

	public:
		Cube(float Length);
		Cube(float Length, const string& Name);
};
