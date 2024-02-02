#pragma once

#include <exception>
#include <string>

class ParsingError : public std::exception
{
public:
    ParsingError() = default;
    ParsingError(const std::string& what)
        : m_What(what)
    {}

    const char* what() const noexcept override
    {
        if(m_What.empty())
            return "Couldn't parse file.";
        else
            return m_What.c_str();
    }

private:
    std::string m_What;
};