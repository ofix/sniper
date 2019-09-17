#include "BaiduPolyphoneSpider.h"
#include <wx/textfile.h>
#include <wx/strconv.h>
#include <wx/file.h>
#include <map>
#include "lib/wxJSON/jsonval.h"
#include "lib/wxJSON/jsonreader.h"

BaiduPolyphoneSpider::BaiduPolyphoneSpider(wxString strUrl):Spider(strUrl)
            ,m_totalPages(0)
            ,m_curPage(0)
{
    //ctor
}

BaiduPolyphoneSpider::~BaiduPolyphoneSpider()
{
    //dtor
}

int BaiduPolyphoneSpider::RemoveDirtyWords(wxString& strResponse)
{
     try{
         wxRegEx reg(_T("(jQuery\\d+_\\d+\\()([^)]*)\\)"),wxRE_ADVANCED);
         int nReplace =  reg.ReplaceAll(&strResponse,"\\2");
         return nReplace;
    }catch(std::exception& e){
        std::cout<<e.what()<<std::endl;
        return 0;
    }
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

    wxString response;
    m_url=wxT("http://sp0.baidu.com/8aQDcjqpAAV3otqbppnN2DJv/api.php");
    kvMap parameters;
    parameters["resource_id"]="28204";
    parameters["from_mid"]="1";
    parameters["ie"]="utf-8";
    parameters["oe"]="utf-8";
    parameters["query"]=wxT("多音字");
    parameters["sort_key"]="";
    parameters["sort_type"]="1";
    parameters["stat0"]="";
    parameters["stat1"]="";
    parameters["stat2"]="";
    parameters["stat3"]="";
    parameters["pn"]="256";
    parameters["rn"]="64";
    parameters["cb"]="jQuery1102029999933179645644_";
    wxDateTime now = wxDateTime::Now();
    parameters["_"]=wxString::Format("%lld",now.GetValue());
    parameters["cb"] = parameters["cb"]+parameters["_"];
    wxString  para = buildUrlPara(parameters);
    m_url = m_url + para;
    http(m_url,response,wxFONTENCODING_UTF8);
    wxJSONReader reader;
    wxJSONValue  jsonArr;
    RemoveDirtyWords(response);
    //std::cout<<response<<std::endl;

    // resStock has already been UNICODE
    int numErrors = 0;
    numErrors = reader.Parse(response, &jsonArr);
    if(numErrors == 0){
        wxString num = jsonArr["data"][0]["listNum"].AsString();
        wxJSONValue data = jsonArr["data"][0]["result"];
        std::cout<<"num: "<<num<<std::endl;
        for(int i=0; i<data.Size();i++){
            std::cout<<"ename: "<<data[i]["ename"].AsString()<<std::endl;
            std::cout<<"jumplink: "<<data[i]["jumplink"].AsString()<<std::endl;
        }

    }
//    if ( numErrors > 0 )  {
//       wxArrayString err = reader.GetErrors();
//       for(size_t i=0; i<err.GetCount(); i++){
//        std::wcout<<"ERROR :  "<<err.Item(i)<<std::endl;
//       }
//       return false;
//    }
    //std::cout<<jsonArr[0][""].AsString()<<std::endl;
    #ifdef M1
    std::map<wxString,wxString> zhMap;
    // 正则匹配
    wxFile bdFile;
    if(!bdFile.Open(getExecDir()+"baidu.html")){
        return false;
    }
    wxString response;
    bdFile.ReadAll(&response);
    //获取页面总数
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
    #endif
    return true;
}
