#pragma once

#include <iostream>
#include <unordered_map>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	// Caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string &filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	
	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3);

private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};