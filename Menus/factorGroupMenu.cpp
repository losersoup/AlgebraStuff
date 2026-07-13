//
// Created by georg on 04/07/2026.
//

#include "factorGroupMenu.h"



void factorMenu(IGroupSession& session) {


    std::string element;
    bool valid = false;


    if (!session.hasSubset()) {
        std::cout << "Error: no subset stored. Please input a subset.\n";

        session.inputSubset();
    }

    while (true) {
        switch (getChoice("Factor Group Menu",
        {
            "Display Center",
            "Quotient Center",
            "Quotient Current Subset",
            "Display Current Quotient Cayley Table",
            "Clear Current Quotient Group",


        }, session
        ) ) {
            case 1: {
                std::cout << "Z(" << session.getgroupName() << ") = "; session.dispCent();

                break;
            }
            case 2: {
                session.QuotCenter();
            }
                break;

            case 3: session.QuotSubset(); break;
            case 4:
                if (!session.hasFactorGroup()) {
                    std::cout << "No Factor Group Stored.\n";
                    break;
                }
                session.dispFGC();

                break;

            case 5: {
                session.clearFactorGroup();
                std::cout<<"Successfully cleared current factor group.\n";
            } break;


            case 0: std::cout << "Returning to Main Menu."; return;
            default: break;
        }
        waitForEnter();
    }

}
