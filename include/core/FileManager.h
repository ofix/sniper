#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <wx/vector.h>

#include "core/Stock.h"
/***********************************************************
 *@class FileManager
 *@todo manage misc. files,include config file and data file
  the config file path is fixed
  parse the config file, we can get the share history data
  store root directory.
 ***********************************************************/
class FileManager
{
    public:
        FileManager();
        virtual ~FileManager();
        wxString GetConfigFilePath() const;
        wxString GetShareDataPath(wxString strShareCode) const;
        wxVector<ShareBrief> GetShareList();
    protected:
        wxString m_configPath;
        wxString m_dataRootDir;// to store the stock history data
        wxVector<ShareBrief> m_shares; // all shares
};

#endif // FILEMANAGER_H
