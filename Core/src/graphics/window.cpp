#include "window.h"

namespace sparky {
	namespace graphics {

		void window_resize (GLFWwindow * windows, int width, int height);

		void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback (GLFWwindow* window, int button, int action, int mods);
		void cursor_position_callback (GLFWwindow* window, double xpos, double ypos);

			Window::Window (const char * name, int width, int height) {

			m_title = name;
			m_height = height;
			m_width = width;

			if (!Init ()) {
				glfwTerminate ();
			}

			for (int i = 0; i < MAX_KEYS; ++i) {
				m_key[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; ++i) {
				m_buttons[i] = false;
			}
		}

		Window::~Window () {
			glfwTerminate ();
		}

		void Window::Update () {

			GLenum error = glGetError ();

			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL error: " << error << std::endl;
			}

			glfwPollEvents ();
			glfwSwapBuffers (m_window);
		}

		bool Window::Init () {

			if (!glfwInit ()) {
				std::cout << "Failed to initalize GLFW!" << std::endl;
				return false;
			}

			m_window = glfwCreateWindow (m_width, m_height, m_title, NULL, NULL);

			if (!m_window) {
				std::cout << "Failed to create GLFW windows!" << std::endl;
				return false;
			}

			glfwMakeContextCurrent (m_window);
			glfwSetWindowUserPointer (m_window, this);
			glfwSetWindowSizeCallback (m_window, window_resize);
			glfwSetKeyCallback (m_window, key_callback);
			glfwSetMouseButtonCallback (m_window, mouse_button_callback);
			glfwSetCursorPosCallback (m_window, cursor_position_callback);

			if (glewInit () != GLEW_OK) {
				std::cout << "Failed to initialize GLEW!" << std::endl;
			}

			return true;
		}

		bool Window::Closed () const {

			return glfwWindowShouldClose (m_window);
		}

		bool Window::isKeyPressed (unsigned int keyCode) const {

			if (keyCode >= MAX_KEYS) {
				return false;
			}

			return m_key[keyCode];
		}

		bool Window::isMouseButtonPressed (unsigned int buttonCode) const {

			if (buttonCode > MAX_BUTTONS) {
				return false;
			}

			return m_buttons[buttonCode];
		}

		void Window::getMousePosition (double & x, double & y) const {
			x = mx;
			y = my;
		}

		void Window::Clear () const {
			glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void window_resize (GLFWwindow * windows, int width, int height) {
			glViewport (0, 0, width, height);
		}

		void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {

			Window* win = (Window *) glfwGetWindowUserPointer (window);

			win->m_key[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback (GLFWwindow* window, int button, int action, int mods) {

			Window* win = (Window*) glfwGetWindowUserPointer (window);
			win->m_buttons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback (GLFWwindow* window, double xpos, double ypos) {

			Window* win = (Window*) glfwGetWindowUserPointer (window);
			win->mx = xpos;
			win->my = ypos;

		}
	}
}