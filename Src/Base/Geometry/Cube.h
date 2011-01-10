#pragma once

#include "../Mesh.hpp"
#include <string>

class Cube : public Mesh {
	private:
		void Init(float Length);

	public:
		Cube(float Length);
		Cube(float Length, const string& Name);
};
