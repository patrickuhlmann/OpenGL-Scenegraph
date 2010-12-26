#include "SkeletonApp.h"

/**
 * \brief Just redirect to SimpleApplication Constructor and create a window called Skeleton with a width of 800 and height of 600 pixels
 */
SkeletonApp::SkeletonApp() : SimpleApplication("Skeleton", 800, 600) {

}

int main(int argc, char *argv[]) {
	SkeletonApp App;
	App.Start();
}
