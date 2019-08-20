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
        wxVector<ShareBrief> GetAllShares();
        size_t GetShareCount() const;
        size_t GetShanghaiShareCount()const;
        size_t GetShenzhenShareCount()const;
        size_t GetChuanyebanShareCount()const;
        void Dump();
        void DumpShareCount();
    protected:
        bool Parse(wxString& strResponse,short iTag=1);
        wxVector<ShareBrief> m_shares;
        wxVector<size_t> m_vecCount; // store three market share count in slot [0,1,2]
};

#endif // IFENGSPIDER_H
