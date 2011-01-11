#pragma once

#include "../Mesh.hpp"
#include <string>

/** \brief Class to create a mesh cotaining a sphere */
class Sphere : public Mesh {
	private:
		void Init(float Radius, int Slices, int Stacks, const Material& SMat = SphereMaterial);
		/** \brief Holds a prototype material to use for sphere. It's blue with a red diffuse component */
		static Material SphereMaterial;

	public:
		Sphere(float Radius, int Slices, int Stacks);
		Sphere(float Radius, int Slices, int Stacks, const string& Name, const Material& Mat = SphereMaterial);
};
