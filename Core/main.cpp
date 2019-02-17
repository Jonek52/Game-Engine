#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/vertexarray.h"
int main () {

	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window ("Sparky!", 960, 540);
	//glClearColor (1.0f, 1.0f, 1.0f, 1.0f);

#if 0


	GLuint vbo;

	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (0);
#else
	GLfloat vertices[] = {
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};
	GLushort indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLfloat colorsA[] = {
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1
	};


	GLfloat colorsB[] = {
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
	};

	VertexArray spriteOne, spriteTwo;
	IndexBuffer ibo (indices, 6);

	spriteOne.AddBuffer (new Buffer (vertices, 4 * 3, 3), 0);
	spriteOne.AddBuffer (new Buffer (colorsA, 4 * 4, 4), 1);

	spriteTwo.AddBuffer (new Buffer (vertices, 4 * 3, 3), 0);
	spriteTwo.AddBuffer (new Buffer (colorsB, 4 * 4, 4), 1);


#endif


	Shader shader ("src/shaders/vertex.hlsl", "src/shaders/frag.hlsl");
	shader.Enable ();

	mat4 ortho = mat4::orthographic (0.0, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	shader.SetUniformMat4 ("pr_matrix", ortho);
	shader.SetUniformMat4 ("ml_matrix", mat4::translation (vec3 (4.0f, 3.0f, 0.0f)));

	shader.SetUniform2f ("light_pos", vec2 (4.0f, 1.5f));
	shader.SetUniform4f ("col", vec4 (0.2f, 0.3f, 0.8f, 1.0f));

	std::cout << "OpenGL " << glGetString (GL_VERSION) << std::endl;
	while (!window.Closed ()) {

		window.Clear ();
		double x, y;
		window.getMousePosition (x, y);
		shader.SetUniform2f ("light_pos", vec2 ((float) (x * 16.0f / 960.0f), (float) (9.0f - y * 9.0f / 540.0f)));
#if 0
		glDrawArrays (GL_TRIANGLES, 0, 6);
#else
		spriteOne.Bind ();
		ibo.Bind ();
		shader.SetUniformMat4 ("ml_matrix", mat4::translation (vec3 (4, 3, 0)));
		glDrawElements (GL_TRIANGLES, ibo.getCount (), GL_UNSIGNED_SHORT, 0);
		ibo.Unbind ();
		spriteOne.Unbind ();

		spriteTwo.Bind ();
		ibo.Bind ();
		shader.SetUniformMat4 ("ml_matrix", mat4::translation (vec3 (0, 0, 0)));
		glDrawElements (GL_TRIANGLES, ibo.getCount (), GL_UNSIGNED_SHORT, 0);
		ibo.Unbind ();
		spriteTwo.Unbind ();
#endif

		window.Update ();
	}

	return 0;
}