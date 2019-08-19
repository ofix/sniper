#ifndef STOCKITEM_H
#define STOCKITEM_H
#include <wx/longlong.h>


#define MARKET_NAME_ZH(i) ((i==1)?_T("沪市"):((i==2)?_T("深市"):_T("创业板")))
#define MARKET_NAME_EN(i) ((i==1)?_T("SHANG HAI"):((i==2)?_T("SHEN ZHEN"):_T("CHUAN YE BAN")))

struct ShareBrief
{
    wxString code; //stock code
    wxString name; //stock name
    short market;  //stock original market, 1 - SHANG HAI,2 -SHEN ZHEN,3 - CHUAN YE BAN
};

struct StockItem
{
   wxString code; // stock code
   wxString name; // stock name
   wxLongLong market_value; // stock market value
   wxInt8 danger; // 0:no danger 1:normal danger 2: damage danger
   bool watch; // 0:not in watch 1:in watch
   float price_open;
   float price_close;
   float price_now;
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
