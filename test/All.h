#ifndef ALL_H
#define ALL_H

#include <string>

namespace Test
{
    void RunAll();
    void mark_down();
    void regex_match();
    int symmetry_nums();
    template<typename T>
    std::string numToBits(T n);
    template<typename T>
    bool is_num_symmetry(T num);
}

#endif // ALL_H
