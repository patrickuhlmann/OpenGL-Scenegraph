#pragma once

#include "../../../Libs/nvwa-0.8.2/debug_new.h"

/** \brief Abstract Base class works as Adapter to Connect the Application to a Graphics System like OpenGL or DirectX */
class GraphicsAdapter {
	public:
		/** Will be called once when initializing the Graphic system */
		virtual void InitializeGraphics() = 0;
		/** Will be called everytime before Rendering */
		virtual void BeforeRendering() = 0;
		/** Will be called everytime after Rendering */
		virtual void AfterRendering() = 0;
		/** Destructor. Empty */
		virtual ~GraphicsAdapter() {};
};
