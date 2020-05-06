#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>

namespace Asteroids {
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static std::string LoadShader(const std::string& filepath);
	static GLuint CreateShader(const std::string& text, GLenum type);

	class Shader {
	public:
		Shader() = default;
		Shader(const std::string& filepath);
		~Shader();
		GLuint program;

		void Bind();

	private:
		static const unsigned int NUM_SHADERS = 2;
		GLuint shaders[NUM_SHADERS];
	};
}

#endif