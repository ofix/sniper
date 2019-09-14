#ifndef MARKDOWN_H
#define MARKDOWN_H
#include <wx/string.h>

class MarkDown
{
    public:
        MarkDown(wxString strSrcFile=wxT(""),wxString strDestFile=wxT(""));
        virtual ~MarkDown();
        bool CsvToMd();
    protected:
        wxString m_strSrcFile;
        wxString m_strDestFile;
};

#endif // MARKDOWN_H
