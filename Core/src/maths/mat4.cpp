#include "mat4.h"
#include "maths.h"
namespace sparky {
	namespace maths {

		mat4::mat4 () {

			for (int i = 0; i < 4 * 4; ++i)
				elements[i] = 0.0f;

		}

		mat4::mat4 (float diagonal) {

			for (int i = 0; i < 4 * 4; ++i)
				elements[i] = 0.0f;

			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		mat4 mat4::identity () {
			return mat4 (1.0f);
		}

		mat4 mat4::multiply (const mat4 & other) {

			mat4 result;
			float sum = 0.0f;
			for (int y = 0; y < 4; ++y) {
				for (int x = 0; x < 4; ++x) {
					sum = 0.0;
					for (int k = 0; k < 4; ++k) {
						sum += elements[k * 4 + x] * other.elements[y * 4 + k];
					}
					result.elements[y * 4 + x] = sum;

				}
			}

			return result;
		}

		mat4 operator*(mat4 left, const mat4& right) {

			return (left.multiply (right));
		}

		mat4 mat4::operator*=(const mat4& other) {
			return multiply (other);
		}

		mat4 mat4::orthographic (float left, float right, float bottom, float top, float near, float far) {

			mat4 result (1.0f);

			result.elements[0 * 4 + 0] = 2 / (right - left);
			result.elements[1 * 4 + 1] = 2 / (top - bottom);
			result.elements[2 * 4 + 2] = -2 / (far - near);
			result.elements[3 * 4 + 0] = (right + left) / (right - left);
			result.elements[3 * 4 + 1] = (top + bottom) / (top - bottom);
			result.elements[3 * 4 + 2] = (far + near) / (far - near);

			return result;
		}

		mat4 mat4::perspective (float fov, float aspectratio, float near, float far) {

			mat4 result (1.0f);

			float q = 1 / (tan (toRadians (fov / 2)));
			float a = q / aspectratio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 * 4 + 0] = a;
			result.elements[1 * 4 + 1] = q;
			result.elements[2 * 4 + 2] = b;
			result.elements[2 * 4 + 3] = -1.0f;
			result.elements[3 * 4 + 2] = c;

			return result;
		}

		mat4 mat4::translation (const vec3& translation) {

			mat4 result (1.0f);

			result.elements[3 * 4 + 0] = translation.x;
			result.elements[3 * 4 + 1] = translation.y;
			result.elements[3 * 4 + 2] = translation.z;

			return result;
		}
		
		mat4 mat4::rotation (float angle, const vec3& axis) {

			mat4 result (1.0f);

			float radians = toRadians (angle);

			float c = cos (radians);
			float s = sin (radians);
			float omc = 1 - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 * 4 + 0] = c + x * x * omc;
			result.elements[0 * 4 + 1] = y * x * omc + z * s;
			result.elements[0 * 4 + 2] = z * x * omc - y * s;

			result.elements[1 * 4 + 0] = x * y * omc - z * s;
			result.elements[1 * 4 + 1] = c + y * y * omc; 
			result.elements[1 * 4 + 2] = z * y * omc + x * s;

			result.elements[2 * 4 + 0] = x * z * omc + y * s;
			result.elements[2 * 4 + 1] = y * z * omc - x * s;
			result.elements[2 * 4 + 2] = c + z * z * omc;

			return result;
		}
		
		mat4 mat4::scale (const vec3& scale) {

			mat4 result (1.0f);

			result.elements[0 * 4 + 0] = scale.x;
			result.elements[1 * 4 + 1] = scale.y;
			result.elements[2 * 4 + 2] = scale.z;

			return result;
		}

		std::ostream & operator<<(std::ostream & os, const mat4 & matrix) {

			std::cout << "Matrix" << std::endl;
			for (int y = 0; y < 4; ++y) {
				for (int x = 0; x < 4; ++x) {
					std::cout << matrix.elements[x * 4 + y] << "\t";
				}

				std::cout << std::endl;
			}

			return os;
		}
	}
}