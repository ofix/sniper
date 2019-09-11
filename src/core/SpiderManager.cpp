#include "core/SpiderManager.h"

SpiderManager::SpiderManager()
{
    //ctor
}

SpiderManager::~SpiderManager()
{
    //dtor
}

bool SpiderManager::CrawlAllShares()
{
    //获取所有股票的代码和简称
    IfengSpider spider;
    spider.Run();
    //抓取历史数据
    wxVector<ShareBrief> shares = spider.GetAllShares();
    HistoryStockSpider hSpider(shares);
    hSpider.Run();
    return true;
}
