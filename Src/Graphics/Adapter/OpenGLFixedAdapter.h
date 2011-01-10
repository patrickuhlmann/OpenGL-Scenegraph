#pragma once

#include "GraphicsAdapter.h"
#include "../../Include/GL/glew.h"

/** \brief Adapter for OpenGL Fixed Pipeline */
class OpenGLFixedAdapter : public GraphicsAdapter {
		virtual void InitializeGraphics();
		virtual void BeforeRendering();
		virtual void AfterRendering();
};
