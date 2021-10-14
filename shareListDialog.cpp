#include "shareListDialog.h"

//(*InternalHeaders(shareListDialog)
#include <wx/string.h>
//*)

//(*IdInit(shareListDialog)
//*)

BEGIN_EVENT_TABLE(shareListDialog,wxDialog)
    //(*EventTable(shareListDialog)
    //*)
END_EVENT_TABLE()

shareListDialog::shareListDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(shareListDialog)
    Create(parent, id, _T("沪深股票列表"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(1072,481));

    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&shareListDialog::OnInit);
    //*)
}

shareListDialog::~shareListDialog()
{
    //(*Destroy(shareListDialog)
    //*)
}


void shareListDialog::OnInit(wxInitDialogEvent& event)
{

    return ;
    //请求数据
    EastMoneySpider spiderEastMoney;
    bool bRet = spiderEastMoney.Run();
    std::vector<ShareDetail> allShares;
    if(bRet) {
        allShares= spiderEastMoney.GetAllShares();
    }

    std::vector<wxString> headers;
    headers.push_back(wxT("序号"));
    headers.push_back(wxT("代码"));
    headers.push_back(wxT("名称"));
    headers.push_back(wxT("最新价"));
    headers.push_back(wxT("涨跌幅"));
    headers.push_back(wxT("涨跌额"));
    headers.push_back(wxT("成交量(手)"));
    headers.push_back(wxT("成交额"));
    headers.push_back(wxT("振幅"));
    headers.push_back(wxT("最高"));
    headers.push_back(wxT("最低"));
    headers.push_back(wxT("今开"));
    headers.push_back(wxT("量比"));
    headers.push_back(wxT("换手率"));
    headers.push_back(wxT("市盈率(动态)"));
    headers.push_back(wxT("市净率"));
    headers.push_back(wxT("总市值"));
    headers.push_back(wxT("流通市值"));


    m_dataView = new wxDataViewCtrl(this, IDDATAVIEW, wxDefaultPosition, wxSize(1700, 800), wxDV_VARIABLE_LINE_HEIGHT);
    wxShareRender* m_dataViewRender = new wxShareRender(wxDATAVIEW_CELL_INERT); //只可查看的cell
    for (unsigned i=0; i<headers.size(); i++) {
        m_dataViewColumns.push_back(new wxDataViewColumn(headers[i], m_dataViewRender, i, 100, wxAlignment(wxALIGN_LEFT | wxALIGN_TOP), wxDATAVIEW_COL_RESIZABLE));
        m_dataView->AppendColumn(m_dataViewColumns[i]);
    }
    m_dataView->AssociateModel(m_dataViewModel);

}
