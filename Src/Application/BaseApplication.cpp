#include "BaseApplication.h"

/**
 * \brief Initialize Glut, Create Window, Setup Callback for Render, Resize and Keyboard Handler
 * \param Title Title which will be print to the titlebar of the window
 * \param WindowWidth decides how wide the window will be (pixel)
 * \param WindowHeight decides how heigh the window will be (pixel)
 */
BaseApplication::BaseApplication(string Title, int WindowWidth, int WindowHeight, GraphicsAdapter* Adapter, NodeVisitor* RenderVisitor) : RootNode(string("Root")) {
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

	this->RenderVisitor = RenderVisitor;

	this->GAdapter = Adapter;
	this->GAdapter->InitializeGraphics();

	this->FrameCounter = 0;

	this->PauseFlag = false;
	this->PrintTime = false;
}

BaseApplication::~BaseApplication() {
	DLOG(INFO) << "~BaseApplication" << endl;
	delete this->GAdapter;
	delete this->RenderVisitor;
}

/**
 * \brief This function is intended to really start our application. It calls Virtual Init Function and Start the glut Main Loop
 */
void BaseApplication::Start() {
	this->Init(&this->RootNode, &this->MeshLoader);

	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION); 

	glutMainLoop();

	Shutdown();
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
 * \brief Check if there was an error, call virtual update function, clear the window, call virtual render, swap the buffers and increase the framecounter
 */
void BaseApplication::RenderBase() {
	if (this->PauseFlag)
		return;

	this->GAdapter->BeforeRendering();

	if (PrintTime) {
		float BeforeUpdate = glutGet(GLUT_ELAPSED_TIME);
		this->Update(&this->RootNode);
		DLOG(INFO) << "Update took: " << glutGet(GLUT_ELAPSED_TIME) - BeforeUpdate << endl;
	} else {
		this->Update(&this->RootNode);
	}

	if (PrintTime) {
		float BeforeRender = glutGet(GLUT_ELAPSED_TIME);
		this->Render(this->RenderVisitor, &this->RootNode);
		DLOG(INFO) << "Render took: " << glutGet(GLUT_ELAPSED_TIME) - BeforeRender << endl;
	} else {
		this->Render(this->RenderVisitor, &this->RootNode);
	}

	this->GAdapter->AfterRendering();

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
