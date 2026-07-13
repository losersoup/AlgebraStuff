//
// Created by georg on 04/07/2026.
//

#include "K4.h"

std::string parseK4(const std::string& s) {
    return s;
}


OneOpAlgebraic<std::string> createKleinFour() {
    std::vector<std::string> elems = {"e", "a", "b", "ab"};


    auto parser = [](const std::string& s)
    {
        return parseK4(s);
    };


    std::vector<std::vector<std::string>> cayley = {
        {"e","a","b","ab"}, // e
        {"a","e","ab","b"}, // a
        {"b","ab","e","a"}, // b
        {"ab","b","a","e"}};// c

    OneOpAlgebraic<std::string> G(elems, cayley, parser);
    return G;
}
