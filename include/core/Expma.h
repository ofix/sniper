#ifndef EXPMA_H
#define EXPMA_H
#include <wx/vector.h>

class Expma
{
    public:
        Expma();
        virtual ~Expma();
        static wxVector<double> Calc(wxVector<double> data,int N);
};

#endif // EXPMA_H
