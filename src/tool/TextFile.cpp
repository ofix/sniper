#include "include/tool/TextFile.h"

TextFile::TextFile()
{
    //ctor
}

TextFile::TextFile(const wxString& strFileName):wxTextFile(strFileName){

}

bool TextFile::OnOpen(const wxString &strBufferName, wxTextBufferOpenMode openMode)
{
    return wxTextFile::OnOpen(strBufferName,wxTextBufferOpenMode::WriteAccess);
}

TextFile::~TextFile()
{
    //dtor
}
