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
#define REG_MATCH_1(re,text) \
    wxString strMatch_1; \
    strMatch_1 = re.GetMatch(text,1);
#define REG_MATCH_2(re,text) \
    wxString strMatch_1; \
    wxString strMatch_2; \
    strMatch_1 = re.GetMatch(text,1); \
    strMatch_2 = re.GetMatch(text,2); \
#define REG_MATCH_3(re,text) \
    wxString strMatch_1; \
    wxString strMatch_2; \
    wxString strMatch_3; \
    strMatch_1 = re.GetMatch(text,1); \
    strMatch_2 = re.GetMatch(text,2); \
    strMatch_3 = re.GetMatch(text,3); \
#define REG_MATCH_4(re,text) \
    wxString strMatch_1; \
    wxString strMatch_2; \
    wxString strMatch_3; \
    wxString strMatch_4; \
    strMatch_1 = re.GetMatch(text,1); \
    strMatch_2 = re.GetMatch(text,2); \
    strMatch_3 = re.GetMatch(text,3); \
    strMatch_4 = re.GetMatch(text,4); \
#define REG_MATCH_5(re,text) \
    wxString strMatch_1; \
    wxString strMatch_2; \
    wxString strMatch_3; \
    wxString strMatch_4; \
    wxString strMatch_5; \
    strMatch_1 = re.GetMatch(text,1); \
    strMatch_2 = re.GetMatch(text,2); \
    strMatch_3 = re.GetMatch(text,3); \
    strMatch_4 = re.GetMatch(text,4); \
    strMatch_5 = re.GetMatch(text,5); \
#define REG_MATCH_6(re,text) \
    wxString strMatch_1; \
    wxString strMatch_2; \
    wxString strMatch_3; \
    wxString strMatch_4; \
    wxString strMatch_5; \
    wxString strMatch_6; \
    strMatch_1 = re.GetMatch(text,1); \
    strMatch_2 = re.GetMatch(text,2); \
    strMatch_3 = re.GetMatch(text,3); \
    strMatch_4 = re.GetMatch(text,4); \
    strMatch_5 = re.GetMatch(text,5); \
    strMatch_6 = re.GetMatch(text,6); \
#define REG_MATCH_7(re,text) \
    wxString strMatch_1; \
    wxString strMatch_2; \
    wxString strMatch_3; \
    wxString strMatch_4; \
    wxString strMatch_5; \
    wxString strMatch_6; \
    wxString strMatch_7; \
    strMatch_1 = re.GetMatch(text,1); \
    strMatch_2 = re.GetMatch(text,2); \
    strMatch_3 = re.GetMatch(text,3); \
    strMatch_4 = re.GetMatch(text,4); \
    strMatch_5 = re.GetMatch(text,5); \
    strMatch_6 = re.GetMatch(text,6); \
    strMatch_7 = re.GetMatch(text,7); \
#define REG_MATCH_8(re,text) \
    wxString strMatch_1; \
    wxString strMatch_2; \
    wxString strMatch_3; \
    wxString strMatch_4; \
    wxString strMatch_5; \
    wxString strMatch_6; \
    wxString strMatch_7; \
    wxString strMatch_8; \
    strMatch_1 = re.GetMatch(text,1); \
    strMatch_2 = re.GetMatch(text,2); \
    strMatch_3 = re.GetMatch(text,3); \
    strMatch_4 = re.GetMatch(text,4); \
    strMatch_5 = re.GetMatch(text,5); \
    strMatch_6 = re.GetMatch(text,6); \
    strMatch_7 = re.GetMatch(text,7); \
    strMatch_8 = re.GetMatch(text,8); \
#define REG_MATCH_9(re,text) \
    wxString strMatch_1; \
    wxString strMatch_2; \
    wxString strMatch_3; \
    wxString strMatch_4; \
    wxString strMatch_5; \
    wxString strMatch_6; \
    wxString strMatch_7; \
    wxString strMatch_8; \
    wxString strMatch_9; \
    strMatch_1 = re.GetMatch(text,1); \
    strMatch_2 = re.GetMatch(text,2); \
    strMatch_3 = re.GetMatch(text,3); \
    strMatch_4 = re.GetMatch(text,4); \
    strMatch_5 = re.GetMatch(text,5); \
    strMatch_6 = re.GetMatch(text,6); \
    strMatch_7 = re.GetMatch(text,7); \
    strMatch_8 = re.GetMatch(text,8); \
    strMatch_9 = re.GetMatch(text,9); \
#define REG_MATCH_10(re,text) \
    wxString strMatch_1; \
    wxString strMatch_2; \
    wxString strMatch_3; \
    wxString strMatch_4; \
    wxString strMatch_5; \
    wxString strMatch_6; \
    wxString strMatch_7; \
    wxString strMatch_8; \
    wxString strMatch_9; \
    wxString strMatch_10; \
    strMatch_1 = re.GetMatch(text,1); \
    strMatch_2 = re.GetMatch(text,2); \
    strMatch_3 = re.GetMatch(text,3); \
    strMatch_4 = re.GetMatch(text,4); \
    strMatch_5 = re.GetMatch(text,5); \
    strMatch_6 = re.GetMatch(text,6); \
    strMatch_7 = re.GetMatch(text,7); \
    strMatch_8 = re.GetMatch(text,8); \
    strMatch_9 = re.GetMatch(text,9); \
    strMatch_10 = re.GetMatch(text,10); \
    (re.GetMatch(text,1);
#define REG_MATCH_1(re,text) (re.GetMatch(text,1);
#define REG_MATCH_1(re,text) (re.GetMatch(text,1);
#define REG_MATCH_1(re,text) (re.GetMatch(text,1);

struct Polyphone{
    wxString strUrl;//query Url;
    wxString strZh;//汉字词组
    std::vector<wxString> strPinYin; //汉字 用|分割
};


#endif // MACRO_H
