#include "spider/StockSpider.h"

StockSpider::StockSpider(wxString urlTarget):Spider(urlTarget)
{
    m_total = 0;
    m_pageSize = 20;
}

StockSpider::~StockSpider()
{
    //dtor
}
