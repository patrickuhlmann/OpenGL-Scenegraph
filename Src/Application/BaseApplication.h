#pragma once

// Frameworks
#include <glog/logging.h>
#include "../Include/GL/glew.h"
#ifdef __APPLE__
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif

// C++
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

// Own classes
#include "../Include/GLShaderManager.h"
#include "../Include/GLBatch.h"
#include "InputManager.h"
#include "../MeshLoaders/MeshFileLoader.h"
#include "../MeshLoaders/MeshLoaderObj.h"
#include "../Graph/Light.hpp"
#include "../Graph/Camera.hpp"
#include "../Graph/RenderVisitor.hpp"

using namespace std;

/**
 * \brief This class initializes OpenGL with Glut and provides some utility methods and lifecycle methods which are useful for all kind of applications. It doesn't draw anything or handle any keys.
 */
class BaseApplication {
	private:
		void RenderBase();
		void SetupOpenGL();
		void CheckOpenGLError();
		void ResizeBase(int NewWidth, int NewHeight);

	protected:
		/** \brief InputManager which we use for this application. */
		InputManager Input;
		/** \brief ShaderManager which we use for this application */
		GLShaderManager ShaderManager;
		/** \brief Batch which we use for this application */
		GLBatch Batch;
		/** \brief always holds the actual number of frames we processed */
		int FrameCounter;
		/** \brief Points to the most recently created instance of this class. This is necessary so that the Static Callbacks for Resize and Render are able to call the methods of the active instance */
		static BaseApplication *Instance;
		/** \brief Indicates if the Application is Paused (true yes, false otherwise) */
		bool PauseFlag;
		/** \brief Helper to Load a Mesh from a file */
		MeshFileLoader MeshLoader;
		/** \brief RootNode of the Scenegraph */
		Light RootNode;
		/** \brief RenderVisitor for the Scenegraph */
		RenderVisitor RVisitor;

	public:
		BaseApplication(string Title, int WindowWidth, int WindowHeight);
		void Start();
		virtual int GetFrameCounter();
		/** \brief This function is called only once before the first update happens to initialize everything we want */
		virtual void Init(Light* RootNode, MeshFileLoader* MeshLoader) = 0;
		/** \brief This function is called always before Render. You can do calculations for the next frame in this function */
		virtual void Update(Light* RootNode) = 0;
		/** \brief This function is called everytime we draw a frame. You need to draw everything you want to be on the next frame */
		virtual void Render(RenderVisitor* RVisitor, Light* RootNode) = 0;
		static void RenderS();
		/** \brief This function is called whenever we change the size of the window (which includes one call when it is created the first time) */
		virtual void Resize(int NewWidth, int NewHeight) = 0;
		static void ResizeS(int NewWidth, int NewHeight);
};
