#include "HtmlSnippetParser.h"

HtmlSnippetParser::HtmlSnippetParser(wxString strHtml):m_strHtml(strHtml),m_pos(0),m_ch("")
{
   m_size = strHtml.length();
}

HtmlSnippetParser::~HtmlSnippetParser()
{
    //dtor
}


/****
 *<div>
 *  <div>
 *     xxx
 *    <div>1.1</div>
 *  </div>
 *  <div>2</div>
 *<div>
 */
bool HtmlSnippetParser::Analysis()
{
    if(m_size == 0){
        return false;
    }
    bool bLeftBracket = false; //在<>号里面
    int state = STATE_UNKNOWN; //当前所处解析状态
    wxString word = "";
    HtmlNode* pRoot = nullptr; //根节点
    HtmlNode* pCurNode = pRoot;
    HtmlNode* pLastNode = pRoot;
    std::vector<wxString,wxString> attrs;
    wxString attr_name="";
    wxString attr_value="";
    for(;;){
        switch(m_strHtml(m_pos++)){
            case '<':{
                //检查是否是注释
                if(m_strHtml(m_pos++)=='!')
                   &&(m_strHtml(m_pos++) =='-')
                   &&(m_strHtml(m_pos++) =='-')){
                        SkipComment();
                }
                word = ReadUntilChar(" ");
                pLastNode = pCurNode;
                pCurNode = new HtmlNode(word);
                state = STATE_NODE_BEGIN_1;
                word = "";
                break;
            },
            case '=':{
                attr_name = word;
                SkipWhiteSpace();
                break;
            },
            case '>':{

            },
            case '\':{
              break;
            },
            case '"':{
                attr_value = ReadAttrValue();
                attrs.push_back(attr_name,attr_value);
                break;
            },
            case '/':{

            }
            default:
                word += m_strHtml(m_pos++);
                break;
        }
    }
}

/**********************************
 * @todo skip comments,
 * comment can't reside in node's attrs
 **********************************/
void HtmlSnippetParser::SkipComment(){
    for(;;){
        if((m_strHtml(m_pos++)=='-')
            &&(m_strHtml(m_pos++)=='-')
            &&(m_strHtml(m_pos++)=='>')){
               break;
        }
    }
}

wxString HtmlSnippetParser::ReadAttrValue()
{

}

void HtmlSnippetParser::SkipWhiteSpace()
{
    while(NextToken(m_pos++)==" ");
}

wxString HtmlSnippetParser::ReadUntilChar(wxUniChar ch)
{
    wxString word="";
    while(NextToken(m_pos++)&&m_ch!=ch){
        word += m_ch;
    }
    m_pos--;
    return word;
}


void HtmlSnippetParser::SkipWith(wxUniChar ch)
{
    if(NextToken(m_pos++) && m_ch !=ch){
        throw new exception(ch+" required!");
    }
}

std::vector<wxString,wxString> HtmlSnippetParser::ParseNodeAttrs(){
    SkipWhiteSpace();
    std::vector<wxString,wxString> attrs = {};
    while(;;){
        ReadUntilEncounter("=");
        SkipWith();
    }
}

