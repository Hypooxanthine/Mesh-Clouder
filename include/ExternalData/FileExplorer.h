#pragma once

#include <string>
#include <vector>

/**
 * @brief Cross-platform (Windows and Unix) class allowing user to search for a file in its OS file explorer.
 * 
 */
class FileExplorer
{
public:
    /**
     * @brief Allows user to search for a file in his OS file explorer.
     * @param ext Supported file extensions.
     * 
     * @return std::string Selected file. Returns an empty string if cancelled.
     */
    static std::string GetFileFromFileExplorer(const std::vector<std::string>& ext);

    /**
     * @brief Allows user to type a file name in his OS file explorer in order of saving data.
     * 
     * @return std::string File path. Empty if cancelled.
     */
    static std::string SaveFileFromFileExplorer();
};