#include "ui/AnalysisCtrl.h"

AnalysisCtrl::AnalysisCtrl(long x,long y,long width,long height):
            m_x(x),m_y(y),m_w(width),m_h(height)
{
    //ctor
}

AnalysisCtrl::~AnalysisCtrl()
{
    //dtor
}

inline void AnalysisCtrl::SetX(long x)
{
    m_x = x;
}

inline void AnalysisCtrl::SetY(long y)
{
    m_y = y;
}


inline void AnalysisCtrl::SetWidth(long width)
{
    m_w = width;
}


inline void AnalysisCtrl::SetHeight(long height)
{
    m_h = height;
}


inline long AnalysisCtrl::GetX()
{
    return m_x;
}

inline long AnalysisCtrl::GetY()
{
    return m_y;
}

inline long AnalysisCtrl::GetWidth()
{
    return m_w;
}

inline long AnalysisCtrl::GetHeight()
{
    return m_h;
}
