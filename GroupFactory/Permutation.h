//
// Created by georg on 04/07/2026.
//

#ifndef INTROALGEBRA_PERMUTATION_H
#define INTROALGEBRA_PERMUTATION_H

#include <vector>
#include <string>
#include "../OneOpAlgebraic.h"
#include <numeric>

struct Permutation {
    std::vector<int> image;


    bool operator==(const Permutation& a) const = default;

    std::string toCycleString() const;
    static Permutation fromCycleString(const std::string&, size_t n);

    
};

Permutation compose(const Permutation& a, const Permutation& b);

std::ostream& operator<<(std::ostream& os, const Permutation& p);
OneOpAlgebraic<Permutation> createSymmetryGroup(int n);

OneOpAlgebraic<Permutation> createAlternatingGroup(int n);
std::istream& operator>>(std::istream& is, Permutation& p);

OneOpAlgebraic<Permutation> customPermutationGroup(int n);
bool evenPermParity(Permutation& p);

namespace std {

    template<>
    struct hash<Permutation>
    {
        size_t operator()(const Permutation& p) const
        {
            size_t h = 0;

            for (int x : p.image)
            {
                h ^= std::hash<int>{}(x)
                     + 0x9e3779b9
                     + (h << 6)
                     + (h >> 2);
            }

            return h;
        }
    };

}




#endif //INTROALGEBRA_PERMUTATION_H
