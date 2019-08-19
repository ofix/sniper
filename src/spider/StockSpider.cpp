#include "spider/StockSpider.h"

StockSpider::StockSpider(wxString strUrl):Spider(strUrl)
{
    m_total = 0;
    m_pageSize = 20;
    std::locale::global(std::locale(""));
    setlocale(LC_CTYPE, "");    // MinGW gcc.
    std::wcout.imbue(std::locale(""));
}

StockSpider::~StockSpider()
{
    //dtor
}
