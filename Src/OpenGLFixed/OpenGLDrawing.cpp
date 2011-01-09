#include "OpenGLDrawing.h"

void OpenGLDrawing::SetDrawingColorAndMaterial(const Material* Mat) {
	const Vector3& Color = Mat->GetAmbientLight();
	glColor3fv(Color.GetConstPointer());
		
	// for specular highlight
	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat->GetSpecularLight().GetConstPointer());
	glMateriali(GL_FRONT,GL_SHININESS, Mat->GetShininess());
}

void OpenGLDrawing::DrawPoint(const Vector3* Vertex1, const Material* Mat) {
	SetDrawingColorAndMaterial(Mat);

	glBegin(GL_POINTS);
		glVertex3fv(Vertex1->Array);
	glEnd();
}

void OpenGLDrawing::DrawLine(const Vector3* Vertex1, const Vector3* Vertex2, const Material* Mat) {
	SetDrawingColorAndMaterial(Mat);

	glBegin(GL_LINES);
		glVertex3fv(Vertex1->Array);
		glVertex3fv(Vertex2->Array);
	glEnd();
}

void OpenGLDrawing::DrawTriangle(const Vector3* Vertex1, const Vector3* Vertex2, const Vector3* Vertex3, const float* Normal, const Material* Mat){
	SetDrawingColorAndMaterial(Mat);

	glBegin(GL_TRIANGLES);
			glNormal3fv(Normal);
			glVertex3fv(Vertex1->Array);
 			glVertex3fv(Vertex2->Array);
 			glVertex3fv(Vertex3->Array);
	glEnd();
}

void OpenGLDrawing::DrawTriangle(const Triangle* T) {
	SetDrawingColorAndMaterial(T->Mat);

	glBegin(GL_TRIANGLES);
			glVertex3fv(T->Vertex1->Array);
 			glVertex3fv(T->Vertex2->Array);
 			glVertex3fv(T->Vertex3->Array);
	glEnd();
}

void OpenGLDrawing::DrawQuad(const Quad* Q) {
	SetDrawingColorAndMaterial(Q->Mat);

	glBegin(GL_QUADS);
			glVertex3fv(Q->Vertex1->Array);
 			glVertex3fv(Q->Vertex2->Array);
 			glVertex3fv(Q->Vertex3->Array);
			glVertex3fv(Q->Vertex4->Array);
	glEnd();
}

void OpenGLDrawing::DrawPolygon(const Polygon* P) {
	SetDrawingColorAndMaterial(P->Mat);

	glBegin(GL_POLYGON);
		for (int i=0; i<P->Size; ++i) {
			glVertex3fv(P->Get(i)->Array);
		}
	glEnd();
}
