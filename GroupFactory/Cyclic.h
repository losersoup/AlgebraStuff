//
// Created by georg on 04/07/2026.
//

#ifndef INTROALGEBRA_CYCLIC_H
#define INTROALGEBRA_CYCLIC_H

#include "../OneOpAlgebraic.h"

struct ZnElement
{
    int value;

    bool operator==(const ZnElement&) const = default;
};
std::ostream& operator<<(std::ostream& os,
                         const ZnElement& x);
std::istream& operator>>(std::istream& is, ZnElement& x);


ZnElement parseZN(const std::string& a);


#include "Cyclic.h"


OneOpAlgebraic<ZnElement> createCyclicGroup(int n);
namespace std
{
    template<>
    struct hash<ZnElement>
    {
        size_t operator()(const ZnElement& x) const
        {
            return hash<int>{}(x.value);
        }
    };
}


#endif //INTROALGEBRA_CYCLIC_H
