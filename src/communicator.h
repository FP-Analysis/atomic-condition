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
class Communicator {
public:
    static Communicator& getInstance() {
        static Communicator instance;
        return instance;
    }
private:
    Communicator() { }
public:
    Communicator(Communicator const &)  = delete;
    void operator=(Communicator const&) = delete;

private:
    std::vector<InstInfo> infoList;
    std::set<uint64_t> instIDSet;
    bool record = false;
    int unStable[OPSIZE] = {};

public:
    void initComm() {
        clearInfoList();
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

    bool isEmpty() {
        return infoList.empty();
    }

};

#endif