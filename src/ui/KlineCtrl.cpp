#include "KLineCtrl.h"

KlineCtrl::KlineCtrl()
{
    Init();
}

KlineCtrl::KlineCtrl(wxString strShareCode,wxWindow* parent,wxWindowID id)
{
    Init();
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Create(parent,id);
    SetCsvPath(getExecDir()+strShareCode+_T(".csv"));
    ReadCsv();
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

bool KlineCtrl::ReadCsv()
{
    m_klines.clear();
    wxTextFile file;
    if(!file.Open(m_csvPath)){
        return false;
    }
    // neglect first line
    for(size_t i=1; i<file.GetLineCount(); i++)
    {
        wxString line = file[i];
        wxVector<wxString> fields = slice(line);
        KlineItem item;
        item.day = fields[0];
        fields[6].ToDouble(&item.price_open);
        fields[3].ToDouble(&item.price_close);
        fields[4].ToDouble(&item.price_max);
        fields[5].ToDouble(&item.price_min);
        fields[9].ToDouble(&item.change_rate);//涨跌额
        fields[8].ToDouble(&item.change_amount);//涨跌幅
        fields[11].ToDouble(&item.trade_amount);//成交额
        fields[10].ToDouble(&item.trade_volume);//成交量
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
    float hPrice = rect_price_max - rect_price_min;
    int hRect = maxY - minY;
    int wRect = maxX - minX;
    int x1,y1,x2,y2;
    int xShadow,yShadowUp,yShadowDown;//上影线,下影线(如果有的话)
    if(visibleKLineCount > wRect){
        if(price_open < price_close) //红盘
        {
            //绘制K线实体
            x1 = nKLine*wRect/visibleKLineCount; // nKLine/visibleKLineCount = x1/wRect;
            y1 = (int)((rect_price_max - price_close)/hPrice*hRect + minY);
            x2 = x1;
            y2 = (int)((rect_price_max - price_open)/hPrice*hRect + minY);
            pDC->SetPen(*wxRED_PEN);
            pDC->SetBrush(*wxBLACK_BRUSH);
            pDC->DrawLine(x1,y1,x2,y2);
            //绘制上影线
            xShadow = x1;
            yShadowUp = static_cast<int>((rect_price_max - price_max)/hPrice*hRect + minY);
            pDC->DrawLine(xShadow,yShadowUp,xShadow,y1);
            //绘制下影线
            yShadowDown = static_cast<int>((rect_price_max - price_min)/hPrice*hRect + minY);
            pDC->DrawLine(xShadow,yShadowDown,xShadow,y2-1);
        }
        else if(price_open >price_close)  //绿盘
        {
            x1 = nKLine*wRect/visibleKLineCount; // nKLine/visibleKLineCount = x1/wRect;
            y1 = (int)((rect_price_max - price_open)/hPrice*hRect+minY);
            x2 = x1;
            y2 = (int)((rect_price_max - price_close)/hPrice*hRect+minY);
            pDC->SetPen(wxPen(wxColor(84,255,255)));
            pDC->SetBrush(wxBrush(wxColor(84,255,255)));
            pDC->DrawLine(x1,y1,x2,y2);
            //绘制上影线
            xShadow = x1;
            yShadowUp = static_cast<int>((rect_price_max - price_max)/hPrice*hRect + minY);
            pDC->DrawLine(xShadow,yShadowUp,xShadow,y1);
            //绘制下影线
            yShadowDown = static_cast<int>((rect_price_max - price_min)/hPrice*hRect + minY);
            pDC->DrawLine(xShadow,yShadowDown,xShadow,y2-1);
        }
    }else{
        if(price_open < price_close) //红盘
        {
            //绘制K线实体
            x1 = (int)(nKLine*(klineWidth+klineSpan));
            y1 = (int)((rect_price_max - price_close)/hPrice*hRect + minY);
            x2 = (int)(x1+klineWidth);
            y2 = (int)((rect_price_max - price_open)/hPrice*hRect + minY);
            pDC->SetPen(*wxRED_PEN);
            pDC->SetBrush(*wxBLACK_BRUSH);
            pDC->DrawRectangle(x1,y1,x2-x1,y2-y1);
            //绘制上影线
            xShadow = static_cast<int>((x1+x2)/2);
            yShadowUp = static_cast<int>((rect_price_max - price_max)/hPrice*hRect + minY);
            pDC->DrawLine(xShadow,yShadowUp,xShadow,y1);
            //绘制下影线
            yShadowDown = static_cast<int>((rect_price_max - price_min)/hPrice*hRect + minY);
            pDC->DrawLine(xShadow,yShadowDown,xShadow,y2-1);
    //        cout<<"x1,y1,w1,h1  "<<x1<<","<<y1<<","<<x2-x1<<","<<y2-y1<<endl;
        }
        else if(price_open >price_close)  //绿盘
        {
            x1 = (int)(nKLine*(klineWidth+klineSpan));
            y1 = (int)((rect_price_max - price_open)/hPrice*hRect+minY);
            x2 = (int)(x1+klineWidth);
            y2 = (int)((rect_price_max - price_close)/hPrice*hRect+minY);
            pDC->SetPen(wxPen(wxColor(84,255,255)));
            pDC->SetBrush(wxBrush(wxColor(84,255,255)));
            pDC->DrawRectangle(x1,y1,x2-x1,y2-y1);
            //绘制上影线
            xShadow = static_cast<int>((x1+x2)/2);
            yShadowUp = static_cast<int>((rect_price_max - price_max)/hPrice*hRect + minY);
            pDC->DrawLine(xShadow,yShadowUp,xShadow,y1);
            //绘制下影线
            yShadowDown = static_cast<int>((rect_price_max - price_min)/hPrice*hRect + minY);
            pDC->DrawLine(xShadow,yShadowDown,xShadow,y2-1);
    //        cout<<"x2,y2,w2,h2  "<<x1<<","<<y1<<","<<x2-x1<<","<<y2-y1<<endl;
        }
    }
    //考虑跌停
    //考虑涨停
}

void KlineCtrl::DrawAnalysisBar(wxDC* pDC)
{
    switch(m_analysisType){
    case 1: // Draw volume Bar
        {
            //int maxVolume = GetMaxVolume();
        }
    default:
        break;
    }
}

double KlineCtrl::GetMaxVolume()
{
    double max = 0;
    wxVector<KlineItem>::const_iterator it;
    for(it = m_klines.begin(); it != m_klines.end(); ++it)
    {
        if(it->trade_volume > max)
        {
            max = it->trade_volume;
        }
    }
    return max;
}

/**********************************
 *@para member KlineItem 数据成员  1:trade_volume,2:trade_amount
 *@para KlineType 1:day,2:week,3:month
 **********************************/
double KlineCtrl::GetMaxValue(int member, int klineType)
{
    return 0;
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
    for(int i=begin; i>end; i--)
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
    for(int i=begin; i>end; i--)
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
KlineRange  KlineCtrl::GetKlineRangeZoomIn(long totalKLines, long rect,
                          int16_t klineWidth,int16_t klineSpan,
                          long crossLine)//放大K线图
{
    KlineRange rng;
    long count = rect/(klineWidth+klineSpan);
    if(count>totalKLines){
        count = totalKLines;
    }
    if(crossLine != NO_CROSS_LINE){
        long left = m_klineRng.begin - crossLine;
        long right = crossLine - m_klineRng.end;
        long removed = abs(left+right - count);
        if(count > left+right){ //K线变多了
            rng.begin = m_klineRng.begin + removed*left/(left+right);
            rng.end = m_klineRng.end - removed*right/(left+right);
        }else{ //K线变少了
            rng.begin = m_klineRng.begin - removed*left/(left+right);
            rng.end = m_klineRng.end + removed*right/(left+right);
        }
    }else{
        rng.begin = count;
        rng.end = 0;
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
        long left = m_klineRng.begin - crossLine;
        long right = crossLine - m_klineRng.end;
        rng.begin = m_klineRng.begin + 360 * left/(left+right);
        rng.end = m_klineRng.end - 360 * right/(left+right);
    }else{
        rng.begin = m_klineRng.begin+360;
        rng.end = m_klineRng.end;
    }
    if(rng.begin >= totalKLines){
        rng.begin = totalKLines-1;
    }
    if(rng.end <=0){
        rng.end = 0;
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
    long x,y;
    long total = m_klineRng.begin - m_klineRng.end;
    KlineItem item = m_klines.at(n);
    float hPrice = m_rectPriceMax - m_rectPriceMin;
    y = (int)((m_rectPriceMax - item.price_close)/hPrice*(m_height-20)+ 10);
    if(total > m_width){//一屏幕已经显示不下了
        x = (m_klineRng.begin-n)/total*m_width;
    }else{
        x = (m_klineWidth+m_klineSpan)*(m_klineRng.begin - n)+m_klineWidth/2;
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
    int visible_klines = m_klineRng.begin - m_klineRng.end +1;
    int nDay=0;

    KlineItem day;
    if(m_klines.size()>(size_t)m_klineRng.begin)
    {
        for(int i=m_klineRng.begin; i>=m_klineRng.end; i--)
        {
            day = m_klines.at(i);
            DrawKline(&dc,nDay,visible_klines,day.price_open,day.price_close,
                         day.price_max,day.price_min,
                         rect_price_max,rect_price_min,0,10,m_width,
                         m_height-20,m_klineWidth,m_klineSpan);
            nDay++;
        }
        DrawCrossLine(&dc,m_crossLinePt.x,m_crossLinePt.y,m_width,m_height-20);
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
    wxSize sizeClient= this->GetParent()->GetClientSize();
    this->SetClientSize(sizeClient);
    this->Refresh(false);//刷新窗口
}

void KlineCtrl::OnKeyDown(wxKeyEvent& event)
{
    int max = m_klines.size();
    int key = event.GetKeyCode();
    if(key == KEY_LEFT){//左移查看
        if(m_klineRng.begin == max-1){
            return;
        }
        if(m_crossLine == m_klineRng.begin){
            m_klineRng.begin+=1;
            m_klineRng.end+=1;
        }else if(m_crossLine >= m_klineRng.end && m_crossLine <= m_klineRng.begin){//重新计算十字线
            if(m_crossLine != max-1){
                m_crossLine += 1;
                m_crossLinePt = GetCrossLinePt(m_crossLine);
            }
        }
    }else if(key == KEY_RIGHT){//向右查看
        if(m_crossLine == m_klineRng.end && m_klineRng.end !=0){//如果右侧还有K线才向右执行
            m_klineRng.begin-=1;
            m_klineRng.end-=1;
        }else if(m_crossLine >= m_klineRng.end && m_crossLine <= m_klineRng.begin){
            if(m_crossLine !=0){
                m_crossLine -= 1;
                m_crossLinePt = GetCrossLinePt(m_crossLine);
            }
        }
    }else if(key == KEY_UP){ //放大K线图
        if(m_crossLine != NO_CROSS_LINE &&
           m_crossLine <= m_klineRng.begin &&
           m_crossLine >= m_klineRng.end){ //以十字线为中心放大
            long left = m_klineRng.begin - m_crossLine;
            long right = m_crossLine - m_klineRng.end;
            long old_begin = m_klineRng.begin;
            long old_end = m_klineRng.end;
            int count = m_klineRng.begin - m_klineRng.end+1;
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
                long removed = left + right - (m_klineRng.begin - m_klineRng.end);
                m_klineRng.begin = old_begin - removed*left/(left+right);
                m_klineRng.end = old_end + removed*right/(left+right);
            }

            if(m_crossLine != NO_CROSS_LINE){
                if(m_crossLine <= m_klineRng.begin && m_crossLine >= m_klineRng.end){
                     m_crossLinePt = GetCrossLinePt(m_crossLine);//修正十字线的位置
                }
            }

        }else{
            int count = m_klineRng.begin - m_klineRng.end+1;
            if((count-360)>m_width){
                m_klineRng.begin -= 360;
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
        std::cout<<"++++++++ crossLine "<<m_crossLine << " ++++++++++"<<std::endl;
    }else if(event.GetKeyCode() == KEY_DOWN){ //缩小K线图
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
                if(m_klineRng.begin>max){
                    m_klineRng.begin = max;
                }
                if(m_klineRng.end<=0){
                    m_klineRng.end = 0;
                }
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
                if(m_klineRng.begin>max){
                    m_klineRng.begin = max;
                }
                if(m_klineRng.end<=0){
                    m_klineRng.end = 0;
                }
            }
        }
        if(m_crossLine != NO_CROSS_LINE){
            if(m_crossLine <= m_klineRng.begin && m_crossLine >= m_klineRng.end){
                 m_crossLinePt = GetCrossLinePt(m_crossLine);//修正十字线的位置
            }
        }
        std::cout<<"--------- crossLine "<<m_crossLine << " ----------"<<std::endl;
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
            m_crossLine = m_klineRng.begin - x*(m_klineRng.begin - m_klineRng.end)/m_width;
        }else{ //获取最靠近的K线
            int k = x/(m_klineWidth+m_klineSpan);
            m_crossLine = m_klineRng.begin-k;
            m_crossLinePt = GetCrossLinePt(m_crossLine);
        }
        std::wcout<<"鼠标左键被按下....."<<std::endl;
        this->Refresh(false);
    }
}
