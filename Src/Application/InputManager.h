#pragma once

#include <string>

using namespace std;

enum enuKey {
	KEY_LEFT = 1,
	KEY_RIGHT = 2,
	KEY_DOWN = 3,
	KEY_UP = 4
};

enum enuMouse {
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	MOUSE_MIDDLE
};

class InputManager {
	private:

	public:
		InputManager();
		void AddBinding(string Action, enuKey KeyInput);
		void AddBinding(string Action, enuMouse MouseInput);
		void AddListener(string Action, void (*HandlerCallback)(enuKey));
};
