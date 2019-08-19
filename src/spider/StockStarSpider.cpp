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
        wxString table = r.GetMatch(response,1);
        table.Replace("\\u003c","<");
        table.Replace("\\u003e",">");
        table.Replace("\\","");
        //get the table column values in two steps make the regex pattern simple.
        wxRegEx r_tr(_T("(<tr[^>]*>(.*?)</tr>)+?"),wxRE_ADVANCED);
        while(r_tr.Matches(table)){
            size_t start, len;
            r_tr.GetMatch(&start, &len, 0);
            wxString tr = r_tr.GetMatch(table,2);
            //Get the content in <td>
            wxRegEx r_td(_T("(<td[^>]*>(.*?)</td>)+?"),wxRE_ADVANCED);
            while(r_td.Matches(tr)){
                size_t s, e;
                r_td.GetMatch(&s, &e, 0);
                wxString td = r_td.GetMatch(tr,2);
                //filter <a> tag
                wxRegEx r_a(_T("<a[^>]*>(.*?)</a>"),wxRE_ADVANCED);
                if(r_a.Matches(td)){
                    td = r_a.GetMatch(td,1);
                }
                //filter <span> tag
                wxRegEx r_span(_T("<span[^>]*>(.*?)</span>"),wxRE_ADVANCED);
                if(r_span.Matches(td)){
                    td = r_span.GetMatch(td,1);
                }
                std::cout<<"***** td = "<<td<<std::endl;
                tr = tr.Mid(s+e);
            }
           table = table.Mid(start + len);
        }
    }
    return data;
}
