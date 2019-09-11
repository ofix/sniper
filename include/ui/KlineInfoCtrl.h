#ifndef KLINEINFOCTRL_H
#define KLINEINFOCTRL_H
#include <ui/AnalysisCtrl.h>
#include <wx/dcclient.h>

class KlineCtrl;
class KlineInfoCtrl:public AnalysisCtrl
{
    public:
        KlineInfoCtrl(KlineCtrl* pKlineCtrl, long x=0,long y=0,long w=0,long h=0);
        virtual ~KlineInfoCtrl();
        void OnDraw(wxDC* pDC);
    protected:
        KlineCtrl* m_pKlineCtrl;
};

#endif // KLINEINFOCTRL_H
