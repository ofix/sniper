#include "BaiduPolyphoneSpider.h"
#include <wx/textfile.h>
#include <wx/strconv.h>

BaiduPolyphoneSpider::BaiduPolyphoneSpider(wxString strUrl):Spider(strUrl)
{
    //ctor
}

BaiduPolyphoneSpider::~BaiduPolyphoneSpider()
{
    //dtor
}

bool BaiduPolyphoneSpider::Run()
{
    wxString response;
    http(m_url,response);
    wxString fileName = getExecDir()+"baidu.html";
    wxTextFile file(fileName);
    if(!file.Exists()){
        file.Create();
    }
    file.Open();
    file.AddLine(response);
    file.Write();
    file.Close();
    return true;
}
