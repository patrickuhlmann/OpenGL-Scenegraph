#include "OpenGLFixedAdapter.h"

void OpenGLFixedAdapter::InitializeGraphics() {
	// Black Background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*// Get Information about OpenGL Version
	const GLubyte *glGetString(GLenum name);

	// Set Preference for Speed/Quality
	void glHint(GLenum target, GLenum mode);*/
}

// Clear the window with current clearing (=background) color
void OpenGLFixedAdapter::BeforeRendering() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

/** \brief Empty implementation. We don't need to do any task */
void OpenGLFixedAdapter::AfterRendering() {

}
