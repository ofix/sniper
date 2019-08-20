#ifndef SPIDERMANAGER_H
#define SPIDERMANAGER_H
#include <wx/vector.h>
#include "Stock.h"
#include "spider/IfengSpider.h"
#include "spider/HistoryStockSpider.h"
#include "spider/SinaStockSpider.h"

/*******************************
 *@class SpiderManager
 *@todo manage all spiders in right sequence
 *******************************/
class SpiderManager
{
    public:
        SpiderManager();
        virtual ~SpiderManager();
        bool CrawlAllShares(); //crawl all share brief data
    protected:
        wxVector<ShareBrief> m_shares; // all shares

};

#endif // SPIDERMANAGER_H
