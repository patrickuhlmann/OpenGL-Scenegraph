#include "PongGame.h"

/**
 * \brief Just redirect to SimpleApplication Constructor and create a window with a width of 800 and height of 600 pixels
 */
PongGame::PongGame() : SimpleApplication("PongGame", 800, 600) {
	SpeedX = 0.03f;
	SpeedY = 0.03f;
	BallPosX = 0;
	BallPosY = 0;
	BatPosY = 0;
	GameOver = false;
}

void PongGame::Init( CompositeNode* l, MeshFileLoader* MeshLoader) {
	// Init Camera
	Camera* c = reinterpret_cast<Camera*>(l->GetByName("GlobalCamera"));
	M3DVector3f pos;
	m3dLoadVector3( pos, 0.0f, 0.0f, 10.0f );
    c->SetPosition( pos );
    c->SetPerspective(45.0f,(GLfloat)800/(GLfloat)600,0.1f,100.0f);

	c->AddChild(
		(new Transform(string("WallLeft")))->AddChild(
			(new Geometry(new Cube(0.2f)))
	));

	c->AddChild(
		(new Transform(string("WallRight")))->AddChild(
			(new Geometry(new Cube(0.2f)))
	));

	c->AddChild(
		(new Transform(string("WallTop")))->AddChild(
			(new Geometry(new Cube(0.2f)))
	));

	c->AddChild(
		(new Transform(string("WallBottom")))->AddChild(
			(new Geometry(new Cube(0.2f)))
	));

	c->AddChild(
		(new Transform(string("BatLeft")))->AddChild(
			(new Geometry(new Cube(0.8f)))
	));

	c->AddChild(
		(new Transform(string("BatRight")))->AddChild(
			(new Geometry(new Cube(0.8f)))
	));

	c->AddChild(
		(new Transform(string("Ball")))->AddChild(
			(new Geometry(new Sphere(0.2f, 20, 20)))
	));
		
	Transform* t = reinterpret_cast<Transform*>(l->GetByName("WallLeft"));
	t->Translate(-5.1f, 0.0f, 0.0f);
	t->Scale(1.0f, 20.0f, 1.0f);

	t = reinterpret_cast<Transform*>(l->GetByName("WallRight"));
	t->Translate(5.1f, 0.0f, 0.0f);
	t->Scale(1.0f, 20.0f, 1.0f);

	t = reinterpret_cast<Transform*>(l->GetByName("WallTop"));
	t->Translate(0, 3.95f, 0.0f);
	t->Scale(25.0f, 0.15f, 1.0f);

	t = reinterpret_cast<Transform*>(l->GetByName("WallBottom"));
	t->Translate(0, -3.95f, 0.0f);
	t->Scale(25.0f, 0.15f, 1.0f);

	t = reinterpret_cast<Transform*>(l->GetByName("BatLeft"));
	t->Translate(-4.3f, 0.0f, 0.0f);
	t->Scale(0.038f, 1, 0.25f);

	t = reinterpret_cast<Transform*>(l->GetByName("BatRight"));
	t->Translate(4.3f, 0.0f, 0.0f);
	t->Scale(0.1f, 1, 0.25f);
}

void PongGame::Update(CompositeNode* RootNode) {
	if (GameOver)
		return;

	Transform* Ball = reinterpret_cast<Transform*>(RootNode->GetByName("Ball"));
	Ball->Translate(SpeedX, SpeedY, 0);
	BallPosX += SpeedX;
	BallPosY += SpeedY;

	// Unbeatable Computer
	Transform* BatRight = reinterpret_cast<Transform*>(RootNode->GetByName("BatRight"));
	BatRight->Translate(0, SpeedY, 0);

	// Reflect from top
	if (BallPosY > 3.75f)
		SpeedY = -SpeedY;

	// Reflect from bottom
	if (BallPosY < -3.75f)
		SpeedY = -SpeedY;

	// Reflect left
	if (BallPosX < -4.1f) {
		SpeedX = -SpeedX;

		// Check for GameOver
		if (abs(BatPosY - BallPosY) > 0.9f) {
			DLOG(INFO) << "BatPosY: " << BatPosY << ", BallPosY: " << BallPosY << endl;
			GameOver = true;
		}
	}

	// Reflect right
	if (BallPosX > 4.1f) {
		SpeedX = -SpeedX;
	}
}

void PongGame::HandleKeys(enuKey Code) {
	if (GameOver)
		return;

	Transform* Bat = reinterpret_cast<Transform*>(RootNode.GetByName("BatLeft"));

	switch (Code) {
		// Bat Up
		case APP_KEY_W:
			if (BatPosY < 3.75) {
				Bat->Translate(0, 0.12f, 0);
				BatPosY += 0.12f;
			}
			break;
			
		// Bat Down
		case APP_KEY_S:
			if (BatPosY > -3.75) {
				Bat->Translate(0, -0.12f, 0);
				BatPosY -= 0.12f;
			}
			break;
	}
}

void PongGame::Render(NodeVisitor* RenderVisitor, CompositeNode* l)
{ 
	RenderVisitor->Visit(l);

	if (FrameCounter < 200) {
		ShowText(-0.2f, 0.2f, "W is up and S is down");
	}

	if (GameOver)
		ShowText(-0.2f, 0.2f, "You lost ;D");
};

void PongGame::Shutdown()
{
};


void PongGame::ShowText(float x, float y, char *str)
{
	int len;
	
	glRasterPos2f(x, y);
	len = (int) strlen(str);
	glColor3f(1,0,0);

	for (int i = 0; i < len; ++i) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}

int main(int argc, char *argv[]) {
	PongGame App;
	App.Start();
}
