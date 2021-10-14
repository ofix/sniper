#ifndef WXSHAREMODEL_H
#define WXSHAREMODEL_H

#include "core/Stock.h"
#include <wx/dataview.h>

class wxShareModel:public wxDataViewModel
{
public:
    wxShareModel();
    virtual ~wxShareModel();
    wxString GetCode( const wxDataViewItem &item ) const;
    wxString GetName( const wxDataViewItem &item ) const;
    double GetPriceNow(const wxDataViewItem &item) const;
    double GetChangeAmount(const wxDataViewItem &item) const;
    uint64_t GetVolume(const wxDataViewItem &item) const;
    uint64_t GetAmount(const wxDataViewItem &item) const;
    double GetPriceMax(const wxDataViewItem &item) const;
    double GetPriceMin(const wxDataViewItem &item) const;
    double GetPriceOpen(const wxDataViewItem &item) const;
    double GetPriceClose(const wxDataViewItem &item) const;
    double GetQrr(const wxDataViewItem &item) const;
    double GetPe(const wxDataViewItem &item) const;
    double GetPb(const wxDataViewItem &item) const;
    double GetTurnOverRate(const wxDataViewItem &item) const;
    uint64_t GetTotalCapital(const wxDataViewItem &item) const;
    uint64_t GetTradeCapital(const wxDataViewItem &item) const;

    /*
     double price_now;//最新价
    double change_amount; //涨跌额
    double change_rate; //涨跌幅度
    uint64_t volume; //成交量
    uint64_t amount; //成交额
    double amplitude; //振幅
    double price_max; //最高价
    double price_min; //最低价
    double price_open; //开盘价
    double price_close; //收盘价
    double qrr;// 量比 quantity relative ratio
    double pe;//市盈率
    double pb;//市净率
    double turnover_rate; //换手率
    uint64_t total_capital; //总市值
    uint64_t trade_capital; //流通股本

    */

    void AddShare(ShareDetail &data);
    /*

    */
    virtual unsigned int GetColumnCount() const wxOVERRIDE
    {
        return 17;
    }
    virtual wxString GetColumnType( unsigned int col ) const wxOVERRIDE
    {
        if(col==0) {
            return wxT("long");
        } else if (col == 1||col==2) {
            return wxT("string");
        } else if(col >=3 && col<=15) {
            return wxT("double");
        } else if(col == 16 || col == 17) {
            return wxT("uint64_t");
        }
    }
    // override sorting to always sort branches ascendingly
    int Compare( const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending ) const wxOVERRIDE;

    virtual void GetValue( wxVariant &variant, const wxDataViewItem &item, unsigned int col ) const wxOVERRIDE;

    virtual bool SetValue( const wxVariant &variant, const wxDataViewItem &item, unsigned int col ) wxOVERRIDE;

    virtual bool IsEnabled( const wxDataViewItem &item, unsigned int col ) const wxOVERRIDE;

    virtual wxDataViewItem GetParent( const wxDataViewItem &item ) const wxOVERRIDE;

    virtual bool IsContainer( const wxDataViewItem &item ) const wxOVERRIDE;

    virtual unsigned int GetChildren( const wxDataViewItem &parent, wxDataViewItemArray &array ) const wxOVERRIDE;

protected:

private:
    std::vector<ShareDetail> m_shares;
};

#endif // WXSHAREMODEL_H
