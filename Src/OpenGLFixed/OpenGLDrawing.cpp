#include "OpenGLDrawing.h"

void OpenGLDrawing::DrawPoint(const float* Vertex, const float* RGBColor) {
	glColor3f(RGBColor[0], RGBColor[1], RGBColor[2]);

	glBegin(GL_POINTS);
		glVertex2f(Vertex[0], Vertex[1]);
	glEnd();
}

void OpenGLDrawing::DrawLine(const float* VertexStart, const float* VertexEnd, const float* RGBColor) {
	glColor3f(RGBColor[0], RGBColor[1], RGBColor[2]);

	glBegin(GL_LINES);
		glVertex2f(VertexStart[0], VertexStart[1]);
		glVertex2f(VertexEnd[0], VertexEnd[1]);
	glEnd();
}

void OpenGLDrawing::DrawTriangle(const float* Vertex1, const float* Vertex2, const float* Vertex3, const float* Normal, const float* RGBColor){
	glColor3f(RGBColor[0], RGBColor[1], RGBColor[2]);

	glBegin(GL_TRIANGLES);
			glNormal3f(Normal[0], Normal[1], Normal[2]);
			glVertex3f(Vertex1[0], Vertex1[1], Vertex1[2]);
 			glVertex3f(Vertex2[0], Vertex2[1], Vertex2[2]);
 			glVertex3f(Vertex3[0], Vertex3[1], Vertex3[2]);
	glEnd();
}

void OpenGLDrawing::DrawQuad(const Quad& Q, const float* RGBColor) {
	glColor3f(RGBColor[0], RGBColor[1], RGBColor[2]);

	glBegin(GL_QUADS);
			glVertex3f(Q.Vertex1.Array[0], Q.Vertex1.Array[1], Q.Vertex1.Array[2]);
 			glVertex3f(Q.Vertex2.Array[0], Q.Vertex2.Array[1], Q.Vertex2.Array[2]);
 			glVertex3f(Q.Vertex3.Array[0], Q.Vertex3.Array[1], Q.Vertex3.Array[2]);
			glVertex3f(Q.Vertex4.Array[0], Q.Vertex4.Array[1], Q.Vertex4.Array[2]);
	glEnd();
}

void OpenGLDrawing::DrawPolygon(const Polygon& P, const float* RGBColor) {
	glColor3f(RGBColor[0], RGBColor[1], RGBColor[2]);

	glBegin(GL_POLYGON);
		for (int i=0; i<P.Size; ++i) {
			glVertex3f(P.Get(i).Components.x, P.Get(i).Components.y, P.Get(i).Components.z);
		}
	glEnd();
}
