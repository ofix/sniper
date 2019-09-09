#ifndef VOLUMEBARCTRL_H
#define VOLUMEBARCTRL_H

#include <AnalysisCtrl.h>
#include <wx/vector.h>
#include <core/Stock.h>
#include <wx/dcclient.h>


class VolumeBarCtrl : public AnalysisCtrl
{
    public:
        VolumeBarCtrl(long x=0,long y=0,long w=0,long h=0);
        virtual ~VolumeBarCtrl();
        void SetKlines(wxVector<KlineItem>* pKlines);
        void SetKlineRng(KlineRange* pRange);
        void SetSpan(int span);
        void OnDraw(wxDC* pDC);
    protected:
        double GetMaxVolumeInRange();
    protected:
        wxVector<KlineItem>* m_pKlines; // the k line data, day | week | month
        KlineRange* m_pKlineRng;
        int m_span; // volume bar span
};

#endif // VOLUMEBARCTRL_H
