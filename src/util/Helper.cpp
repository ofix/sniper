#include "util/Helper.h"
#include <sstream>
#include <wx/regex.h>
#include <map>
#include <vector>
#include "include/util/Macro.h"

// http request
bool http(wxString strUrl,wxString& strResponse,wxFontEncoding enumCharSet)
{
    try {
        wxURL _url(strUrl);
        wxCSConv conv(enumCharSet);
        wxStringOutputStream out_stream(&strResponse,conv);
        _url.GetInputStream()->Read(out_stream);
        return true;
    } catch(...) {
        return false;
    }
}

/**
 *@func 保持文件到指定路径
 *@notice 注意参数 const 要和 声明的一致，遗漏了会报错 undefined referenced to xxx
 *@author code lighter
 */
bool saveTo(wxString strPath, const wxString& strText)
{
    wxFile file;
    bool bRet = false;
    if(file.Create(strPath,true)) {
        bRet = file.Write(strText);
        file.Flush();
        file.Close();
    }
    return bRet;
}


bool downloadHttpFile(wxString strUrl,wxString& strResponse)
{
//    wxFileSystem::AddHandler(new wxInternetFSHandler);
//    wxFileSystem* pFileSystem= new wxFileSystem;
//    wxFSFile* pFile = pFileSystem->OpenFile(url);
//    if(pFile){
//        wxInputStream* pStream = pFile->GetStream();
//        size_t sz = pStream->GetSize();
//        std::cout<<"input size === "<<sz<<endl;
//        char* pBuf = new char[sz+1];
//        pStream->Read((void*) pBuf, sz);
//        pBuf[sz] = 0;
//
//        response = wxString::FromAscii(pBuf,sz+1);
//        delete[] pBuf;
//        delete pFile;
//        return true;
//    }
//    delete pFileSystem;
    return false;
}

wxString getExecDir()
{
    wxString strExePath ;
    wxStandardPathsBase& stdp = wxStandardPaths::Get();
    wxFileName exeFile(stdp.GetExecutablePath());
    strExePath = exeFile.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
    return strExePath ;
}

// fix bad json without "" in keys
int fixBadJson(wxString& strJson)
{
    try {
        wxRegEx reg(_T("([a-zA-Z]\\w*):"),wxRE_ADVANCED);
        int nReplace =  reg.ReplaceAll(&strJson,"\"\\1\":");
        return nReplace;
    } catch(std::exception& e) {
        std::cout<<e.what()<<std::endl;
        return 0;
    }
}

//output debug information to console window
void console(wxString strText)
{
    static int count = 1;
    wxString strCount = wxString::Format("%03d",count);
    std::cout<<std::endl<<_T("*************")+strCount+_T("*************")<<std::endl;
    std::wcout<<strText<<std::endl;
    std::cout<<_T("*****************************")<<std::endl<<std::endl;
    count++;
}


//return URL parameter in wxString
wxString buildUrlPara(kvMap para,bool bComma)
{
    wxString s= wxT("");
    if(bComma) {
        s.Append("?");
    }
    kvMap::iterator it;
    for(it=para.begin(); it!=para.end(); ++it) {
        s.Append(it->first);
        s.Append("=");
        s.Append(it->second);
        s.Append("&");
    }
    s.RemoveLast(1);
    return s;
}

// slice string in delimiter
wxVector<wxString> slice(wxString src,wxString delimiter)
{
    wxVector<wxString> vec;
    wxString::const_iterator it;
    size_t nPos, nPrevPos;
    nPos = nPrevPos = 0;
    bool quotation = 0;
    for(it=src.begin(); it!=src.end(); ++it,nPos++) { //引号内的字符串不分割
        if(*it == '"') {
            quotation = !quotation;
        }
        if(quotation==0) {
            if(*it != delimiter) {
                continue;
            } else {
                vec.push_back(src.SubString(nPrevPos,nPos-1));
                nPrevPos = nPos+1;
            }
        }
    }
    vec.push_back(src.SubString(nPrevPos,nPos-1));
    return vec;
}


/**
 * @target : 多字节字符串转十六进制，支持中英文混合
 * @param str : 要转换成十六进制的字符串
 * @param separator : 十六进制字符串间的分隔符
 * @return : 16进制字符串
 */
std::string stringToHex(std::string str, std::string separator)
{
    const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;
    for (std::string::size_type i = 0; i<str.size(); ++i) {
        ss << hex[(unsigned char)str[i] >> 4]
           << hex[(unsigned char)str[i] & 0x0f]
           << separator;
    }
    return ss.str();
}

/**
 * @target : Unicode宽字符串转十六进制,支持中英文混合
 * @param str: 要转换成十六进制的Unicode字符串
 * @param separator: 十六进制字符串间的分隔符
 * @return : 16进制字符串
 */
std::string wstringToHex(std::wstring str, std::string separator)
{
    const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;
    for (std::wstring::size_type i = 0; i < str.size(); ++i) {
        ss << hex[(uint16_t)str[i] >> 12 & 0x0f]
           << hex[(uint16_t)str[i] >> 8 & 0x0f]
           << separator
           << hex[(uint16_t)str[i] >> 4 & 0x0f]
           << hex[(uint16_t)str[i] & 0x0f]
           << separator;
    }
    return ss.str();
}

//十六进制
std::string uint16ToHex(uint16_t num,bool bPrefix)
{
    const std::string hex="0123456789ABCDEF";
    std::string s = "";
    s += hex[num>>16&0x0f];
    s += hex[num>>8&0x0f];
    s += hex[num>>4&0x0f];
    s += hex[num&0x0f];
    if(bPrefix) {
        s = "0x" +s;
    }
    return s;
}

uint16_t StringToGbk(std::string str)
{
    uint16_t i= (str[0]<<8&0xFF00)|(str[1]&0x00FF);
    return i;
}

wxString GenerateRandomString(uint8_t width)
{
    static std::vector<wxString> AlphaNum = {"0","a","b","R","S","T","V","W","U","9","X","c","1","3","f","g","h",
                                             "i","j","k","4","o","p","d","e","2","q","v","5","6","w","x","y","z","A",
                                             "B","E","D","F","C","r","s","t","u","O","I","J","K","8","Y","Z","P","Q",
                                             "7","G","H"
                                            };
    wxString strRandom = wxT("");
    if(width <=6) {
        width = 8;
    }
    if(width >= 30) {
        width = 30;
    }
    uint16_t MAX_ALPHA = AlphaNum.size();

    unsigned int seed = (unsigned int)time(0);
    srand(seed);
    while(width--) {
        unsigned int i = GetRandomNum(0,MAX_ALPHA-1); // 0 ~ MAX_ALPHA-1
        strRandom.Append(AlphaNum.at(i));
    }
    return strRandom;
}

unsigned int GetRandomNum(unsigned int min, unsigned int max)
{
    if(min >= max) {
        unsigned int tmp = max;
        max = min;
        min = tmp;
    }
    unsigned int  num = rand() % (max-min+1) + min;
    return num;
}

/******************
 *@param strRegex 匹配的表达式
 *@param strSrc 匹配的字符串
 *@param nType 返回的结果类型
 *@param result 返回的结果
 *@param nKeyIndex 将第几个匹配表达式作为返回结果
 *@param return bool 1找到了，0未找到
 ******************/
bool GetRegexMatches(wxString strPattern,wxString& strExpress,int nType,size_t nKeyIndex,void* result)
{
//    wxASSERT(nType==1||nType==2);
//    if(nType ==2){
//        wxASSERT(nKeyIndex >0);
//    }
//    wxRegEx re(strPattern,wxRE_ADVANCED);
//    if(!re.Compile(strPattern,wxRE_ADVANCED)){
//        return false;
//    }
//    size_t cnt = 0;
//    if((cnt=re.GetMatchCount())<2){ // 没有子表达式
//        return false; //返回失败
//    }
//
//    if(nKeyIndex>=cnt-1){
//        return false;
//    }
//    wxString text = strExpress;
//    wxString rand = GenerateRandomString(8);
//    saveTo(EXE_DIR+rand+".txt",text);
//    bool bFound = false;
//    while(re.Matches(text)){
//        bFound = true;
//        size_t start, len;
//        re.GetMatch(&start, &len, 0);
//        std::cout<<"start len "<<start<<" , "<<len<<std::endl;
//        if(nType == 1){ //vector
//            wxString strMatch;
//            if(cnt==2){
//                ((std::vector<wxString>*)result)->push_back(re.GetMatch(text,1)); //只有1个子匹配
//            }else if(cnt>2){
//                std::vector<wxString> vec;
//                size_t i=1;
//                while(i<=cnt){
//                    vec.push_back(re.GetMatch(text,i));
//                    i++;
//                }
//                ((std::vector<std::vector<wxString>>*)result)->push_back(vec);
//            }
//        }else if(nType == 2 && cnt>=2){//map
//            wxString strKey;
//            strKey = re.GetMatch(text,nKeyIndex);
//            if(cnt == 2){
//                (*(std::map<wxString,wxString>*)result)[strKey] = re.GetMatch(text,0x03|(~nKeyIndex));
//            }else{
//                size_t i=1;
//                std::vector<wxString> vec;
//                while(i<=cnt){
//                    if(i!=nKeyIndex){
//                        vec.push_back(re.GetMatch(text,i));
//                    }
//                    (*(std::map<wxString,std::vector<wxString>>*)result)[strKey] = vec;
//                    i++;
//                }
//            }
//        }
//        text = text.Mid(start+len);
//    }
//    return bFound;
    return false;
}

/******************
 *@param strRegex 匹配的表达式
 *@param strSrc 匹配的字符串
 *@param nType 返回的结果类型
 *@param result 返回的结果
 *@param nKeyIndex 将第几个匹配表达式作为返回结果
 *@param return bool 1找到了，0未找到
 ******************/
bool GetRegexMatches(wxString strPattern,wxString& strExpress,int nType,size_t nKeyIndex,std::map<wxString,wxString> result)
{
//    wxASSERT(nType==1||nType==2);
//    if(nType ==2){
//        wxASSERT(nKeyIndex >0);
//    }
//    wxRegEx re(strPattern,wxRE_ADVANCED);
//    if(!re.Compile(strPattern,wxRE_ADVANCED)){
//        return false;
//    }
//    size_t cnt = 0;
//    if((cnt=re.GetMatchCount())<2){ // 没有子表达式
//        return false; //返回失败
//    }
//
//    if(nKeyIndex>=cnt-1){
//        return false;
//    }
//    wxString text = strExpress;
//    wxString rand = GenerateRandomString(8);
//    saveTo(EXE_DIR+rand+".txt",text);
//    bool bFound = false;
//    while(re.Matches(text)){
//        bFound = true;
//        size_t start, len;
//        re.GetMatch(&start, &len, 0);
//        std::cout<<"start len "<<start<<" , "<<len<<std::endl;
//        if(nType == 1){ //vector
//            wxString strMatch;
//            if(cnt==2){
//                ((std::vector<wxString>*)result)->push_back(re.GetMatch(text,1)); //只有1个子匹配
//            }else if(cnt>2){
//                std::vector<wxString> vec;
//                size_t i=1;
//                while(i<=cnt){
//                    vec.push_back(re.GetMatch(text,i));
//                    i++;
//                }
//                ((std::vector<std::vector<wxString>>*)result)->push_back(vec);
//            }
//        }else if(nType == 2 && cnt>=2){//map
//            wxString strKey;
//            strKey = re.GetMatch(text,nKeyIndex);
//            if(cnt == 2){
//                (*(std::map<wxString,wxString>*)result)[strKey] = re.GetMatch(text,0x03|(~nKeyIndex));
//            }else{
//                size_t i=1;
//                std::vector<wxString> vec;
//                while(i<=cnt){
//                    if(i!=nKeyIndex){
//                        vec.push_back(re.GetMatch(text,i));
//                    }
//                    (*(std::map<wxString,std::vector<wxString>>*)result)[strKey] = vec;
//                    i++;
//                }
//            }
//        }
//        text = text.Mid(start+len);
//    }
//    return bFound;
    return false;
}

// Get Current Timestamp in Milliseconds
uint64_t CurrentTimestamp()
{
    using namespace std::chrono;
    return static_cast<uint64_t>(duration_cast<milliseconds>(
                                     system_clock::now().time_since_epoch()).count());
}

// Format data with RMB Uint(亿,万)
wxString FormatDataWithUint(uint64_t data)
{
    if(data >= RMB_UINT_YI) {
        double _data = static_cast<double>(data/RMB_UINT_YI);
        wxString str_data = wxString::Format("%.2f",_data);
        wxString res = str_data + _T("亿");
        return res;
    } else if(data >= RMB_UINT_WAN) {
        double _data = static_cast<double>(data/RMB_UINT_WAN);
        wxString str_data = wxString::Format("%.2f",_data);
        wxString res = str_data + _T("万");
        return res;
    } else {
        wxString str_data = wxString::Format("%d",data);
        return str_data;
    }
}

wxString FormatDataWithPercent(double data)
{
    double _data = static_cast<double>(data/100);
    wxString str_data = wxString::Format("%.2f",_data);
    wxString res = str_data + _T("%");
    return res;
}
