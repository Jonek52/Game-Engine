#pragma once

#include "GL/glew.h"
#include "../maths/maths.h"
#include "../utils/fileutils.h"

namespace sparky {
	namespace graphics {

		class Shader {
		public:
			Shader (const char * vertPath, const char * fragPath);
			~Shader ();

			void Enable () const;
			void Disable () const;

			void SetUniform1f (const GLchar * name, float value);
			void SetUniform1i (const GLchar * name, int value);
			void SetUniform2f (const GLchar * name, maths::vec2 vector);
			void SetUniform3f (const GLchar * name, maths::vec3 vector);
			void SetUniform4f (const GLchar * name, maths::vec4 vector);
			void SetUniformMat4 (const GLchar * name, const maths::mat4 & matrix);

		private:

			GLuint m_shaderID;
			const char * m_vertPath;
			const char * m_fragPath;

			GLuint Load ();
			GLint GetUniformLocation (const GLchar * name);
		};

	}
}