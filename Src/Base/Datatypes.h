#pragma once

union Vector3 { 
	struct sComponents {
		float x;
		float y;
		float z;
	} Components;

	float Array[3];

	Vector3() {
		Array[0] = 0;
		Array[1] = 0;
		Array[2] = 0;
	}

	Vector3(float x, float y, float z) { 
		Array[0] = x;
		Array[1] = y;
		Array[2] = z;
	}

	Vector3(const Vector3& v) {
		Array[0] = v.Array[0];
		Array[1] = v.Array[1];
		Array[2] = v.Array[2];
	}

	const float* GetConstPointer() const {
		return Array;
	}

	float* GetPointer() {
		return Array;
	}
};

union Vector4 { 
	struct sComponents { 
		float x;
		float y;
		float z;
		float w;
	} Components;

	float Array[4];

	struct {
		float r;
		float g;
		float b;
		float a;
	} Color;

	Vector4() { 
		Array[0] = 0;
		Array[1] = 0;
		Array[2] = 0;
		Array[3] = 0;
	}

	Vector4(float x, float y, float z, float w) { 
		Array[0] = x;
		Array[1] = y;
		Array[2] = z;
		Array[3] = w;
	}

	Vector4(const Vector4& v) {
		Array[0] = v.Components.x;
		Array[1] = v.Components.y;
		Array[2] = v.Components.z;
		Array[3] = v.Components.w;
	}

	const float* GetConstPointer() const {
		return Array;
	}

	float* GetPointer() {
		return Array;
	}
};
