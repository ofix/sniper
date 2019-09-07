#include "PinYinSpider.h"

PinYinSpider::PinYinSpider(wxString strUrl):Spider(strUrl)
{
    //ctor
}

PinYinSpider::~PinYinSpider()
{
    //dtor
}

bool PinYinSpider::Run()
{
    wxString response;
    http(m_url,response);
    std::cout<<response<<std::endl;
    return true;
}
