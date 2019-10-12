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

    for(;;){
        switch(m_strHtml(m_pos++)){
            case '<':{
                //检查是否是注释
                if(m_strHtml(m_pos++)=='!')
                   &&(m_strHtml(m_pos++) =='-')
                   &&(m_strHtml(m_pos++) =='-')){
                        SkipComment();
                }
                word = ReadUntilEncounter(" ");
                pLastNode = pCurNode;
                pCurNode = new HtmlNode(word);
                state = STATE_NODE_BEGIN_1;
                SkipWhiteSpace();
                word = "";
                break;
            },
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
            case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
            case 's': case 't': case 'u': case 'v': case 'w': case 'x':
            case 'y': case 'z': case 'A': case 'B': case 'C': case 'D':
            case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
            case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
            case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V':
            case 'W': case 'X': case 'Y': case 'Z': case '-':{
                word+= m_ch;
                m_pos++;
                break;
            },
            case '!':{

            },
            case '':{

            },
            case '=':{

            },
            case ' ':{

            },
            case '>':{

            },
            case '"':{

            },
            case '/':{

            }
            default:
                break;
        }
    }
}

/**********************************
 * @todo skip comments,
 * comment can't resid in attrs
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

