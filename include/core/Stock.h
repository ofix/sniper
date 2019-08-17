#ifndef STOCKITEM_H
#define STOCKITEM_H
#include <wx/longlong.h>

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

#endif // STOCKITEM_H
