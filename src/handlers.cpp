#include <cstdio>
#include <cstdint>
#include <cinttypes>
#include "communicator.h"

extern "C" bool fCmpInstHandler(double, double, bool, int32_t,
                                char*, char*, uint64_t, int32_t, int32_t);
extern "C" bool iCmpInstHandler(uint64_t, uint64_t, bool, int32_t,
                                char*, char*, uint64_t, int32_t, int32_t);
extern "C" void fAddHandler(double, double, char*, char*, uint64_t, int32_t, int32_t);
extern "C" void fSubHandler(double, double, char*, char*, uint64_t, int32_t, int32_t);
extern "C" void fMulHandler(double, double, char*, char*, uint64_t, int32_t, int32_t);
extern "C" void fDivHandler(double, double, char*, char*, uint64_t, int32_t, int32_t);
extern "C" void callOneArgHandler(int32_t, double, char*, char*, uint64_t, int32_t, int32_t);
extern "C" void callTwoArgsHandler(int32_t, double, double, char*, char*, uint64_t, int32_t, int32_t);

bool fCmpInstHandler(
        double a,
        double b,
        bool origin_res,
        int32_t predicate,
        char* funcName,
        char* modName,
        uint64_t instID,
        int32_t debugLine,
        int32_t debugCol)
{
    return origin_res;
}

bool iCmpInstHandler(
        uint64_t a,
        uint64_t b,
        bool origin_res,
        int32_t predicate,
        char* funcName,
        char* modName,
        uint64_t instID,
        int32_t debugLine,
        int32_t debugCol)
{
    return origin_res;
}

void fAddHandler(
    double a,
    double b,
    char* funcName,
    char* modName,
    uint64_t instID,
    int32_t debugLine,
    int32_t debugCol)
{
    Communicator &comm = Communicator::getInstance();
    comm.writeInstInfo(OP_ADD, a, b, instID);
}

void fSubHandler(
    double a,
    double b,
    char* funcName,
    char* modName,
    uint64_t instID,
    int32_t debugLine,
    int32_t debugCol)
{
    Communicator &comm = Communicator::getInstance();
    comm.writeInstInfo(OP_SUB, a, b, instID);
}

void fMulHandler(
    double a,
    double b,
    char* funcName,
    char* modName,
    uint64_t instID,
    int32_t debugLine,
    int32_t debugCol)
{
    Communicator &comm = Communicator::getInstance();
    comm.writeInstInfo(OP_MUL, a, b, instID);
}

void fDivHandler(
    double a,
    double b,
    char* funcName,
    char* modName,
    uint64_t instID,
    int32_t debugLine,
    int32_t debugCol)
{
    Communicator &comm = Communicator::getInstance();
    comm.writeInstInfo(OP_DIV, a, b, instID);
}

void callOneArgHandler(
    int32_t functionID,
    double a,
    char* funcName,
    char* modName,
    uint64_t instID,
    int32_t debugLine,
    int32_t debugCol)
{
    Communicator &comm = Communicator::getInstance();
    comm.writeInstInfo(functionID, a, a, instID);
}

void callTwoArgsHandler(
    int32_t functionID,
    double a,
    double b,
    char* funcName,
    char* modName,
    uint64_t instID,
    int32_t debugLine,
    int32_t debugCol)
{
    Communicator &comm = Communicator::getInstance();
    comm.writeInstInfo(functionID, a, b, instID);
}
