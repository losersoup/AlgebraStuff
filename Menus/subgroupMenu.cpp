//
// Created by georg on 04/07/2026.
//

#include "subgroupMenu.h"


void subgroupMenu(IGroupSession& session) {


    std::string element;
    bool valid = false;

    if (!session.hasSubset()) {
        std::cout << "Error: no subset stored. Please input a subset.\n";

        session.inputSubset();
    }
    while (true) {
        switch (getChoice("Subgroup Menu",
        {
            "Input New Subset",
            "Test Subgroup",
            "Test Normal Subgroup",
            "Generate Cyclic Subgroup",
            "Find Element Order",

        }, session
        )) {

            case 1: session.inputSubset(); break;
            case 2: std::cout << (session.isSubgroup() ? ("This is a subgroup.") : "This is not a subgroup."); break;
            case 3: std::cout << (session.isNormal() ? ("This is a normal subgroup.") : "This is not a normal subgroup."); break;
            case 4: {
                std::cout << "Input Element:";
                std::cin >> element;
                session.generateCyclicSubgroup(element);
            }
                break;
            case 5: {
                std::cout << "Input Element:";
                std::cin >> element;

                int n = session.elementOrder(element);

                std::cout << "Element Order: " << n; break;
            }

            case 0: std::cout << "Returning to Main Menu."; return;
            default: continue;
        }
        waitForEnter();
    }
}
