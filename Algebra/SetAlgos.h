//
// Created by georg on 04/07/2026.
//

#ifndef INTROALGEBRA_SETALGOS_H
#define INTROALGEBRA_SETALGOS_H


#include "../Set.h"




template<typename T>
Set<T> intersect(Set<T> &set1, Set<T> &set2) {
    std::vector<T> arr1 = set1.getElements();
    std::vector<T> arr2 = set2.getElements();
    std::vector<T> intr;
    int pos = 0;
    for (int i = 0; i < arr1.size(); i++) {
        if (set2.searchSet(arr1[i])) {
            intr.push_back(arr1[i]); // corrected
            pos++;
        }
    }
    Set res(intr);
    return res;
}


template<typename T>
Set<T> unio(Set<T> &set1, Set<T> &set2) {

    std::vector<T> v1 = set1.getElements();
    std::vector<T> v2 = set2.getElements();
    std::vector<T> v3 = v1;
    v3.insert(v3.end(), v2.begin(), v2.end());
    Set<T> res(v3);
    return res;
}


template<typename T>
bool compareSets(Set<T> &set1, Set<T> &set2) {
    return (set1.getElements() == set2.getElements());

}


#endif //INTROALGEBRA_SETALGOS_H
