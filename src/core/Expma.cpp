#include "Expma.h"

Expma::Expma()
{
    //ctor
}

Expma::~Expma()
{
    //dtor
}

wxVector<double> Expma::Calc(wxVector<double> data,int N)
{
    double Y = data[0];
    wxVector<double> expma;
    wxVector<double>::const_iterator it;
    for(it = data.begin(); it != data.end(); ++it)
    {
        double Y2 = (2*(*it)+(N-1)*Y)/(N+1);
        expma.push_back(Y2);
        Y = Y2;
    }
    return expma;
}
