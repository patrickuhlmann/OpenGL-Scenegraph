#pragma once

#include "../Application/SimpleApplication.h"
#include "../Base/Geometry/Cube.h"
#include "../Base/Geometry/Torus.h"
#include "../Base/Geometry/Sphere.h"

#ifdef MEMORY_CHECK_ACTIVE
	#include "../../Libs/nvwa-0.8.2/debug_new.h"
#endif

using namespace std;

/**
 * \brief Very simple Application that just loads a sphere, a cube and a torus
 */
class SimpleGeometry : public SimpleApplication {
	private:

	public:
		SimpleGeometry();
		void Render(NodeVisitor* RenderVisitor, CompositeNode* l);
		void Init(CompositeNode* l, MeshFileLoader* MeshLoader);
		void Shutdown();
};
