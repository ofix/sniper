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
    MarkDown md(strExe+_T("install.txt"),strExe+_T("install.md"));
    md.CsvToMd();
}
