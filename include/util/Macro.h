#ifndef MACRO_H
#define MACRO_H

#define OPEN_TEXT_FILE(filePath,file,line) \
    wxTextFile file(filePath); \
    if(!file.Exists()){ \
        file.Create(); \
    } \
    file.Open(); \
    wxString line;

#define CLOSE_TEXT_FILE(file) \
   file.Write(); \
   file.Close();

struct Polyphone{
    wxString strUrl;//query Url;
    wxString strZh;//汉字词组
    std::vector<wxString> strPinYin; //汉字 用|分割
};


#endif // MACRO_H
