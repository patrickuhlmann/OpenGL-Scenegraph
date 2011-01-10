#include "InputManager.h"

/**
 * \brief Save this instance in the static variable
 */
InputManager::InputManager() {
	Instance = this;
}

InputManager::~InputManager() {
	DLOG(INFO) << "~InputManager" << endl;
}

/**
 * \brief Needs to be static as it is called from glut. It will redirect to the HandleKeys method of the active instance
 */
void InputManager::HandleKeysS(unsigned char Code, int x, int y) {
	Instance->HandleKeys((int)Code, x, y);
}

/**
 * \brief Handles all glut Keys. Checks if we defined an action and calls it if we did
 * \param Code Key Code
 * \param x x mouse coordinate
 * \param y y mouse coordinate
 */
void InputManager::HandleKeys(int Code, int x, int y) {
	DLOG(INFO) << "Handle Key " << Code << endl;

	// Global Callback
	mmsppairit Global = ActionCallbackMap.equal_range("_GLOBAL_");
	for (mmsp::iterator it = Global.first; it != Global.second; ++it) {
		((*it).second)(static_cast<enuKey>(Code), x, y);
	}

	// Find Actions with this Code
	mmispairit ARet = ActionInputMap.equal_range(Code);

	for (mmis::iterator it = ARet.first; it != ARet.second; ++it) {
		string Action = (*it).second;
		DLOG(INFO) << "HandleKeys for Action " << Action << endl;

		// Get Callbacks for Actions
		mmsppairit CRet = ActionCallbackMap.equal_range(Action);

		for (mmsp::iterator it = CRet.first; it != CRet.second; ++it) {
			((*it).second)(static_cast<enuKey>(Code), x, y);
		}
	}
}

/**
 * \brief Bind a Key to an action
 */
void InputManager::AddBinding(string Action, enuKey KeyInput) {
	ActionInputMap.insert(mmis::value_type(KeyInput, Action));
	DLOG(INFO) << "Added Binding for " << Action << " for key " << KeyInput << endl;
}

/**
 * \brief Bind a MouseKey to an action
 */
void InputManager::AddBinding(string Action, enuMouse MouseInput) {
	ActionInputMap.insert(mmis::value_type(MouseInput, Action));
	DLOG(INFO) << "Added Binding for " << Action << endl;
}

/**
 * \brief Add a Callback Method for an Action. This callback will be called whenever a key activates an action which is associated to this callback
 */
void InputManager::AddListener(string Action, void (*HandlerCallback)(enuKey, int, int)) {
	ActionCallbackMap.insert(mmsp::value_type(Action, HandlerCallback));
	DLOG(INFO) << "Added Callback for " << Action << endl;
}

/**
 * \brief Add a Callback Method for every key. This callback will be called whenever a key is pressed
 */
void InputManager::AddGlobalListener(void (*HandlerCallback)(enuKey, int, int)) {
	ActionCallbackMap.insert(mmsp::value_type("_GLOBAL_", HandlerCallback));
	DLOG(INFO) << "Added Global Callback" << endl;
}
