#pragma once

#include <GL/glut.h>
#include <string>
#include <map>
#include <glog/logging.h>

using namespace std;

enum enuKey {
	APP_KEY_ESC = 27,
	APP_KEY_A = 97,
	APP_KEY_B = 98,
	APP_KEY_C = 99,
	APP_KEY_D = 100,
	APP_KEY_E = 101,
	APP_KEY_F = 102,
	APP_KEY_G = 103,
	APP_KEY_H = 104,
	APP_KEY_I = 105,
	APP_KEY_J = 106,
	APP_KEY_K = 107,
	APP_KEY_L = 108,
	APP_KEY_M = 109,
	APP_KEY_N = 110,
	APP_KEY_O = 111,
	APP_KEY_P = 112,
	APP_KEY_Q = 113,
	APP_KEY_R = 114,
	APP_KEY_S = 115,
	APP_KEY_T = 116,
	APP_KEY_U = 117,
	APP_KEY_V = 118,
	APP_KEY_W = 119,
	APP_KEY_X = 120,
	APP_KEY_Y = 120,
	APP_KEY_Z = 120,
};

enum enuMouse {
	APP_MOUSE_LEFT,
	APP_MOUSE_RIGHT,
	APP_MOUSE_MIDDLE
};

typedef multimap<int, string> mmis;
typedef multimap<string, void (*)(enuKey, int, int)> mmsp;
typedef pair<mmis::iterator, mmis::iterator> mmispairit;
typedef pair<mmsp::iterator, mmsp::iterator> mmsppairit;

/**
 * \brief Allows to bind a key or mouse button to an action (string). Furthermore allows binding of an action to a Callback
   function. Whenever a Key is pressed (glut) it checks if we have an action for this key and then it calls all callbacks that
   listen for this action
 */
class InputManager {
	private:
		/** \brief This reference is needed so that the static callback function can redirect to the most recently created instance */
		static InputManager* Instance;
		/** \brief This is the callback function which (will be called indirectly via HandleKeysS) can then call all registred callback function of this class */
		void HandleKeys(int Code, int x, int y);
		/** \brief Stores the Binding which Action is associated with which key */
		mmis ActionInputMap;
		/** \brief Stores the Binding which Callback function is called for which action */
		mmsp ActionCallbackMap;

	public:
		InputManager();
		void AddBinding(string Action, enuKey KeyInput);
		void AddBinding(string Action, enuMouse MouseInput);
		void AddListener(string Action, void (*HandlerCallback)(enuKey, int, int));
		void AddGlobalListener(void (*HandlerCallback)(enuKey, int, int));
		static void HandleKeysS(unsigned char Code, int x, int y);
};
