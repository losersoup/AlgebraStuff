//
// Created by georg on 30/06/2026.
//

#ifndef INTROALGEBRA_ONEOPALGEBRAIC_H
#define INTROALGEBRA_ONEOPALGEBRAIC_H
#include <iostream>
#include <functional>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Set.h"


template<typename T>
using bOp = std::function<T(const T& el1, const T& el2)>;
template<typename T>
class OneOpAlgebraic : public Set<T> {
private:
    int identity;
    bOp<T> op;
    bool hasIdentity;
    bool hasInverses;
    bool commutative;
    bool associative;
    bool cyclic;
    size_t parseSize = 0;
    std::string structure;
    std::vector<std::vector<int>> Cayley;
    std::unordered_map<T,int> index;
    std::vector<int> inverses;
    std::function<T(const std::string&)> parser;

    static void printCentered(const std::string& s, size_t width)
    {
        size_t len = displayWidth(s);

        if (len >= width)
        {
            std::cout << s;
            return;
        }

        size_t totalPad = width - len;
        size_t leftPad  = totalPad / 2;
        size_t rightPad = totalPad - leftPad;

        std::cout << std::string(leftPad, ' ')
                  << s
                  << std::string(rightPad, ' ');
    }

    static size_t displayWidth(const std::string& s)
    {
        size_t width = 0;

        for (unsigned char c : s)
        {
            // Count only the leading byte of each UTF-8 codepoint
            if ((c & 0xC0) != 0x80)
                ++width;
        }

        return width;
    }

    void validateAxioms() {
        checkComm();
        checkAss();
        checkId();
        checkInv();

        classifyAlgebraic();
    }
    void checkComm() {
        for (size_t i = 0; i < this->elements.size(); i++) {
            for (size_t j = 0; j < this->elements.size(); j++) {
                if (Cayley[i][j] != Cayley[j][i]) {
                    commutative = false;
                    return;
                }
            }
        }
    }
    void checkAss() {
        for (size_t i = 0; i < this->elements.size(); i++) {
            for (size_t j = 0; j < this->elements.size(); j++) {
                for (size_t k = 0; k < this->elements.size(); k++)
                if (Cayley[i][Cayley[j][k]] != Cayley[Cayley[i][j]][k]) {
                    associative = false;
                    return;
                }
            }
        }
    }
    void checkId() {
        for (int i = 0; i < this->elements.size(); i++) {
            bool idcand = true;
            for (size_t j = 0; j < this->elements.size(); j++) {
                if (Cayley[i][j] == Cayley[j][i] && Cayley[i][j] == j) {

                    continue;
                }
                idcand = false;
                break;
            }
            if (idcand) {
                hasIdentity = true;
                setIdentity(i);
                return;
            }
        }
    }
    void checkInv() {
        if (hasIdentity) {
            for (int a = 0; a < this->elements.size(); a++) {
                bool found = false;

                for (int b = 0; b < this->elements.size(); b++) {
                    if (Cayley[a][b] == Cayley[b][a] && Cayley[a][b] == identity) {
                        found = true;
                        inverses[a] = b;
                    }
                }
                if (!found) {
                    hasInverses = false;
                    return;
                }
            }
        }
        else {
            hasInverses = false;
        }
    }



    void buildCayley() {
        for (int i = 0; i < this->elements.size(); i++) {
            for (int j=0; j < this->elements.size(); j++) {
                T k = op(this->elements[i], this->elements[j]);

                if (!this->searchSet(k)) {
                    std::cout << "Missing element: " << k << '\n';
                    throw std::logic_error("This is not a closed structure.");
                }
                Cayley[i][j] = index[k];
            }
        }
    }

    void buildCayleyFromValues(const std::vector<std::vector<T>>& table)
    {
        int n = this->elements.size();

        Cayley.assign(n, std::vector<int>(n));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                auto it = index.find(table[i][j]);

                if (it == index.end())
                    throw std::logic_error("This is not a closed structure.");

                Cayley[i][j] = it->second;
            }
        }
    }

    int toIndex(const T& x) const{
        return index.at(x);
    }
    const T& toElement(int i) const {
        return this->elements[i];
    }

public:
    OneOpAlgebraic() = default;
    OneOpAlgebraic(const std::vector<T>& elems, bOp<T> operation,     std::function<T(const std::string&)> parser) :
    Set<T>(elems), identity(0),
    op(std::move(operation)),
    hasIdentity(false),
    hasInverses(true),
    commutative(true),
    associative(true),
    cyclic(false),

    structure(""),
    Cayley(this->elements.size(),
        std::vector<int>(this->elements.size())
              ),
    inverses(this->elements.size(), -1),
    parser(std::move(parser))

    {
        for (int i = 0; i < this->elements.size(); ++i) {
            index[this->elements[i]] = i;
        }
        buildCayley();
        validateAxioms();
    }

    OneOpAlgebraic(const std::vector<T>& elems, std::vector<std::vector<T>>&cayley, std::function<T(const std::string&)> parser) :
        Set<T>(elems), identity(0),
        op(nullptr),
        hasIdentity(false),
        hasInverses(true),
        commutative(true),
        associative(true),
        cyclic(false),
        structure(""),
        Cayley(this->elements.size()),
    inverses(this->elements.size(), -1),
    parser(std::move(parser))


    {
        for (int i = 0; i < this->elements.size(); ++i) {
            index[this->elements[i]] = i;
        }

        buildCayleyFromValues(cayley);
        validateAxioms();

    }




    void setIdentity(int e) {
        identity = e;
    }
    T getIdentity() {
        return(hasIdentity ? this->elements[identity] : (throw std::invalid_argument("This structure does not have an identity.")));
    }
    T getIdentity() const {
        return(hasIdentity ? this->elements[identity] : (throw std::invalid_argument("This structure does not have an identity.")));
    }

    void displayCayley() const
    {
        int n = this->elements.size();
        std::string crnt;

        std::vector<std::string> names;
        size_t cellWidth = 0;
        size_t nameWidth = 0;
        size_t numWidth = 0;
        bool indexmode = false;
        int count = 0;
        for (const auto& e : this->elements)
        {
            names.push_back(pretty(e));
            nameWidth = std::max(nameWidth, displayWidth(names.back()));

            numWidth = std::max(numWidth, displayWidth(std::to_string(count)));

            count++;
        }

        if (names.size() * nameWidth >= 60) {
            indexmode=true;
            cellWidth = numWidth;
        }
        else {
            cellWidth = nameWidth;
        }

        cellWidth += 2; // padding around each entry

        std::cout << "\n";


        // Header
        printCentered("", cellWidth);
        std::cout << "│";
        if (!indexmode) {
            for (const auto& name : names)
                printCentered(name, cellWidth);
        }
        else {

            for (int i =0; i< names.size(); i++)
                printCentered(std::to_string(i), cellWidth);
        }
        std::cout << '\n';

        // Divider
        std::cout << std::string(cellWidth, ' ')
                  << "┼"
                  << std::string(cellWidth * n, '-')
                  << '\n';

        // Rows
        if (!indexmode) {
            for (int i = 0; i < n; ++i)
            {
                printCentered(names[i], cellWidth);
                std::cout << "│";

                for (int j = 0; j < n; ++j)
                    printCentered(names[Cayley[i][j]], cellWidth);

                std::cout << '\n';
            }
        }
        else {
            for (int i = 0; i < n; ++i)
            {
                printCentered(std::to_string(i), cellWidth);
                std::cout << "│";

                for (int j = 0; j < n; ++j)
                    printCentered(std::to_string(Cayley[i][j]), cellWidth);

                std::cout << '\n';

            }
            std::cout << "Key: \n";
            for (int i=0; i < n; i++) {
                printCentered(std::to_string(i) + " : " + names[i], 2*(nameWidth + numWidth)); std::cout << " │ ";
                if ((i+1) % 5 == 0) {
                    std::cout << "\n";
                }
            }
        }
    }

    std::string classifyAlgebraic() {
        if (associative && commutative && hasInverses && hasIdentity) {
            structure = "Abelian Group";
        }
        else if (associative && hasInverses && hasIdentity) {
            structure = "Non-Abelian Group";
        }
        else if (associative && hasIdentity) {
            structure = "Monoid";
        }
        else if (associative) {
            structure = "Semigroup";
        }
        else if (hasInverses && hasIdentity) {
            structure = "Loop";
        }
        else if (hasInverses) {
            structure = "Quasigroup";
        }
        else {
            structure = "Magma";
        }
        return structure;
    }
    void displayStructure() {
        std::cout << (structure != "Abelian Group" ? ("This structure is a " + structure + ".\n") : ("This structure is an Abelian group"));
    }
    std::string getStruct() const {
        return structure;
    }
    T parse(const std::string& s) const {
        return parser(s);
    }

    void setSize(size_t n) {
        parseSize = n;
    }
    size_t getSize() const {
        return parseSize;
    }

    bOp<T>& getOp() {
        if (op == nullptr) {
            throw std::logic_error("No defined operation");
        }

        return op;
    }
    const bOp<T>& getOp() const {
        if (op == nullptr) {
            throw std::logic_error("No defined operation");
        }

        return op;
    }


    bool isGroup() const {
        return (structure == "Abelian Group" || structure == "Non-Abelian Group");
    }

    bool isAbelian() const {
        return (structure == "Abelian Group");
    }

    T invertElement(const T& x) const {
        return this->elements[inverses[index.at(x)]];
    }

    T multiply(const T& x, const T& y) const
    {
        int ix = index.at(x);
        int iy = index.at(y);

        return this->elements[Cayley[ix][iy]];
    }

    T conjugate(const T& g, const T& h) const
    {
        T gh = multiply(g, h);
        T inv = invertElement(g);
        return multiply(gh, inv);
    }

OneOpAlgebraic<T> cyclicSubgroup(const T& g)
    {

        std::vector<T> elements;
        T current = getIdentity();

        // Generate <g> = {e, g, g², ...}
        do
        {
            elements.push_back(current);
            current = multiply(current, g);
        }
        while (!std::ranges::contains(elements, current));


        bOp<T> subgroupOp = [this](const T& a, const T& b)
        {
            return multiply(a, b);
        };

        return OneOpAlgebraic<T>(elements, subgroupOp, parser);
    }

    Set<T> Center() const {
        std::vector<T> elems;
        bool current;
        for (size_t i = 0; i < this->elements.size(); i++) {
            current = true;
            for (size_t j = 0; j < this->elements.size(); j++) {
                if (Cayley[i][j] != Cayley[j][i]) {
                    current = false;
                    break;
                }
            }
            if (current) {
                elems.push_back(this->elements[i]);
            }
        }
        return Set<T>(elems);
    }
    bool isCyclic() {
        if (structure != "Abelian Group") {
            return false;
        }
        for (const T& x : this->elements) {
            Set sub = cyclicSubgroup(x);
            if (sub.getOrder()==this->getOrder()) {
                return true;
            }
        }
        return false;
    }

    int elementOrder(T g) {
        return cyclicSubgroup(g).getElements().size();
    }

    Set<T> getGenerators() {
        std::vector<T> gens;
        if (!isCyclic()) {
            return gens;
        }
        for (const T& g : this->elements) {
            if (elementOrder(g) == this->getOrder()) {
                gens.push_back(g);
            }
        }
        Set Gens(gens);
        return Gens;
    }


    bool  isSubgroup(Set<T>& H)  {
        if (!isGroup()) {
            throw std::logic_error("Invalid Algebraic Structure Provided");
        }
        if (!H.searchSet(getIdentity())) {
            return false;
        }

        for (T h : H.getElements()) {
            for (T k : H.getElements()) {
                if (!H.searchSet(multiply(h, invertElement(k)))) {
                    return false;
                }
            }
        }
        return true;
    }


    bool isNormal( Set<T>& H)  {
        if (!isSubgroup(H)) {
            return false;
        }

        std::vector<T> v = H.getElements();

        for (const T& g : this->elements) {
            for (const T& h : v) {
                T cnjg = conjugate(g,h);
                if (!H.searchSet(cnjg)) {
                    return false;
                }
            }
        }
        return true;

    }

};



#endif //INTROALGEBRA_ONEOPALGEBRAIC_H
