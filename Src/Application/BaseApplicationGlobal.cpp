#include "BaseApplication.h"

// Those global objects and function are necessary as we can't register a class member as callback for glutReshapeFunc() or glutDisplayFunc() otherwise we get fel: argument av typen "void (BaseApplication::)()" matchar inte "void (*)()
BaseApplication* BaseApplicationObject = 0;
void BaseApplication_Render() {
	BaseApplicationObject->RenderBase();
}

void BaseApplication_Resize(int NewWidth, int NewHeight) {
	BaseApplicationObject->Resize(NewWidth, NewHeight);
}
