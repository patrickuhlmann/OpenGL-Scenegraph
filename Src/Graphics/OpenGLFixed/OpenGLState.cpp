#include "OpenGLState.h"

/** \brief Apply the state for the OpenGL fixed pipeline. First it goes through the disable list and then through the enable list
 */
// TODO: solve with for_each
void OpenGLState::Apply() const
{
	if (_disables) {
		// disable all states from the disable list
		for (StateVariableIterator DisableIt = _disables->begin(); DisableIt != _disables->end(); ++DisableIt) {
			glDisable(*DisableIt);
		}
	}

	if (_enables) {
		// enable all states from the enable list
		for (StateVariableIterator EnableIt = _enables->begin(); EnableIt != _enables->end(); ++EnableIt) {
			glEnable(*EnableIt);
		}
	}
}

/** \brief Undo the state for the OpenGL fixed pipeline. First it goes through the enable list and disables all of them and then it goes throught the disable list and enables all of them
 */
// TODO: solve with foreach
void OpenGLState::Undo() const
{
	if (_enables) {
		// disable all states from the enable list
		for (StateVariableIterator EnableIt = _enables->begin(); EnableIt != _enables->end(); ++EnableIt) {
			glDisable(*EnableIt);
		}
	}

	if (_disables) {
		// enable all states from the disable list
		for (StateVariableIterator DisableIt = _disables->begin(); DisableIt != _disables->end(); ++DisableIt) {
			glEnable(*DisableIt);
		}
	}
}
