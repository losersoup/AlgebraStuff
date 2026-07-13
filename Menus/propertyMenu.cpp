//
// Created by on 04/07/2026.
//

#include "smallhelpers.h"
#include "../session.h"

void propertyMenu(IGroupSession& session) {


    while (true) {
        switch (getChoice("Group Properties",
        {
            "Is Abelian?",
            "Is Cyclic?",
            "Display Generators",
            "Display Algebra Type"
        }, session
        )) {
            case 1: std::cout << (session.isAbelian() ? "True" : "False") << "\n"; break;
            case 2: std::cout << (session.isCyclic() ? "True" : "False") << "\n"; break;
            case 3: session.getGenerators(); break;
            case 4: std::cout << session.getStruct(); break;
            case 5: std::cout << "Returning to Main Menu."; return;
            default: continue;
        }
        waitForEnter();
    }
}
