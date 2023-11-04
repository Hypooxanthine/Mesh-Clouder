#include "Rendering/Shader.h"

#include <iostream>
#include <fstream>

#include "Rendering/GLCall.h"

#if defined(WIN32)
#define alloca(x) _malloca(x)
#endif

Shader::Shader()
{
}

Shader::~Shader()
{
    unload();
}

bool Shader::loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    unload();

    std::ifstream ifs;
    std::string line;

    ifs.open(vertexShaderPath);
        if (!ifs.is_open())
        {
            std::cout << "Couldn't load \"" << vertexShaderPath << "\"." << std::endl;
            return false;
        }

        std::string vertexShader;
        while (!ifs.eof())
        {
            std::getline(ifs, line);
            vertexShader += line;
            vertexShader += "\n";
        }
    ifs.close();

    ifs.open(fragmentShaderPath);
        if (!ifs.is_open())
        {
            std::cout << "Couldn't load \"" << fragmentShaderPath << "\"." << std::endl;
            return false;
        }

        std::string fragmentShader;
        while (!ifs.eof())
        {
            std::getline(ifs, line);
            fragmentShader += line;
            fragmentShader += "\n";
        }
    ifs.close();

    m_RendererID = createShader(vertexShader, fragmentShader);
    if (m_RendererID == 0) return false;
    
    return true;
}

void Shader::unload()
{
    if (m_RendererID != 0)
    {
        GLCall(glDeleteProgram(m_RendererID));
        m_RendererID = 0;
    }
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string& name, int value) const
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string& name, float value) const
{
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& mat) const
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compiler " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

int Shader::getUniformLocation(const std::string& name) const
{
    if (m_UniformLocationCache.contains(name))
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Uniform " << name << " does not exist." << std::endl;
    
    m_UniformLocationCache[name] = location;

    return location;
}
