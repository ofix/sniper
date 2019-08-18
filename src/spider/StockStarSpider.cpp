#include "spider/StockStarSpider.h"

StockStarSpider::StockStarSpider(wxString strUrl):StockSpider(strUrl)
{
    //ctor
}

StockStarSpider::~StockStarSpider()
{
    //dtor
}

bool StockStarSpider::Run()
{
    wxString url = m_url;
    kvMap parameters;
    parameters["type"]="a";
    parameters["sortfield"]="1";
    parameters["direction"]="0";
    parameters["pageid"]="5";
    wxDateTime now = wxDateTime::Now();
    parameters["_"]=wxString::Format("%lld",now.GetValue());
    wxString  para = buildUrlPara(parameters);
    url.Append(para);
    //begin to request remote URL.
    wxString response;
    http(url,response);
    wxString data = Parse(response);

    return true;
}

wxString StockStarSpider::Parse(wxString& response)
{
    wxString data = _T("");
    wxString pattern(_T("\"html\":\"([^,]*)\","));
    wxRegEx r(pattern,wxRE_ADVANCED);
    if(r.Matches(response)){
        wxString html = r.GetMatch(response,1);
        std::cout<<html<<std::endl;
    }
    return data;
}
