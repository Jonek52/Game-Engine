#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

int main () {

	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window ("Sparky!", 800, 600);
	glClearColor (0.2f, 0.3f, 0.8f, 1.0f);

	std::string main_file = read_file ("main.cpp");
	std::cout << main_file << std::endl;
	system ("PAUSE");

	GLuint vao;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);


 	while (!window.Closed ()) {

		window.Clear ();

#if 1
		glBegin (GL_QUADS);
		glVertex2f (-0.5f, -0.5f);
		glVertex2f (-0.5f, 0.5f);
		glVertex2f (0.5f, 0.5f);
		glVertex2f (0.5f, -0.5f);
		glEnd ();
#else
		glDrawArrays (GL_ARRAY_BUFFER, 0, 6);
#endif
		window.Update ();
	}

	return 0;
}