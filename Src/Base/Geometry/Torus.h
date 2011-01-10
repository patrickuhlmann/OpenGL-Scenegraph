#pragma once

#include "../Mesh.hpp"

class Torus : public Mesh {
	public:
		Torus(float MajorRadius, float MinorRadius, int MajorNum, int MinorNum);
};
