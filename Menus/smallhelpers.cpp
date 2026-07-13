//
// Created by georg on 04/07/2026.
//



#include <iostream>
#include <numeric>
#include "smallhelpers.h"
#include <vector>
#include "../OneOpAlgebraic.h"
#include "../Set.h"
#include "../session.h"


void waitForEnter()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

Set<std::string> inputSubset(OneOpAlgebraic<std::string>& G) {

    std::vector<std::string> elems;

    std::string input;

    std::cout << "Enter element of subset, or type '}' to finish. \n >";

    std::cin >> input;

    while (input != "}") {
        input = validateElement(input, G);
        elems.push_back(input);
        std::cout << "Accepted.\n>";
        std::cin >> input;
    }


    std::cout << "Terminated and successfully stored set.";
    Set set(elems);

    return set;
}
int getChoice(const std::string& title,
              const std::vector<std::string>& options)
{
    int choice;

    std::cout<< "\n═══════════════════════════════════════════════\n";
    std::cout<< "            ALGEBRA LIBRARY v1.0               \n";
    std::cout<< "═══════════════════════════════════════════════\n";

    for (size_t i=0; i< (41 - title.length())/2; i++) {
        std::cout<<"=";
    }
    std::cout<<" [ " << title << " ] ";

    for (size_t i=0; i< (41 - title.length())/2; i++) {
        std::cout<<"=";
    }
    std::cout<<"\n\n";

    for (int i = 0; i < options.size(); ++i)
        std::cout << i + 1 << ". " << options[i] << '\n';

    std::cout << "\n0. Return\n";
    std::cout<<"===============================================\n";
    std::cout<<"───────────────────────────────────────────────\n";

    std::cout << "> ";

    std::cin >> choice;



    return choice;
}


int getChoice(const std::string& title,
              const std::vector<std::string>& options, IGroupSession& session)
{
    int choice;

    std::cout<< "\n═══════════════════════════════════════════════\n";
    std::cout<< "            ALGEBRA LIBRARY v1.0               \n";
    std::cout<< "═══════════════════════════════════════════════\n";

    if (session.hasGroup()) {
        std::cout<<"\nCurrent Group: " << session.getgroupName();
        std::cout<<"\nOrder: " << session.order();
        std::cout<<"\nStructure: " << session.getStruct() << "\n";
        if (session.order() < 15) {
            std::cout<<"Elements: "; session.displayGroup();
        }
        if (session.hasSubset()) {
            std::cout<<"Stored Subset: "; session.displaySubset();
        }
        if (session.hasFactorGroup()) {
            std::cout<<"Stored Factor Group: "; session.displayFactorGroup();
        }
        std::cout<<"\n";
        std::cout<<"───────────────────────────────────────────────\n";
    }

    for (size_t i=0; i< (41 - title.length())/2; i++) {
        std::cout<<"=";
    }
    std::cout<<" [ " << title << " ] ";

    for (size_t i=0; i< (41 - title.length())/2; i++) {
        std::cout<<"=";
    }
    std::cout<<"\n\n";

    for (int i = 0; i < options.size(); ++i)
        std::cout << i + 1 << ". " << options[i] << '\n';

    std::cout << "\n0. Return\n";
    std::cout<<"===============================================\n";
    std::cout<<"───────────────────────────────────────────────\n";

    std::cout << "> ";

    std::cin >> choice;



    return choice;
}