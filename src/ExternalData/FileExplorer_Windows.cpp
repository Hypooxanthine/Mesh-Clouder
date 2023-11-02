#if defined(_WIN32)

#include "ExternalData/FileExplorer.h"

#include <Windows.h>
#include <commdlg.h>

std::string FileExplorer::GetFileFromFileExplorer()
{
    OPENFILENAME ofn;
    char szFile[MAX_PATH] = ""; // Stores selected file path

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = nullptr;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
        return std::string(szFile);

    return std::string(); // Empty string if user cancelled file selection
}

#endif