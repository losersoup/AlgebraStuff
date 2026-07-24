//
// Created by georg on 05/07/2026.
//

#ifndef INTROALGEBRA_GSESSION_H
#define INTROALGEBRA_GSESSION_H

#include "session.h"
#include "OneOpAlgebraic.h"
#include "Coset.h"
#include "GroupFactory/Cyclic.h"
#include "GroupFactory/Dihedral.h"
#include "GroupFactory/Quaternions.h"
#include "GroupFactory/K4.h"
#include "algebra/CosetAlgos.h"



template<typename T>
class GSession : public IGroupSession {

    OneOpAlgebraic<T> group;
    Set<T> subset;
    OneOpAlgebraic<Coset<T>> factorgroup;

    std::string groupName;

public:

    OneOpAlgebraic<T>& getGroup() {
        return group;
    }


    void displayGroup() override {
        group.displaySet();
    }

    void displaySubset() override {
        subset.displaySet();
    }

    void displayFactorGroup() override {
        factorgroup.displaySet();
    }

    void getGenerators() override {
        group.getGenerators().displaySet();
    }

    bool isCyclic() override {
        return group.isCyclic();
    }

    void getId() override {
        std::cout << "Identity: " << group.getIdentity();
    }

    void QuotCenter() override {
        auto center = group.Center();
        auto K = FactorGroup(group, center);
        bool valid = false;

        if (!hasFactorGroup()) {

            factorgroup = K;
            std::cout<< groupName << "/Z("<<groupName<<") = "; K.displaySet();

        }
        char choice = 'y';
        std::cout<< groupName << "/Z("<<groupName<<") = "; K.displaySet();
        std::cout << "Replace current Factor Group? Y/N\n>";
        std::cin >> choice;
        while (!valid) {
            if (std::toupper(choice) == 'Y') {
                factorgroup = K;
                std::cout << "Success. Current Factor Group:"; K.displaySet();
                valid = true;
            }
            else if (std::toupper(choice) == 'N') {

                valid = true;
            }
            else {
                std::cout << "Invalid option. Re-enter choice Y/N.\n>";
            }

    }


    }


    void dispCent() override {
        group.Center().displaySet();


        bool valid = false;
        char choice = 'y';
        std::cout << "Replace current subset? Y/N\n>";
        std::cin >> choice;
        while (!valid) {
            if (std::toupper(choice) == 'Y') {
                auto set(group.Center().getElements());
                subset = set;
                std::cout << "Success. Current subset:"; subset.displaySet();
                valid = true;
            }
            else if (std::toupper(choice) == 'N') {

                valid = true;
            }
            else {
                std::cout << "Invalid option. Re-enter choice Y/N.\n>";
            }
        }

    }

    void dispC() override {
        group.displayCayley();
    }


    void dispFGC() override {
        if (hasFactorGroup()) {
            factorgroup.displayCayley();
        }
    }

    bool hasFactorGroup() const override {
        return !factorgroup.getElements().empty();
    }

    bool hasGroup() const override {
        return !group.getElements().empty();

    }

    std::string getStruct() const override {
        return group.getStruct();
    }

    void setGroup(OneOpAlgebraic<T>& G) {

        group = G;
    }
    void setName(const std::string& q) {
        groupName = q;
    }

    bool checkElement(std::string& element) override {
            T value = group.parse(element);

        if (group.searchSet(value)) {
                    return true;
        }
            std::cout << "Invalid element. Please re-enter:";
            return false;
    }
    int order() const override {
        return group.getOrder();
    }

    int elementOrder(std::string g) override {
        while (!checkElement(g)) {
            std::cin >> g;
        }
        return group.elementOrder(group.parse(g));
    }

    bool isAbelian() override {
        return group.isAbelian();
    }

    void leftCoset(std::string g) override {
        while (!checkElement(g)) {
            std::cin >> g;
            checkElement(g);
        }
        LeftCoset(group, group.parse(g), subset).displaySet();
    }

    void rightCoset(std::string g)  override {
        while (!checkElement(g)) {
            std::cin >> g;
        }
        RightCoset(group, group.parse(g), subset).displaySet();
    }

    void leftCosetPartition() override {
        LeftCosetPartitionCompact(group, subset);
    }

    void rightCosetPartition() override {
        RightCosetPartitionCompact(group, subset);
    }

    void inputSubset() override {

            std::vector<T> elems;
            std::cout << "Enter element of subset, or type '}' to finish. \n >";
            std::string input;

            std::getline(std::cin >> std::ws, input);
            while (input != "}") {

                while (!checkElement(input)) {
                    std::cin >> input;
                }
                elems.push_back(group.parse(input));
                std::cout << "Accepted.\n>";


                std::getline(std::cin >> std::ws, input);
            }
            std::cout << "Terminated and successfully stored set.";
            subset = Set(elems);
        }

    void createGroup() override;

    std::string getgroupName() const override {
        return groupName;
    }

    void generateCyclicSubgroup(std::string g) override {
        while (!checkElement(g)) {
            std::cin >> g;
        }

        OneOpAlgebraic<T> K = group.cyclicSubgroup(group.parse(g));
        K.displaySet();
        char choice = 'y';

        bool valid = false;
        std::cout << "Replace current subset? Y/N\n>";
        std::cin >> choice;
        while (!valid) {
            if (std::toupper(choice) == 'Y') {
                auto set(K.getElements());
                subset = set;
                std::cout << "Success. Current subset:"; subset.displaySet();
                valid = true;
            }
            else if (std::toupper(choice) == 'N') {

                valid = true;
            }
            else {
                std::cout << "Invalid option. Re-enter choice Y/N.\n>";
            }
        }
    }







    void setgroupName(std::string& n) override {
        groupName = n;
    }


    void QuotSubset() override {
        auto K = FactorGroup(group, subset);

            bool valid = false;

            if (!hasFactorGroup()) {

                factorgroup = K;

            }
            char choice = 'y';
            std::cout<< groupName << "/";subset.displaySet(); std::cout <<" = "; K.displaySet();
            std::cout << "Replace current Factor Group? Y/N\n>";
            std::cin >> choice;
            while (!valid) {
                if (std::toupper(choice) == 'Y') {
                    factorgroup = K;
                    std::cout << "Success. Current Factor Group:"; K.displaySet();
                    valid = true;
                }
                else if (std::toupper(choice) == 'N') {

                    valid = true;
                }
                else {
                    std::cout << "Invalid option. Re-enter choice Y/N.\n>";
                }

            }



    }

    bool hasSubset() const override {
        return !subset.getElements().empty();
    }

    bool isSubgroup() override {
        return group.isSubgroup(subset);
    }


    bool isNormal() override {
        return group.isNormal(subset);
    }

    void clearSubset() override {
        subset = Set<T>{};
    }


    void clearFactorGroup() override {
        factorgroup = OneOpAlgebraic<Coset<T>>();
    }


};


template<typename T>
void GSession<T>::createGroup()
{


    std::cout<< "\n═══════════════════════════════════════════════\n";
    std::cout<< "            ALGEBRA LIBRARY v1.0               \n";
    std::cout<< "═══════════════════════════════════════════════\n";
    int choice;
    while (true) {
        clearSubset();
        if constexpr (std::same_as<T, ZnElement>)
        {
            std::string title = "Cyclic Groups";


            for (size_t i=0; i< (41 - title.length())/2; i++) {
                std::cout<<"=";
            }
            std::cout<<" [ " << title << " ] ";

            for (size_t i=0; i< (41 - title.length())/2; i++) {
                std::cout<<"=";
            }
            std::cout<<"\n\n";

            std::cout <<"Enter order of cyclic group. \n";

            std::cout << "\n0. Return\n";
            std::cout<<"===============================================\n";
            std::cout<<"───────────────────────────────────────────────\n";

            std::cout << "> ";

            std::cin >> choice;

        if (choice ==0) {
            return;
        }

            group = createCyclicGroup(choice);
            groupName = "Cyclic Group ℤ" + std::to_string(choice);
            return;
        }
        else if constexpr (std::same_as<T, DihedralElement>)
        {


            std::string title = "Dihedral Groups";


            for (size_t i=0; i< (41 - title.length())/2; i++) {
                std::cout<<"=";
            }
            std::cout<<" [ " << title << " ] ";

            for (size_t i=0; i< (41 - title.length())/2; i++) {
                std::cout<<"=";
            }
            std::cout<<"\n\n";

            std::cout <<"Enter number of sides of n-gon. \n";

            std::cout << "\n0. Return\n";
            std::cout<<"===============================================\n";
            std::cout<<"───────────────────────────────────────────────\n";

            std::cout << "> ";

            std::cin >> choice;


            if (choice ==0) {
                return;
            }
            group = createDihedral(choice);
            groupName = "Dihedral group D" + std::to_string(choice);
            return;
        }
        else if constexpr (std::same_as<T, std::string>)
        {

            {

                std::string title = "Named Groups";


                for (size_t i=0; i< (41 - title.length())/2; i++) {
                    std::cout<<"=";
                }
                std::cout<<" [ " << title << " ] ";

                for (size_t i=0; i< (41 - title.length())/2; i++) {
                    std::cout<<"=";
                }
                std::cout<<"\n\n";

                std::cout <<"1. Klein Four-Group\n";
                std::cout <<"2. Quaternion Group \n";

                std::cout << "\n0. Return\n";
                std::cout<<"===============================================\n";
                std::cout<<"───────────────────────────────────────────────\n";

                std::cout << "> ";

                std::cin >> choice;
                if (choice==0) {
                    return;
                }


                switch (choice)
                {
                    case 1: {

                        OneOpAlgebraic G = createKleinFour();

                        setGroup(G);
                        std::cout << "Successfully changed group to Klein four-group.\n";
                        setName("Klein Four-group");
                        return;
                    }
                    case 2: {

                        OneOpAlgebraic G = createQuatGroup();

                        setGroup(G);
                        std::cout << "Successfully changed group to the Quaternion group";

                        setName("Quaternion Group");

                        return;
                    }
                    default:
                        continue;
                }

            }


        }
        else if constexpr (std::same_as<T, Permutation>)
        {
            int n;


            std::string title = "Permutation Groups";


            for (size_t i=0; i< (41 - title.length())/2; i++) {
                std::cout<<"=";
            }
            std::cout<<" [ " << title << " ] ";

            for (size_t i=0; i< (41 - title.length())/2; i++) {
                std::cout<<"=";
            }
            std::cout<<"\n\n";

            std::cout <<"1. Symmetry Group Sn \n";
            std::cout <<"2. Alternating Group An \n";
            std::cout <<"3. Custom Permutation Group \n";

            std::cout << "\n0. Return\n";
            std::cout<<"===============================================\n";
            std::cout<<"───────────────────────────────────────────────\n";

            std::cout << "> ";

            std::cin >> choice;
            if (choice==0) {
                return;
            }
            std::cout << "Please input number of elements to permute. Bear in mind symmetry groups are quite large!\n>";
            std::cin >> n;


            switch (choice)
            {
                case 1: {
                    OneOpAlgebraic<Permutation> S = createSymmetryGroup(n);
                    setGroup(S);
                    std::cout << "Successfully changed group to S" << n << "\n";
                    setName("Symmetric Group S" + std::to_string(n));
                    return;
                }
                case 2: {

                    OneOpAlgebraic<Permutation> S = createAlternatingGroup(n);
                    setGroup(S);
                    std::cout << "Successfully changed group to A" << n << "\n";
                    setName("Alternating Group A" + std::to_string(n));
                    return;
                }
                case 3: {

                    OneOpAlgebraic<Permutation> S = customPermutationGroup(n);
                    setGroup(S);
                    std::cout << "Successfully changed group to Custom Permutation Group";
                    setName("Custom Permutation Group");
                    return;
                }
                default:
                    continue;
            }

        }
    }

}




#endif //INTROALGEBRA_GSESSION_H
