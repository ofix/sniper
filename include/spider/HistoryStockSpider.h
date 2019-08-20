#ifndef HISTORYSTOCKSPIDER_H
#define HISTORYSTOCKSPIDER_H

#include <StockSpider.h>
#include "core/Stock.h"
#include "util/Helper.h"

/************************************************************
 *@class HistoryStockSpider
 *@todo to crawl all stock history data from 163 website
 *@author tom song
 ************************************************************/
class HistoryStockSpider : public StockSpider
{
    public:
        // please reference http://quotes.money.163.com/trade/lsjysj_002421.html#01b07
        HistoryStockSpider(wxVector<ShareBrief>& stockList,wxString savePath=_T(""), wxString strUrl=_T(""));
        virtual ~HistoryStockSpider();
        virtual bool Run();

    protected:
        wxVector<ShareBrief> m_stockList;
        wxString m_saveRootPath;
        bool m_saveWay; // "csv" 或者 "mysql"

};

#endif // HISTORYSTOCKSPIDER_H
