#ifndef HTMLNODE_H
#define HTMLNODE_H
#include <map>

class HtmlNode
{
    public:
        HtmlNode(wxString nodeName);
        virtual ~HtmlNode();
    wxString name; //�ڵ�����
    HtmlNode* parent; //���ڵ�
    HtmlNode* left; //���ֵ�
    HtmlNode* right; //���ֵ�
    std::vector<HtmlNode*> children; //�ӽڵ㼯��
    std::map<wxString,wxString> attrs; //����
    size_t attr_size;
    size_t brother_size;
    size_t children_size;
};

#endif // HTMLNODE_H
