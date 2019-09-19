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
            ,m_totalRecords(0)
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

bool BaiduPolyphoneSpider::QueryFromHtml()
{
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
        #ifdef DEBUG
            std::cout<<"strUrlZh: "<<strUrlZh<<std::endl;
            std::cout<<"strZh: "<<strZh<<std::endl;
        #endif // DEBUG
        zhMap[strZh] = strUrlZh;
        processText = processText.Mid(start+len);
        #ifdef DEBUG
            std::cout<<"processText: "<<processText.length()<<std::endl;
        #endif
    }
    return false;
}

wxString BaiduPolyphoneSpider::GetApiUrl(int nPageIndex, int nPageSize)
{
    wxString strPageIndex = wxString::Format("%d",nPageIndex*nPageSize);
    wxString strPageSize = wxString::Format("%d",nPageSize);
    wxString url=wxT("http://sp0.baidu.com/8aQDcjqpAAV3otqbppnN2DJv/api.php");
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
    parameters["pn"]=strPageIndex;
    parameters["rn"]=strPageSize;
    parameters["cb"]="jQuery1102029999933179645644_";
    wxDateTime now = wxDateTime::Now();
    parameters["_"]=wxString::Format("%lld",now.GetValue());
    parameters["cb"] = parameters["cb"]+parameters["_"];
    wxString  para = buildUrlPara(parameters);
    url = url + para;
    return url;
}

bool BaiduPolyphoneSpider::QueryFromApi()
{
    long nPages = 10000; // a value would impossible occurs in response
    long iPage = 0;
    do{
        wxString response;
        wxString strUrl = GetApiUrl(iPage,64);
        std::cout<<"@@ url: "<<strUrl<<std::endl;
        http(strUrl,response,wxFONTENCODING_UTF8);
        wxJSONReader reader;
        wxJSONValue  jsonArr;
        RemoveDirtyWords(response);

        std::cout<<"@@@ Query Page: "<<iPage<<", total: "<<nPages<<std::endl;

        int numErrors = reader.Parse(response, &jsonArr);
        if(numErrors == 0){
            if(nPages == 10000){
                wxString num = jsonArr["data"][0]["listNum"].AsString();
                long totalRecords;
                num.ToLong(&totalRecords);
                nPages = totalRecords/64+((totalRecords%64==0)?0:1);
                #ifdef DEBUG
                    std::cout<<"num: "<<nPages<<std::endl;
                #endif
            }
            wxJSONValue data = jsonArr["data"][0]["result"];
            for(int i=0; i<data.Size();i++){
                Polyphone ph;
                ph.strUrl = data[i]["jumplink"].AsString();
                wxString name = data[i]["ename"].AsString();
                if(name.length() == 1){
                    m_dyz[name] = ph;
                }
            }
            iPage++;
        }
    }while(iPage<=nPages-1);
    return true;
}

void BaiduPolyphoneSpider::DumpToFile()
{
    OPEN_TEXT_FILE(EXE_DIR +"baidu.polyphone.txt",file,line);
    std::map<wxString,Polyphone>::const_iterator it;
    LOOP(m_dyz,it){
        wxString url = it->second.strUrl;
        wxString name = it->first;
        line = name+","+url;
        file.AddLine(line);
    }
    CLOSE_TEXT_FILE(file);
}

bool BaiduPolyphoneSpider::QueryPhases()
{
    std::map<wxString,Polyphone>::const_iterator it;
    for(it=m_dyz.begin();it!=m_dyz.end();++it)
    {
        wxString url = it->second.strUrl;
        wxString response;
        http(url,response,wxFONTENCODING_UTF8); // https is not valid
        std::cout<<response<<std::endl;
        break;
    }
    return true;
}
//查看页面是否可以查看更多词组
bool BaiduPolyphoneSpider::HasMorePhases(wxString strHtml,wxString& strUrl)
{
    //先查看是否有相关词组
    return false;
}

bool BaiduPolyphoneSpider::Run()
{
    if(!QueryFromApi()){
        return false;
    }
    DumpToFile();
    return true;
    if(!QueryPhases()){
        return false;
    }
    return true;
}
