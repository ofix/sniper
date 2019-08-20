#ifndef STOCKITEM_H
#define STOCKITEM_H
#include <wx/longlong.h>


#define MARKET_NAME_ZH(i) ((i==1)?_T("沪市"):((i==2)?_T("深市"):_T("创业板")))
#define MARKET_NAME_EN(i) ((i==1)?_T("SHANG HAI"):((i==2)?_T("SHEN ZHEN"):_T("CHUAN YE BAN")))
#define MARKET_SHANG_HAI 1
#define MARKET_SHEN_ZHEN 2
#define MARKET_CHUAN_YE_BAN 3

struct ShareBrief
{
    wxString code; //stock code
    wxString name; //stock name
    short market;  //stock original market, 1 - SHANG HAI,2 -SHEN ZHEN,3 - CHUAN YE BAN
};

// for k line drawing
struct KlineRange{
    int begin; // beginning position of K lines
    int end;   // end position of K Lines
};

struct KlineItem
{
   wxString day; //日期
   wxString code; // share code
   wxString name; // share name
   double market_cap; // share market value
   double change_rate; //涨跌幅
   double change_amount; //涨跌额
   double trade_volume; //成交量
   double trade_amount; //成交额
   double price_open; //开盘价
   double price_close; //收盘价
   double price_max; //最高价
   double price_min; //最低价
   double price_now; //当前实时价
   wxInt8 danger; // 1:security 2:warning 3: danger 4: damage
   wxInt8 favorite; // 0:not favorite 1:favorite
};

struct ShareItem
{
    wxString code; //代码
    wxString name; //名称
    double price; //当前价格
    double change_percent; //涨跌幅
    double change; //涨跌额
    double to; //成交金额 turnover
    double qr; //量比 quantity relative
    double pe; //市盈率 price earnings ratio (P/E ratio)
    double pb; //市净率 price net asset ratio (PBR)
    double roe; //净资产收益率 return on equity
};

#endif // STOCKITEM_H
