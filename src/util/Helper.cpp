#include "util/Helper.h"

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

wxString GetExecDir()
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
    for(it=src.begin(); it!=src.end(); ++it,nPos++){
        if((*it) != delimiter){
           continue;
        }else{
            vec.push_back(src.SubString(nPrevPos,nPos));
            nPrevPos = nPos;
        }
    }
    return vec;
}
