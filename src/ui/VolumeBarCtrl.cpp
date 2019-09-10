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
    long w = (long)(m_pKlineCtrl->m_width/(klineRng.end - klineRng.begin) - span);
    w = GUARD(w,1);
    long hVolumeBar = m_pKlineCtrl->m_height*0.3;
    long yVolumeBar = m_pKlineCtrl->m_height*0.7;
    #ifdef DEBUG
        std::cout<<"volume bar w,h,y = ["<<w<<","<<hVolumeBar<<","<<yVolumeBar<<"]"<<std::endl;
    #endif // _DEBUG_
    int i=0;
    for(it = klines.begin()+klineRng.begin; it != klines.begin()+klineRng.end; ++it,++i){
        long x = i*(w+span);
        long y = yVolumeBar + static_cast<long>((1-it->trade_volume/max_volume)*hVolumeBar);
        long h = it->trade_volume/max_volume*hVolumeBar;
        pDC->SetPen(*wxTRANSPARENT_PEN);
        if(it->price_close >= it->price_open){ // red bar
            pDC->SetBrush(wxBrush(wxColor(255,0,0)));
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
    for(it = klines.begin()+ klineRng.begin; it != klines.begin()+klineRng.end; ++it){
        if(it->trade_volume > max)
        {
            max = it->trade_volume;
        }
    }
    return max;
}
