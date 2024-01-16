#pragma once

#include <string>

/**
 * @brief Cross-platform (Windows and Unix) class allowing user to search for a file in its OS file explorer.
 * 
 */
class FileExplorer
{
public:
    /**
     * @brief Allows user to search for a file in his OS file explorer.
     * 
     * @return std::string Selected file. Returns an empty string if cancelled.
     */
    static std::string GetFileFromFileExplorer();

    /**
     * @brief Allows user to type a file name in his OS file explorer in order of saving data.
     * 
     * @return std::string File path. Empty if cancelled.
     */
    static std::string SaveFileFromFileExplorer();
};