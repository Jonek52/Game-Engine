#pragma once

#include <GL/glew.h>
#include <vector>
#include "buffer.h"

namespace sparky {
	namespace graphics {

		class VertexArray {

		public:
			VertexArray ();
			~VertexArray ();
			
			void AddBuffer (Buffer * buffer, GLuint index);
			void Bind () const;
			void Unbind () const;
		private:
			GLuint m_ArrayID;
			std::vector <Buffer *> m_Buffers;
		};
	}
}