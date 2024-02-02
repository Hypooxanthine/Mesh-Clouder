#if defined(_WIN32)

#include "ExternalData/FileExplorer.h"

#include <Windows.h>
#include <commdlg.h>
#include <filesystem>

static std::string ToUpperCase(const std::string& str)
{
    std::string upper;
    upper.reserve(str.size());

    for(const char& c : str)
    {
        if(c >= 'a' && c <= 'z')
            upper += (c - 'a' + 'A');
        else
            upper += c;
    }

    return upper;
}

static std::string ToLowerCase(const std::string& str)
{
    std::string lower;
    lower.reserve(str.size());

    for(const char& c : str)
    {
        if(c >= 'A' && c <= 'Z')
            lower += (c - 'A' + 'a');
        else
            lower += c;
    }

    return lower;
}

static std::string FormatExtensions(const std::vector<std::string>& exts)
{
    std::string str = "Fichiers";

    for(size_t i = 0; i < exts.size(); i++)
    {
        std::string upper = ToUpperCase(exts[i]);

        if(i == 0) str += ' ';
        else if(i == (exts.size() - 1)) str += " et ";
        else str += ", ";

        str += upper;
    }

    str += '\0';

    for(size_t i = 0; i < exts.size(); i++)
    {
        std::string lower = ToLowerCase(exts[i]);

        str += ("*." + lower);

        if(!(i == exts.size() - 1)) str += ';';
    }

    str += "\0Tous les fichiers (*.*)\0*.*\0";

    return str;
}

std::string FileExplorer::GetFileFromFileExplorer(const std::vector<std::string>& ext)
{
    auto backupPath = std::filesystem::current_path();
    std::string formattedExtensions = FormatExtensions(ext);

    OPENFILENAME ofn;
    char szFile[MAX_PATH] = ""; // Stores selected file path

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = formattedExtensions.c_str();
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = nullptr;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    auto success = GetOpenFileNameA(&ofn);
    std::filesystem::current_path(backupPath);
    
    if (success)
        return std::string(szFile);

    return std::string(); // Empty string if user cancelled file selection
}

std::string FileExplorer::SaveFileFromFileExplorer()
{
    auto backupPath = std::filesystem::current_path();

    OPENFILENAME ofn;
    char szFile[MAX_PATH] = ""; // Stores selected file path

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Tous les fichiers\0*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = nullptr;
    ofn.Flags = OFN_PATHMUSTEXIST;

    auto success = GetOpenFileNameA(&ofn);
    std::filesystem::current_path(backupPath);
    
    if (success)
        return std::string(szFile);

    return std::string(); // Empty string if user cancelled file selection
}

#endif