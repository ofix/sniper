#ifndef ANALYSISCTRL_H
#define ANALYSISCTRL_H


class AnalysisCtrl
{
    public:
        AnalysisCtrl(long x=0,long y=0,long w=0,long h=0);
        AnalysisCtrl() = delete;
        virtual ~AnalysisCtrl();
        void SetX(long x);
        void SetY(long y);
        void SetWidth(long width);
        void SetHeight(long height);
        long GetX();
        long GetY();
        long GetWidth();
        long GetHeight();

    protected:
        long m_x;
        long m_y;
        long m_w;
        long m_h;
};

#endif // ANALYSISCTRL_H
