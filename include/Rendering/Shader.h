#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader
{
public:
	Shader();
	virtual ~Shader();
	
	bool loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void unload();

	void bind() const;
	void unbind() const;

	void setUniform1i(const std::string& name, int value) const;
	void setUniform1f(const std::string& name, float value) const;
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void setUniformMat4f(const std::string& name, const glm::mat4& mat) const;

	inline unsigned int getID() const { return m_RendererID; }

private:
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	int getUniformLocation(const std::string& name) const;
	
private:
	unsigned int m_RendererID = 0;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
};