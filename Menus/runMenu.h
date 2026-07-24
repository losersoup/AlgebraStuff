//
// Created by georg on 04/07/2026.
//

#ifndef INTROALGEBRA_RUNMENU_H
#define INTROALGEBRA_RUNMENU_H
#include <memory>

#include "../session.h"

void run();

std::unique_ptr<IGroupSession> makeSession(int choice);


#endif //INTROALGEBRA_RUNMENU_H
