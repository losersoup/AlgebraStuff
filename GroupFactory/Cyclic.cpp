//
// Created by georg on 04/07/2026.
//

#include "Cyclic.h"
#include "../OneOpAlgebraic.h"


OneOpAlgebraic<ZnElement> createCyclicGroup(const int n)  {

    std::vector<ZnElement> elems;

    for (int i = 0; i < n; i++) {
        elems.push_back(ZnElement(i));
    }
    bOp<ZnElement> modn  = [n](ZnElement a, ZnElement b)
    {
        return ZnElement{ (a.value + b.value) % n };
    };

    OneOpAlgebraic<ZnElement> G(elems, modn, parseZN);

    return G;
}
std::ostream& operator<<(std::ostream& os,
                         const ZnElement& x)
{
    return os << x.value;
}

std::istream& operator>>(std::istream& is, ZnElement& x)
{
    return is >> x.value;
}


ZnElement parseZN(const std::string& a) {

    int num = std::stoi(a);
    ZnElement x(num);
    return x;
}

