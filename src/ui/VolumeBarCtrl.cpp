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
    m_pKlineRng = pRng;
}

void VolumeBarCtrl::SetSpan(int span)
{
    m_span = span;
}

void VolumeBarCtrl::OnDraw(wxDC* pDC)
{
    // get canvas height
    double max_volume = GetMaxVolumeInRange();
    wxVector<KlineItem>::const_iterator it;
    // calc single volume bar width
    long w = (long)(m_w/(m_pKlineRng->end - m_pKlineRng->begin) - m_span);
    int i=0;
    for(it = m_pKlines->begin()+m_pKlineRng->begin; it != m_pKlines->begin()+m_pKlineRng->end; ++it,++i){
        long x = i*(w+m_span);
        long y = m_y + static_cast<long>((1-it->trade_volume/max_volume)*m_h);
        long h = it->trade_volume/max_volume*m_h;
        if(it->price_close >= it->price_open){ // 红柱
            pDC->SetBrush(wxBrush(wxColor(84,255,255)));
        }else{ //绿柱
            pDC->SetBrush(wxBrush(wxColor(84,255,255)));
        }
        pDC->DrawRectangle(x,y,w,h);
    }
}

double VolumeBarCtrl::GetMaxVolumeInRange()
{
    double max = 0;
    wxVector<KlineItem>::const_iterator it;
    for(it = m_pKlines->begin()+ m_pKlineRng->begin; it != m_pKlines->begin()+m_pKlineRng->end; ++it){
        if(it->trade_volume > max)
        {
            max = it->trade_volume;
        }
    }
    return max;
}
