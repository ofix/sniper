#ifndef HTMLSNIPPETPARSER_H
#define HTMLSNIPPETPARSER_H

#include <wx/string.h>
#include <wx/unichar.h>
#include "HtmlNode.h"

#define STATE_NODE_BEGIN_1    0x00000001
#define STATE_NODE_BEGIN_2    0x00000010
#define STATE_ATTR_BEGIN      0x00000100
#define STATE_ATTR_END        0x00001000
#define STATE_NODE_END_1      0x00010000
#define STATE_NODE_END_2      0x00100000
#define STATE_COMMENT_BEGIN   0x01000000
#define STATE_COMMENT_END     0x10000000
#define STATE_WHITE_SPACE     0x00000011
#define STATE_UNKNOWN         -1

class HtmlSnippetParser
{
    public:
        HtmlSnippetParser(wxString strHtml);
        virtual ~HtmlSnippetParser();
        bool Analysis();

    protected:
        inline bool NextToken(){ if(m_pos++<m_size){ m_ch=m_strHtml(m_pos); return true;}else{return false;}};
        wxString ReadUntilChar(wxUniChar ch);
        void SkipComment();
        void SkipWhiteSpace();
        void SkipWith(wxUniChar ch);
    private:
        wxString m_strHtml; //HTML片段
        size_t m_size; //HTML片段长度
        size_t m_pos; //当前位置
};

#endif // CODESNIPPETPARSER_H
