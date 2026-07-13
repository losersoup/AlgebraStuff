//
// Created by georg on 04/07/2026.
//

#ifndef INTROALGEBRA_COSETALGOS_H
#define INTROALGEBRA_COSETALGOS_H

#include "../OneOpAlgebraic.h"
#include "../Coset.h"

template<typename T>
Coset<T> LeftCoset(OneOpAlgebraic<T>& G, const T& g, Set<T> &H) {
    if (!G.isSubgroup(H)) {
        throw std::logic_error("Bad Subset.");
    }

    Coset<T> K(G, H.getElements(), g, true);

    return K;

}

template<typename T>
Coset<T> RightCoset(OneOpAlgebraic<T>& G, const T& g, Set<T> &H) {
    if (!G.isSubgroup(H)) {
        throw std::logic_error("Bad Subset.");
    }

    Coset<T> K(G, H.getElements(), g, false);

    return K;

}


template<typename T>
OneOpAlgebraic<Coset<T>> FactorGroup(OneOpAlgebraic<T>& G, Set<T>& H) {
    if (!G.isNormal(H)) {
        throw std::logic_error("Subgroup is not normal in G. Exiting..");
    }
    std::vector<T> s1 = G.getElements();
    std::vector<T> s2 = H.getElements();
    std::vector<Coset<T>> cosets;
    bOp<Coset<T>> op = [](const Coset<T>& A,
                      const Coset<T>& B)
    {
        return A * B;
    };
    for (const T& g : s1) {
        Coset<T> current = LeftCoset(G, g, H);
        if (!std::ranges::contains(cosets, current)) {
            cosets.push_back(current);
        }
    }
    auto parser = [&G, &H](const std::string& s)
    {
        T representative = G.parse(s);
        return LeftCoset(G, representative, H);
    };
    OneOpAlgebraic<Coset<T>> FG(cosets, op, parser);
    return FG;
}


template<typename T>
void LeftCosetPartitionCompact(OneOpAlgebraic<T>& G, Set<T> &H) {
    std::vector<T> s1 = G.getElements();
    std::vector<T> s2 = H.getElements();
    std::vector<Coset<T>> cosets;
    std::cout<<"{";
    for (const T& g : s1) {
        Coset<T> current = LeftCoset(G, g, H);
        if (!std::ranges::contains(cosets, current)) {
            cosets.push_back(current);
            current.displayCompact();
            std::cout<<", ";
        }
    }
    std::cout<<"}";
}


template<typename T>
void RightCosetPartitionCompact(OneOpAlgebraic<T>& G, Set<T> &H) {
    std::vector<T> s1 = G.getElements();
    std::vector<T> s2 = H.getElements();
    std::vector<Coset<T>> cosets;
    std::cout<<"{";
    for (const T& g : s1) {
        Coset<T> current = RightCoset(G, g, H);
        if (!std::ranges::contains(cosets, current)) {
            cosets.push_back(current);
            current.displayCompact();
            std::cout<<", ";
        }
    }
    std::cout<<"}";
}




#endif //INTROALGEBRA_COSETALGOS_H
