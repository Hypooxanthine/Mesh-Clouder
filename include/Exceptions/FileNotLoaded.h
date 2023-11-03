#pragma once

#include <exception>
#include <string>

class FileNotLoaded : public std::exception
{
public:
    FileNotLoaded() = default;
    FileNotLoaded(const std::string& what)
        : m_What(what)
    {}

    const char* what() const noexcept override
    {
        if(m_What.empty())
            return "Couldn't load file.";
        else
            return m_What.c_str();
    }

private:
    std::string m_What;
};