#pragma once

#include "../Application/SimpleApplication.h"
#include "../Base/Geometry/Cube.h"
#include "../Base/Geometry/Torus.h"
#include "../Base/Geometry/Sphere.h"
#include "../../Libs/nvwa-0.8.2/debug_new.h"

using namespace std;

/**
 * \brief Very simple Application that just loads a sphere, a cube and a torus
 */
class PongGame : public SimpleApplication {
	private:
		float SpeedX;
		float SpeedY;
		float BallPosX;
		float BallPosY;
		float BatPosY;
		bool GameOver;

	public:
		PongGame();
		void Render(NodeVisitor* RenderVisitor, CompositeNode* l);
		void Init(CompositeNode* l, MeshFileLoader* MeshLoader);
		void Update(CompositeNode* RootNode);
		void Shutdown();
		void HandleKeys(enuKey Code);
		void ShowText(float x, float y, char *string);
};
