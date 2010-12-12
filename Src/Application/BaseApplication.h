#pragma once

// Frameworks
#include <glog/logging.h>
#include "../Include/GL/glew.h"
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "../Include/GLShaderManager.h"
#include "../Include/GLBatch.h"

#include "InputManager.h"

class BaseApplication {
	private:
		void RenderBase();
		void SetupOpenGL();
		void CheckOpenGLError();

	protected:
		InputManager Input;
		GLShaderManager ShaderManager;
		GLBatch Batch;
		int FrameCounter;

	public:
		BaseApplication(string Title, int WindowWidth, int WindowHeight);
		void Start();
		virtual int GetFrameCounter();
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Resize(int NewWidth, int NewHeight) = 0;

	friend void BaseApplication_Render();
};

extern void BaseApplication_Resize(int, int);
extern void BaseApplication_Render();
extern BaseApplication* BaseApplicationObject;
