#include "OpenGLState.h"

/** \brief Appy the state for the OpenGL fixed pipeline. First it goes through the disable list and then through the enable list
 */
void OpenGLState::Apply()
{
	// first disable all states in the disable list
	if (_enables) {
		for (StateVariableIterator EnableIt = _enables->begin(); EnableIt != _enables->end(); ++EnableIt) {
			glEnable(*EnableIt);
		}
	}

	if (_disables) {
		// then enable all states in the enable list
		for (StateVariableIterator DisableIt = _disables->begin(); DisableIt != _disables->end(); ++DisableIt) {
			glDisable(*DisableIt);
		}
	}
}
