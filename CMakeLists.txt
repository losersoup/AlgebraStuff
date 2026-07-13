cmake_minimum_required(VERSION 4.2)
project(IntroAlgebra)

set(CMAKE_CXX_STANDARD 23)

add_executable(IntroAlgebra main.cpp
        Set.h
        OneOpAlgebraic.h
        Coset.h
        session.h
        Menus/propertyMenu.cpp
        Menus/propertyMenu.h
        Menus/smallhelpers.cpp
        Menus/smallhelpers.h
        Menus/factorGroupMenu.cpp
        Menus/factorGroupMenu.h
        Algebra/GroupAlgos.cpp
        Algebra/GroupAlgos.h
        Algebra/CosetAlgos.cpp
        Algebra/CosetAlgos.h
        GroupFactory/Dihedral.cpp
        GroupFactory/Dihedral.h
        GroupFactory/K4.cpp
        GroupFactory/K4.h
        GroupFactory/Cyclic.cpp
        GroupFactory/Cyclic.h
        Algebra/SetAlgos.cpp
        Algebra/SetAlgos.h
        Menus/cosetMenu.cpp
        Menus/cosetMenu.h
        Menus/subgroupMenu.cpp
        Menus/subgroupMenu.h
        Menus/groupInfoMenu.cpp
        Menus/groupInfoMenu.h
        Menus/mGroupMenu.cpp
        Menus/mGroupMenu.h
        GroupFactory/Permutation.cpp
        GroupFactory/Permutation.h
        Menus/selectFamMenu.h
        Menus/runMenu.cpp
        Menus/runMenu.h
        GSession.h
        GroupFactory/Quaternions.cpp
        GroupFactory/Quaternions.h
        GroupFactory/ProductElement.cpp
        GroupFactory/ProductElement.h
)
