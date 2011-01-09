#pragma once

struct Triangle {
	int vert1, vert2, vert3;
	float* Normal;

	Triangle(int v1, int v2, int v3) {
		vert1 = v1;
		vert2 = v2;
		vert3 = v3;
		Normal = 0;
	}

	~Triangle() {
		if (Normal)
			delete[] Normal;
	}

};
