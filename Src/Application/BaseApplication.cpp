#include "BaseApplication.h"

/**
 * \brief Initialize Glut, Create Window, Setup Callback for Render, Resize and Keyboard Handler
 * \param Title Title which will be print to the titlebar of the window
 * \param WindowWidth decides how wide the window will be (pixel)
 * \param WindowHeight decides how heigh the window will be (pixel)
 */
BaseApplication::BaseApplication(string Title, int WindowWidth, int WindowHeight) : RVisitor(&ShaderManager), RootNode(string("GlobalLight")) {
	// Initialize Glut and our Window
	char* argv[] = { "BaseApplication" };
	int argc = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(Title.c_str());

	// Setup the Callback Functions
	BaseApplication::Instance = this;
	glutReshapeFunc(this->ResizeS);
	glutDisplayFunc(this->RenderS);
	LOG(INFO) << "Registred Render Function in Glut" << endl;

	// Setup KeyHandler
	glutKeyboardFunc(Input.HandleKeysS);
	DLOG(INFO) << "Registred Keyboard Handler in Glut" << endl;

	// Initialize Glew
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		exit(1);
	}

	// Initialize the MeshLoader
	this->MeshLoader.AddMeshLoader(new MeshLoaderObj());

	this->SetupOpenGL();

	// Initialize the Scenegraph
	this->RootNode.AddChild(new Camera("GlobalCamera"));

	this->FrameCounter = 0;

	this->PauseFlag = false;
}

/**
 * \brief This function is intended to really start our application. It calls Virtual Init Function and Start the glut Main Loop
 */
void BaseApplication::Start() {
	this->Init(&this->RootNode, &this->MeshLoader);

	glutMainLoop();
}

/**
 * \brief Return how many frames we already displayed
 */
int BaseApplication::GetFrameCounter() {
	return this->FrameCounter;
}

/**
 * \brief Adjust the OpenGL Viewport and calls the Resize Lifecycle method
 */
void BaseApplication::ResizeBase(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	this->Resize(NewWidth, NewHeight);
}

/**
 * \brief Set the Background Color
 */
void BaseApplication::SetupOpenGL() {
	// Black Background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*// Get Information about OpenGL Version
	const GLubyte *glGetString(GLenum name);

	// Set Preference for Speed/Quality
	void glHint(GLenum target, GLenum mode);*/

	ShaderManager.InitializeStockShaders();
}

/**
 * \brief Check if there was an error. If there was one we log it to the console
 */
void BaseApplication::CheckOpenGLError() {
	GLenum err = glGetError();
	while (err != GL_NO_ERROR) {
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
		err = glGetError();
	}
}

/**
 * \brief Check if there was an error, call virtual update function, clear the window, call virtual render, swap the buffers and increase the framecounter
 */
void BaseApplication::RenderBase() {
	this->CheckOpenGLError();

	if (this->PauseFlag)
		return;

	this->Update(&this->RootNode);
			
	// Clear the window with current clearing (=background) color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->Render(&this->RVisitor, &this->RootNode);

	// Perform the buffer swap to display the back buffer
	glutSwapBuffers();

	++this->FrameCounter;

	// Redraw
	glutPostRedisplay();
}

/**
 * \brief Needs to be static because it is a callback function which needs to be called from glut. Redirects the call
 to the RenderBase function of the Instance
 */
void BaseApplication::RenderS() {
	BaseApplication::Instance->RenderBase();
}

/**
 * \brief Needs to be static because it is a callback function which needs to be called from glut. Redirects the call
 to the Resize function of the Instance
 */
void BaseApplication::ResizeS(int NewWidth, int NewHeight) {
	BaseApplication::Instance->ResizeBase(NewWidth, NewHeight);
}
