#include "spider/EastMoneySpider.h"

EastMoneySpider::EastMoneySpider(wxString strUrl):StockSpider(strUrl)
{
    //ctor
    m_urlData = wxT("http://98.push2.eastmoney.com/api/qt/clist/get?cb=jQuery112406416960359221422_1566051679805" \
                     "&pn=188&pz=20&po=1&np=1&ut=bd1d9ddb04089700cf9c27f6f7426281&fltt=2&invt=2&fid=f12"\
                     "&fs=m:0+t:6,m:0+t:13,m:0+t:80,m:1+t:2&fields=f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f12,f13,"\
                     "f14,f15,f16,f17,f18,f20,f21,f23,f24,f25,f22,f11,f62,f128,f136,f115,f152&_=1566051679850");
}

EastMoneySpider::~EastMoneySpider()
{
    //dtor
}

/************************************
 *@param none
 *@return bool if failure return false
 ************************************/
bool EastMoneySpider::Run()
{
    return false;
}
