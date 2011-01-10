#pragma once

#include "../../Graph/State.hpp"
#include "../../Include/GL/glew.h"

/** \brief This State uses OpenGLFixed Pipeline enable and disable calls to activate/deactivate the states */
class OpenGLState : public State {
	void Apply();
};
