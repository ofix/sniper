#include "Https.h"

size_t curl_easy_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
   return (size_t)nmemb*size;
}
/**
 *@para strUrl wxString, request URL
 *@para strResponse wxString response content
 *@para enumCharSet enum request page font-encoding
 *@return CURLcode, CURL_OK-success, other-falied
 */
CURLcode Https(wxString strUrl,wxString& strResponse,wxFontEncoding enumCharSet)
{
    //curl_global_init(CURL_GLOBAL_ALL);
    CURL* handle = curl_easy_init();
    if(NULL == handle){
        return CURLE_FAILED_INIT;
    }
    //证书路径
    wxString strCertPath = EXE_DIR+"cacert.pem";
    //设置请求选项
    curl_easy_setopt(handle,CURLOPT_URL,strUrl.c_str().AsChar());
    curl_easy_setopt(handle,CURLOPT_SSL_VERIFYPEER, 1L);//openssl编译时使用curl官网或者firefox导出的第三方根证书文件
    curl_easy_setopt(handle,CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(handle,CURLOPT_CAINFO, strCertPath.c_str().AsChar());
    //curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,curl_easy_write_callback);
    //开始请求
    CURLcode ret = curl_easy_perform(handle);
    if(CURLE_OK == ret){
        std::cout<<"request baidu success!"<<std::endl;
    }else{
        std::cout<<"request baidu failed!"<<std::endl;
    }
    curl_easy_cleanup(handle);
   // curl_global_cleanup();
    return ret;
}
