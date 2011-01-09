#pragma once

#include "Application/SimpleApplication.h"

using namespace std;

/**
 * \brief Very simple Application which does nothing but use our framework to create a Window
 */
class SkeletonApp : public SimpleApplication {
	private:

	public:
		SkeletonApp();
		void Render(NodeVisitor* RenderVisitor, CompositeNode* l);
		void Init(CompositeNode* l, MeshFileLoader* MeshLoader);
		void Shutdown();
};
