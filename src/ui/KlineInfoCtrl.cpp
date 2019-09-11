#include "KlineInfoCtrl.h"
#include "ui/KlineCtrl.h"
#include <wx/datetime.h>

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
    KlineItem cur = GetCurrentKlineInfo();
    KlineItem old = GetPrevKlineInfo();
    pDC->SetPen(wxPen(wxColor(255,0,0)));
    pDC->SetBrush(*wxBLACK_BRUSH);
    pDC->DrawRectangle(10,40,65,340);
    int x =10;
    int y =40;
    int hFont = 21;
    wxString day = FormatDay(cur.day);
    wxString week = GetWeek(cur.day);
    // day
    pDC->SetTextForeground(wxColor(210,210,210));
    pDC->DrawText(wxT("时间"),x+4,y+4);
    pDC->DrawText(day,x+4,y+hFont);
    pDC->DrawText(week,x+4,y+hFont*2);
    pDC->DrawText(wxT("开盘价"),x+4,y+hFont*3);
    pDC->DrawText(wxT("最高价"),x+4,y+hFont*5);
    pDC->DrawText(wxT("最低价"),x+4,y+hFont*7);
    pDC->DrawText(wxT("收盘价"),x+4,y+hFont*9);
    pDC->DrawText(wxT("涨幅"),x+4,y+hFont*11);
    pDC->DrawText(wxT("振幅"),x+4,y+hFont*13);
    pDC->DrawText(wxT("成交量"),x+4,y+hFont*15);
    pDC->DrawText(wxT("成交额"),x+4,y+hFont*17);
    // price open
    if(cur.price_open < old.price_close){
        pDC->SetTextForeground(wxColor(0,255,0));
    }else if(cur.price_open == old.price_close){
        pDC->SetTextForeground(wxColor(255,255,255));
    }else{
        pDC->SetTextForeground(wxColor(255,0,0));
    }
    pDC->DrawText(wxString::Format("%.2f",cur.price_open),x+4,y+hFont*4);
    // price max
    if(cur.price_max < old.price_close){
        pDC->SetTextForeground(wxColor(0,255,0));
    }else if(cur.price_max == old.price_close){
        pDC->SetTextForeground(wxColor(255,255,255));
    }else{
        pDC->SetTextForeground(wxColor(255,0,0));
    }
    pDC->DrawText(wxString::Format("%.2f",cur.price_max),x+4,y+hFont*6);
    // price min
    if(cur.price_min < old.price_close){
        pDC->SetTextForeground(wxColor(0,255,0));
    }else if(cur.price_min == old.price_close){
        pDC->SetTextForeground(wxColor(255,255,255));
    }else{
        pDC->SetTextForeground(wxColor(255,0,0));
    }
    pDC->DrawText(wxString::Format("%.2f",cur.price_min),x+4,y+hFont*8);
    // price close
    if(cur.price_close < old.price_close){
        pDC->SetTextForeground(wxColor(0,255,0));
    }else if(cur.price_close == old.price_close){
        pDC->SetTextForeground(wxColor(255,255,255));
    }else{
        pDC->SetTextForeground(wxColor(255,0,0));
    }
    pDC->DrawText(wxString::Format("%.2f",cur.price_close),x+4,y+hFont*10);
}

wxString KlineInfoCtrl::FormatDay(wxString date)
{
    wxString year = date.Left(4);
    wxString month = date.Mid(5,2);
    wxString day = date.Mid(8,2);
    return year +wxT("\r\n")+month+day;
}

wxString KlineInfoCtrl::GetWeek(wxString date)
{
    wxString strYear = date.Left(4);
    wxString strMonth = date.Mid(5,2);
    wxString strDay = date.Mid(8,2);
    long year,month,day;
    strYear.ToLong(&year);
    strMonth.ToLong(&month);
    strDay.ToLong(&day);
    return CalcWeek(year,month,day);
}

//通过日期判断是星期几可以通过基姆拉尔森计算公式算出
wxString KlineInfoCtrl::CalcWeek(int year,int month, int day){
    if(month==1||month==2) //把一月和二月换算成上一年的十三月和是四月
    {
        month+=12;
        year--;
    }
    int week=(day+2*month+3*(month+1)/5+year+year/4-year/100+year/400)%7;
    switch(week)
    {
        case 0: return wxT("星期一");
        case 1: return wxT("星期二");
        case 2: return wxT("星期三");
        case 3: return wxT("星期四");
        case 4: return wxT("星期五");
        case 5: return wxT("星期六");
        case 6: return wxT("星期日");
    }
    return wxT("");
}

KlineItem KlineInfoCtrl::GetCurrentKlineInfo()
{
    int n;
    if(m_pKlineCtrl->m_crossLine == NO_CROSS_LINE){
        n = m_pKlineCtrl->m_klines.size()-1;
    }else{
        n = m_pKlineCtrl->m_crossLine;
    }
    return m_pKlineCtrl->m_klines.at(n);
}

KlineItem KlineInfoCtrl::GetPrevKlineInfo(){
    int n;
    if(m_pKlineCtrl->m_crossLine == NO_CROSS_LINE){
        n = m_pKlineCtrl->m_klines.size()-1;
    }else{
        n = m_pKlineCtrl->m_crossLine;
    }
    return m_pKlineCtrl->m_klines.at((n-1)>=0?(n-1):0);
}
