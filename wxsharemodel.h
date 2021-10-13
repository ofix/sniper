#ifndef WXSHAREMODEL_H
#define WXSHAREMODEL_H

#include "core/Stock.h"
#include <wx/dataview.h>

class wxShareModel:public wxDataViewModel
{
public:
    wxShareModel();
    virtual ~wxShareModel();
    void AddShare(ShareDetail data);
    /*

    */
    virtual unsigned int GetColumnCount() const wxOVERRIDE
    {
        return 17;
    }
    virtual wxString GetColumnType( unsigned int col ) const wxOVERRIDE
    {
        if(col==0) {
            return wxT('longint');
        } else if (col == 1||col==2) {
            return wxT("string");
        } else if(col >=3 && col<=15) {
            return wxT("double");
        } else if(col == 16 || col == 17) {
            return wxT("int64");
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
