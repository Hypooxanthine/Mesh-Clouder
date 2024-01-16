#pragma once

#include <exception>
#include <string>

class FileNotSaved : public std::exception
{
public:
    FileNotSaved() = default;
    FileNotSaved(const std::string& what)
        : m_What(what)
    {}

    const char* what() const noexcept override
    {
        if(m_What.empty())
            return "Couldn't save file.";
        else
            return m_What.c_str();
    }

private:
    std::string m_What;
};