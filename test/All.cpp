#include "All.h"
#include "include/tool/MarkDown.h"
#include "include/util/Helper.h"

void Test::RunAll()
{
    mark_down();
}

void Test::mark_down()
{
    wxString strExe = getExecDir();
    MarkDown md(_T("D:\work_c++\openssl-1.1.1d\INSTALL"),strExe+_T("INSTALL.md"));
    md.CsvToMd();

}
