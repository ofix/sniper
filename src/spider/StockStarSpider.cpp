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
    Parse(response);
    Dump();
    return true;
}

bool StockStarSpider::Parse(wxString& response)
{
    wxString pattern(_T("\"html\":\"([^,]*)\","));
    wxRegEx r(pattern,wxRE_ADVANCED);
    if(!r.Matches(response)) {
        return false;
    }
    m_rows.clear();//清空数据
    wxString table = r.GetMatch(response,1);
    table.Replace("\\u003c","<");
    table.Replace("\\u003e",">");
    table.Replace("\\","");
    //get the table column values in two steps make the regex pattern simple.
    wxRegEx r_tr(_T("(<tr[^>]*>(.*?)</tr>)+?"),wxRE_ADVANCED);
    while(r_tr.Matches(table)) {
        size_t start, len;
        r_tr.GetMatch(&start, &len, 0);
        wxString tr = r_tr.GetMatch(table,2);
        //Get the content in <td>
        wxRegEx r_td(_T("(<td[^>]*>(.*?)</td>)+?"),wxRE_ADVANCED);
        wxVector<wxString> columns;
        while(r_td.Matches(tr)) {
            size_t s, e;
            r_td.GetMatch(&s, &e, 0);
            wxString td = r_td.GetMatch(tr,2);
            //filter <a> tag
            wxRegEx r_a(_T("<a[^>]*>(.*?)</a>"),wxRE_ADVANCED);
            if(r_a.Matches(td)) {
                td = r_a.GetMatch(td,1);
            }
            //filter <span> tag
            wxRegEx r_span(_T("<span[^>]*>(.*?)</span>"),wxRE_ADVANCED);
            if(r_span.Matches(td)) {
                td = r_span.GetMatch(td,1);
            }
            columns.push_back(td);
            tr = tr.Mid(s+e);
        }
        ShareItem item = VecToItem(columns);
        m_rows.push_back(item);
        columns.clear();
        table = table.Mid(start + len);
    }
    return true;
}

ShareItem StockStarSpider::VecToItem(wxVector<wxString> vec)
{
    ShareItem item;
    item.code = vec[0];//代码
    item.name = vec[1];//简称
    vec[2].ToDouble(&item.price);//最新价
    wxString change_percent;
    vec[3].EndsWith(_T("%"),&change_percent);
    change_percent.ToDouble(&item.change_percent);//涨跌幅
    vec[4].ToDouble(&item.change);//涨跌额
    vec[7].ToDouble(&item.to);//成交额
    vec[10].ToDouble(&item.qr);//量比
    vec[12].ToDouble(&item.pe);//市盈率
    return item;
}

void StockStarSpider::Dump()
{
    wxVector<ShareItem>::const_iterator it;
    for(it = m_rows.begin(); it != m_rows.end(); ++it) {
        std::wcout<<_T("代码:  ")<<it->code<<std::endl;
        std::wcout<<_T("简称:  ")<<it->name<<std::endl;
        std::wcout<<_T("最新价:  ")<<it->price<<std::endl;
        std::wcout<<_T("涨跌幅:  ")<<wxString::Format("%.2f",it->change_percent) + _T("%")<<std::endl;
        std::wcout<<_T("涨跌额:  ")<<it->change<<std::endl;
        std::wcout<<_T("成交额:  ")<<wxString::Format("%.2f",it->to) + _T("万元")<<std::endl;
        std::wcout<<_T("量比: ")<<it->qr<<std::endl;
        std::wcout<<_T("市盈率: ")<<it->pe<<std::endl;
        std::wcout<<"=============================="<<std::endl;
    }
}
