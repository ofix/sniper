#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <wx/textfile.h>


class TextFile : public wxTextFile
{
    public:
         // constructors
        TextFile();
        TextFile(const wxString& strFileName);
        virtual bool OnOpen(const wxString &strBufferName, wxTextBufferOpenMode openMode);
        virtual ~TextFile();
    protected:
        wxTextFile m_textFile;
};

#endif // TEXTFILE_H
