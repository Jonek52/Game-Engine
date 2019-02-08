#pragma once

#include <iostream>
#include <GL/glew.h>  
#include <GLFW/glfw3.h>
namespace sparky {
	namespace graphics {


#define MAX_KEYS 1024
#define MAX_BUTTONS 32

		class Window {
		public:

			Window (const char * name, int width, int height);
			~Window ();

			void Update ();
			bool Closed () const;
			void Clear () const;
			int getWidth () const { return m_width; }
			int getHeight () const { return m_height; }

			bool isKeyPressed (unsigned int keyCode) const;
			bool isMouseButtonPressed (unsigned int buttonCode) const;
			void getMousePosition (double & x, double & y) const;
		private:

			const char * m_title;
			int m_width;
			int m_height;
			GLFWwindow* m_window;
			bool m_closed;

			bool m_key[MAX_KEYS];
			bool m_buttons[MAX_BUTTONS];
			double mx, my;

			bool Init ();
			friend static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback (GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback (GLFWwindow* window, double xpos, double ypos);
		};
	}
}