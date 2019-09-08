#ifndef PINYIN_H
#define PINYIN_H

#include <string>
#include <map>
#include <util/Helper.h>

class gbkRawPacket{
    public:
    uint32_t gbk_index;
    std::string zh_char;
    std::string pinyin_full;
    std::string pinyin_1;
    std::string pinyin_2;
    std::string pinyin_3;
    std::string pinyin_4;
    std::string pinyin_5;
    std::string pinyin_6;
};

struct gbkCompare {
  bool operator() (const std::string& lhs, const std::string& rhs) const
  {
      wxCSConv gbkConv(wxFONTENCODING_CP936);
      std::string gbk_lhs(gbkConv.cWX2MB(wxString(lhs)));
      std::string gbk_rhs(gbkConv.cWX2MB(wxString(rhs)));
      return gbk_lhs<gbk_rhs;
  }
};

// 汉字转拼音要考虑字符的编码是GB2312,GBK,还是utf8,
// utf-8编码和字符集字符序号的对应关系
/***********************************
 * 0x0000 - 0x007F       0xxxxxxx
 * 0x0080 - 0x07FF       110yyyxx 10xxxxxx
 * 0x0800 - 0xFFFF       1110yyyy 10yyyyxx 10xxxxxx
 * 0x100000 - 0x10FFFF   11110zzz 10zzyyyy 10yyyyxx 10xxxxxx
 ***********************************/

 /************************************************
  *@class PinYin
  *@note
  * usage 1:
  * ```cpp
  * PinYin py;
  * std::string pinying = py.Full(wxString(wxT("*ST雏鹰")));
  * std::string pinying = py.Full(std::string("*ST雏鹰"));
  ************************************************/
class PinYin
{
public:
    PinYin();
    ~PinYin();
    std::string Full(std::string strChinese);// utf8 format
    std::string Full(wxString strChinese);// utf8 format
    std::string FirstLetter(std::string strChinese); // utf8 format
    std::string FirstLetter(wxString strChinese); // utf8 format
protected:
    std::string Convert(wxString strChinese,bool bFirstLetter=false);
    bool GenerateMapFile(wxString strFileName = getExecDir()+wxT("GBK汉字拼音对照表.csv"));
    bool GenerateMapFileEx(wxString strFileName = getExecDir()+wxT("GBK汉字拼音对照表.csv"));
private:
    static std::map<std::string,std::string> m_pinyin;
};

#endif // PINYIN_H
