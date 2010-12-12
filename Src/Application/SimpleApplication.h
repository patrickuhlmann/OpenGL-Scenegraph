#pragma once

#include "BaseApplication.h"

class SimpleApplication : public BaseApplication {
	private:

	public:
		SimpleApplication(string Title, int WindowWidth, int WindowHeight);
		virtual void Init();
		virtual void Update();
		virtual void Render();
		virtual void Resize(int NewWidth, int NewHeight);
		// TODO: implement
		virtual void HandleKeys(enuKey Code);
		// TODO: implement
		virtual void Pause();
		// TODO: implement
		virtual void Continue();
		// TODO: implement
		virtual void Shutdown();
};
