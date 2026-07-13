//
// Created by georg on 04/07/2026.
//

#ifndef INTROALGEBRA_SELECTFAMMENU_H
#define INTROALGEBRA_SELECTFAMMENU_H

#include<iostream>
#include "smallhelpers.h"

inline int selectFamily(bool product=true)
{
    //if (!product) {
    while (true) {
        switch (getChoice("Select Group Family", {

                                  "Cyclic Groups",
                                  "Dihedral Groups",
                                  "Permutation Groups",
                                  "Named Groups",
                              })) {
            default: std::cout << "Invalid choice\n"; break;
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            case 4: return 4;
            case 0: return 0;
        }
    }//}
    //else {
        while (true) {
            switch (getChoice("Select Group Family", {

                                      "Cyclic Groups",
                                      "Dihedral Groups",
                                      "Permutation Groups",
                                      "Named Groups",
                "Direct Product"
                                  })) {
                default: std::cout << "Invalid choice\n"; break;
                case 1: return 1;
                case 2: return 2;
                case 3: return 3;
                case 4: return 4;
                case 5: return 5;
                case 0: return 0;
                                  }
        }
    //}
}



#endif //INTROALGEBRA_SELECTFAMMENU_H
