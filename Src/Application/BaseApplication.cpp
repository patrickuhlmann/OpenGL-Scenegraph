#include "BaseApplication.h"

BaseApplication::BaseApplication(string Title, int WindowWidth, int WindowHeight) {
	// Initialize Glut and our Window
	char *argv[] = {"BaseApplication"};
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(Title.c_str());

	// Setup the Callback Functions
	BaseApplicationObject = this;
	glutReshapeFunc(BaseApplication_Resize);
	glutDisplayFunc(BaseApplication_Render);

	// Initialize Glew
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		exit(1);
	}

	this->SetupOpenGL();

	this->FrameCounter = 0;
}

void BaseApplication::Start() {
	this->Init();

	// Start Application
	glutMainLoop();
}

int BaseApplication::GetFrameCounter() {
	return this->FrameCounter;
}

void BaseApplication::SetupOpenGL() {
	// Black Background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*// Get Information about OpenGL Version
	const GLubyte *glGetString(GLenum name);

	// Set Preference for Speed/Quality
	void glHint(GLenum target, GLenum mode);*/

	// TODO: gives segmentfault!!!
	//ShaderManager.InitializeStockShaders();
}

void BaseApplication::CheckOpenGLError() {
	GLenum err;
	while (err != GL_NO_ERROR) {
		err = glGetError();
		switch (err) {
			case GL_INVALID_ENUM:
				DLOG(WARNING) << "OpenGL Render Error in Frame " << this->FrameCounter << ": enum value was out of Range" << endl;
			case GL_INVALID_VALUE:
				DLOG(WARNING) << "OpenGL Render Error in Frame " << this->FrameCounter << ": numeric argument was out of Range" << endl;
			case GL_INVALID_OPERATION:
				DLOG(WARNING) << "OpenGL Render Error in Frame " << this->FrameCounter << ": operation was illegal for current state" << endl;
			case GL_OUT_OF_MEMORY:
				DLOG(WARNING) << "OpenGL Render Error in Frame " << this->FrameCounter << ": not enough memory to execute the command" << endl;
		}
	}
}

void BaseApplication::RenderBase() {
	this->CheckOpenGLError();

	this->Update();
			
	// Clear the window with current clearing (=background) color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->Render();

	// Perform the buffer swap to display the back buffer
	glutSwapBuffers();

	++this->FrameCounter;
}
