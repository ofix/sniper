#include "spider/EastMoneySpider.h"
#include <wx/datetime.h>
EastMoneySpider::EastMoneySpider(wxString strUrl):StockSpider(strUrl)
{
    //ctor
    m_url = wxT("http://98.push2.eastmoney.com/api/qt/clist/get?"\
                "pn=1&pz=1000&po=1&np=1&ut=bd1d9ddb04089700cf9c27f6f7426281&fltt=2&invt=2&fid=f3&fs=m:0+t:6,m:0+t:80,m:1+t:2,m:1+t:23"\
                "&fields=f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f12,f13,f14,f15,f16,f17,f18,f20,f21,f23,f24,f25,f22,f11,f62,f128,f136,f115,f152&_=");
    wxDateTime now = wxDateTime::UNow(); //获取当前Linux时间戳，单位:毫秒
    wxString strNow = wxString::Format("%lld",now.GetValue());
    m_url += strNow;
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
    wxString response;
    http(m_url,response,wxFONTENCODING_UTF8);

    wxJSONReader reader;
    wxJSONValue  jsonRoot;
    console(m_url);
    fixBadJson(response);

    // resStock has already been UNICODE
    int numErrors = 0;
    numErrors = reader.Parse(response, &jsonRoot);
    // parse error
    if ( numErrors != 0 ) {
        wxArrayString err = reader.GetErrors();
        for(size_t i=0; i<err.GetCount(); i++) {
            std::wcout<<"ERROR :  "<<err.Item(i)<<std::endl;
        }
        return false;
    }
    // response format error
    if(!jsonRoot.HasMember(wxT("data"))) {
        return false;
    }
    wxJSONValue total = jsonRoot["data"]["total"];
#ifdef DEBUG_SNIPER
    std::cout<<"total stock: "<<total.AsInt()<<std::endl;
    std::cout<<"response: "<<response<<std::endl;
#endif // DEBUG_SNIPER
    wxJSONValue diff = jsonRoot["data"]["diff"];
    if(diff.IsArray()) {
        m_shares.clear();
        ShareDetail item;
        for(int i=0; i<diff.Size(); i++) {
//            std::cout<<"i:"<<i<<diff[i]["f14"].AsString()<<std::endl;

            if(diff[i]["f2"].IsString()) { //未上市公司
                std::wcout<<"未上市公司: "<<diff[i]["f14"].AsString()<<",  i="<<i<<std::endl;
                continue;
            }
            item.code = diff[i]["f12"].AsString(); //股票代码
            item.name = diff[i]["f14"].AsString(); //股票名称
            item.price_now = diff[i]["f2"].AsDouble(); //最新价
            item.change_rate =diff[i]["f3"].AsDouble(); //涨跌幅
            item.change_amount = diff[i]["f4"].AsDouble(); //涨跌额
            item.volume = diff[i]["f5"].AsUInt64(); //成交量

            if(diff[i]["f6"].IsDouble()) { //修正成交额大于 MAX_INT 时格式化为浮点数的问题
                item.amount = static_cast<uint64_t>(diff[i]["f6"].AsDouble());
            } else {
                item.amount = diff[i]["f6"].AsUInt64(); //成交额
            }
            item.amplitude = diff[i]["f7"].AsDouble(); //振幅
            item.turnover_rate = diff[i]["f8"].AsDouble(); //换手率
            item.pe = diff[i]["f9"].AsDouble(); //动态市盈率
            item.pb= diff[i]["f23"].AsDouble();//市净率
            if(diff[i]["f10"].IsDouble()) {
                item.qrr = diff[i]["f10"].AsDouble(); //量比
            } else {
                item.qrr = 0.0f;
            }
            item.price_max = diff[i]["f15"].AsDouble(); //最高价
            item.price_min = diff[i]["f16"].AsDouble(); //最低价
            item.price_open = diff[i]["f17"].AsDouble(); //开盘价
            item.total_capital = diff[i]["f20"].AsUInt64(); //总市值
            item.trade_capital = diff[i]["f21"].AsUInt64(); //流通市值
            m_shares.push_back(item);
#ifdef DEBUG_SNIPER
            std::cout<<"code:"<<item.code<<",";
            std::cout<<"name:"<<item.name<<",";
            std::cout<<"price_now:"<<item.price_now<<",";
            std::cout<<"price_max:"<<item.price_max<<",";
            std::cout<<"price_min:"<<item.price_min<<",";
            std::cout<<"price_open:"<<item.price_open<<",";
            std::cout<<"change_rate:"<<item.change_rate<<",";
            std::cout<<"change_amount:"<<item.change_amount<<",";
            std::cout<<"volume:"<<item.volume<<",";
            std::cout<<"amount:"<<item.amount<<",";
            std::cout<<"amplitude:"<<item.amplitude<<",";
            std::cout<<"turnover_rate:"<<item.turnover_rate<<",";
            std::cout<<"pe:"<<item.pe<<",";
            std::cout<<"pb:"<<item.pb<<",";
            std::cout<<"qrr:"<<item.qrr<<",";
            std::cout<<"total_capital:"<<item.total_capital<<",";
            std::cout<<"trade_capital:"<<item.trade_capital<<std::endl;
#endif // DEBUG_SNIPER
        }
        return true;
    }
    return false;
}
