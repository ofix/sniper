#include "PinYinSpider.h"
#include <wx/textfile.h>
#include <wx/debug.h>

PinYinSpider::PinYinSpider(wxString strUrl):Spider(strUrl)
{
    //ctor
}

PinYinSpider::~PinYinSpider()
{
    //dtor
}

bool PinYinSpider::Run()
{
    wxTextFile gbkFile;
    wxString fileName = getExecDir()+wxT("GBK汉字拼音对照表.csv"); //gbk 编码的格式
    if(!gbkFile.Open(fileName,wxConvAuto(wxFONTENCODING_CP936))){ // 以gbk方式打开
        return false;
    }
    wxString line = gbkFile.GetNextLine(); // skip first line
    while(!gbkFile.Eof()){
        line = gbkFile.GetNextLine();
        wxVector<wxString> parts = slice(line);
        if(parts.size()>=9){
            gbkRawPacket packet;
            packet.index = (uint32_t)atoi(parts[0].c_str());
            packet.zh_char = parts[1].ToStdString();
            packet.pinyin_full = parts[2].ToStdString();
            packet.pinyin_1 = parts[3].ToStdString();
            packet.pinyin_2 = parts[4].ToStdString();
            packet.pinyin_3 = parts[5].ToStdString();
            packet.pinyin_4 = parts[6].ToStdString();
            packet.pinyin_5 = parts[7].ToStdString();
            packet.pinyin_6 = parts[8].ToStdString();
            m_pinyin.push_back(packet);
        }
    }

    // generate map file
//    wxTextFile gbkFileSimple;
//    wxString path = getExecDir()+wxT("gbk.txt");
//    if(!gbkFileSimple.Open(path)){
//        gbkFileSimple.Create(path);
//    }
//    gbkFileSimple.Clear();
//    std::vector<gbkRawPacket>::const_iterator it;
//    for(it=m_pinyin.begin();it!=m_pinyin.end();++it){
////        wxCSConv gbkConv(wxFONTENCODING_CP936);
////        std::string str_gbk(gbkConv.cWX2MB(wxString(it->zh_char))); //gbk格式
////        std::cout<<str_gbk<<std::endl;
//        wxString strLine = it->zh_char+",";
//        if(it->pinyin_1!=""){
//            strLine += it->pinyin_1+"|";
//        }
//        if(it->pinyin_2!=""){
//            strLine += it->pinyin_2+"|";
//        }
//        if(it->pinyin_3!=""){
//            strLine += it->pinyin_3+"|";
//        }
//        if(it->pinyin_4!=""){
//            strLine += it->pinyin_4+"|";
//        }
//        if(it->pinyin_5!=""){
//            strLine += it->pinyin_5+"|";
//        }
//        if(it->pinyin_6!=""){
//            strLine += it->pinyin_6+"|";
//        }
//        strLine = strLine.Left(strLine.length()-1);
//        gbkFileSimple.AddLine(strLine);
//    }
//    gbkFileSimple.Write();
//    gbkFileSimple.Close();

    wxTextFile gbkMapFile;
    wxString path = getExecDir()+wxT("gbk_utf8_map.cpp");
    if(!gbkMapFile.Open(path)){
        gbkMapFile.Create(path);
    }
    gbkMapFile.Clear();
    wxString strHead = "std::map<std::string,std::string> PinYin::m_pinyin_utf8_map = { ";
    gbkMapFile.AddLine(strHead);
    std::vector<gbkRawPacket>::const_iterator it;
    for(it=m_pinyin.begin();it!=m_pinyin.end();++it){
//        wxCSConv gbkConv(wxFONTENCODING_CP936);
//        std::string str_gbk(gbkConv.cWX2MB(wxString(it->zh_char))); //gbk格式
//        std::cout<<str_gbk<<std::endl;
        wxString strLine = "{\"" +it->zh_char+"\",\"";
        if(it->pinyin_1!=""){
            strLine += it->pinyin_1+"|";
        }
        if(it->pinyin_2!=""){
            strLine += it->pinyin_2+"|";
        }
        if(it->pinyin_3!=""){
            strLine += it->pinyin_3+"|";
        }
        if(it->pinyin_4!=""){
            strLine += it->pinyin_4+"|";
        }
        if(it->pinyin_5!=""){
            strLine += it->pinyin_5+"|";
        }
        if(it->pinyin_6!=""){
            strLine += it->pinyin_6+"|";
        }
        strLine = strLine.Left(strLine.length()-1);
        strLine += "\"";
        if(it != m_pinyin.end()-1){
            strLine += "},";
        }else{
            strLine += "} ";
        }
        gbkMapFile.AddLine(strLine);
    }
    gbkMapFile.AddLine("};");
    gbkMapFile.Write();
    gbkMapFile.Close();


    return true;
}
