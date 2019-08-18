#ifndef EASTMONEYSPIDER_H
#define EASTMONEYSPIDER_H

#include "StockSpider.h"

/************************************************************
 *@class EastMoneySpider
 *@todo to crawl all stock newest data from EastMoney website
 *@author tom song
 ************************************************************/
class EastMoneySpider : public StockSpider
{
    public:
        EastMoneySpider(wxString strUrl=wxT("http://quote.eastmoney.com/center/gridlist.html#hs_a_board"));
        virtual ~EastMoneySpider();
        virtual bool Run();

    protected:
        wxString m_urlData;
};

#endif // EASTMONEYSPIDER_H
