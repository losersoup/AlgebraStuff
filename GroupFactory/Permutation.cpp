//
// Created by georg on 04/07/2026.
//

#include "Permutation.h"
#include "../OneOpAlgebraic.h"
#include <numeric>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <stdexcept>

Permutation Permutation::fromCycleString(const std::string& s, size_t n)
{
    // Start with the identity permutation
    Permutation result;
    result.image.resize(n);
    std::iota(result.image.begin(), result.image.end(), 0);

    size_t i = 0;

    while (i < s.size()) {

        // Skip whitespace
        while (i < s.size() && std::isspace((unsigned char)s[i]))
            ++i;

        if (i >= s.size())
            break;

        if (s[i] != '(') {
            ++i;      // Ignore unexpected characters
            continue;
        }

        ++i; // Skip '('

        std::vector<int> cycle;

        // Read one cycle
        while (true) {

            while (i < s.size() && std::isspace((unsigned char)s[i]))
                ++i;

            if (i >= s.size())
                throw std::runtime_error("Unmatched parenthesis");

            if (s[i] == ')')
                break;

            if (!std::isdigit((unsigned char)s[i]))
                throw std::runtime_error("Expected number in cycle");

            int num = 0;
            while (i < s.size() && std::isdigit((unsigned char)s[i])) {
                num = num * 10 + (s[i] - '0');
                ++i;
            }

            if (num < 1 || num > (int)n)
                throw std::runtime_error("Cycle element out of range");

            cycle.push_back(num - 1);
        }

        ++i; // Skip ')'

        // Convert this cycle into a permutation
        Permutation cyclePerm;
        cyclePerm.image.resize(n);
        std::iota(cyclePerm.image.begin(), cyclePerm.image.end(), 0);

        if (cycle.size() > 1) {
            for (size_t k = 0; k < cycle.size(); ++k) {
                cyclePerm.image[cycle[k]] = cycle[(k + 1) % cycle.size()];
            }
        }

        // Compose with accumulated permutation.
        // compose(a,b) = a ∘ b, so this interprets
        // (1 2)(1 3) as "apply (1 3) first, then (1 2)".
        result = compose(cyclePerm, result);
    }

    return result;
}

Permutation compose(const Permutation& a, const Permutation& b) {
    if (a.image.size() != b.image.size()) {
        throw std::logic_error("Mismatched Permutations.");
    }
    size_t n = a.image.size();

    Permutation result;

    result.image.resize(n);
    for (size_t i =0; i < n; i++) {
        result.image[i] = a.image[b.image[i]];
    }

    return result;
}

std::string Permutation::toCycleString() const {
    std::vector<bool> visited(image.size(), false);
    std::ostringstream out;

    bool anyCycle = false;

    for (int i = 0; i < image.size(); i++) {
        if (visited[i] || image[i] == i)
            continue;

        int current = i;
        bool firstInCycle = true;

        out << "(";

        do {
            visited[current] = true;

            if (!firstInCycle)
                out << " ";

            out << (current + 1); // 1-based output

            current = image[current];
            firstInCycle = false;

        } while (current != i);

        out << ")";
        anyCycle = true;
    }

    if (!anyCycle)
        return "ε"; // identity permutation

    return out.str();
}



bool evenPermParity(Permutation& p) {

    // true = even, false = odd

    std::string s = p.toCycleString();
    std::vector<int> cycleLengths;
    int current = 0;

    if (s=="ε") {
        return true;
    }

    for (char c : s) {

        if (c=='(' || c==' ') {
            continue;
        }
        if (c==')') {
            current -= 1;
            cycleLengths.push_back(current);
            current = 0;
            continue;
        }

        current++;

    }
    int total = std::accumulate(cycleLengths.begin(), cycleLengths.end(),0);

    return (total % 2 ==0);
}



OneOpAlgebraic<Permutation> createSymmetryGroup(int n) {
    std::vector<int> p(n);
    std::vector<Permutation> elems;

    std::iota(p.begin(), p.end(), 0);
    do
    {
        elems.emplace_back(Permutation(p));
    }
    while (std::next_permutation(p.begin(), p.end()));

    bOp<Permutation> mult =
            [](const Permutation& a, const Permutation& b)
    {
     return compose(a,b);
    };

    std::function<Permutation(const std::string&)> parser = [n](const std::string& s)
    {
        return Permutation::fromCycleString(s,n);
    };

    OneOpAlgebraic<Permutation> G(elems, mult, parser);
    G.setSize(n);
    return G;
}

OneOpAlgebraic<Permutation> createAlternatingGroup(int n) {
    std::vector<int> p(n);
    std::vector<Permutation> elems;

    std::iota(p.begin(), p.end(), 0);
    do
    {
        Permutation q(p);

        if (evenPermParity(q)) {
            elems.emplace_back(q);
        }
    }
    while (std::next_permutation(p.begin(), p.end()));

    bOp<Permutation> mult =
            [](const Permutation& a, const Permutation& b)
            {
                return compose(a,b);
            };

    std::function<Permutation(const std::string&)> parser = [n](const std::string& s)
    {
        return Permutation::fromCycleString(s,n);
    };

    OneOpAlgebraic G(elems, mult, parser);
    G.setSize(n);
    return G;
}




OneOpAlgebraic<Permutation> customPermutationGroup(int n) {
    std::vector<int> p(n);
    std::vector<Permutation> elems;

    std::string inp;
    Permutation current;
    std::cout << "Enter permutation element of group, or type '}' to finish. \n >";


    while (inp != "}") {

        std::getline(std::cin >> std::ws, inp);
        try {
            current = Permutation::fromCycleString(inp, n);
            elems.emplace_back(current);
            std::cout << "Accepted.\n>";
        }
        catch (std::runtime_error& e) {
            std::cout << e.what();
        }

    }


    bOp<Permutation> mult =
            [](const Permutation& a, const Permutation& b)
            {
                return compose(a,b);
            };

    std::function<Permutation(const std::string&)> parser = [n](const std::string& s)
    {
        return Permutation::fromCycleString(s,n);
    };



    OneOpAlgebraic G(elems, mult, parser);
    return G;
}

std::ostream& operator<<(std::ostream& os, const Permutation& p)
{
    return os << p.toCycleString();
}

std::istream& operator>>(std::istream& is, Permutation& p)
{
    std::string s;
    std::getline(is >> std::ws, s);

    p = Permutation::fromCycleString(s, p.image.size());
    return is;
}