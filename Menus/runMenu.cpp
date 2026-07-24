//
// Created by georg on 04/07/2026.
//

#include "runMenu.h"
#include "mGroupMenu.h"
#include "selectFamMenu.h"
#include "../GSession.h"

std::unique_ptr<IGroupSession> makeSession(int choice)
{
    switch(choice)
    {
        case 1: return std::make_unique<GSession<ZnElement>>();
        case 2: return std::make_unique<GSession<DihedralElement>>();
        case 3: return std::make_unique<GSession<Permutation>>();
        case 4: return std::make_unique<GSession<std::string>>();
        // case 5: if (product){
        //     std::cout << "Select left group";
        //     auto left = makeSession(selectFamily(false));
        //     std::cout << "Select right group";
        //     auto right = makeSession(selectFamily(false));
        //
        // }
        //     else {
        //         return nullptr;
        //     }
        case 0: return nullptr;
    }

    return nullptr;
}

void run()
{

    while (true) {

        auto s = makeSession(selectFamily());
        s->createGroup();
        while (!s->hasGroup()){
            if (s == nullptr) {
                return;
            }
            s = makeSession(selectFamily());
            s->createGroup();
        }

        menu(*s);

    }
}