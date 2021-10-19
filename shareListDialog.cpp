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
    if(m_pChineseUnitRender){
        delete m_pChineseUnitRender;
    }
    if(m_pDoubleRender){
        delete m_pDoubleRender;
    }
    if(m_pPercentRender){
        delete m_pPercentRender;
    }
    if(m_pTextRender){
        delete m_pTextRender;
    }
    if(m_pIntRender){
        delete m_pIntRender;
    }
    if(m_dataView){
        delete m_dataView;
    }
}


void shareListDialog::OnInit(wxInitDialogEvent& event)
{

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



    m_dataView = new wxDataViewListCtrl(this, IDDATAVIEW, wxDefaultPosition, wxSize(1400, 800));
    m_pChineseUnitRender = new wxChineseUintRender(wxDATAVIEW_CELL_ACTIVATABLE);
    m_pDoubleRender = new wxDoubleRender(wxDATAVIEW_CELL_ACTIVATABLE);
    m_pPercentRender = new wxPercentRender(wxDATAVIEW_CELL_ACTIVATABLE);
    m_pTextRender = new wxDataViewTextRenderer();
    m_pIntRender = new wxIntRender(wxDATAVIEW_CELL_ACTIVATABLE);
    for (unsigned i=0; i<headers.size(); i++) {
        if(i==0) {
            m_dataView->AppendColumn(new wxDataViewColumn(headers[i], m_pIntRender, i, 100,
                                     wxAlignment(wxALIGN_LEFT | wxALIGN_TOP),
                                     wxDATAVIEW_COL_SORTABLE|wxDATAVIEW_COL_RESIZABLE));
        } else if(i == 1 || i == 2) {
            m_dataView->AppendColumn(new wxDataViewColumn(headers[i], m_pTextRender, i, 100,
                                     wxAlignment(wxALIGN_LEFT | wxALIGN_TOP),
                                     wxDATAVIEW_COL_SORTABLE|wxDATAVIEW_COL_RESIZABLE));
        } else if(i==6||i==7||i==16||i==17) {
            m_dataView->AppendColumn(new wxDataViewColumn(headers[i], m_pChineseUnitRender, i, 100,
                                     wxAlignment(wxALIGN_LEFT | wxALIGN_TOP),
                                     wxDATAVIEW_COL_SORTABLE|wxDATAVIEW_COL_RESIZABLE));
        } else if(i ==3||i==5||i==9||i==10||i==11||i==12||i==14||i==15) {
            m_dataView->AppendColumn(new wxDataViewColumn(headers[i], m_pDoubleRender, i, 100,
                                     wxAlignment(wxALIGN_LEFT | wxALIGN_TOP),
                                     wxDATAVIEW_COL_SORTABLE|wxDATAVIEW_COL_RESIZABLE));
        } else if(i==4||i==8||i==13) {
            m_dataView->AppendColumn(new wxDataViewColumn(headers[i], m_pPercentRender, i, 100,
                                     wxAlignment(wxALIGN_LEFT | wxALIGN_TOP),
                                     wxDATAVIEW_COL_SORTABLE|wxDATAVIEW_COL_RESIZABLE));
        }

    }
    //shares 转化成 wxVariant
    wxVector<wxVariant> data;
    for(unsigned i=0; i<allShares.size(); i++) {
        ShareDetail share = allShares[i];
        data.clear();
        data.push_back( wxVariant(static_cast<int>(i+1)) );
        data.push_back( wxVariant(share.code) );
        data.push_back( wxVariant(share.name) );
        data.push_back( wxVariant(share.price_now) );
        data.push_back( wxVariant(share.change_rate) );
        data.push_back( wxVariant(share.change_amount) );
        data.push_back( wxVariant(static_cast<long>(share.volume)) );
        data.push_back( wxVariant(static_cast<long>(share.amount)) );
        data.push_back( wxVariant(share.amplitude) );
        data.push_back( wxVariant(share.price_max) );
        data.push_back( wxVariant(share.price_min) );
        data.push_back( wxVariant(share.price_open) );
        data.push_back( wxVariant(share.qrr) );
        data.push_back( wxVariant(share.turnover_rate) );
        data.push_back( wxVariant(share.pe) );
        data.push_back( wxVariant(share.pb) );
        data.push_back( wxVariant(static_cast<long>(share.total_capital)) );
        data.push_back( wxVariant(static_cast<long>(share.trade_capital)) );
        m_dataView->AppendItem( data );
    }
}
