#include "wxsharemodel.h"

#include <wx/log.h>
#define INITIAL_NUMBER_OF_ITEMS 5000

wxShareModel::wxShareModel():
    wxDataViewModel()
{
    // the first 100 items are really stored in this model;
    // all the others are synthesized on request

}

wxShareModel::~wxShareModel()
{
    //dtor
}

wxString wxShareModel::GetCode( const wxDataViewItem &item ) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return wxEmptyString;
    return node->code;
}
wxString wxShareModel::GetName( const wxDataViewItem &item ) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return wxEmptyString;
    return node->name;
}
double wxShareModel::GetPriceNow(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->price_now;
}
double wxShareModel::GetChangeAmount(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->change_amount;
}
uint64_t wxShareModel::GetVolume(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0;
    return node->volume;
}
uint64_t wxShareModel::GetAmount(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0;
    return node->amount;
}
double wxShareModel::GetPriceMax(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->price_max;
}
double wxShareModel::GetPriceMin(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->price_min;
}
double wxShareModel::GetPriceOpen(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->price_open;
}
double wxShareModel::GetPriceClose(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->price_close;
}
double wxShareModel::GetQrr(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->qrr;
}
double wxShareModel::GetPe(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->pe;
}
double wxShareModel::GetPb(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->pb;
}
double wxShareModel::GetTurnOverRate(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0.0f;
    return node->turnover_rate;
}
uint64_t wxShareModel::GetTotalCapital(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0;
    return node->total_capital;
}
uint64_t wxShareModel::GetTradeCapital(const wxDataViewItem &item) const
{
    ShareDetail *node = (ShareDetail*) item.GetID();
    if(!node)
        return 0;
    return node->trade_capital;
}

void wxShareModel::AddShare(ShareDetail &data)
{
    m_shares.push_back(data);
}


static int my_sort_reverse( int *v1, int *v2 )
{
    return *v2-*v1;
}

static int my_sort( int *v1, int *v2 )
{
    return *v1-*v2;
}

int wxShareModel::Compare( const wxDataViewItem &item1, const wxDataViewItem &item2,
                           unsigned int column, bool ascending ) const
{
    wxASSERT(item1.IsOk() && item2.IsOk());
    // should never happen

    if (IsContainer(item1) && IsContainer(item2)) {
        wxVariant value1, value2;
        GetValue( value1, item1, 0 );
        GetValue( value2, item2, 0 );

        wxString str1 = value1.GetString();
        wxString str2 = value2.GetString();
        int res = str1.Cmp( str2 );
        if (res) return res;

        // items must be different
        wxUIntPtr litem1 = (wxUIntPtr) item1.GetID();
        wxUIntPtr litem2 = (wxUIntPtr) item2.GetID();

        return litem1-litem2;
    }

    return wxDataViewModel::Compare( item1, item2, column, ascending );
}

void wxShareModel::GetValue( wxVariant &variant, const wxDataViewItem &item, unsigned int col ) const
{
    wxASSERT(item.IsOk());

    ShareDetail *node = (ShareDetail*) item.GetID();
    switch (col) {
    case 0:
        variant = (long int)node->id;
        break;
    case 1:
        variant = node->code;
        break;
    case 2:
        variant = node->name;
        break;
    case 3:
        variant = (double)node->price_now;
        break;
    case 4:
        variant = (double)node->change_rate;
        break;
    case 5:
        variant = (double)node->change_amount;
        break;
    case 6:
        variant = (wxULongLong)node->volume;
        break;
    case 7:
        variant = (wxULongLong)node->amount;
        break;
    case 8:
        variant = (double)node->amplitude;
        break;
    case 9:
        variant = (double)node->price_max;
        break;
    case 10:
        variant = (double)node->price_min;
        break;
    case 11:
        variant = (double)node->price_open;
        break;
    case 12:
        variant = (double)node->qrr;
        break;
    case 13:
        variant = (double)node->turnover_rate;
        break;
    case 14:
        variant = (double)node->pe;
        break;
    case 15:
        variant = (double)node->pb;
        break;
    case 16:
        variant = (long)node->total_capital;
        break;
    case 17:
        variant = (long)node->trade_capital;
        break;

    default:
        wxLogError( "wxShareModel::GetValue: wrong column %d", col );
    }
}

bool wxShareModel::SetValue( const wxVariant &variant,const wxDataViewItem &item, unsigned int col )
{
    wxASSERT(item.IsOk());

    ShareDetail *node = (ShareDetail*) item.GetID();
    switch (col) {
    case 0:
        node->id = variant.GetInteger();
        return true;
    case 1:
        node->code = variant.GetString();
        return true;
    case 2:
        node->name = variant.GetString();
        return true;
    case 3:
        node->price_open = variant.GetDouble();
        return true;
    case 4:
        node->change_rate=variant.GetDouble();
        break;
    case 5:
        node->change_amount=variant.GetDouble();
        break;
    case 6:
        node->volume=variant.GetDouble();
        break;
    case 7:
        node->amount=variant.GetDouble();
        break;
    case 8:
        node->amplitude=variant.GetDouble();
        break;
    case 9:
        node->price_max=variant.GetDouble();
        break;
    case 10:
        node->price_min=variant.GetDouble();
        break;
    case 11:
        node->price_open=variant.GetDouble();
        break;
    case 12:
        node->qrr=variant.GetDouble();
        break;
    case 13:
        node->turnover_rate=variant.GetDouble();
        break;
    case 14:
        node->pe=variant.GetDouble();
        break;
    case 15:
        node->pb=variant.GetDouble();
        break;
    case 16:
        node->total_capital=(uint64_t)variant.GetLong();
        break;
    case 17:
        node->trade_capital=(uint64_t)variant.GetLong();
        break;
    default:
        wxLogError( "wxShareModel::SetValue: wrong column" );
    }
    return false;
}

bool wxShareModel::IsEnabled( const wxDataViewItem &item,unsigned int col ) const
{
    wxASSERT(item.IsOk());

    return true;
}

wxDataViewItem wxShareModel::GetParent( const wxDataViewItem &item ) const
{
    // the invisible root node has no parent
    return  wxDataViewItem(NULL);
}

bool wxShareModel::IsContainer( const wxDataViewItem &item ) const
{
    // the invisble root node can have children
    // (in our model always "MyMusic")
    return false;
}

unsigned int wxShareModel::GetChildren( const wxDataViewItem &parent,wxDataViewItemArray &array ) const
{
    return 0;
}
