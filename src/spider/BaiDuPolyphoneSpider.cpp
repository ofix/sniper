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
    #ifdef ##
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
    wxFile bdFile(getExecDir()+"baidu.html");
    if(!bdFile.Open()){
        return false;
    }
    wxString response;
    bdFile.ReadAll(&response);
    wxString patternTotal("class=\"op_exactqa_item\s+.*\">.?<p><a\s+href='(.*)'>(.?)</a>.?</p>");
    wxRegEx re(patternTotal,wxRE_ADVANCED); // must use wxRE_ADVANCED, or \\d+ would not work correctly.
    wxString processText = response;
    while(re.Matches(processText)){
        size_t start, len;
        processText.GetMatch(&start, &len, 0);
        wxString strUrlZh = re.GetMatch(processText,1); // url
        wxString strZh = re.GetMatch(processText,1);
        zhMap[strUrlZh] = strZh;
        processText = processText.Mid(start+len);
    }
    return true;
}
