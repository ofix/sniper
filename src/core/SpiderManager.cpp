#include "SpiderManager.h"

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
    IfengSpider spider;
    spider.Run();
    spider.DumpShareCount();
    spider.Dump();
    return true;
}
