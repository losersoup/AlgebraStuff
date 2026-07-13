//
// Created by georg on 04/07/2026.
//

#ifndef INTROALGEBRA_DIHEDRAL_H
#define INTROALGEBRA_DIHEDRAL_H


#pragma once

#include <string>
#include "../OneOpAlgebraic.h"



template<typename T>
using bOp = std::function<T(const T& el1, const T& el2)>;

struct DihedralElement {
    int rotation;
    bool reflection;

    bool operator==(const DihedralElement&) const = default;
};


std::string toString(int rot, bool refl);
DihedralElement parseD(const std::string& x);

OneOpAlgebraic<DihedralElement> createDihedral(int n);

std::ostream& operator<<(std::ostream& os, const DihedralElement& x);
std::istream& operator>>(std::istream& is, DihedralElement& d);



namespace std
{
    template<>
    struct hash<DihedralElement>
    {
        size_t operator()(const DihedralElement& x) const
        {
            size_t h = hash<int>{}(x.rotation);

            h ^= hash<bool>{}(x.reflection)
                 + 0x9e3779b9
                 + (h << 6)
                 + (h >> 2);

            return h;
        }
    };
}


#endif //INTROALGEBRA_DIHEDRAL_H
