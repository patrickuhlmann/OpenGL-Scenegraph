#pragma once

#include "../Include/GL/glew.h"
#include <vector>
#include "../Base/Datatypes.h"
#include "../Graph/Material.hpp"
#include <vector>

class OpenGLDrawing {
	public:
		static void DrawPoint(const Vector3* Vertex1, const Material* Mat);
		static void DrawLine(const Vector3* Vertex1, const Vector3* Vertex2, const Material* Mat);
		static void DrawTriangle(const Vector3* Vertex1, const Vector3* Vertex2, const Vector3* Vertex3, const float* Normal, const Material* Mat);
		static void DrawTriangle(const Triangle* T);
		static void DrawTriangles(const vector<Triangle*>& T);
		static void DrawQuad(const Quad* Q);
		static void DrawPolygon(const Polygon* P);

		static int TriangleCounter;
		static int QuadCounter;
		static int PolygonCounter;
		static const void* LastMaterialPointer;

	private:
		static void SetDrawingColorAndMaterial(const Material* Mat);
};