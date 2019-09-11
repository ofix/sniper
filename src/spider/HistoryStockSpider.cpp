#include "spider/HistoryStockSpider.h"

HistoryStockSpider::HistoryStockSpider(wxVector<ShareBrief>& stockList,wxString saveRootPath,wxString strUrl)
                        :StockSpider(strUrl)
{
    m_stockList = stockList;
    m_saveRootPath = saveRootPath;
    m_saveWay= wxT("csv");
}


HistoryStockSpider::~HistoryStockSpider()
{
    //dtor
}

bool HistoryStockSpider::Run()
{
    wxVector<ShareBrief>::iterator it = m_stockList.begin();
    while( it != m_stockList.end()){
        wxString code = (*it).code; //股票代号
        int market = (*it).market; //东方财富股票详情数据
        wxString prefix = wxT("1"); //深市+创业板
        if(market == MARKET_SHANG_HAI){
            prefix = '0';//沪市
        }
        wxString response;
        wxDateTime _now = wxDateTime::Now();
        wxString now = _now.Format("%Y%m%d");
        wxString url = wxT("http://quotes.money.163.com/service/chddata.html?code=");
          url += prefix;
          url += code;
          url += wxT("&start=19901219&end=")+now+wxT(
                     "&fields=TCLOSE;HIGH;LOW;TOPEN;LCLOSE;CHG;PCHG;TURNOVER;"\
                     "VOTURNOVER;VATURNOVER;TCAP;MCAP"); // 反斜杠续行不包含空格的方法
          std::cout<<"(code,url) === ("<<code<<","<<url<<")"<<std::endl;
          http(url,response);
          wxString saveRoot = m_saveRootPath.CmpNoCase(wxT(""))?m_saveRootPath:getExecDir();
          wxString target = saveRoot+code+wxT(".csv");
          if(!saveTo(target,response)){
                std::cout<<"flush data failed."<<std::endl;
                break;
          }
          it++;
          break;
    }
    return true;
}
