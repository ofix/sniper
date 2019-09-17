#include "BaiduPolyphoneSpider.h"
#include <wx/textfile.h>
#include <wx/strconv.h>
#include <wx/file.h>
#include <map>

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
    #ifdef xx
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
    #endif
    std::map<wxString,wxString> zhMap;
    // 正则匹配
    wxFile bdFile;
    if(!bdFile.Open(getExecDir()+"baidu.html")){
        return false;
    }
    wxString response;
    bdFile.ReadAll(&response);
    wxString pattern("class=\"op_exactqa_item[^\"]*\">[^<]*<p><a\\s+href='([^']*)'[^>]*>(.?)</a>");
    wxRegEx re(pattern,wxRE_ADVANCED); // must use wxRE_ADVANCED, or \\d+ would not work correctly.
    wxString processText = response;
    while(re.Matches(processText)){
        size_t start, len;
        re.GetMatch(&start, &len, 0);
        wxString strUrlZh = re.GetMatch(processText,1); // url
        wxString strZh = re.GetMatch(processText,2);
        std::cout<<"strUrlZh: "<<strUrlZh<<std::endl;
        std::cout<<"strZh: "<<strZh<<std::endl;
        zhMap[strZh] = strUrlZh;
        processText = processText.Mid(start+len);
        std::cout<<"processText: "<<processText.length()<<std::endl;
    }
    return true;
}
