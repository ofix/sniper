#ifndef PINYINSPIDER_H
#define PINYINSPIDER_H
#include "Spider.h"

class gbkRawPacket{
    public:
    uint32_t index;
    std::string zh_char;
    std::string pinyin_full;
    std::string pinyin_1;
    std::string pinyin_2;
    std::string pinyin_3;
    std::string pinyin_4;
    std::string pinyin_5;
    std::string pinyin_6;
};

class PinYinSpider:public Spider
{
    public:
        PinYinSpider(wxString strUrl=wxT("http://xh.5156edu.com/page/z1792m6697j19744.html"));
        virtual ~PinYinSpider();
        virtual bool Run();
    protected:
        std::vector<gbkRawPacket> m_pinyin;
};

#endif // PINYINSPIDER_H
