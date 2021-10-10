#ifndef HTMLPRINTER_H
#define HTMLPRINTER_H
#include <map>
#include <wx/string.h>

class HtmlPrinter
{
    public:
        HtmlPrinter(wxString strRootPage);
        virtual ~HtmlPrinter();
        wxString GetRootPage();
        void SetRootPage(wxString strRootPage);
        bool FetchAllLinks();
        void DumpAllLinks();
    protected:
        wxString m_strRootPage;
        bool m_bPause;
        std::map<wxString,wxString> m_vecLinks;
};

#endif // HTMLPRINTER_H
