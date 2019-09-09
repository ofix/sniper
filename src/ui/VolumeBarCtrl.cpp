#include "VolumeBarCtrl.h"

VolumeBarCtrl::VolumeBarCtrl(long x,long y,long w,long h):AnalysisCtrl(x,y,w,h)
{
    //ctor
    m_span =0;
}

VolumeBarCtrl::~VolumeBarCtrl()
{
    //dtor
}

void VolumeBarCtrl::SetKlines(wxVector<KlineItem>* pKlines)
{
    m_pKlines = pKlines;
}

void VolumeBarCtrl::SetKlineRng(KlineRange* pRng)
{
    m_pRng = pRng;
}

void VolumeBarCtrl::SetSpan(int span)
{
    m_span = span;
}

void VolumeBarCtrl::OnDraw(wxDC* pDC)
{

}
