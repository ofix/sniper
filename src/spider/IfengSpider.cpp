#include "IfengSpider.h"

IfengSpider::IfengSpider(wxString strUrl):StockSpider(strUrl)
{

}

IfengSpider::~IfengSpider()
{
    //dtor
}

bool IfengSpider::Run()
{
    wxString strUrlBase = _T("http://app.finance.ifeng.com/hq/list.php?type=stock_a&class=");
    wxString response;
    //沪A
    wxString strSH = strUrlBase+_T("ha");
    http(strSH,response,wxFONTENCODING_UTF8);
    Parse(response,1);
    //深A
    wxString strSZ = strUrlBase+_T("sa");
    http(strSZ,response,wxFONTENCODING_UTF8);
    Parse(response,2);
    //创业板
    wxString strCYB = strUrlBase+_T("gem");
    http(strCYB,response,wxFONTENCODING_UTF8);
    Parse(response,3);
    return true;
}

bool IfengSpider::Parse(wxString& strResponse,short iTag)
{
    wxRegEx r(_T("<li>[\\r\\n\\s]*<a\\s+href=\"[^\"]+?\"\\s+target=\"_blank\">"\
                    "([^(]+?)\\((\\d+)\\)</a>[\\r\\n\\s]*</li>"),wxRE_ADVANCED);
    while(r.Matches(strResponse)){
        size_t start, len;
        r.GetMatch(&start, &len, 0);
        wxString code = r.GetMatch(strResponse,1);
        wxString name= r.GetMatch(strResponse,2);
        std::cout<<"code = "<<code<<std::endl;
        std::cout<<"name = "<<name<<std::endl;
        std::wcout<<"market = "<<MARKET_NAME_ZH(iTag)<<std::endl;
        strResponse = strResponse.Mid(start + len);
    }
    return true;
}


void IfengSpider::Dump()
{
    wxVector<ShareBrief>::const_iterator it;
    for(it=m_shares.begin(); it!=m_shares.end();it++){
        std::wcout<<"股票代号: "<<it->code<<std::endl;
        std::wcout<<"股票名称: "<<it->name<<std::endl;
        std::wcout<<"股票市场: "<<MARKET_NAME_ZH(it->market)<<std::endl;
    }
}

