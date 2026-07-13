//
// Created by georg on 03/07/2026.
//

#ifndef INTROALGEBRA_COSET_H
#define INTROALGEBRA_COSET_H
#include "Set.h"
#include "OneOpAlgebraic.h"

template<typename T>




class Coset : public Set<T> {

private:
    const OneOpAlgebraic<T>* Parent;
    T repr;
    Set<T> base;
    T repinv;
    bool left;
    char name;

    static std::vector<T> makeCoset(
        const OneOpAlgebraic<T> &G,
        const std::vector<T> &subgroup,
        const T &repr,
        bool left
        )
    {
        if (repr == G.getIdentity()) {
            return subgroup;
        }
        std::vector<T> result;
        result.reserve(subgroup.size());

        for (const auto& x : subgroup) {
            if (left)
                result.push_back(G.multiply(repr, x));
            else
                result.push_back(G.multiply(x, repr));
        }

        return result;
    }

public:
    Coset(const OneOpAlgebraic<T>& G,
          const std::vector<T>& subgroup,
          T repr,
          bool left,
          char name = 'H')
        : Set<T>(makeCoset(G, subgroup, repr, left)),
          Parent(&G),
          repr(repr),
          base(subgroup),
          left(left),
          name(name)
    {
        repinv = Parent->invertElement(repr);
    }

    std::string compactString() const
    {
        if (repr == Parent->getIdentity())
            return std::string(1, name);

        return pretty(repr) + std::string(1, name);
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const Coset& c)
    {
        return os << c.compactString();
    }

    void displayWoutRep() {
        if (repr!=Parent->getIdentity()) {
            std::cout << repr << "·";
        }
        base.displaySet();
    }


    void displayCompact() {
        std::cout << pretty(repr) << name;
    }


    void displayWRep() {
        this->displaySet();
    }
    bool operator==(const Coset& other) const
    {
        return static_cast<const Set<T>&>(*this)
             == static_cast<const Set<T>&>(other);
    }

    Coset operator*(const Coset& other) const {

        if (Parent != other.Parent || !(base == other.base)) {
            throw std::logic_error("Incompatible Cosets");
        }

        return Coset(
            *Parent,
            base.getElements(),
            Parent->multiply(repr, other.repr),
            left,
            name
        );
    }

};
namespace std {

    template<typename T>
    struct hash<Coset<T>>
    {
        size_t operator()(const Coset<T>& c) const
        {
            size_t h = 0;

            for (const auto& x : c.getElements())
            {
                h ^= std::hash<T>{}(x);
            }

            return h;
        }
    };

}
#endif //INTROALGEBRA_COSET_H
