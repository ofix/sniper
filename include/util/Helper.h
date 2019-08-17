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

bool saveTo(wxString path, const wxString& text);
bool http(wxString strUrl,wxString& strResponse);
bool downloadHttpFile(wxString strUrl,wxString& strResponse);
int FixBadJson(wxString& strJson);
wxString GetExecDir();

#endif // COMMON_H
