#include "spider/SinaStockSpider.h"

SinaStockSpider::SinaStockSpider(wxString strUrl):StockSpider(strUrl)
{
    m_pageSize = 40;
    m_urlTotalCount = wxT("http://vip.stock.finance.sina.com.cn/quotes_service/api/json_v2.php/"\
                          "Market_Center.getHQNodeStockCount?node=hs_a");
    m_urlPageData = wxT("http://vip.stock.finance.sina.com.cn/quotes_service/api/json_v2.php/Market_Center.getHQNodeData"\
                        "?page=1&num=");
    m_urlPageData.Append(wxString::Format(_T("%d"),m_pageSize));
    m_urlPageData.Append(wxT("&sort=symbol&asc=1&node=hs_a&symbol=&_s_r_a=auto"));

    std::locale::global(std::locale(""));
    setlocale(LC_CTYPE, "");    // MinGW gcc.
    std::wcout.imbue(std::locale(""));
}

SinaStockSpider::~SinaStockSpider()
{
    //dtor
}

bool SinaStockSpider::Run()
{
    m_timeStart = wxDateTime::Now();
    wxString resStockNum;
    http(m_urlTotalCount,resStockNum);
    wxString patternTotal(_T("\\(new\\s+String\\(\"(\\d+)\"\\)\\)"));
    wxRegEx reTotal(patternTotal,wxRE_ADVANCED); // must use wxRE_ADVANCED, or \\d+ would not work correctly.
    wxString processText = resStockNum;
    if(reTotal.Matches(processText)){
        wxString strTotal = reTotal.GetMatch(processText,1);
        m_total = wxAtoi(strTotal);
    }
    if(m_total >0){
        for(int i=0,j=0;i<=m_total;i+=m_pageSize,j++){
            wxString jsonStock;
            wxString urlStock = wxT("http://vip.stock.finance.sina.com.cn/quotes_service/api/json_v2.php/"\
                                    "Market_Center.getHQNodeData");
            kvMap parameters;
            parameters["page"]=wxString::Format("%d",j);
            parameters["num"]=wxString::Format("%d",m_pageSize);
            parameters["sort"]="symbol";
            parameters["asc"]="1";
            parameters["node"]="hs_a";
            parameters["symbol"] = "auto";
            wxString  para = buildUrlPara(parameters);
            urlStock.Append(para);
            http(urlStock,jsonStock);
            wxJSONReader reader;
            wxJSONValue  jsonArr;
            console(urlStock);
            fixBadJson(jsonStock);

            // resStock has already been UNICODE
            int numErrors = 0;
            numErrors = reader.Parse(jsonStock, &jsonArr);
            if ( numErrors > 0 )  {
               wxArrayString err = reader.GetErrors();
               for(size_t i=0; i<err.GetCount(); i++){
                std::wcout<<"ERROR :  "<<err.Item(i)<<std::endl;
               }
               return false;
            }
            std::wcout<<jsonArr[0]["symbol"].AsString()<<std::endl;
            break;
        }
    }else{
        std::cout<<"Load Sina Stock Data Error."<<std::endl;
    }
    m_timeEnd = wxDateTime::Now();
    return true;
}

void* SinaStockSpider::GetResult()
{
    return nullptr;
}
