#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
namespace sparky {
	namespace graphics {

		class Window {

		public:
			Window (const char * name, int width, int height);
			~Window ();
			void Update ();
			bool Closed () const;
			void Clear () const;


			int getWidth () const { return m_width; }
			int getHeight () const { return m_height; }
		private:
			const char * m_title;
			int m_width;
			int m_height;
			GLFWwindow* m_window;
			bool m_closed;

			bool Init ();
		};
	}
}