#include "SimpleApplication.h"

SimpleApplication::SimpleApplication(string Title, int WindowWidth, int WindowHeight) : BaseApplication(Title, WindowWidth, WindowHeight) {
}

void SimpleApplication::Init() {

}

void SimpleApplication::Update() {

}

void SimpleApplication::Render() {

}

void SimpleApplication::Resize(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
}

void SimpleApplication::HandleKeys(enuKey Code) {

}

void SimpleApplication::Pause() {

}

void SimpleApplication::Continue() {

}

void SimpleApplication::Shutdown() {

}
