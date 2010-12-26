#include "SimpleApplication.h"

/**
 * \brief Initialize the Application which means it registres the Esc button to close the Application
 * \param Title Title which you can see in the titlebar
 * \param WindowWidth decides how wide the window will be (pixel)
 * \param WindowHeight decies how high the window will be (pixel)
 */
SimpleApplication::SimpleApplication(string Title, int WindowWidth, int WindowHeight) : BaseApplication(Title, WindowWidth, WindowHeight) {
	// Register Esc for Exit
	enuKey Esc = APP_KEY_ESC;
	Input.AddBinding("Exit", Esc);
	Input.AddListener("Exit", this->HandleKeysS);
}

/**
 * \brief This function is called only once before the first update happens to initialize everything we want
 * Empty Implementation
 */
void SimpleApplication::Init() {

}

/**
 * \brief This function is called always before Render. You can do calculations for the next frame in this function
 * Empty implementation
 */
void SimpleApplication::Update() {

}

/**
 * \brief This function is called everytime we draw a frame. You need to draw everything you want to be on the next frame
 * Empty implementation
 */
void SimpleApplication::Render() {

}

/**
 * \brief This function is called whenever we change the size of the window (which includes one call when it is created the first time).
 * Default Implementation: Adjust GLViewport to new Width and Height
 */
void SimpleApplication::Resize(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
}

/**
 * \brief needs to be static as it is the callback function for key inputs which will be called from glut. Just redirects the call to the HandleKeys method of the most recently created real instance of SimpleApplication
 */
void SimpleApplication::HandleKeysS(enuKey Code, int x, int y) {
	reinterpret_cast<SimpleApplication*>(Instance)->HandleKeys(Code);
}

/**
 * \brief Method which gets the Key Events from Glut. Here we can handle all inputs
 * Default Implementation: Esc closes the Application
 * TODO: doesn't yet get all key inputs
 */
void SimpleApplication::HandleKeys(enuKey Code) {
	if (Code == APP_KEY_ESC) {
		exit(0);
	}
}

/**
 * \brief This method will be called if the Application is paused
 * Empty Implementation
 * TODO: not yet implemented
 */
void SimpleApplication::Pause() {

}

/**
 * \brief This method will be called if the Application is resumed
 * Empty Implementation
 * TODO: not yet implemented
 */
void SimpleApplication::Continue() {

}

/**
 * \brief This method will be called if the Application is closed
 * Empty Implementation
 * TODO: not yet implemented
 */
void SimpleApplication::Shutdown() {

}
