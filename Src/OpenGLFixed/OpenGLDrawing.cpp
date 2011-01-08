#include "OpenGLDrawing.h"

void OpenGLDrawing::DrawTriangle(const float* Vertex1, const float* Vertex2, const float* Vertex3, const float* Normal, const float* RGBColor){
	glColor3f(RGBColor[0], RGBColor[1], RGBColor[2]);

	glBegin(GL_TRIANGLES);
			glNormal3f(Normal[0], Normal[1], Normal[2]);
			glVertex3f(Vertex1[0], Vertex1[1], Vertex1[2]);
 			glVertex3f(Vertex2[0], Vertex2[1], Vertex2[2]);
 			glVertex3f(Vertex3[0], Vertex3[1], Vertex3[2]);
	glEnd();
}

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
