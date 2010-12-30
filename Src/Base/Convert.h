#pragma once

void GetM3DVector3f(float* f, M3DVector3f g) {
	memcpy(f, g, sizeof(M3DVector3f));
}

void GetM3DVector2f(float* f, M3DVector3f g) {
	memcpy(f, g, sizeof(M3DVector2f));
}
