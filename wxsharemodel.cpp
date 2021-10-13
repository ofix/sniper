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
        variant = (double)node->price_open;
        break;
    case 4:
        variant = 80L;  // all music is very 80% popular
        break;
    case 5:
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
        return true;
    case 5:
        return true;
    case 6:
        return true;
    case 7:
        return true;
    case 8:
        return true;

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
    return wxDataViewItem(0);
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
