#include "Shader.h"
#include <fstream>
#include <string>
#include <cassert>
#include "Renderer.h"

void Shader::Bind() const {
	glUseProgram(RendererID);
}

void Shader::Unbind() {
	glUseProgram(0);
}

std::string Shader::LoadSource(const std::string& filePath) {
	try {
		std::ifstream file(filePath);

		std::string source;
		std::string line;
		while (std::getline(file, line)) {
			source += (line + '\n');
		}

		return source;

	}
	catch (int e) {
		std::cout << "Exception caught, error code:- " << e << '\n';
		assert(false);

		return "-1";
	}
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}

VertexShader::VertexShader(const std::string& filePath) {
	std::string source = LoadSource(filePath);

	if (RendererID == -1) {
		RendererID = glCreateProgram();
	}

	unsigned int shader = CompileShader(GL_VERTEX_SHADER, source);
	glAttachShader(RendererID, shader);
	glLinkProgram(RendererID);
	glValidateProgram(RendererID);

	glDeleteShader(shader);
}

void VertexShader::Bind() const
{
	Shader::Bind();
}

FragmentShader::FragmentShader(const std::string& filePath) {
	std::string source = LoadSource(filePath);

	if (RendererID == -1) {
		RendererID = glCreateProgram();
	}

	unsigned int shader = CompileShader(GL_FRAGMENT_SHADER, source);
	glAttachShader(RendererID, shader);
	glLinkProgram(RendererID);
	glValidateProgram(RendererID);

	glDeleteShader(shader);
}

void FragmentShader::Bind()
{
	Shader::Bind();
}

Shader::~Shader() {
	glDeleteProgram(RendererID);
}