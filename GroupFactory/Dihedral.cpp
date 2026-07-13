//
// Created by georg on 04/07/2026.
//

#include "Dihedral.h"
#include "../OneOpAlgebraic.h"
#include "../Set.h"

std::string toString(const DihedralElement& x)
{
    int rot = x.rotation;
    bool refl = x.reflection;



    if (!refl)
    {
        if (rot == 0) return "e";
        if (rot == 1) return "r";
        return pretty("r^" + std::to_string(rot));
    }

    if (rot == 0) return "v";
    if (rot == 1) return "rv";

    return pretty("r^" + std::to_string(rot) + "v");
}

std::string toString(int rot, bool refl)
{
    return toString({rot, refl});
}

DihedralElement parseD(const std::string& x)
{
    if (x == "e")
        return {0,false};

    if (x == "v")
        return {0,true};

    if (x == "r")
        return {1,false};

    if (x == "rv")
        return {1,true};

    if (x.starts_with("r^"))
    {
        auto pos = x.find('v');
        bool refl = pos != std::string::npos;

        std::string number =
            refl ? x.substr(2, pos - 2)
                 : x.substr(2);

        return {std::stoi(number), refl};
    }

    throw std::runtime_error("Bad dihedral element");
}

OneOpAlgebraic<DihedralElement> createDihedral(const int n) {
    std::vector<DihedralElement> elems;

    for (int i = 0; i < n; ++i)
        elems.push_back({i,false});

    for (int i = 0; i < n; ++i)
        elems.push_back({i,true});
    bOp<DihedralElement> mult = [n]
        (const DihedralElement& A,
            const DihedralElement& B)
    {
        auto mod = [n](int x)
        {
            x %= n;
            if (x < 0) x += n;
            return x;
        };

        DihedralElement result;

        if (!A.reflection && !B.reflection)
        {
            result.rotation = mod(A.rotation + B.rotation);
            result.reflection = false;
        }
        else if (!A.reflection && B.reflection)
        {
            result.rotation = mod(A.rotation + B.rotation);
            result.reflection = true;
        }
        else if (A.reflection && !B.reflection)
        {
            result.rotation = mod(A.rotation - B.rotation);
            result.reflection = true;
        }
        else
        {
            result.rotation = mod(A.rotation - B.rotation);
            result.reflection = false;
        }

        return result;
    };
    return OneOpAlgebraic<DihedralElement>(elems, mult, parseD);
}

std::ostream& operator<<(std::ostream& os, const DihedralElement& x)
{
    return os << toString(x);
}
std::istream& operator>>(std::istream& is, DihedralElement& d)
{
    std::string token;
    is >> token;

    try
    {
        d = parseD(token);
    }
    catch (...)
    {
        is.setstate(std::ios::failbit);
    }

    return is;
}
