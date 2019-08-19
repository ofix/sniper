#ifndef STOCKSTARSPIDER_H
#define STOCKSTARSPIDER_H

#include <wx/regex.h>
#include <wx/vector.h>
#include "StockSpider.h"
#include "core/Stock.h"

/**********************************************
 *@class StockStarSpider
 *@todo crawl all data from StockStar website
 *@author tom song
 **********************************************/
class StockStarSpider : public StockSpider
{
    public:
        StockStarSpider(wxString strUrl=wxT("http://q.ssajax.cn/webhandler/rank.ashx"));
        virtual ~StockStarSpider();
        virtual bool Run();
        bool Parse(wxString& response);
        ShareItem VecToItem(wxVector<wxString> vec);
        void Dump();
    protected:
        wxVector<ShareItem> m_rows;
};

#endif // STOCKSTARSPIDER_H
