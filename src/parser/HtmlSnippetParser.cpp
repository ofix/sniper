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
    NextToken(m_pos++);
    while(NextToken(m_pos++)){
        switch(m_ch){
            case "<":{
                state = STATE_NODE_BEGIN_1;
                word = ReadUntilEncounter(" ");
                pCurNode = new HtmlNode(word);
            },
            case "=":{

            },
            case " ":{
                if(state == STATE_NODE_BEGIN_1){

                }
            },
            case ">":{
                EndNode();
            },
            case "\"":{

            },
            case "/":{

            }
            default:
                break;
        }
    }

        if(bLeftBracket){
            NextToken(m_pos++);
            if(m_ch !=" "){
                nodeName.Append(m_ch);
            }
            if(pRoot == nullptr){
                pRoot =
            }
        }
        bLeftBracket = false;
        bInNode = true;
    }
}

void HtmlSnippetParser::BeginNode()
{

}

void HtmlSnippetParser::SkipWhiteSpace()
{
    while(NextToken(m_pos++)==" ");
}

wxString HtmlSnippetParser::ReadUntilEncounter(wxUniChar ch)
{
    wxString word="";
    while(NextToken(m_pos++)&&m_ch!=ch){
        word += m_ch;
    }
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

