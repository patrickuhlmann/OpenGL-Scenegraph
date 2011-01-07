#include "SimpleApplication.h"

/**
 * \brief Initialize the Application which means it registres the Esc button to close the Application
 * \param Title Title which you can see in the titlebar
 * \param WindowWidth decides how wide the window will be (pixel)
 * \param WindowHeight decies how high the window will be (pixel)
 */
SimpleApplication::SimpleApplication(string Title, int WindowWidth, int WindowHeight) : BaseApplication(Title, WindowWidth, WindowHeight) {
	Input.AddGlobalListener(this->HandleKeysS);
	atexit(this->ShutdownS);
}

/**
 * \brief This function is called only once before the first update happens to initialize everything we want
 * Empty Implementation
 *
 * \param RootNode of the Scenegraph
 * \param MeshLoader that can be used to Load Meshs from Files
 */
void SimpleApplication::Init(Light* RootNode, MeshFileLoader* MeshLoader) {

}

/**
 * \brief This function is called always before Render. You can do calculations for the next frame in this function
 * Empty implementation
 * \param RootNode of the Scenegraph
 */
void SimpleApplication::Update(Light* RootNode) {

}

/**
 * \brief This function is called everytime we draw a frame. You need to draw everything you want to be on the next frame
 * Empty implementation
 *
 * \param RVisitor to visit and render the Scenegraph
 * \param RootNode of the Scenegraph
 */
void SimpleApplication::Render(RenderVisitor* RVisitor, Light* RootNode) {

}

/**
 * \brief This function is called whenever we change the size of the window (which includes one call when it is created the first time).
 * Empty Implementation
 * \param NewWidth of the Window
 * \param NewHeight of the Window
 */
void SimpleApplication::Resize(int NewWidth, int NewHeight) {

}

/**
 * \brief needs to be static as it is the callback function for key inputs which will be called from glut. Just redirects the call to the HandleKeys method of the most recently created real instance of SimpleApplication
 * \param Code of the pressed key
 * \param x position of the mouse
 * \param y position of the mouse
 */
void SimpleApplication::HandleKeysS(enuKey Code, int x, int y) {
	reinterpret_cast<SimpleApplication*>(Instance)->HandleKeysSimple(Code);
}

/**
 * \brief Method which gets the Key Events from Glut. Here we handle the SimpleApplication Inputs
 * at the end we call the HandleKeys method
 * \param Code of the pressed key
 */
void SimpleApplication::HandleKeysSimple(enuKey Code) {
	if (Code == APP_KEY_ESC) {
		exit(0);
	} else if (Code == APP_KEY_P) {
		this->PauseFlag = !this->PauseFlag;
		if (this->PauseFlag)
			this->Pause();
		else
			this->Continue();
	}

	this->HandleKeys(Code);
}

/**
 * \brief Method which gets the Key Events from Glut. Here we can handle all inputs
 * Default Implementation: Empty
 * \param Code of the pressed key
 */
void SimpleApplication::HandleKeys(enuKey Code) {

}

/**
 * \brief This method will be called if the Application is paused
 * Empty Implementation
 */
void SimpleApplication::Pause() {

}

/**
 * \brief This method will be called if the Application is resumed
 * Empty Implementation
 */
void SimpleApplication::Continue() {

}

/**
 * \brief This method will be called if the Application is closed
 * Empty Implementation
 */
void SimpleApplication::Shutdown() {

}

/**
 * \brief needs to be static as it is the callback function for key inputs which will be called from glut. Just redirects the call to the HandleKeys method of the most recently created real instance of SimpleApplication
 */
void SimpleApplication::ShutdownS() {
	reinterpret_cast<SimpleApplication*>(Instance)->Shutdown();
}
