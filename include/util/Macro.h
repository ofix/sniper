#ifndef MACRO_H
#define MACRO_H
// open text file
#define OPEN_TEXT_FILE(filePath,file,line) \
    wxTextFile file(filePath); \
    if(!file.Exists()){ \
        file.Create(); \
    } \
    file.Open(); \
    wxString line;
// flush data and close file
#define CLOSE_TEXT_FILE(file) \
   file.Write(); \
   file.Close();
// exec exec path
#define EXE_DIR getExecDir()
// iteration loop begin.
#define LOOP(name,it) \
  for(it=name.begin();it!=name.end();++it)


/**********************
 * Regex Macros
 **********************/
#define REG_RESULT_MAP 1
#define REG_RESULT_VECTOR 2
#define REG_RESULT_STRING 3

struct Polyphone{
    wxString strUrl;//query Url;
    wxString strZh;//汉字词组
    std::vector<wxString> strPinYin; //汉字 用|分割
};


#endif // MACRO_H
