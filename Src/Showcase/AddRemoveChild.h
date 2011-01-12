#pragma once

#include "../Application/SimpleApplication.h"
#include "../Base/Geometry/Cube.h"
#include "../Base/Geometry/Torus.h"
#include "../Base/Geometry/Sphere.h"

using namespace std;

/**
 * \brief Very simple Application which creates and deletes a bunch of objects
 */
class AddRemoveChild : public SimpleApplication {
	private:
		bool Increasing;
		int ChildCount;

	public:
		AddRemoveChild();
		void Render(NodeVisitor* RenderVisitor, CompositeNode* l);
		void Update(CompositeNode* RootNode);
		void Init(CompositeNode* l, MeshFileLoader* MeshLoader);
		void Shutdown();
};
