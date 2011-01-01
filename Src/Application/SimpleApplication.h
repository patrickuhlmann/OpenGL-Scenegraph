#pragma once

#include "BaseApplication.h"

/**
 * \brief This class can be used to develop simple applications. It has some lifecycle methods and simple keyhandling for example Esc to close the application
 */
class SimpleApplication : public BaseApplication {
	private:
		void HandleKeysSimple(enuKey Code);

	public:
		SimpleApplication(string Title, int WindowWidth, int WindowHeight);
		virtual void Init();
		virtual void Update();
		virtual void Render();
		virtual void Resize(int NewWidth, int NewHeight);
		virtual void HandleKeys(enuKey Code);
		static  void HandleKeysS(enuKey Code, int x, int y);
		virtual void Pause();
		virtual void Continue();
		virtual void Shutdown();
		static void ShutdownS();
};
