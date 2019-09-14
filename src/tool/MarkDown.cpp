#include "include/tool/MarkDown.h"
#include <wx/textfile.h>
#include <map>
#include <vector>
#include <iostream>

MarkDown::MarkDown(wxString strSrcFile,wxString strDestFile):m_strSrcFile(strSrcFile)
                    ,m_strDestFile(strDestFile)
{
    //ctor
}

MarkDown::~MarkDown()
{
    //dtor
}

bool MarkDown::CsvToMd()
{
    if(m_strSrcFile == wxT("")
       || m_strDestFile == wxT("")){
            return false;
    }
    wxTextFile txtFile(m_strSrcFile);
    if(!txtFile.Exists()){
        return false;
    }
    txtFile.Open();
    std::map<wxString,std::vector<wxString>> mdLines;
    while(!txtFile.Eof()){
        wxString line = txtFile.GetNextLine();
        if(line.Trim().length()>0){
            static wxString option=wxT("");
            static std::vector<wxString> comments;
            if(line.StartsWith(wxT("                   "))){
                comments.push_back(line.Trim(false).Trim(true)); //去除左右两边的空格
            }else{
                if(option != wxT("")){
                    mdLines[option] = comments;
                    comments.clear();
                    option = line.Trim(false).Trim(true);
                }else{
                    option = line.Trim(false).Trim(true); // 去除左右两边的空格
                }
            }

        }
    }
    // write MD content to file
    wxTextFile mdFile(m_strDestFile);
    if(mdFile.Exists()){
        mdFile.Clear();
        std::cout<<"xxxx empty file"<<std::endl;
    }else{
        mdFile.Create();
    }
    mdFile.Open();
    wxString mdline= wxT("|选项|选项说明|");
    mdFile.AddLine(mdline);
    mdline = wxT("|:--|:--|");
    mdFile.AddLine(mdline);
    std::map<wxString,std::vector<wxString>>::const_iterator it;
    for(it=mdLines.begin();it!=mdLines.end();++it){
        std::vector<wxString> comments = it->second;
        mdline = wxT("|**")+it->first+wxT("**|") + (comments.size()>0?comments[0]+wxT("<br/>"):wxT("<br/>"));
        if(comments.size()>1){
            std::vector<wxString>::const_iterator itt;
            for(itt = comments.begin()+1; itt!=comments.end()-1;++itt){
                mdline.Append((*itt)+wxT("<br/>"));
            }
        }
        mdline.Append((comments.size()>0?comments.at(comments.size()-1):wxT(""))+wxT("|"));
        mdFile.AddLine(mdline);
    }
    mdFile.Write();
    mdFile.Close();
    #ifdef DEBUG
        std::cout<<"############## test MarkDown::csvToMd finished. ##############"<<std::endl;
    #endif // DEBUG
    return true;
}
