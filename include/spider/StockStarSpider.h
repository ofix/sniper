#ifndef STOCKSTARSPIDER_H
#define STOCKSTARSPIDER_H

#include <wx/regex.h>
#include "StockSpider.h"

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
        wxString Parse(wxString& response);
    protected:
};

#endif // STOCKSTARSPIDER_H
