#ifndef VOLUMEBARCTRL_H
#define VOLUMEBARCTRL_H

#include <AnalysisCtrl.h>
#include <wx/vector.h>
#include <core/Stock.h>


class VolumeBarCtrl : public AnalysisCtrl
{
    public:
        VolumeBarCtrl(long x=0,long y=0,long w=0,long h=0);
        virtual ~VolumeBarCtrl();
        void SetKlines(wxVector<KlineItem>* pKlines);
        void SetKlineRng(KlineRange* pRange);
    protected:
        wxVector<KlineItem>* m_pKlines; // the k line data, day | week | month
        KlineRange* m_pRng;
};

#endif // VOLUMEBARCTRL_H
