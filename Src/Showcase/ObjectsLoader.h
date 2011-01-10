#pragma once

#include "../Application/SimpleApplication.h"
#include "../Base/Geometry/Cube.h"
#include "../Base/Geometry/Torus.h"
#include "../Base/Geometry/Sphere.h"

using namespace std;

/**
 * \brief Very simple Application which loads some objects from .obj files
 */
class ObjectsLoader : public SimpleApplication {
	private:

	public:
		ObjectsLoader();
		void Render(NodeVisitor* RenderVisitor, CompositeNode* l);
		void Init(CompositeNode* l, MeshFileLoader* MeshLoader);
		void Shutdown();
};
