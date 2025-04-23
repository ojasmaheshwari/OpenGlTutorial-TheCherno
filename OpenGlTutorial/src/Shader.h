#pragma once

#include <iostream>

static unsigned int RendererID = -1;

class Shader {
public:
	~Shader();

	void Bind() const;
	void Unbind();

	std::string LoadSource(const std::string &filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
};

class VertexShader : Shader {
public:
	VertexShader(const std::string& filePath);
	~VertexShader() = default;

	void Bind() const;
};

class FragmentShader : Shader {
public:
	FragmentShader(const std::string& filePath);
	~FragmentShader() = default;

	void Bind();
};