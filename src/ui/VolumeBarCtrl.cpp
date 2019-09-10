#include "VolumeBarCtrl.h"
#include "KlineCtrl.h"

VolumeBarCtrl::VolumeBarCtrl(KlineCtrl* pKlineCtrl,long x,long y,long w,long h):
                AnalysisCtrl(x,y,w,h),m_pKlineCtrl(pKlineCtrl)
{

}

VolumeBarCtrl::~VolumeBarCtrl()
{
    //dtor
}

void VolumeBarCtrl::OnDraw(wxDC* pDC)
{
    wxVector<KlineItem>& klines = m_pKlineCtrl->m_klines;
    KlineRange& klineRng = m_pKlineCtrl->m_klineRng;
    int span = m_pKlineCtrl->m_klineSpan;
    // get canvas height
    double max_volume = GetMaxVolumeInRange();
    wxVector<KlineItem>::const_iterator it;
    // calc single volume bar width
    long w = (long)(m_w/(klineRng.end - klineRng.begin) - span);
    int i=0;
    for(it = klines.begin()+klineRng.begin; it != klines.begin()+klineRng.end; ++it,++i){
        long x = i*(w+span);
        long y = m_y + static_cast<long>((1-it->trade_volume/max_volume)*m_h);
        long h = it->trade_volume/max_volume*m_h;
        if(it->price_close >= it->price_open){ // red bar
            pDC->SetBrush(wxBrush(wxColor(84,255,255)));
        }else{ // green bar
            pDC->SetBrush(wxBrush(wxColor(84,255,255)));
        }
        pDC->DrawRectangle(x,y,w,h);
    }
}

double VolumeBarCtrl::GetMaxVolumeInRange()
{
    double max = 0;
    wxVector<KlineItem>::const_iterator it;
    wxVector<KlineItem>& klines = m_pKlineCtrl->m_klines;
    KlineRange& klineRng = m_pKlineCtrl->m_klineRng;
    wxASSERT(klineRng.begin < klineRng.end);
    for(it = klines.begin()+ klineRng.begin; it != klines.begin()+klineRng.end; ++it){
        if(it->trade_volume > max)
        {
            max = it->trade_volume;
        }
    }
    return max;
}
