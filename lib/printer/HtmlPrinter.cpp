#include "HtmlPrinter.h"
#include "tool/Https.h"
#include "util/Helper.h"
#include <wx/textfile.h>

HtmlPrinter::HtmlPrinter(wxString strRootPage):m_strRootPage(strRootPage)
{

}

HtmlPrinter::~HtmlPrinter()
{
    //dtor
}

wxString HtmlPrinter::GetRootPage()
{
    return m_strRootPage;
}

void HtmlPrinter::SetRootPage(wxString strRootPage)
{
    m_strRootPage = strRootPage;
}

bool HtmlPrinter::FetchAllLinks()
{
    wxString strResponse;
    Https(m_strRootPage,strResponse,wxFONTENCODING_UTF8);
    wxString strPattern = wxT("<aside.*?widget_categories\">.*?</aside>");
    GetRegexMatches(strPattern,strResponse,2,0,m_vecLinks);
    return false;
}

void HtmlPrinter::DumpAllLinks()
{
    wxTextFile file(EXE_DIR+"print.log");
    if(!file.Open()){
        file.Create();
    }
    std::map<wxString,wxString>::const_iterator it;
    for(it=m_vecLinks.begin();it!=m_vecLinks.end();++it){
        file.AddLine(it->first+" , "+it->second);
    }
    file.Write();
    file.Close();
}
