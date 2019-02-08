#include "src/graphics/window.h"
#include "src/maths/maths.h"

int main () {

	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window ("Sparky!", 800, 600);
	glClearColor (0.2f, 0.3f, 0.8f, 1.0f);


	GLuint vao;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);

	vec4 vector (0.2f, 0.3f, 0.8f, 1.0f);
	vec4 vector1 (0.5f, 0.2f, 0.1f, 1.0f);
	vec4 result = vector + vector1;

	while (!window.Closed ()) {

		window.Clear ();
		std::cout << result << std::endl;

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