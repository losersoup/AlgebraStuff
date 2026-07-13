#include <iostream>
//#include <functional>
//#include <vector>
#include <algorithm>
#include <cmath>
//#include "OneOpAlgebraic.h"
#include <string>
#include <windows.h>
#include "Menus/runMenu.h"

int AddModN(int x, int y, int n);

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);



    run();

    return 0;
}

int AddModN(int x, int y, int n) {
    return (x+y) % n;
}



// void LeftCosetPartition(OneOpAlgebraic& G, Set &H) {
//     std::vector<int> s1 = G.getElements();
//     std::vector<int> s2 = H.getElements();
//     std::vector<Set> cosets(s1.size() / s2.size());
//     int count = 0;
//     for (int g : s1) {
//         Set current = LeftCoset(G, g, H);
//         if (!std::ranges::contains(cosets, current)) {
//             cosets[count] = current;
//         }
//     }
//
//
//
// }
// template<typename T>
// Set<Coset<T>> LeftCosetPartition(OneOpAlgebraic<T>& G, Set<T> &H) {
//     std::vector<T> s1 = G.getElements();
//     std::vector<T> s2 = H.getElements();
//     std::vector<Coset<T>> cosets;
//     std::cout<<"{";
//     for (const T& g : s1) {
//         Coset<T> current = LeftCoset(G, g, H);
//         if (!std::ranges::contains(cosets, current)) {
//             cosets.push_back(current);
//
//         }
//     }
//
//     return cosets;
// }
//
// template<typename T>
// void RightCosetPartition(OneOpAlgebraic<T>& G, Set<T> &H) {
//     std::vector<T> s1 = G.getElements();
//     std::vector<T> s2 = H.getElements();
//     std::vector<Set<T>> cosets;
//
//     for (const T& g : s1) {
//         Set<T> current = RightCoset(G, g, H);
//         if (!std::ranges::contains(cosets, current)) {
//             cosets.push_back(current);
//             current.displaySet();
//         }
//     }
// }











//
//
// //void elementMenu(Session& session) {
//
//     // while (true) {
//     //     switch (getChoice("Group Properties",
//     //     {
//     //         "Is Group?",
//     //         "Is Abelian?",
//     //         "Is Cyclic?",
//     //         "Display Generators",
//     //         "Display Structure"
//     //     }
//     //     )) {
//     //         case 1: std::cout << (G.isGroup() ? "True" : "False") << "\n"; break;
//     //         case 2: std::cout << (G.isAbelian() ? "True" : "False") << "\n"; break;
//     //         case 3: std::cout << (isCyclic(G) ? "True" : "False") << "\n"; break;
//     //         case 4: getGenerators(G); break;
//     //         case 5: G.displayStructure(); break;
//     //         case 0: std::cout << "Returning to Main Menu."; return;
//     //         default: continue;
//     //     }
//     //     waitForEnter();
//     // }
//     std::cout<<"Not yet implemented. Coming soon!";
// }
