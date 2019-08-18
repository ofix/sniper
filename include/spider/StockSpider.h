#ifndef STOCKSPIDER_H
#define STOCKSPIDER_H

#include "Spider.h"

/*******************************************
 *@class StockSpider
 *@todo the parent class of all Stock Spider
 *@author tom song
 *******************************************/
class StockSpider : public Spider
{
    public:
        StockSpider(wxString strUrl);
        virtual ~StockSpider();

    protected:
       int m_total; //total rows need to be crawler
       int m_pageSize; //how many rows each page contains

};

#endif // STOCKSPIDER_H
