#include "window.h"

namespace sparky {
	namespace graphics {

		void windowResize (GLFWwindow * windows, int width, int height);
		Window::Window (const char * name, int width, int height) {

			m_title = name;
			m_height = height;
			m_width = width;

			if (!Init ()) {
				glfwTerminate ();
			}
		}

		Window::~Window () {
			glfwTerminate ();
		}

		void Window::Update () {
			glfwPollEvents ();
			//glfwGetFramebufferSize (m_window, &m_width, &m_height);
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
			glfwSetWindowSizeCallback (m_window, windowResize);
			return true;
		}

		bool Window::Closed () const {

			return glfwWindowShouldClose (m_window);
		}

		void Window::Clear () const {
			glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void windowResize (GLFWwindow * windows, int width, int height) {
			glViewport (0, 0, width, height);
		}
	}
}