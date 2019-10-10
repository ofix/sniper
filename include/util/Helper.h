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
#include "include/core/Global.h"
#include "include/core/Map.h"


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
/******************
 *@param strRegex 匹配的表达式
 *@param strSrc 匹配的字符串
 *@param nType 返回的结果类型
 *@param result 返回的结果
 *@param nKeyIndex 将第几个匹配表达式作为返回结果
 *@param return bool 1找到了，0未找到
 ******************/
bool GetRegexMatches(wxString strRegex,wxString& strSrc,int nType,size_t nKeyIndex,void* result);

#endif // COMMON_H
