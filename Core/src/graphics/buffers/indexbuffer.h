#pragma once

#include "GL/glew.h"

namespace sparky {
	namespace graphics {

		class IndexBuffer {

		public:
			IndexBuffer (GLushort * data, GLsizei count);

			void Bind () const;
			void Unbind () const;

			GLuint getCount () const { return m_Count; }

		private:
			GLuint m_BufferID;
			GLuint m_Count;
		};
	}
}