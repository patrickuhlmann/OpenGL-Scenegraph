#pragma once

#include <iostream>
#include <sstream>
#include <string>

void GetM3DVector3f(float* f, M3DVector3f g) {
	memcpy(f, g, sizeof(M3DVector3f));
}

void GetM3DVector2f(float* f, M3DVector3f g) {
	memcpy(f, g, sizeof(M3DVector2f));
}

inline std::string IntegerToString(int x) {
	std::ostringstream o;
	
	//if (!(o << x))
	//	throw BadConversion("IntegerToString failed for: " + x);
	o << x;
	
	return o.str();
}
