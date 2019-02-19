#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"

int main () {

	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window ("Sparky!", 960, 540);
	//glClearColor (1.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic (0.0, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);


	Shader shader ("src/shaders/vertex.hlsl", "src/shaders/frag.hlsl");
	shader.Enable ();

	shader.SetUniformMat4 ("pr_matrix", ortho);
	shader.SetUniformMat4 ("ml_matrix", mat4::translation (vec3 (4.0f, 3.0f, 0.0f)));

	Renderable2D sprite (maths::vec3 (5, 5, 0), maths::vec2 (4, 4), maths::vec4 (1, 0, 1, 1), shader);
	Renderable2D sprite2 (maths::vec3 (7, 1, 0), maths::vec2 (2, 3), maths::vec4 (0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;

	shader.SetUniform2f ("light_pos", vec2 (4.0f, 1.5f));
	shader.SetUniform4f ("col", vec4 (0.2f, 0.3f, 0.8f, 1.0f));

	std::cout << "OpenGL " << glGetString (GL_VERSION) << std::endl;
	while (!window.Closed ()) {

		window.Clear ();
		double x, y;
		window.getMousePosition (x, y);
		shader.SetUniform2f ("light_pos", vec2 ((float) (x * 16.0f / 960.0f), (float) (9.0f - y * 9.0f / 540.0f)));
		renderer.Submit (&sprite);
		renderer.Submit (&sprite2);
		renderer.Flush ();

		window.Update ();
	}

	return 0;
}