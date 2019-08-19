#ifndef IFENGSPIDER_H
#define IFENGSPIDER_H

#include <StockSpider.h>
#include "core/Stock.h"

class IfengSpider : public StockSpider
{
    public:
        IfengSpider(wxString strUrl = wxT(""));
        virtual ~IfengSpider();
        virtual bool Run();
        bool Parse(wxString& strResponse,short iTag=1);
        void Dump();
    protected:
        wxVector<ShareBrief> m_shares;
};

#endif // IFENGSPIDER_H
