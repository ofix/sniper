#include "spider/IfengSpider.h"

IfengSpider::IfengSpider(wxString strUrl):StockSpider(strUrl)
{

}

IfengSpider::~IfengSpider()
{
    //dtor
}

bool IfengSpider::Run()
{
    m_shares.clear();
    m_vecCount.clear();
    wxString strUrlBase = _T("http://app.finance.ifeng.com/hq/list.php?type=stock_a&class=");
    wxString response;
    //沪A
    wxString strSH = strUrlBase+_T("ha");
    http(strSH,response,wxFONTENCODING_UTF8);
    Parse(response,MARKET_SHANG_HAI);
    //深A
    wxString strSZ = strUrlBase+_T("sa");
    http(strSZ,response,wxFONTENCODING_UTF8);
    Parse(response,MARKET_SHEN_ZHEN);
    //创业板
    wxString strCYB = strUrlBase+_T("gem");
    http(strCYB,response,wxFONTENCODING_UTF8);
    Parse(response,MARKET_CHUAN_YE_BAN);
    return true;
}

bool IfengSpider::Parse(wxString& strResponse,short iTag)
{
    wxRegEx r(_T("<li>[\\r\\n\\s]*<a\\s+href=\"[^\"]+?\"\\s+target=\"_blank\">"\
                 "([^(]+?)\\((\\d+)\\)</a>[\\r\\n\\s]*</li>"),wxRE_ADVANCED);
    size_t oldSize = m_shares.size();
    while(r.Matches(strResponse)) {
        size_t start, len;
        r.GetMatch(&start, &len, 0);
        wxString code = r.GetMatch(strResponse,2);
        wxString name= r.GetMatch(strResponse,1);
        ShareBrief s;
        s.code = code;
        s.name = name;
        s.market = iTag;
        m_shares.push_back(s);
        strResponse = strResponse.Mid(start + len);
    }
    m_vecCount.push_back(m_shares.size()-oldSize); // store different market share count
    return true;
}


void IfengSpider::Dump()
{
    wxVector<ShareBrief>::const_iterator it;
    for(it=m_shares.begin(); it!=m_shares.end(); it++) {
        std::wcout<<_T("股票代号: ")<<it->code<<std::endl;
        std::wcout<<_T("股票名称: ")<<it->name<<std::endl;
        std::wcout<<_T("股票市场: ")<<MARKET_NAME_ZH(it->market)<<std::endl;
    }
}

void IfengSpider::DumpShareCount()
{
    std::wcout<<_T("沪市股票数量:   ")<<m_vecCount[0]<<std::endl;
    std::wcout<<_T("深市股票数量:   ")<<m_vecCount[1]<<std::endl;
    std::wcout<<_T("创业板股票数量: ")<<m_vecCount[2]<<std::endl;
    std::wcout<<_T("全市场股票数量: ")<<m_shares.size()<<std::endl;
}

wxVector<ShareBrief> IfengSpider::GetAllShares()
{
    return m_shares;
}

size_t IfengSpider::GetShareCount() const
{
    return m_shares.size();
}

size_t IfengSpider::GetShanghaiShareCount()const
{
    if(m_vecCount.size() == 3) {
        return m_vecCount[0];
    }
    return 0;
}

size_t IfengSpider::GetShenzhenShareCount()const
{
    if(m_vecCount.size() == 3) {
        return m_vecCount[1];
    }
    return 0;
}

size_t IfengSpider::GetChuanyebanShareCount()const
{
    if(m_vecCount.size() == 3) {
        return m_vecCount[2];
    }
    return 0;
}

