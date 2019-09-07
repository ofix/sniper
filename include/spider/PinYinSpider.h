#ifndef PINYINSPIDER_H
#define PINYINSPIDER_H
#include "Spider.h"

class PinYinSpider:public Spider
{
    public:
        PinYinSpider(wxString strUrl=wxT("http://xh.5156edu.com/page/z1792m6697j19744.html"));
        virtual ~PinYinSpider();
        virtual bool Run();
    protected:

};

#endif // PINYINSPIDER_H
