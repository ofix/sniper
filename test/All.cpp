#include "All.h"
#include "tool/MarkDown.h"
#include "util/Helper.h"
#include <iomanip>
#include "util/Macro.h"
#include "lib/curl/include/curl.h"
#include "lib/curl/include/easy.h"

void Test::RunAll()
{
    #ifdef xx
    mark_down();
    symmetry_nums();
    regex_match();
    //
    char* str = (char*)"Hello World XXX YYY ZZZ";
    ReplaceSpace(&str,strlen(str));
    std::cout<<str<<std::endl;
    #else
        CurlHttps();
    #endif
}

int Test::CurlHttps()
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    const char* url = "https://www.baidu.com";
    wxString strCertPath = EXE_DIR+"cacert.pem";
    const char* pCaPath = strCertPath.c_str();
    //...
    if(pCaPath){
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);//openssl编译时使用curl官网或者firefox导出的第三方根证书文件
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);/*pCaPath为证书路径 */
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    //...
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
        std::cout<<"curl url "<<url<<" ERROR!"<<std::endl;
    }else{
        std::cout<<"###### Request Https Baidu Success!"<<std::endl;
    }
    curl_easy_cleanup(curl);
}

void Test::ReplaceSpace(char** str,int length)
{
    //统计空格的个数
    int space=0;
    for(int i=0; i<length; i++){
        if(isspace(*((*str)+i))){
            space++;
        }
    }

    char* new_str =new char[(length+space*2+1)*sizeof(char)];
    int j=0;
    for(int i=0;i<length;i++){
        if(isspace(*((*str)+i))){
            *(new_str+j++) = '%';
            *(new_str+j++) = '2';
            *(new_str+j++) = '0';
        }else{
            *(new_str+j++) = *((*str)+i);
        }
    }
    *(new_str+j) = '\0';
    *str = new_str;
}

void Test::regex_match(){
    wxString pattern(wxT("<(.*?)>.*?</\\1>"));
    wxString strText(wxT("<xxx>value</xxx><tag>xxx</tag>"));
    std::vector<wxString> result;
    bool found = GetRegexMatches(pattern,strText,1,0,&result);
    if(found){
        std::vector<wxString>::const_iterator it;
        LOOP(result,it){
            std::cout<<"result "<<(*it)<<std::endl;
        }
    }
}

void Test::mark_down()
{
    wxString strExe = getExecDir();
    MarkDown md(strExe+_T("install.txt"),strExe+_T("install.md"));
    md.CsvToMd();
}

int Test::symmetry_nums()
{
    int sum=0;
    for(int i=0xF000; i<=0xFFFF; i++){// if i is uint8_t here, would overflow after 255 and cause dead loop!!!
        if(is_num_symmetry((uint16_t)i)){
            sum++;
            std::cout<<"######  "<<std::setw(3)<<i;
            std::cout<<"  "<<numToBits((uint16_t)i)<<std::endl;
        }else{
            std::cout<<"XXX  "<<std::setw(3)<<i;
            std::cout<<"  "<<numToBits((uint16_t)i)<<std::endl;
        }
    }
    std::cout<<"### total symmetry numbers: "<<sum<<std::endl;
    return sum;
}

template <typename T>
std::string Test::numToBits(T n){
    uint32_t nBytes = sizeof(n);
    int bits = nBytes*8-1;
    std::string s="";
    while(bits>=0){
        s += ((n>>bits)&1) == 1? "1":"0";
        bits --;
    }
    return s;
}

template <typename T>
bool Test::is_num_symmetry(T num)
{
    uint32_t n = sizeof(num)*8;
    uint32_t mid = n/2;
    uint32_t M = n;
    while(n>=mid)
    {
        if((((num>>n)&1)!=((num>>(M-1-n))&1)))
        {
            return false;
        }
        n--;
    }
    return true;
}
