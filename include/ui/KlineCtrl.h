#ifndef KLINECTRL_H
#define KLINECTRL_H
#include <wx/control.h>
#include <wx/vector.h>
#include <wx/textfile.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include "core/Stock.h"
#include "util/Helper.h"

#define KEY_LEFT 314
#define KEY_RIGHT 316
#define KEY_UP 315
#define KEY_DOWN 317

#define KLINE_MODE_DAY 1
#define KLINE_MODE_WEEK 2
#define KLINE_MODE_MONTH 4
#define KLINE_MODE_YEAR 8
#define KLINE_MODES (KLINE_MODE_DAY|KLINE_MODE_WEEK|KLINE_MODE_MONTH|KLINE_MODE_YEAR)
#define NO_CROSS_LINE 0


class KlineCtrl:public wxControl
{
    wxDECLARE_DYNAMIC_CLASS(KlineCtrl);
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_NO_COPY_CLASS(KlineCtrl);
    public:
        KlineCtrl();
        KlineCtrl(wxString strShareCode);
        KlineCtrl(wxWindow* parent,wxWindowID id,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style=0,
                 const wxValidator& validator = wxDefaultValidator);
        bool Create(wxWindow* parent,wxWindowID id,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style= 0,
                const wxValidator& validator = wxDefaultValidator);
        virtual ~KlineCtrl();
        void Init();
        void SetShare(ShareBrief share);
        ShareBrief GetShare()const;
        void SetMode(int iMode);//Day|Week|Month|Year
        int GetMode() const;
        void SetCsvPath(wxString strPath);
        wxString GetCsvPath() const;

        //event callback functions
        void OnPaint(wxPaintEvent& event);
        void OnBackground(wxEraseEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnKeyDown(wxKeyEvent& event);
        void OnLeftMouseDown(wxMouseEvent& event);
    protected:
        bool ReadCsv();

        //draw helper functions
        void DrawKline(wxDC* pDC,int nKLine,int visibleKLineCount,
                      float price_open,float price_close,
                      float price_max,float price_min,
                      float rect_price_high,float rect_price_low,
                      int minX,int minY,int maxX,int maxY,int lineWidth,int lineSpan);
        void DrawCrossLine(wxDC* pDC,int centerX,int centerY,int w,int h);//光标十字线
        void DrawAnalysisBar(wxDC* pDC);
        double GetMaxVolume();
        double GetMaxValue(int member, int klineType);
        wxVector<KlineItem> GetWeekKlines();
        wxVector<KlineItem> GetMonthKlines();
        float GetRectMinPrice(wxVector<KlineItem>& data,int begin, int end);
        float GetRectMaxPrice(wxVector<KlineItem>& data,int begin, int end);
        KlineRange  GetKlineRangeZoomIn(long totalKLines, long widthContainer,
                                  int16_t klineWidth=5,int16_t klineSpan=2,
                                  long crossLine = NO_CROSS_LINE);//放大K线图
        KlineRange  GetKlineRangeZoomOut(long totalKLines,long crossLine = NO_CROSS_LINE);//以十字线为中心，否则右侧缩放
        wxPoint GetCrossLinePt(long n);
    protected:
        ShareBrief m_share; // the share whose k line want to be draw
        int m_iMode; // DAY|Week|Month|Year
        int m_iOrigin; // 0-CSV 1-pointer
        int m_width; // the drawing rect width
        int m_height; // the drawing rect height
        int m_curKline; // the current k line under the cursor
        int m_klineWidth; // single k line width
        int m_klineSpan; // span between two single k line
        float m_rectPriceMax; // the maximum price in the drawing rect
        float m_rectPriceMin; // the minimum price in the drawing rect
        wxPoint m_crossLinePt; // the current k line mouse point
        int m_crossLine;
        wxString m_csvPath; // csv file path of day k line history data
        wxVector<KlineItem> m_klines; // the k line data
        wxVector<KlineItem> m_weekKlines; //week k line data;
        wxVector<KlineItem> m_monthKlines; //month k line data;
        KlineRange m_klineRng;
        bool m_showAnalysisBar; // if true, draw volume,MCDA,KDJ index
        int m_analysisType;
};

#endif // KLINECTRL_H
