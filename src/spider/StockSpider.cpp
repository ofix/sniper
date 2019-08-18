#include "spider/StockSpider.h"

StockSpider::StockSpider(wxString strUrl):Spider(strUrl)
{
    m_total = 0;
    m_pageSize = 20;
}

StockSpider::~StockSpider()
{
    //dtor
}
