#ifndef BAIDUPOLYPHONESPIDER_H
#define BAIDUPOLYPHONESPIDER_H
#include <spider/Spider.h>

class BaiduPolyphoneSpider:public Spider
{
    public:
        BaiduPolyphoneSpider(wxString strUrl=wxT("http://www.baidu.com/s?wd=%E5%A4%9A%E9%9F%B3%E5%AD%97&rsv_spt=1&rsv_iqid=0xb2fb14e300369650&issp=1&f=8&rsv_bp=1&rsv_idx=2&ie=utf-8&rqlang=cn&tn=baiduhome_pg&rsv_enter=1&rsv_dl=tb&inputT=766&rsv_t=34a1oKGlK5KB%2B6GQNeKfhig8ChYo0o8Vezo4uY9JXTEw481rcIncxODYpbEIQRiR8Jr2&oq=%2526lt%253B%252B%252B%2520%25E5%25A4%259A%25E9%259F%25B3%25E5%25AD%2597&rsv_pq=e1b97ed400002a43&rsv_sug3=14&rsv_sug1=9&rsv_sug7=100&rsv_sug2=0&rsv_sug4=766"));
        virtual bool Run();
        virtual ~BaiduPolyphoneSpider();
        int RemoveDirtyWords(wxString& strResponse);
    protected:
        uint32_t m_totalPages;
        uint32_t m_curPage;
};

#endif // BAIDUPOLYPHONESPIDER_H
