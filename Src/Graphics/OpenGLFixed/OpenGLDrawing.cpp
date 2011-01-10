#include "OpenGLDrawing.h"

int OpenGLDrawing::TriangleCounter = 0;
int OpenGLDrawing::QuadCounter = 0;
int OpenGLDrawing::PolygonCounter = 0;
const void* OpenGLDrawing::LastMaterialPointer = 0;

void OpenGLDrawing::SetDrawingColorAndMaterial(const Material* Mat) {
	// Tests showed that it is easily 20% faster if we don't need to change the material definition all the time
	if (LastMaterialPointer == Mat) {
		return;
	}

	glMaterialfv(GL_FRONT, GL_AMBIENT, Mat->GetAmbientLight().GetConstPointer());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Mat->GetDiffuseLight().GetConstPointer());
	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat->GetSpecularLight().GetConstPointer());
	glMateriali(GL_FRONT,GL_SHININESS, Mat->GetShininess());

	LastMaterialPointer = Mat;
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

	OpenGLDrawing::TriangleCounter++;
}

void OpenGLDrawing::DrawTriangle(const Triangle* T) {
	SetDrawingColorAndMaterial(T->Mat);

	glBegin(GL_TRIANGLES);
			glNormal3fv(T->Normal->Array);
			glVertex3fv(T->Vertex1->Array);
 			glVertex3fv(T->Vertex2->Array);
 			glVertex3fv(T->Vertex3->Array);
	glEnd();

	OpenGLDrawing::TriangleCounter++;
}

void OpenGLDrawing::DrawTriangles(const vector<Triangle*>& T) {
	glBegin(GL_TRIANGLES);

	for (vector<Triangle*>::const_iterator it = T.begin(); it != T.end(); ++it) {
		SetDrawingColorAndMaterial((*it)->Mat);

		glNormal3fv((*it)->Normal->Array);
		glVertex3fv((*it)->Vertex1->Array);
		glVertex3fv((*it)->Vertex2->Array);
		glVertex3fv((*it)->Vertex3->Array);
		OpenGLDrawing::TriangleCounter++;
	}

	glEnd();
}

void OpenGLDrawing::DrawQuad(const Quad* Q) {
	SetDrawingColorAndMaterial(Q->Mat);

	glBegin(GL_QUADS);
			glNormal3fv(Q->Normal->Array);
			glVertex3fv(Q->Vertex1->Array);
 			glVertex3fv(Q->Vertex2->Array);
 			glVertex3fv(Q->Vertex3->Array);
			glVertex3fv(Q->Vertex4->Array);
	glEnd();

	OpenGLDrawing::QuadCounter++;
}

void OpenGLDrawing::DrawPolygon(const Polygon* P) {
	SetDrawingColorAndMaterial(P->Mat);

	glBegin(GL_POLYGON);
		glNormal3fv(P->Normal->Array);
		for (int i=0; i<P->Size; ++i) {
			glVertex3fv(P->Get(i)->Array);
		}
	glEnd();

	OpenGLDrawing::PolygonCounter++;
}

/**
 * \brief Check if there was an error. If there was one we log it to the console
 */
void OpenGLDrawing::CheckOpenGLError() {
	GLenum err = glGetError();

	while (err != GL_NO_ERROR) {
		switch (err) {
			case GL_INVALID_ENUM:
				DLOG(WARNING) << "OpenGL Render Error: enum value was out of Range" << endl;
			case GL_INVALID_VALUE:
				DLOG(WARNING) << "OpenGL Render Error: numeric argument was out of Range" << endl;
			case GL_INVALID_OPERATION:
				DLOG(WARNING) << "OpenGL Render Error in Frame: operation was illegal for current state" << endl;
			case GL_OUT_OF_MEMORY:
				DLOG(WARNING) << "OpenGL Render Error in Frame: not enough memory to execute the command" << endl;
		}
		err = glGetError();
	}
}
