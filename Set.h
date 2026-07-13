//
// Created by georg on 30/06/2026.
//

#ifndef INTROALGEBRA_SET_H
#define INTROALGEBRA_SET_H
#include <vector>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>




template<typename U>
std::string pretty(const U& value)
{
    std::ostringstream out;
    out << value;
    return pretty(out.str());
}

template<>
inline std::string pretty(const std::string& st) {
    static const std::string superscripts[] =
    {
        "⁰","¹","²","³","⁴",
        "⁵","⁶","⁷","⁸","⁹"
    };

    std::string result;
    for (size_t i = 0; i < st.size(); i++) {
        if (st[i] == '^') {
            i++;
            while (i < st.size() && std::isdigit(static_cast<unsigned char>(st[i]))) {
                result += superscripts[st[i] - '0'];
                i++;
            }
            i--;
        }
        else {
            result += st[i];
        }

    }
    if (st.contains(",")) {
        result.erase(std::remove_if(result.begin(), result.end(), [](unsigned char ch) {
        return std::isspace(ch);
    }), result.end());
    }
    return result;
}



template<typename T>
class Set {
protected:
    std::vector<T> elements;
    std::unordered_set<T> lookup;
public:
    Set() = default;
    Set(const std::vector<T>& elems)
    : elements(elems) {

        std::unordered_set<T> seen;
        std::vector<T> uniqueElems;

        for (const T& x : elements) {
            if (seen.insert(x).second) {
                uniqueElems.push_back(x);
            }
        }

        elements = std::move(uniqueElems);
        lookup.insert(elements.begin(), elements.end());
    }



    bool operator==(const Set& other) const {
        if (elements.size() != other.elements.size()) {
            return false;
        }

        for (const T& x : elements) {
            if (!other.searchSet(x)) {
                return false;
            }
        }

        return true;
    }

    int getOrder() const {
        return elements.size();
    }
    std::vector<T>& getElements() {
        return elements;
    }
    const std::vector<T>& getElements() const {
        return elements;
    }

    bool searchSet(const T& elem) const {
        return lookup.contains(elem);
    }
    void displaySet() const {
        std::cout << "{";
        for (int i = 0; i < elements.size(); i++) {
            std::cout << pretty(elements[i]);
            if (i != elements.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "}" << std::endl;

    }
};


#endif //INTROALGEBRA_SET_H
