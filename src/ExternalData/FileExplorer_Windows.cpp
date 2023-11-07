#if defined(_WIN32)

#include "ExternalData/FileExplorer.h"

#include <Windows.h>
#include <commdlg.h>
#include <filesystem>

std::string FileExplorer::GetFileFromFileExplorer()
{
    auto backupPath = std::filesystem::current_path();

    OPENFILENAME ofn;
    char szFile[MAX_PATH] = ""; // Stores selected file path

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Fichiers OBJ et PLY (*.obj;*.ply)\0*.obj;*.ply\0Tous les fichiers (*.*)\0*.*\0";
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

#endif