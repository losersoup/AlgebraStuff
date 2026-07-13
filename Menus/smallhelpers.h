//
// Created by on 04/07/2026.
//
#pragma once
#ifndef INTROALGEBRA_SMALLHELPERS_H
#define INTROALGEBRA_SMALLHELPERS_H


#include <vector>
#include "../OneOpAlgebraic.h"
#include "../Set.h"
#include "../Coset.h"

class IGroupSession;

template<typename T>
using bOp = std::function<T(const T& el1, const T& el2)>;


void waitForEnter();

int getChoice(const std::string& title,
              const std::vector<std::string>& options);
//
// template<typename T>
// int getChoice(const std::string& title,
//               const std::vector<std::string>& options, Session<T>& session)
// {
//     int choice;
//
//     std::cout<< "\n═══════════════════════════════════════════════\n";
//     std::cout<< "            ALGEBRA LIBRARY v1.0               \n";
//     std::cout<< "═══════════════════════════════════════════════\n";
//
//     if (!session.group.getElements().empty()) {
//         std::cout<<"\nCurrent Group: " << session.groupName;
//         std::cout<<"\nOrder: " << session.getOrder();
//         std::cout<<"\nStructure: " << session.group.getStruct() << "\n";
//         if (session.getOrder() < 15) {
//             std::cout<<"Elements: "; session.group.displaySet();
//         }
//         if (session.hasSubset()) {
//             std::cout<<"Stored Subset: "; session.subset.displaySet();
//         }
//         if (session.hasFactorGroup()) {
//             std::cout<<"Stored Factor Group: "; session.factorgroup.displaySet();
//         }
//         std::cout<<"\n";
//         std::cout<<"───────────────────────────────────────────────\n";
//     }
//
//     for (size_t i=0; i< (41 - title.length())/2; i++) {
//         std::cout<<"=";
//     }
//     std::cout<<" [ " << title << " ] ";
//
//     for (size_t i=0; i< (41 - title.length())/2; i++) {
//         std::cout<<"=";
//     }
//     std::cout<<"\n\n";
//
//     for (int i = 0; i < options.size(); ++i)
//         std::cout << i + 1 << ". " << options[i] << '\n';
//
//     std::cout << "\n0. Return\n";
//     std::cout<<"===============================================\n";
//     std::cout<<"───────────────────────────────────────────────\n";
//
//     std::cout << "> ";
//
//     std::cin >> choice;
//
//
//
//     return choice;
// }
//

int getChoice(const std::string& title,
              const std::vector<std::string>& options, IGroupSession& session);


template<typename T>
Set<T> inputSubset(OneOpAlgebraic<T>& G) {

    std::vector<T> elems;



    std::cout << "Enter element of subset, or type '}' to finish. \n >";

    std::string input;

    std::getline(std::cin >> std::ws, input);

    while (input != "}") {
        T q = validateElement(input, G);
        elems.push_back(q);
        std::cout << "Accepted.\n>";


        std::getline(std::cin >> std::ws, input);
    }


    std::cout << "Terminated and successfully stored set.";
    Set set(elems);

    return set;
}

template<typename T>
T validateElement(std::string& element, OneOpAlgebraic<T>& G) {
    T value = G.parse(element);
    while (true) {
        if (G.searchSet(value)) {
            break;
        }
        std::cout << "Invalid element. Please re-enter:";
        std::cin  >> element;
        value = G.parse(element);
    }
    return value;
}



#endif //INTROALGEBRA_SMALLHELPERS_H
