#include "include/tool/MarkDown.h"

MarkDown::MarkDown(wxString strSrcFile,wxString strDestFile):m_strSrcFile(strSrcFile)
                    ,m_strDestFile(strDestFile)
{
    //ctor
}

MarkDown::~MarkDown()
{
    //dtor
}

bool MarkDown::CsvToMd()
{
    if(m_strSrcFile == wxT("")
       || m_strDestFile == wxT("")){
            return false;
    }
    return true;
}
