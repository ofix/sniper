#include "Expma.h"

Expma::Expma(wxVector<double> data,int N):m_data(data),m_n(N)
{
    //ctor
}

Expma::~Expma()
{
    //dtor
}

static wxVector<double> Expma::Calc()
{
    double Y = m_data[0];
    wxVector<double> expma;
    wxVector<double>::const_iterator it;
    for(it = m_data.begin(); it != m_data.end(); ++it)
    {
        double Y2 = 2*(*it)+(N-1)*Y)/(N+1);
        expma.push_back(Y2);
        Y = Y2;
    }
    return expma;
}
