#ifndef PINYIN_H
#define PINYIN_H

#include <wx/string.h>
#include <wx/except.h>
#include <string>
#include <map>
#include <vector>
/**
 *\brief 编译器对代码文件中的字符如何进行处理
 * please visit link (https://www.cnblogs.com/jiangxueqiao/archive/2017/09/01/7464408.html)
 * 第1步：预处理
 * 1 读取源文件，判断源文件采用的字符编码类型。(这一步不会改变文件内容)
 * 编译器判断源文件编码类型的步骤为：
 * 1.1 若文件开始处有BOM(EF BB BF)，则判定为UTF-8编码；
 * 1.2 若没有BOM，则试图从文件的前8个字节来判断文件是否像UTF-16编码，如果像，则就判断为UTF-16编码。
 * 1.3 如果既没BOM，也不是UTF-16编码，则使用系统当前的代码页（简体中文操作系统为CP936）。
 * 2 将源文件内容转成源字符集(Source Character Set)，默认为UTF-8编码。
 *第2步：链接
 * 3 将1.2中得到的UTF-8转为执行字符集(Execution Character Set)：
 * 对于宽字符串（即C/C++中以L标记的串，如L"abc", L'中'），执行字符集为UTF-16编码。
 * 对于窄字符串（和宽字符串对应，即不以L标记的串），执行字符集为系统当前的代码页。
 *\link (https://www.cnblogs.com/KevinYang/archive/2010/06/18/1760597.html)
 */

// 汉字转拼音要考虑字符的编码是GB2312,GBK,还是utf8,
// utf-8编码和字符集字符序号的对应关系
/***********************************
 * 0x0000 - 0x007F       0xxxxxxx
 * 0x0080 - 0x07FF       110yyyxx 10xxxxxx
 * 0x0800 - 0xFFFF       1110yyyy 10yyyyxx 10xxxxxx
 * 0x100000 - 0x10FFFF   11110zzz 10zzyyyy 10yyyyxx 10xxxxxx
 ***********************************/

class PinYin
{
public:
    PinYin();
    ~PinYin();
    void Init();
private:
    std::map<uint16_t,unsigned char> m_gb2312;
    std::vector<std::string> m_pinyin;
    static bool Convert(wxString& strChinese,wxString& strPinYin);
};

#endif // PINYIN_H
