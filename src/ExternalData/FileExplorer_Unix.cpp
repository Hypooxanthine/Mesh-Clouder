#if defined(__unix__)

#include "ExternalData/FileExplorer.h"

#include "osdialog/osdialog.h"

std::string FileExplorer::GetFileFromFileExplorer()
{
    char* filename = osdialog_file(OSDIALOG_OPEN, NULL, NULL, NULL);
    if (filename == nullptr)
        return "";
    
    std::string out = filename;
    free(filename);
    return out;
}

#endif