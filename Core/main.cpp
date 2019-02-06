#include "src/graphics/window.h"

int main () {

	using namespace sparky;
	using namespace graphics;

	Window window ("Sparky!", 800, 600);
	glClearColor (0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString (GL_VERSION) << std::endl;
	while (!window.Closed ()) {

		window.Clear ();
		glBegin (GL_TRIANGLES);
		glVertex2f (-0.5f, -0.5f);
		glVertex2f (0.0f, 0.5f);
		glVertex2f (0.5f, -0.5f);
		glEnd ();
		window.Update ();
	}

	return 0;
}