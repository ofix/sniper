#ifndef VOLUMEBARCTRL_H
#define VOLUMEBARCTRL_H

#include <AnalysisCtrl.h>
#include <wx/vector.h>
#include <core/Stock.h>
#include <wx/dcclient.h>

class KlineCtrl;
class VolumeBarCtrl : public AnalysisCtrl
{
    public:
        VolumeBarCtrl(KlineCtrl* pKlineCtrl, long x=0,long y=0,long w=0,long h=0);
        virtual ~VolumeBarCtrl();
        void OnDraw(wxDC* pDC);
    protected:
        double GetMaxVolumeInRange();
    protected:
        KlineCtrl* m_pKlineCtrl;
};

#endif // VOLUMEBARCTRL_H
