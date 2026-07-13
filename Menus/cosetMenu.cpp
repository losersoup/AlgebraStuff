//nothing

#include "cosetMenu.h"

void cosetMenu(IGroupSession& session) {

    std::string element;


    if (!session.hasSubset()) {
        std::cout << "Error: no subset stored. Please input a subset.\n";

        session.inputSubset();
    }

    while (true) {
        switch (getChoice("Coset Menu",
        {
            "Display Current Subset",
            "Left Coset",
            "Right Coset",
            "Left Coset Partition",
            "Right Coset Partition",
        }, session
        ) ) {
            case 1: session.displaySubset(); break;
            case 2: {
                std::cout << "Input Element:";
                std::cin >> element;

                std::cout << "Original: "; session.displaySubset();
                std::cout <<"Coset: ";session.leftCoset(element)
                ; break;
            }
            case 3: {
                std::cout << "Input Element:";
                std::cin >> element;

                std::cout << "Original: "; session.displaySubset();
                std::cout <<"Coset: ";session.rightCoset(element)
                ; break;
            }
            case 4: session.leftCosetPartition(); break;
            case 5: session.rightCosetPartition(); break;
            case 0: std::cout << "Returning to Main Menu."; return;
            default: break;
        }
        waitForEnter();
    }

}