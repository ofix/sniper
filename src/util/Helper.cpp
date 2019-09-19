#include "util/Helper.h"
#include <sstream>
#include <wx/regex.h>
#include <map>
#include <vector>
#include "include/util/Macro.h"

// http request
bool http(wxString strUrl,wxString& strResponse,wxFontEncoding enumCharSet)
{
    try{
        wxURL _url(strUrl);
        wxCSConv conv(enumCharSet);
        wxStringOutputStream out_stream(&strResponse,conv);
        _url.GetInputStream()->Read(out_stream);
        return true;
    }catch(...){
        return false;
    }
}

/**
 *@func 保持文件到指定路径
 *@notice 注意参数 const 要和 声明的一致，遗漏了会报错 undefined referenced to xxx
 *@author code lighter
 */
bool saveTo(wxString strPath, const wxString& strText){
  wxFile file;
  bool bRet = false;
  if(file.Create(strPath,true)){
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
    try{
     wxRegEx reg(_T("([a-zA-Z]\\w*):"),wxRE_ADVANCED);
     int nReplace =  reg.ReplaceAll(&strJson,"\"\\1\":");
     return nReplace;
    }catch(std::exception& e){
        std::wcout<<e.what()<<std::endl;
        return 0;
    }
}

//output debug information to console window
void console(wxString& strText)
{
    static int count = 1;
    wxString strCount = wxString::Format("%03d",count);
    std::cout<<std::endl<<_T("*************")+strCount+_T("*************")<<std::endl;
    std::wcout<<strText<<std::endl;
    std::cout<<_T("*****************************")<<std::endl<<std::endl;
    count++;
}


//return URL parameter in wxString
wxString buildUrlPara(kvMap para,bool bComma){
    wxString s= wxT("");
    if(bComma){
        s.Append("?");
    }
    kvMap::iterator it;
    for(it=para.begin();it!=para.end();++it){
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
    for(it=src.begin(); it!=src.end(); ++it,nPos++){ //引号内的字符串不分割
        if(*it == '"'){
            quotation = !quotation;
        }
        if(quotation==0){
            if(*it != delimiter){
               continue;
            }else{
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
	for (std::string::size_type i = 0; i<str.size(); ++i)
	{
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
	for (std::wstring::size_type i = 0; i < str.size(); ++i)
	{
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
    if(bPrefix){
        s = "0x" +s;
    }
    return s;
}

uint16_t StringToGbk(std::string str){
    uint16_t i= (str[0]<<8&0xFF00)|(str[1]&0x00FF);
    return i;
}


bool GetRegexMatches(wxString strPattern,wxString& strExpress,int nType,int nKeyIndex,void* result)
{
    wxASSERT(nType>0);
    wxASSERT(nKeyIndex >0);
    wxRegEx reg(strPattern,wxRE_ADVANCED);
    if(!reg.Compile(strPattern,wxRE_ADVANCED)){
        return false;
    }
    size_t cnt = 0;
    if(!(cnt=reg.GetMatchCount())){
        return false; //返回失败
    }
    if(nKeyIndex>=cnt){
        return false;
    }
    wxString processText = strExpress;
    while(reg.Matches(processText)){
        size_t start, len;
        re.GetMatch(&start, &len, 0);
        int _cnt = cnt;
        if(cnt==1){
            REG_MATCH_1(re,processText) //第1个结果
        }else if(cnt==2){
            REG_MATCH_2(re,processText) //第2个结果
        }else if(cnt==3){
            REG_MATCH_3(re,processText) //第3个结果
         }else if(cnt==4){
            REG_MATCH_4(re,processText) //第4个结果
         }else if(cnt==5){
            REG_MATCH_5(re,processText) //第5个结果
         }else if(cnt==6){
            REG_MATCH_6(re,processText) //第6个结果
         }else if(cnt==7){
            REG_MATCH_7(re,processText) //第7个结果
         }else if(cnt==8){
            REG_MATCH_8(re,processText) //第8个结果
         }else if(cnt==9){
            REG_MATCH_9(re,processText) //第9个结果
         }else if(cnt==10){
            REG_MATCH_10(re,processText) //第10个结果
        }
        re.GetMatch(processText,1);
        processText = processText.Mid(start+len);
    }
}
