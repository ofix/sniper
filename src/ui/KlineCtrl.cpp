#include "ui/KlineCtrl.h"
#include "ui/VolumeBarCtrl.h"
#include "ui/KlineInfoCtrl.h"

KlineCtrl::KlineCtrl()
{
    Init();
}

KlineCtrl::KlineCtrl(wxString strShareCode,wxWindow* parent,wxWindowID id)
{
    Init();
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Create(parent,id);
    GetClientSize(&m_width,&m_height);
    SetCsvPath(getExecDir()+strShareCode+_T(".csv"));
    ReadCsv();
    m_klineRng = GetKlineRangeZoomIn(m_klines.size(),m_width,m_klineWidth,m_klineSpan);
    m_pVolumeBar = new VolumeBarCtrl(this);
    m_pInfoToolbar = new KlineInfoCtrl(this);
}

KlineCtrl::KlineCtrl(wxWindow* parent,wxWindowID id,
                   const wxPoint& pos,
                   const wxSize& size,
                   long style, const wxValidator& validator)
{
    Init();
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Create(parent,id,pos,size,style,validator);
    m_width = size.GetWidth();
    m_height = size.GetHeight();
}

//以下函数实现必须写，否则会爆错误 undefined reference to 'vtable for KlineCtrl'
wxBEGIN_EVENT_TABLE(KlineCtrl, wxControl)
    EVT_PAINT(KlineCtrl::OnPaint)
//    EVT_ERASE_BACKGROUND(KlineCtrl::OnBackground)
    EVT_SIZE(KlineCtrl::OnSize)
    EVT_LEFT_DOWN(KlineCtrl::OnLeftMouseDown)
    EVT_KEY_DOWN(KlineCtrl::OnKeyDown)
//    EVT_MOUSE_EVENTS(KlineCtrl::OnMouseEvent)
wxEND_EVENT_TABLE()
wxIMPLEMENT_DYNAMIC_CLASS(KlineCtrl, wxControl)

void KlineCtrl::Init()
{
    m_share.code = wxT("");
    m_share.name = wxT("");
    m_share.market = 1;
    m_iMode = KLINE_MODE_DAY;
    m_csvPath = wxT("");
    m_klineWidth = 5;
    m_klineSpan = m_klineWidth*0.8;
    m_klineRng.begin = 0;
    m_klineRng.end = 0;
    m_curKline = -1;
    m_rectPriceMax = 0;
    m_rectPriceMin = 0;
    m_paddingTop = 10;
    m_paddingBottom = 10;
    m_paddingRight =10;
    m_crossLine = NO_CROSS_LINE;
}

bool KlineCtrl::Create(wxWindow* parent,
                      wxWindowID id,
                      const wxPoint& pos,
                      const wxSize& size,
                      long style,
                      const wxValidator& validator)
{
    if (!wxControl::Create(parent, id, pos, size, style, validator))
    {
        return false;
    }
    return true;
}

KlineCtrl::~KlineCtrl()
{

}

void KlineCtrl::SetShare(ShareBrief share)
{
    m_share = share;
}

ShareBrief KlineCtrl::GetShare() const
{
    return m_share;
}

/**
 *@param iMode int the Kline draw mode
 */
void KlineCtrl::SetMode(int iMode)
{
    if(!(iMode & (KLINE_MODES))){
        return;
    }
    m_iMode = iMode;
}

/**
 *@return int the Kline draw mode
 */
int KlineCtrl::GetMode() const
{
    return m_iMode;
}

void KlineCtrl::SetCsvPath(wxString strPath)
{
    m_csvPath = strPath;
}

wxString KlineCtrl::GetCsvPath() const
{
    return m_csvPath;
}

int KlineCtrl::GetInnerWidth()
{
    return m_width - m_paddingRight;
}

int KlineCtrl::GetInnerHeight()
{
    return m_height*0.7 - m_paddingTop - m_paddingBottom;
}

bool KlineCtrl::ReadCsv()
{
    m_klines.clear();
    wxTextFile file;
    if(!file.Open(m_csvPath)){
        return false;
    }
    // neglect first line
    for(size_t i=file.GetLineCount()-1; i>=1;i--)
    {
        wxString line = file[i];
        wxVector<wxString> fields = slice(line);
        KlineItem item;
        item.day = fields[0];
        fields[6].ToDouble(&item.price_open);
        fields[3].ToDouble(&item.price_close);
        fields[4].ToDouble(&item.price_max);
        fields[5].ToDouble(&item.price_min);
        fields[8].ToDouble(&item.change_amount);//涨跌额
        fields[9].ToDouble(&item.change_rate);//涨跌幅
        fields[11].ToDouble(&item.trade_volume);//成交量
        fields[12].ToDouble(&item.trade_amount);//成交额
        item.favorite = 0;
        item.danger = 0 ;
        item.price_now = item.price_close;
        m_klines.push_back(item);
    }
    return true;
}

/**
 * @func 绘制日K线的函数
 * @param wxDC pDC 绘制设备上下文
 * @param nKLine 第几个日K线
 * @param visibleKLineCount 总共需要显示日K线总数
 * @param float price_open 当日开盘价
 * @param float price_close 当日收盘价
 * @param float price_max 当日最高价
 * @param float price_min 当日最低价
 * @param float rect_price_max 绘制K线的最高价(最高的上影线)
 * @param float rect_price_min 绘制K线的最低价(最低的下影线)
 * @param int minX 绘制区域左上角X坐标
 * @param int minY 绘制区域左上角Y坐标
 * @param int maxX 绘制区域右下角X坐标
 * @param int maxY 绘制区域右下角Y坐标
 * @param int kLineWidth K线实体的宽度(包含K线之间的间隙)
 * @param int kLineSpan  K线实体之间的间隙
 * @author code lighter
 * @date 2019/8/20
 */
void KlineCtrl::DrawKline(wxDC* pDC,int nKLine,int visibleKLineCount,
              float price_open,float price_close,
              float price_max,float price_min,
              float rect_price_max,float rect_price_min,
              int minX,int minY,int maxX,int maxY,int klineWidth,int klineSpan)
{
    double hPrice = rect_price_max - rect_price_min;
    int hRect = maxY - minY;
    int wRect = maxX - minX;
    double x1,y1,x2,y2;
    double xShadow,yShadowUp,yShadowDown;//上影线,下影线(如果有的话)
    if(visibleKLineCount > wRect){
        if(price_open < price_close) //红盘
        {
            //绘制K线实体
            x1 = nKLine*wRect/visibleKLineCount; // nKLine/visibleKLineCount = x1/wRect;
            y1 = (rect_price_max - price_close)/hPrice*hRect + minY;
            x2 = x1;
            y2 = (rect_price_max - price_open)/hPrice*hRect + minY;
            pDC->SetPen(*wxRED_PEN);
            pDC->SetBrush(*wxBLACK_BRUSH);
            pDC->DrawLine(x1,y1,x2,y2);
            //绘制上影线
            xShadow = x1;
            yShadowUp = (rect_price_max - price_max)/hPrice*hRect + minY;
            pDC->DrawLine(xShadow,yShadowUp,xShadow,y1);
            //绘制下影线
            yShadowDown = (rect_price_max - price_min)/hPrice*hRect + minY;
            pDC->DrawLine(xShadow,yShadowDown,xShadow,y2-1);
        }
        else if(price_open >price_close)  //绿盘
        {
            x1 = nKLine*wRect/visibleKLineCount; // nKLine/visibleKLineCount = x1/wRect;
            y1 = (rect_price_max - price_open)/hPrice*hRect+minY;
            x2 = x1;
            y2 = (rect_price_max - price_close)/hPrice*hRect+minY;
            pDC->SetPen(wxPen(wxColor(84,255,255)));
            pDC->SetBrush(wxBrush(wxColor(84,255,255)));
            pDC->DrawLine(x1,y1,x2,y2);
            //绘制上影线
            xShadow = x1;
            yShadowUp = (rect_price_max - price_max)/hPrice*hRect + minY;
            pDC->DrawLine(xShadow,yShadowUp,xShadow,y1);
            //绘制下影线
            yShadowDown = (rect_price_max - price_min)/hPrice*hRect + minY;
            pDC->DrawLine(xShadow,yShadowDown,xShadow,y2-1);
        }
    }else{
        if(price_open < price_close) //红盘
        {
            //绘制K线实体
            x1 = nKLine*(klineWidth+klineSpan);
            y1 = (rect_price_max - price_close)/hPrice*hRect + minY;
            x2 = x1+klineWidth;
            y2 = (rect_price_max - price_open)/hPrice*hRect + minY;
            pDC->SetPen(*wxRED_PEN);
            pDC->SetBrush(*wxBLACK_BRUSH);
            pDC->DrawRectangle(x1,y1,x2-x1,y2-y1);
            //绘制上影线
            xShadow = (x1+x2)/2;
            yShadowUp = (rect_price_max - price_max)/hPrice*hRect + minY;
            pDC->DrawLine(xShadow,yShadowUp,xShadow,y1);
            //绘制下影线
            yShadowDown = (rect_price_max - price_min)/hPrice*hRect + minY;
            pDC->DrawLine(xShadow,yShadowDown,xShadow,y2-1);
    //        cout<<"x1,y1,w1,h1  "<<x1<<","<<y1<<","<<x2-x1<<","<<y2-y1<<endl;
        }
        else if(price_open >price_close)  //绿盘
        {
            x1 = nKLine*(klineWidth+klineSpan);
            y1 = (rect_price_max - price_open)/hPrice*hRect+minY;
            x2 = x1+klineWidth;
            y2 = (rect_price_max - price_close)/hPrice*hRect+minY;
            pDC->SetPen(wxPen(wxColor(84,255,255)));
            pDC->SetBrush(wxBrush(wxColor(84,255,255)));
            pDC->DrawRectangle(x1,y1,x2-x1,y2-y1);
            //绘制上影线
            xShadow = (x1+x2)/2;
            yShadowUp = (rect_price_max - price_max)/hPrice*hRect + minY;
            pDC->DrawLine(xShadow,yShadowUp,xShadow,y1);
            //绘制下影线
            yShadowDown = (rect_price_max - price_min)/hPrice*hRect + minY;
            pDC->DrawLine(xShadow,yShadowDown,xShadow,y2-1);
    //        cout<<"x2,y2,w2,h2  "<<x1<<","<<y1<<","<<x2-x1<<","<<y2-y1<<endl;
        }
    }
    //考虑跌停
    //考虑涨停
}

wxVector<KlineItem> KlineCtrl::GetWeekKlines()
{
    if(m_weekKlines.empty()){
        // calc week klines;
    }
    return m_weekKlines;
}

wxVector<KlineItem> KlineCtrl::GetMonthKlines()
{
    if(m_monthKlines.empty()){
        // calc month klines;
    }
    return m_monthKlines;
}



/**
 * @func 绘制十字线
 * @param wxDC* pDC 设备绘制上下文
 * @param int centerX 十字线中心X坐标
 * @param int centerY 十字线中心Y坐标
 * @param int w 控件宽度
 * @param int h 控件高度
 * @author code lighter
 */
void KlineCtrl::DrawCrossLine(wxDC* pDC,int centerX,int centerY,int w,int h)//光标十字线
{
    pDC->SetPen(wxPen(wxColor(255,255,255)));
    pDC->DrawLine(0,centerY,w,centerY); //横线
    pDC->DrawLine(centerX,0,centerX,h); //竖线
}

/**
 *@func 获取日K线最低价
 *@param vector<KlineItem> data 日K线数据
 *@param int begin 开始位置
 *@param int end 结束位置
 *@author code lighter
 */
float KlineCtrl::GetRectMinPrice(wxVector<KlineItem>& data,int begin, int end)
{
    float min = 100000000;
    for(int i=begin; i<=end; i++)
    {
        if(data.at(i).price_min < min)
        {
            min = data.at(i).price_min;
        }
    }
    m_rectPriceMin = min;
    return min;
}

/**
 *@func 获取日K线最高价
 *@param vector<KlineItem> data 日K线数据
 *@param int begin 开始位置
 *@param int end 结束位置
 *@author code lighter
 */
float KlineCtrl::GetRectMaxPrice(wxVector<KlineItem>& data,int begin, int end)
{
    float max = -100000000;
    for(int i=begin; i<=end; i++)
    {
        if(data.at(i).price_max > max)
        {
            max = data.at(i).price_max;
        }
    }
    m_rectPriceMax = max;
    return max;
}

/**
 *@func 获取K线的范围
 *@param long totalKLines //总共的K线数
 *@param long rect 容器的宽度
 *@param int16_t klineWidth 日K线的宽度
 *@param int16_t klineSpan 日K线的间距
 *@param long crossLine 十字线所在位置
 *@return KlineRange
 *@author code lighter
 */
KlineRange  KlineCtrl::GetKlineRangeZoomIn(long totalKlines, long rect,
                          int16_t klineWidth,int16_t klineSpan,
                          long crossLine)
{
    KlineRange rng;
    long count = rect/(klineWidth+klineSpan);
    if(count>totalKlines){
        count = totalKlines-1;
    }
    if(crossLine != NO_CROSS_LINE){
        long left = crossLine - m_klineRng.begin;
        long right = m_klineRng.end - crossLine;
        long removed = abs(left+right - count);
        if(count > left+right){ // more klines to be shown
            rng.begin = m_klineRng.begin - removed*left/(left+right);
            rng.end = m_klineRng.end + removed*right/(left+right);
        }else{ // less klines to be shown
            rng.begin = m_klineRng.begin + removed*left/(left+right);
            rng.end = m_klineRng.end - removed*right/(left+right);
        }
    }else{
        rng.begin = totalKlines-1 - count;
        rng.end = totalKlines-1;
    }

    return rng;
}

/**
 * @func 根据 十字线 位置，计算缩小查看的日K线可视范围
 * @param int
 */
KlineRange  KlineCtrl::GetKlineRangeZoomOut(long totalKLines,long crossLine)
{
    KlineRange rng;
    if(crossLine != NO_CROSS_LINE){
        long left = crossLine - m_klineRng.begin;
        long right = m_klineRng.end - crossLine;
        rng.begin = m_klineRng.begin - 360 * left/(left+right);
        rng.end = m_klineRng.end + 360 * right/(left+right);
    }else{
        rng.begin = m_klineRng.begin-360;
        rng.end = m_klineRng.end;
    }
    if(rng.begin <=0){
        rng.begin = 0;
    }
    if(rng.end >= totalKLines-1){
        rng.end = totalKLines-1;
    }
    return rng;
}


/**
 * @func 获取第N条日K线的十字线位置
 * @param long n 从左往右数第N条K线
 * @param return wxPoint
 * @author code lighter
 */
wxPoint KlineCtrl::GetCrossLinePt(long n)
{
    double x,y;
    long total = m_klineRng.end - m_klineRng.begin;
    KlineItem item = m_klines.at(n);
    double hPrice = m_rectPriceMax - m_rectPriceMin;
    y = m_paddingTop+(1-(item.price_close-m_rectPriceMin)/hPrice)*GetInnerHeight();
    if(total > m_width){//一屏幕已经显示不下了
        x = (n-m_klineRng.begin)/total*m_width;
    }else{
        x = (m_klineWidth+m_klineSpan)*(n - m_klineRng.begin)+m_klineWidth/2;
    }
    return wxPoint(x,y);
}

//event callback functions
void KlineCtrl::OnPaint(wxPaintEvent& event)
{
    //自动双缓冲，如果系统默认支持双缓冲，会调用系统，否则使用位图实现，
     //必须在 Create之前调用 SetBackgroundStyle(wxBG_STYLE_PAINT);
    wxAutoBufferedPaintDC dc(this);
    //绘制黑色背景
    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();
    float rect_price_max = GetRectMaxPrice(m_klines,m_klineRng.begin,m_klineRng.end);
    float rect_price_min = GetRectMinPrice(m_klines,m_klineRng.begin,m_klineRng.end);
    int visible_klines = m_klineRng.end - m_klineRng.begin +1;
    int nDay=0;

    KlineItem day;
    if(m_klines.size()>(size_t)m_klineRng.end)
    {
        for(int i=m_klineRng.begin; i<=m_klineRng.end; i++)
        {
            day = m_klines.at(i);
            DrawKline(&dc,nDay,visible_klines,day.price_open,day.price_close,
                         day.price_max,day.price_min,
                         rect_price_max,rect_price_min,0,m_paddingTop,GetInnerWidth(),
                         GetInnerHeight(),m_klineWidth,m_klineSpan);
            nDay++;
        }
        // draw volume bar
        m_pVolumeBar->OnDraw(&dc);
        DrawCrossLine(&dc,m_crossLinePt.x,m_crossLinePt.y,m_width,m_height*0.7);
        m_pInfoToolbar->OnDraw(&dc);
    }
}

void KlineCtrl::OnBackground(wxEraseEvent& event)
{
	wxClientDC * clientDC = NULL;
	if(!event.GetDC())
        clientDC = new wxClientDC(this);
	wxDC* dc = clientDC ? clientDC : event.GetDC();
	dc->SetBrush(wxBrush(wxColour(0,0,0)));
	wxSize sz = GetClientSize();
	dc->DrawRectangle(wxRect(0,0,sz.x,sz.y));
	dc->SetBrush(wxNullBrush);
	if (clientDC)
        wxDELETE(clientDC);
}

void KlineCtrl::OnSize(wxSizeEvent& event)
{
    GetClientSize(&m_width,&m_height);
    m_klineRng = GetKlineRangeZoomIn(m_klines.size(),m_width,m_klineWidth,m_klineSpan);
    Refresh();//刷新窗口
}

void KlineCtrl::OnKeyDown(wxKeyEvent& event)
{
    int max = m_klines.size();
    int key = event.GetKeyCode();
    if(key == WXK_LEFT){ // look left
        if(m_klineRng.begin == 0){// no more klines in the left
            return;
        }
        if(m_crossLine == m_klineRng.begin){
            m_klineRng.begin-=1;
            m_klineRng.end-=1;
        }else if(m_crossLine >= m_klineRng.begin && m_crossLine <= m_klineRng.end){
            if(m_crossLine != 0){
                m_crossLine -= 1;
                m_crossLinePt = GetCrossLinePt(m_crossLine);
            }
        }
    }else if(key == WXK_RIGHT){// look right
        if(m_crossLine == m_klineRng.end && m_klineRng.end != max){
            m_klineRng.begin+=1;
            m_klineRng.end+=1;
        }else if(m_crossLine >= m_klineRng.begin && m_crossLine <= m_klineRng.end){
            if(m_crossLine != max-1){
                m_crossLine += 1;
                m_crossLinePt = GetCrossLinePt(m_crossLine);
            }
        }
    }else if(key == WXK_UP){ //scale up klines
        if(m_crossLine != NO_CROSS_LINE &&
           m_crossLine <= m_klineRng.begin &&
           m_crossLine >= m_klineRng.end){ //以十字线为中心放大
            long left = m_crossLine - m_klineRng.begin;
            long right = m_klineRng.end - m_crossLine;
            long old_begin = m_klineRng.begin;
            long old_end = m_klineRng.end;
            int count = m_klineRng.end - m_klineRng.begin+1;
            if((count-360)>m_width){
                m_klineRng.begin -= 360*left/(left+right);
                m_klineRng.end += 360*right/(left+right);
            }else{
                m_klineWidth+=2;
                m_klineSpan+=1;
                if(m_klineWidth >31){
                    m_klineWidth -=2;
                    m_klineSpan -=1;
                }
                m_klineRng = GetKlineRangeZoomIn(max,m_width,m_klineWidth,m_klineSpan);
                long removed = left + right - (m_klineRng.end - m_klineRng.begin);
                m_klineRng.begin = old_begin - removed*left/(left+right);
                m_klineRng.end = old_end + removed*right/(left+right);
            }

            if(m_crossLine != NO_CROSS_LINE){
                if(m_crossLine <= m_klineRng.begin && m_crossLine >= m_klineRng.end){
                     m_crossLinePt = GetCrossLinePt(m_crossLine);//修正十字线的位置
                }
            }

        }else{
            int count = m_klineRng.end - m_klineRng.begin+1;
            if((count-360)>m_width){
                m_klineRng.end -= 360;
            }else{
                m_klineWidth+=2;
                m_klineSpan+=1;
                if(m_klineWidth >31){
                    m_klineWidth -=2;
                    m_klineSpan -=1;
                }
                m_klineRng = GetKlineRangeZoomIn(max,m_width,m_klineWidth,m_klineSpan);
            }
        }
    }else if(event.GetKeyCode() == WXK_DOWN){ // scale down klines
        if(m_crossLine != NO_CROSS_LINE &&
           m_crossLine <= m_klineRng.begin &&
           m_crossLine >= m_klineRng.end){ //以十字线为中心缩小
            if(m_klineWidth == 1 && m_klineSpan == 0){
                m_klineRng = GetKlineRangeZoomOut(max,m_crossLine);
            }else{
                m_klineWidth-=2;
                m_klineSpan-=1;
                if(m_klineWidth<1){
                    m_klineWidth =1;
                }
                if(m_klineSpan<0){
                    m_klineSpan = 0;
                }
                m_klineRng = GetKlineRangeZoomIn(max,m_width,m_klineWidth,m_klineSpan,m_crossLine);
            }
        }else{
            if(m_klineWidth == 1 && m_klineSpan == 0){
                m_klineRng = GetKlineRangeZoomOut(max);
            }else{
                m_klineWidth-=2;
                m_klineSpan-=1;
                if(m_klineWidth<1){
                    m_klineWidth =1;
                }
                if(m_klineSpan<0){
                    m_klineSpan = 0;
                }
                m_klineRng = GetKlineRangeZoomIn(max,m_width,m_klineWidth,m_klineSpan);
            }
        }
    }
    if(m_klineRng.begin <= 0){
        m_klineRng.begin = 0;
    }
    if(m_klineRng.end >= max-1){
        m_klineRng.end = max-1;
    }
    if(m_crossLine != NO_CROSS_LINE){
        if(m_crossLine >= m_klineRng.begin && m_crossLine <= m_klineRng.end){
             m_crossLinePt = GetCrossLinePt(m_crossLine);//修正十字线的位置
        }
    }
    this->Refresh(false);
}

void KlineCtrl::OnLeftMouseDown(wxMouseEvent& event)
{
    if(event.LeftIsDown()){ //左键按下
        long x,y;
        event.GetPosition(&x,&y);
        if(this->m_klineWidth == 1){
            m_crossLinePt.x = x;
            m_crossLinePt.y = y;
            m_crossLine = m_klineRng.begin + x*(m_klineRng.end - m_klineRng.begin)/m_width;
        }else{ //获取最靠近的K线
            int k = x/(m_klineWidth+m_klineSpan);
            m_crossLine = m_klineRng.begin + k;
            m_crossLinePt = GetCrossLinePt(m_crossLine);
        }
        this->Refresh(false);
    }
}
