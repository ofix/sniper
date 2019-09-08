#ifndef HELPER_H
#define HELPER_H

#include <wx/url.h>
#include <wx/sstream.h>
#include <wx/convauto.h>
#include <wx/stream.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/string.h>
#include <wx/regex.h>
#include "core/Global.h"
#include "core/Map.h"


bool saveTo(wxString path, const wxString& text);
bool http(wxString strUrl,wxString& strResponse,wxFontEncoding enumCharSet=wxFONTENCODING_CP936);
bool downloadHttpFile(wxString strUrl,wxString& strResponse);
int fixBadJson(wxString& strJson);
void console(wxString& strText);
wxString getExecDir();
wxString buildUrlPara(kvMap para,bool bComma=true);
wxVector<wxString> slice(wxString src,wxString delimiter=_T(","));
std::string stringToHex(std::string str, std::string separator = " ");
std::string wstringToHex(std::wstring str,std::string separator = " ");
std::string uint16ToHex(uint16_t num,bool bPrefix=true);
uint16_t StringToGbk(std::string str);

#endif // COMMON_H
