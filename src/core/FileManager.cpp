#include "core/FileManager.h"

FileManager::FileManager()
{
    //ctor
}

FileManager::~FileManager()
{
    //dtor
}

wxString FileManager::GetConfigFilePath() const
{
    return _T("");
}

wxString FileManager::GetShareDataPath(wxString strShareCode) const
{
    return _T("");
}

wxVector<ShareBrief> FileManager::GetShareList()
{
    wxVector<ShareBrief> vec;
    return vec;
}
