#include "HtmlSnippetParser.h"

HtmlSnippetParser::HtmlSnippetParser(wxString strHtml):m_strHtml(strHtml),m_pos(0),m_ch(""),m_lineNo(0)
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
                }else if(state == STATE_UNKNOWN || state == STATE_NODE_END_2){
                    word = ReadUntilChar(" ");
                    pLastNode = pCurNode;
                    pCurNode = new HtmlNode(word);
                    state = STATE_NODE_BEGIN_1;
                    word = "";
                }else if(state == STATE_NODE_BEGIN_2){
                    word = ReadUntilChar(" ");
                    pLastNode = pCurNode;
                    pCurNode = new HtmlNode(word);
                    pCurNode->parent = pLastNode; //父级节点，相当于压栈
                    state = STATE_NODE_BEGIN_1;
                    word = "";

                }
                break;
            },
            case '=':{
                attr_name = word;
                SkipWhiteSpace();
                break;
            },
            case '>':{
                if(state == STATE_NODE_BEGIN_1){
                    state = STATE_NODE_BEGIN_2;
                }else if(state == STATE_NODE_END_1){
                    state = STATE_NODE_END_2;
                }
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


void HtmlSnippetParser::CleanUp(HtmlNode* pNode)
{
    HtmlNode* pNext = null;
    while(pNode != nullptr){ //深度优先删除
       if(pNode->children){
            for(size_t i=0; i<pNode->children_size; i++){
                CleanUp(pNode->children[i]);
            }
        }
        HtmlNode* pBrotherNode=nullptr;
        //删除属性
        pNode->attrs.clear();
        pNode->children.clear(); //删除子元素
        pNode = nullptr; //删除自身
        pNode->left = nullptr;
        pNode->right = nullptr;
        pNode->children_size = 0;
        pNode->brother_size = 0;
        pNode->attr_size = 0;
        delete pNode;
        pNode = pNode->right;
    }

    delete pNode;
}

wxString HtmlSnippetParser::ReadAttrValue()
{
   wxString value ="";
   for(;;){
        if(m_strHtml(m_pos++)=='\\'){
            m_pos++;
        }
        if(m_strHtml(m_pos++)=='"'){
            break;
        }
        value += m_strHtml(m_pos);
   }
   return value;
}

void HtmlSnippetParser::SkipWhiteSpace()
{
    while(m_strHtml(m_pos++)==" ");
}

wxString HtmlSnippetParser::ReadUntilChar(wxUniChar ch)
{
    wxString word="";
    while(m_strHtml(m_pos++)!=ch){
        word += m_ch;
    }
    m_pos--;
    return word;
}


void HtmlSnippetParser::SkipWith(wxUniChar ch)
{
    if(m_strHtml(m_pos++) !=ch){
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

