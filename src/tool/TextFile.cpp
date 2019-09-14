#include "include/tool/TextFile.h"

TextFile::TextFile()
{
    //ctor
}

TextFile::TextFile(const wxString& strFileName):wxTextFile(strFileName){

}

bool TextFile::Open(wxFile::OpenMode openMode)
{
    switch(openMode){
        case wxFile::read:
            return OnOpen(m_strBufferName,wxTextBufferOpenMode::ReadAccess);
        case wxFile::write:
            return OnOpen(m_strBufferName,wxTextBufferOpenMode::WriteAccess);
        case wxFile::read_write:
            return OnOpen(m_strBufferName,wxTextBufferOpenMode::WriteAccess);
        case wxFile::write_append:
            return OnOpen(m_strBufferName,wxTextBufferOpenMode::WriteAccess);
        case wxFile::write_excl:
            return OnOpen(m_strBufferName,wxTextBufferOpenMode::WriteAccess);
        default:
            return OnOpen(m_strBufferName,wxTextBufferOpenMode::WriteAccess);
    }
    return false;
}

TextFile::~TextFile()
{
    //dtor
}
