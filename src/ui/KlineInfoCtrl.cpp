#include "KlineInfoCtrl.h"
#include "ui/KlineCtrl.h"

KlineInfoCtrl::KlineInfoCtrl(KlineCtrl* pKlineCtrl,long x,long y,long w,long h):
                AnalysisCtrl(x,y,w,h),m_pKlineCtrl(pKlineCtrl)
{
    //ctor
}

KlineInfoCtrl::~KlineInfoCtrl()
{
    //dtor
}

void KlineInfoCtrl::OnDraw(wxDC* pDC)
{

}

