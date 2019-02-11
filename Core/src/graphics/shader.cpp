#include "shader.h"
#include <vector>
#include <iostream>

namespace sparky {
	namespace graphics {

		Shader::Shader (const char * vertPath, const char * fragPath)
			: m_vertPath (vertPath), m_fragPath (fragPath) {

			m_shaderID = Load ();
		}

		Shader::~Shader () {
			glDeleteProgram (m_shaderID);
		}

		GLuint Shader::Load () {

			GLuint program = glCreateProgram ();

			GLuint vertexShaderID = glCreateShader (GL_VERTEX_SHADER);

			std::string vertSourceString = read_file (m_vertPath).c_str ();
			const char * vertSource = vertSourceString.c_str ();

			glShaderSource (vertexShaderID, 1, &vertSource, NULL);
			glCompileShader (vertexShaderID);

			GLint result;
			glGetShaderiv (vertexShaderID, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {
				GLint lenght;
				glGetShaderiv (vertexShaderID, GL_INFO_LOG_LENGTH, &lenght);

				std::vector<char> error (lenght);
				glGetShaderInfoLog (vertexShaderID, lenght, &lenght, &error[0]);

				std::cout << "Failed to compile vertex shader: " << &error[0] << std::endl;
				glDeleteShader (vertexShaderID);
			}

			GLuint fragShaderID = glCreateShader (GL_FRAGMENT_SHADER);
			std::string fragSourceString = read_file (m_fragPath);
			const char * fragSource = fragSourceString.c_str ();

			glShaderSource (fragShaderID, 1, &fragSource, NULL);
			glCompileShader (fragShaderID);

			glGetShaderiv (fragShaderID, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {

				GLint lenght;
				glGetShaderiv (fragShaderID, GL_INFO_LOG_LENGTH, &lenght);
				std::vector <char> error (lenght);

				glGetShaderInfoLog (fragShaderID, lenght, &lenght, &error[0]);

				std::cout << "Failed to compile fragment shader: " << &error[0] << std::endl;
				glDeleteShader (fragShaderID);

			}

			glAttachShader (program, vertexShaderID);
			glAttachShader (program, fragShaderID);

			glLinkProgram (program);
			glValidateProgram (program);

			glDeleteShader (vertexShaderID);
			glDeleteShader (fragShaderID);

			return program;

		}

		void Shader::Enable () const {
			glUseProgram (m_shaderID);
		}

		void Shader::Disable () const {
			glUseProgram (0);
		}

		GLint Shader::GetUniformLocation (const GLchar * name) {
			return glGetUniformLocation (m_shaderID, name);
		}

		void Shader::SetUniform1f (const GLchar * name, float value) {

			glUniform1f (GetUniformLocation (name), value);
		}

		void Shader::SetUniform1i (const GLchar * name, int value) {

			glUniform1i (GetUniformLocation (name), value);
		}

		void Shader::SetUniform2f (const GLchar * name, maths::vec2 vector) {

			glUniform2f (GetUniformLocation (name), vector.x, vector.y);
		}

		void Shader::SetUniform3f (const GLchar * name, maths::vec3 vector) {

			glUniform3f (GetUniformLocation (name), vector.x, vector.y, vector.z);
		}

		void Shader::SetUniform4f (const GLchar * name, maths::vec4 vector) {

			glUniform4f (GetUniformLocation (name), vector.x, vector.y, vector.z, vector.w);

		}

		void Shader::SetUniformMat4 (const GLchar * name, const maths::mat4 & matrix) {

			glUniformMatrix4fv (GetUniformLocation (name), 1, GL_FALSE, matrix.elements);
		}

	}
}