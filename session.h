//
// Created by  on 04/07/2026.
//

#ifndef INTROALGEBRA_SESSION_H
#define INTROALGEBRA_SESSION_H


#include "Set.h"
#include "GroupFactory/Permutation.h"

class IGroupSession
{
public:

    virtual ~IGroupSession() = default;

    virtual void displayGroup() = 0;

    virtual void displaySubset() = 0;

    virtual void displayFactorGroup() = 0;

    virtual void inputSubset() = 0;

    virtual void leftCosetPartition() = 0;

    virtual void rightCosetPartition() = 0;

    virtual void leftCoset(std::string g) = 0;

    virtual void rightCoset(std::string g) = 0;

    virtual bool checkElement(std::string&) = 0;
    virtual bool isSubgroup() = 0;

    virtual bool isNormal() = 0;

    virtual void QuotCenter() = 0;

    virtual bool isAbelian() = 0;
    virtual bool isCyclic() = 0;

    virtual void createGroup() = 0;

    virtual int elementOrder(std::string g) = 0;

    virtual bool hasSubset() const = 0;

    virtual bool hasFactorGroup() const = 0;

    virtual bool hasGroup() const = 0;

    virtual void dispCent() = 0;

    virtual std::string getgroupName() const = 0;

    virtual void QuotSubset() = 0;

    virtual void setgroupName(std::string& n) = 0;

    virtual std::string getStruct() const = 0;

    virtual void dispC() = 0;
    virtual void dispFGC() = 0;
    virtual void clearFactorGroup() = 0;
    virtual void clearSubset() = 0;


    virtual void getGenerators() = 0;

    virtual void getId() = 0;

    virtual int order() const = 0;

    virtual void generateCyclicSubgroup(std::string g) = 0;
};

#endif //INTROALGEBRA_SESSION_H

