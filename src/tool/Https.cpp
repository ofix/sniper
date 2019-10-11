#include "Https.h"
#include <stdio.h>
#include <stdlib.h>


struct MemoryStruct {
  char *memory;
  size_t size;
};



size_t curl_easy_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userdata;

  char* ptrRecv = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(ptrRecv == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptrRecv;
  memcpy(&(mem->memory[mem->size]), ptr, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}
/**
 *@para strUrl wxString, request URL
 *@para strResponse wxString response content
 *@para enumCharSet enum request page font-encoding
 *@return CURLcode, CURL_OK-success, other-falied
 */
CURLcode Https(wxString strUrl,wxString& strResponse,wxFontEncoding enumCharSet)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    if(NULL == curl){
        return CURLE_FAILED_INIT;
    }
    //证书路径
    wxString strCertPath = EXE_DIR+"cacert.pem";
    struct MemoryStruct chunk;
    chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */
    // 设置请求选项
    curl_easy_setopt(curl,CURLOPT_URL,strUrl.c_str().AsChar());
    bool bHttps = false;
    if(strUrl.Find("https://") !=  wxNOT_FOUND){
        bHttps = true;
    }
    // 设置自定义请求头
    struct curl_slist *list = NULL;
    list = curl_slist_append(list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    //设置其他请求选项
    if(bHttps){
        curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER, 1L);//openssl编译时使用curl官网或者firefox导出的第三方根证书文件
        curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl,CURLOPT_CAINFO, strCertPath.c_str().AsChar());
    }
    // 设置回调函数
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,curl_easy_write_callback);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void *)&chunk);
    // 开始请求
    CURLcode ret = curl_easy_perform(curl);
    if(ret == CURLE_OK){
        if(enumCharSet == wxFONTENCODING_UTF8){
            strResponse = wxString::FromUTF8(chunk.memory,chunk.size);
        }
    }
    curl_slist_free_all(list); /* free the list again */
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return ret;
}
