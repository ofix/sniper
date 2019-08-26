#ifndef EXPMA_H
#define EXPMA_H
#include <wx/vector.h>

class Expma
{
    public:
        Expma(wxVector<double> data,int N);
        virtual ~Expma();
        static wxVector<double> Calc();
    protected:
        static wxVector<double> m_data;
        int m_n;
};

#endif // EXPMA_H
