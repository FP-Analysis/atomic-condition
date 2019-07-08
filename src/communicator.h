#ifndef COMM_H
#define COMM_H

#include <stdint.h>
#include <vector>
#include <set>
#include "opcode.h"

struct InstInfo
{
    uint64_t    opcode = -1;
    double      op1 = 0;
    double      op2 = 0;
    uint64_t    instID = 0;
};
// Singleton Class. See more:
// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class Communicator {
public:
    static Communicator& getInstance() {
        static Communicator instance; // Guaranteed to be destroyed.
                                // Instantiated on first use.
        return instance;
    }
private:
    // Constructor? (the {} brackets) are needed here.
    Communicator() { }

public:
    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    Communicator(Communicator const &)  = delete;
    void operator=(Communicator const&) = delete;
// Template Done.


/*
 *  Reader and Writer using std::vector
 *  
 *  Basic logic:
 *  If not initialed, the writer will not write anything to vector.
 *  
 *  Format define:
 *  See the definition of struct InstInfo.
 */
private:
    std::vector<InstInfo> infoList;
    std::set<uint64_t> instIDSet;
    bool record = false;
    int unStable[OPSIZE] = {};

public:

    void initComm() {
        clearInfoList();
        // clearInstIDSet();
        record = true;
        // setup all unstable operations.
        unStable[OP_ADD] = 1;
        unStable[OP_SUB] = 1;
        unStable[OP_MUL] = 0;
        unStable[OP_DIV] = 0;

        unStable[OP_SIN] = 1;
        unStable[OP_COS] = 1;
        unStable[OP_TAN] = 1;
        unStable[OP_ASIN] = 1;
        unStable[OP_ACOS] = 1;
        unStable[OP_ATAN] = 0;
        unStable[OP_ATAN2] = 0;

        unStable[OP_SINH] = 1;
        unStable[OP_COSH] = 1;
        unStable[OP_TANH] = 0;

        unStable[OP_EXP] = 0;
        unStable[OP_LOG] = 1;
        unStable[OP_LOG10] = 1;

        unStable[OP_SQRT] = 0;
        unStable[OP_POW] = 1;
    }

    void clearInstIDSet() {
        std::set<uint64_t> emptySet;
        std::swap(instIDSet, emptySet);
    }

    void clear() {
        clearInfoList();
    }
 
    void clearInfoList() {
        std::vector<InstInfo> emptyList;
        std::swap(infoList, emptyList);
    }

    void writeInstInfo(uint64_t opcode, double op1, double op2, uint64_t instID) {
        if (record == false) {
            return;
        }
        // After get the statistic, We no longer need this.
        // Fast 50% if we do not maintain the set everytime.
        // instIDSet.insert(instID);

        if (unStable[opcode] == 0) {
            return;
        }
        // The below code works if record sets to true.
        InstInfo info;
        info.opcode = opcode;
        info.op1 = op1;
        info.op2 = op2;
        info.instID = instID;
        infoList.push_back(info);
    }

    std::vector<InstInfo> getInstInfoList() {
        return infoList;
    }

    int32_t getInstIDSize() {
        return instIDSet.size();
    }

    bool isEmpty() {
        return infoList.empty();
    }

};

#endif