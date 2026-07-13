//
// Created by georg on 04/07/2026.
//

#include "mGroupMenu.h"
#include "selectFamMenu.h"
#include "smallhelpers.h"
#include <stdexcept>
#include "PropertyMenu.h"
#include "factorGroupMenu.h"
#include "cosetMenu.h"
#include "subgroupMenu.h"
#include "groupInfoMenu.h"


void menu(IGroupSession& current) {



    while (true){
        try {

            switch (getChoice("Main Menu", {

                                  "Group Information",
                                  "Element Operations",
                                  "Subgroup Operations",
                                  "Cosets",
                                  "Group Properties",
                                    "Factor Group Operations",

                              }, current)) {
                default: std::cout << "Invalid choice\n"; break;
                case 1:
                    groupInfoMenu(current);
                    break;

                    case 2: std::cout<<"Coming soon!";break;
                    //     elementMenu(G);
                    //     break;
                    //
                    case 3:
                        if (current.hasSubset()) {
                            std::cout << "Subset currently stored:"; current.displaySubset();
                        }
                        subgroupMenu(current);
                        break;

                    case 4:
                        if (current.hasSubset()) {
                            std::cout << "Subset currently stored:";
                            current.displaySubset();
                        }
                        cosetMenu(current);
                        break;

                    case 5:
                        propertyMenu(current);
                        break;
                    //
                    case 6:
                        factorMenu(current);
                        break;

                case 0:
                    //current.done = true; find replacement
                    return;

                              }

            waitForEnter();
        }
        catch (const std::logic_error& e) {
            std::cout << e.what();
        }

    }
}
