//
// Created by on 04/07/2026.
//

#include "groupInfoMenu.h"



void groupInfoMenu(IGroupSession& current) {


    while (true) {
        switch (getChoice("Group Information",
        {
            "Elements",
            "Cayley Table",
            "Identity",
            "Inverses",
            "Order"
        }, current
        )) {
            case 1: current.displayGroup(); break;
            case 2: current.dispC(); break;
            case 3: current.getId(); break;
            case 4: std::cout << "Come back later!"; break;
            case 5: std::cout << current.order(); break;
            case 0: std::cout << "Returning to Main Menu."; return;
            default: continue;
        }
        waitForEnter();
    }
}
