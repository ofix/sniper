#ifndef PINYIN_H
#define PINYIN_H

#include <wx/string.h>
#include <wx/except.h>

class PinYin
{
public:
    PinYin();
    ~PinYin();
    static bool Convert(wxString& strChinese,wxString& strPinYin);
};

#endif // PINYIN_H
