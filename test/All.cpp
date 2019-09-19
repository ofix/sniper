#include "All.h"
#include "include/tool/MarkDown.h"
#include "include/util/Helper.h"
#include <iomanip>
#include "include/util/Macro.h"

void Test::RunAll()
{
    #ifdef xx
    mark_down();
    symmetry_nums();
    #else
    regex_match();
    #endif
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
