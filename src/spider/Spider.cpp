#include "spider/Spider.h"

Spider::Spider(wxString strUrl)
{
    m_url= strUrl;
    m_bRun = false;
    m_timeStart = wxDateTime::Now();
    m_timeEnd = wxDateTime::Now();
}

Spider::~Spider()
{
    //dtor
}

wxLongLong Spider::GetUsedTime()
{
    wxTimeSpan span = m_timeEnd- m_timeStart;
    return span.GetSeconds();
}

bool Spider::Run()
{
    return false;
}

void* Spider::GetResult()
{
    return nullptr;
}
