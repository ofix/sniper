#ifndef HTMLNODE_H
#define HTMLNODE_H
#include <map>

class HtmlNode
{
    public:
        HtmlNode(wxString nodeName);
        virtual ~HtmlNode();
    wxString name; //节点名称
    HtmlNode* parent; //父节点
    HtmlNode* left; //左兄弟
    HtmlNode* right; //右兄弟
    std::vector<HtmlNode*> children; //子节点集合
    std::map<wxString,wxString> attrs; //属性
    size_t attr_size;
    size_t brother_size;
    size_t children_size;
};

#endif // HTMLNODE_H
