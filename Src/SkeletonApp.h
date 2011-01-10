#pragma once

#include "Application/SimpleApplication.h"
#include "Base/Geometry/Cube.h"
#include "Base/Geometry/Torus.h"
#include "Base/Geometry/Sphere.h"

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
