#include "BaseApplication.h"

int BaseApplication::MaxFrameRate = 25;

/**
 * \brief Initialize Glut, Create Window, Setup Callback for Render, Setup Time to restrict FPS, Resize and Keyboard Handler
 * \param Title Title which will be print to the titlebar of the window
 * \param WindowWidth decides how wide the window will be (pixel)
 * \param WindowHeight decides how heigh the window will be (pixel)
 * \param GraphicsAdapter as interface to the Graphics Library (OpenGL/DirectX) to use, we take ownership and remove it at the end
 * \param NodeVisitor to use for rendering, we take ownership and remove it at the end
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
	glutTimerFunc(1000/MaxFrameRate, this->TimerS, 0);
	LOG(INFO) << "Registred Render Function in Glut" << endl;

	// Setup KeyHandler
	glutKeyboardFunc(Input.HandleKeysS);
	DLOG(INFO) << "Registred Keyboard Handler in Glut" << endl;

	// Initialize the MeshLoader
	this->MeshLoader.AddMeshLoader(new MeshLoaderObj());

	this->RenderVisitor = RenderVisitor;

	this->GAdapter = Adapter;
	this->GAdapter->InitializeGraphics();

	this->FrameCounter = 0;

	this->PauseFlag = false;
	this->PrintTime = false;
}

/**
 * \brief Removes the GraphicsAdapter and the RenderVisitor
 */
BaseApplication::~BaseApplication() {
	delete this->GAdapter;
	delete this->RenderVisitor;
	DLOG(INFO) << "~BaseApplication" << endl;
}

/**
 * \brief This function is intended to really start our application. It calls Virtual Init Function and Start the glut Main Loop. It will hang until we end the Application and then it will call Shutdown
 */
void BaseApplication::Start() {
	this->Init(&this->RootNode, &this->MeshLoader);

    #if defined(linux) || defined(__linux)
		glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION); 
    #endif

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
 * \param NewWidth of the Window
 * \param NewHeight of the Window
 */
void BaseApplication::ResizeBase(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	this->Resize(NewWidth, NewHeight);
}

/**
 * \brief Do nothing if the pause flag ist set. Otherwise execute the the Update and Render function. If PrintTime is set it will also messure how long it takes for them to execute
 */
void BaseApplication::RenderBase() {
	if (this->PauseFlag)
		return;

	float BeforeUpdate = glutGet(GLUT_ELAPSED_TIME);
	this->Update(&this->RootNode);
	float UpdateTime = glutGet(GLUT_ELAPSED_TIME) - BeforeUpdate;

	if (PrintTime)
		DLOG(INFO) << "Update took: " << UpdateTime << endl;

	this->GAdapter->BeforeRendering();

	float BeforeRender = glutGet(GLUT_ELAPSED_TIME);
	this->Render(this->RenderVisitor, &this->RootNode);
	float RenderTime = glutGet(GLUT_ELAPSED_TIME) - BeforeRender;

	if (PrintTime)
		DLOG(INFO) << "Render took: " << RenderTime << endl;

	this->GAdapter->AfterRendering();

	// Perform the buffer swap to display the back buffer
	glutSwapBuffers();

	++this->FrameCounter;
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
 * \param NewWidth of the Window
 * \param NewHeight of the Window
 */
void BaseApplication::ResizeS(int NewWidth, int NewHeight) {
	BaseApplication::Instance->ResizeBase(NewWidth, NewHeight);
}

/** \brief This timer function gets called whenever a frame is ready (regarding to FPS). It will display a frame and set a callback for itself 
 * \param int ignored
 */
void BaseApplication::TimerS(int) {
	glutTimerFunc(1000/MaxFrameRate, BaseApplication::TimerS, 0);
	glutPostRedisplay();
}
