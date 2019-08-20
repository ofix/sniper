#ifndef SINASTOCKSPIDER_H
#define SINASTOCKSPIDER_H

#include <wx/vector.h>
#include <wx/regex.h>
#include "core/Stock.h"
#include "util/Helper.h"
#include "lib/wxJSON/jsonval.h"
#include "lib/wxJSON/jsonreader.h"
#include "StockSpider.h"

/************************************************************
 *@class SinaStockSpider
 *@todo to crawl all stock newest data from Sina website
 *@author tom song
 ************************************************************/
class SinaStockSpider : public StockSpider
{
    public:
        SinaStockSpider(wxString strUrl=wxT("http://vip.stock.finance.sina.com.cn/mkt/#hs_a"));
        virtual ~SinaStockSpider();
        virtual bool Run();
        virtual void* GetResult();
    protected:
        wxVector<KlineItem> m_data;
        wxString m_urlTotalCount; // URL to get stock total count
        wxString m_urlPageData; //URL to get stock page data
};

#endif // SINASTOCKSPIDER_H
