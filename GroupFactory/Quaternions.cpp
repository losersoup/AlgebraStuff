//
// Created by georg on 08/07/2026.
//

#include "Quaternions.h"
#include <vector>


OneOpAlgebraic<std::string> createQuatGroup() {

    auto parser = [](const std::string& s)
    {
        return s;
    };
    std::vector<std::string> elems = {"1", "-1", "i", "-i", "j", "-j", "k", "-k"};

    std::vector<std::vector<std::string>> cayley = {
        {"1", "-1", "i", "-i", "j", "-j", "k", "-k"},
        {"-1", "1", "-i", "i", "-j", "j", "-k", "k"},
        {"i", "-i", "-1", "1", "k", "-k", "-j", "j"},
        {"-i", "i", "1", "-1", "-k","k", "j", "-j"},
        {"j", "-j", "-k", "k", "-1", "1", "i", "-i"},
        {"-j", "j", "k", "-k", "1", "-1", "-i", "i"},
        {"k", "-k", "j", "-j", "-i", "i", "-1", "1"},
        {"-k", "k", "-j", "j", "i", "-i", "1", "-1"}
    };

    OneOpAlgebraic<std::string> G(elems, cayley, parser);
    return G;
}