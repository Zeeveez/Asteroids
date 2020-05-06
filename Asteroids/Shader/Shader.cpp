#include "Shader.h"

namespace Asteroids {
	Shader::Shader(const std::string& filepath) {
		program = glCreateProgram();
		shaders[0] = CreateShader(LoadShader(filepath + ".vert"), GL_VERTEX_SHADER);
		shaders[1] = CreateShader(LoadShader(filepath + ".frag"), GL_FRAGMENT_SHADER);
		
		for (int i = 0; i < NUM_SHADERS; i++) {
			if (shaders[i]) {
				glAttachShader(program, shaders[i]);
			}
		}

		glLinkProgram(program);
		CheckShaderError(program, GL_LINK_STATUS, true, "Error: Shader Linking Failed: ");
		glValidateProgram(program);
		CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader Validation Failed: ");
	}

	Shader::~Shader() {
		for (int i = 0; i < NUM_SHADERS; i++) {
			glDetachShader(program, shaders[i]);
			glDeleteShader(shaders[i]);
		}
		glDeleteProgram(program);
	}

	void Shader::Bind() {
		glUseProgram(program);
	}

	static GLuint CreateShader(const std::string& text, GLenum type) {
		if (text.length() == 0) {
			return 0;
		}
		GLuint shader = glCreateShader(type);

		if (shader == 0) {
			std::cout << "Error: Shader Creation Failed" << std::endl;
		}

		const GLchar* shaderSourceStrings[1];
		GLint shaderSourceStringLengths[1];

		shaderSourceStrings[0] = text.c_str();
		shaderSourceStringLengths[0] = (GLint)text.length();

		glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
		glCompileShader(shader);
		CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation Failed: ");

		return shader;
	}

	static std::string LoadShader(const std::string& filepath) {
		std::ifstream file;
		file.open((filepath).c_str());

		std::string output;
		std::string line;

		if (file.is_open()) {
			while (file.good()) {
				getline(file, line);
				output.append(line + "\n");
			}
		} else {
			std::cout << "Unable to load shader: " << filepath << std::endl;
		}

		return output;
	}

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram) {
			glGetProgramiv(shader, flag, &success);
		} else {
			glGetShaderiv(shader, flag, &success);
		}

		if (success == GL_FALSE) {
			if (isProgram) {
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			} else {
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);
			}

			std::cout << errorMessage << ": '" << error << "'" << std::endl;
		}
	}
}