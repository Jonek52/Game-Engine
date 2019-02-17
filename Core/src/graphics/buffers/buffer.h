#pragma once

#include "GL/glew.h"

namespace sparky {
	namespace graphics {

		class Buffer {

		public:
			Buffer (GLfloat * data, GLsizei count, GLuint componentCount);

			void Bind () const;
			void Unbind () const;

			GLuint getComponenetCount () const { return m_ComponentCount; }

		private:
			GLuint m_BufferID;
			GLuint m_ComponentCount;
		};
	}
}
