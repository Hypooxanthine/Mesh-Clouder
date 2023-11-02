#pragma once

#include <exception>
#include <string>

class FileNotLoaded : public std::exception
{
public:
    FileNotLoaded() = default;

    const char* what() const noexcept override
    {
        return ("Couldn't load file.");
    }
};