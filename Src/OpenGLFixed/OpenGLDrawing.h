#pragma once

#include "../Include/GL/glew.h"

class OpenGLDrawing {
	public:
		static void DrawTriangle(const float* Vertex1, const float* Vertex2, const float* Vertex3, const float* Normal, const float* RGBColor);
		static void DrawPoint(const float* Vertex, const float* RGBColor);
		static void DrawLine(const float* VertexStart, const float* VertexEnd, const float* RGBColor);
};
