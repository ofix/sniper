#include "HtmlNode.h"

HtmlNode::HtmlNode(wxString nodeName):name(nodeName)
{
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    children_size = 0;
    brother_size = 0;
    attr_size = 0;
}

HtmlNode::~HtmlNode()
{
    //dtor
}
