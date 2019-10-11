#ifndef HTTPS_H
#define HTTPS_H
#include <wx/string.h>
#include "util/Helper.h"
#include "util/Macro.h"
#include "lib/curl/include/curl.h"

size_t curl_easy_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
CURLcode Https(wxString strUrl,wxString& strResponse,wxFontEncoding enumCharSet=wxFONTENCODING_UTF8);

#endif // HTTPS_H
