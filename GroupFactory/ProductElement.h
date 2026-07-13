//
// Created by georg on 09/07/2026.
//

#ifndef INTROALGEBRA_PRODUCTELEMENT_H
#define INTROALGEBRA_PRODUCTELEMENT_H

#include <iostream>
#include "../OneOpAlgebraic.h"


std::pair<std::string, std::string>
splitProduct(const std::string& s);
template<typename A, typename B>

struct ProductElement {
    A first;
    B second;

    bool operator==(const ProductElement&) const = default;
};



template<typename A, typename B>
std::ostream& operator<<(std::ostream& os,
                        const ProductElement<A,B>& x)
{
    return os << "(" << x.first << ", " << x.second << ")";
}

template<typename A, typename B>
OneOpAlgebraic<ProductElement<A,B>> directProduct(const OneOpAlgebraic<A>& G, const OneOpAlgebraic<B>& H) {
    std::vector<ProductElement<A,B>> elems;

    for (const A& a : G.getElements()) {
        for (const B& b : H.getElements()) {
            elems.push_back({a,b});
        }
    }


    auto op = [&G, &H](const auto& x, const auto& y)
    {
        return ProductElement<A,B>{
            G.multiply(x.first, y.first),
            H.multiply(x.second, y.second)
        };
    };


    auto parser = [&G,&H](const std::string& s)
    {
        auto [left,right] = splitProduct(s);


        return ProductElement<A,B>{
            G.parse(left),
            H.parse(right)
        };
    };


    return OneOpAlgebraic<ProductElement<A,B>>(elems, op, parser);


}

namespace std {


    template<typename A, typename B>
    struct hash<ProductElement<A,B>>
    {
        size_t operator()(const ProductElement<A,B>& x) const
        {
            size_t h = hash<A>{}(x.first);


            h ^= hash<B>{}(x.second)
                 + 0x9e3779b9
                 + (h << 6)
                 + (h >> 2);


            return h;
        }
    };


}





#endif //INTROALGEBRA_PRODUCTELEMENT_H
