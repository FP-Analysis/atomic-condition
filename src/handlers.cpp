#include <cstdio>
#include <cstdint>
#include <cinttypes>
#include "solver.h"
#include "communicator.h"

#define USE_COMM true

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
    Solver &solver = Solver::getInstance();
    solver.catchPredicateF(a,b,origin_res,instID);
    // printf("----Floating----\nModule-Function-Inst: %s - %s - %" PRIx64 "\n", modName, funcName, instID);
    // printf("Operand 1:  %.5e\n", a);
    // printf("Operand 2:  %.5e\n", b);
    // printf("Predicate:  %d\n", predicate);
    // printf("CompareRes: %d\n", origin_res);
    // if (debugLine != 0) {
    //     printf("DebugInfo:  %d:%d\n", debugLine, debugCol);
    // }
    // else {
    //     printf("No DebugInfo.\n");
    // }
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
    Solver &solver = Solver::getInstance();
    solver.catchPredicateI(a,b,origin_res,instID);
    // printf("----Integer----\nModule-Function-Inst: %s - %s - %" PRIx64 "\n", modName, funcName, instID);
    // printf("Operand 1:  %" PRIu64 "\n", a);
    // printf("Operand 2:  %" PRIu64 "\n", b);
    // printf("Predicate:  %d\n", predicate);
    // printf("CompareRes: %d\n", origin_res);
    // if (debugLine != 0) {
    //     printf("DebugInfo:  %d:%d\n", debugLine, debugCol);
    // }
    // else {
    //     printf("No DebugInfo.\n");
    // }
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
    if (USE_COMM) {
        Communicator &comm = Communicator::getInstance();
        comm.writeInstInfo(OP_ADD, a, b, instID);
    }

    else {
        Solver &solver = Solver::getInstance();
        solver.catchFAdd(a,b,instID);
    }

    // printf("----FAdd----\nModule-Function-Inst: %s - %s - %" PRIx64 "\n", modName, funcName, instID);
    // printf("Operand 1:  %.5e\n", a);
    // printf("Operand 2:  %.5e\n", b);
    // if (debugLine != 0) {
    //     printf("DebugInfo:  %d:%d\n", debugLine, debugCol);
    // }
    // else {
    //     printf("No DebugInfo.\n");
    // }
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
    if (USE_COMM) {
        Communicator &comm = Communicator::getInstance();
        comm.writeInstInfo(OP_SUB, a, b, instID);
    }
    else {
        Solver &solver = Solver::getInstance();
        solver.catchFSub(a,b,instID);
    }

    // printf("----FSub----\nModule-Function-Inst: %s - %s - %" PRIx64 "\n", modName, funcName, instID);
    // printf("Operand 1:  %.5e\n", a);
    // printf("Operand 2:  %.5e\n", b);
    // if (debugLine != 0) {
    //     printf("DebugInfo:  %d:%d\n", debugLine, debugCol);
    // }
    // else {
    //     printf("No DebugInfo.\n");
    // }
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
    if (USE_COMM) {
        Communicator &comm = Communicator::getInstance();
        comm.writeInstInfo(OP_MUL, a, b, instID);
    }
    else {
        Solver &solver = Solver::getInstance();
        solver.catchFMul(a,b,instID);
    }

    // printf("----FMul----\nModule-Function-Inst: %s - %s - %" PRIx64 "\n", modName, funcName, instID);
    // printf("Operand 1:  %.5e\n", a);
    // printf("Operand 2:  %.5e\n", b);
    // if (debugLine != 0) {
    //     printf("DebugInfo:  %d:%d\n", debugLine, debugCol);
    // }
    // else {
    //     printf("No DebugInfo.\n");
    // }
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
    if (USE_COMM) {
        Communicator &comm = Communicator::getInstance();
        comm.writeInstInfo(OP_DIV, a, b, instID);
    }
    else {
        Solver &solver = Solver::getInstance();
        solver.catchFDiv(a,b,instID);
    }

    // printf("----FDiv----\nModule-Function-Inst: %s - %s - %" PRIx64 "\n", modName, funcName, instID);
    // printf("Operand 1:  %.5e\n", a);
    // printf("Operand 2:  %.5e\n", b);
    // if (debugLine != 0) {
    //     printf("DebugInfo:  %d:%d\n", debugLine, debugCol);
    // }
    // else {
    //     printf("No DebugInfo.\n");
    // }
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
    if (USE_COMM) {
        Communicator &comm = Communicator::getInstance();
        comm.writeInstInfo(functionID, a, a, instID);
    }
    else {
        Solver &solver = Solver::getInstance();
        switch (functionID) {
            case OP_SIN:   solver.catchSin(a,instID);  break;
            case OP_COS:   solver.catchCos(a,instID);  break;
            case OP_TAN:   solver.catchTan(a,instID);  break;
            case OP_ASIN:  solver.catchAsin(a,instID); break;
            case OP_ACOS:  solver.catchAcos(a,instID); break;
            case OP_ATAN:  solver.catchAtan(a,instID); break;
            case OP_SINH:  solver.catchSinh(a,instID); break;
            case OP_COSH:  solver.catchCosh(a,instID); break;
            case OP_TANH:  solver.catchTanh(a,instID); break;
            case OP_EXP:   solver.catchExp(a,instID);  break;
            case OP_LOG:   solver.catchLog(a,instID);  break;
            case OP_LOG10: solver.catchLog10(a,instID);break;
            case OP_SQRT:  solver.catchSqrt(a,instID); break;
        }
    }
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
    if (USE_COMM) {
        Communicator &comm = Communicator::getInstance();
        comm.writeInstInfo(functionID, a, b, instID);
    }
    else {
        Solver &solver = Solver::getInstance();
        switch (functionID) {
            case OP_ATAN2: solver.catchAtan2(a,b,instID); break;
            case OP_POW:   solver.catchPow(a,b,instID);   break;
        }
    }
}