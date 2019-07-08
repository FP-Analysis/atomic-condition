#ifndef FPUTIL_H
#define FPUTIL_H

#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cfloat>
#include <assert.h>
#include <cmath>
#include <random>
#include "opcode.h"

namespace fpUtil {
    const uint64_t DBL_SIGNMASK = 0x8000000000000000uLL;
    const uint64_t DBL_EXPOMASK = 0x7FF0000000000000uLL;
    const uint64_t DBL_FRACMASK = 0x000FFFFFFFFFFFFFuLL;

    const uint64_t DBL_POSINF = 0x7FF0000000000000uLL;
    const uint64_t DBL_NEGINF = 0xFFF0000000000000uLL;
    const uint64_t DBL_NAN    = 0x7FFFFFFFFFFFFFFFuLL;

    const uint32_t FLT_SIGNMASK = 0x80000000;
    const uint32_t FLT_EXPOMASK = 0x7F800000;
    const uint32_t FLT_FRACMASK = 0x007FFFFF;

    const uint32_t FLT_POSINF = 0x7F800000;
    const uint32_t FLT_NEGINF = 0xFF800000;
    const uint32_t FLT_NAN    = 0x7FFFFFFF;

    const double PI   = 3.14159265358979;
    const double PI_2 = 1.57079632679490;

    // Convert between floating point and bits.
    double   i64ToDouble(uint64_t i);
    uint64_t doubleToI64(double d);

    float    i32ToFloat(uint32_t i);
    uint32_t floatToI32(float f);

    // Get parts from floating point.
    uint64_t getDoubleSign(double d);
    uint64_t getDoubleExpo(double d);
    uint64_t getDoubleFrac(double d);

    uint32_t getFloatSign(float f);
    uint32_t getFloatExpo(float f);
    uint32_t getFloatFrac(float f);

    // Build floating point from parts.
    double buildDouble(uint64_t sign, uint64_t expo, uint64_t frac);

    float buildFloat(uint32_t sign, uint32_t expo, uint32_t frac);

    // ULP value.
    double doubleULP(double d);
    float floatULP(float f);

    // POPL19 Dist value.
    uint64_t doubleDist(double d1, double d2);
    uint32_t floatDist(float f1, float f2);

    // Random functions.
    uint64_t rand64();
    double randNeighbor(double x, uint64_t mindis,uint64_t maxdis);
    double randDouble();

    uint32_t rand32();
    float randFloat();

    double rand01();

    // ConditionNumber
    double revisedCondition(uint64_t opcode, double lhs, double rhs);
    double negInvRevisedCondition(uint64_t opcode, double lhs, double rhs);
    double rawCondition(uint64_t opcode, double lhs, double rhs);
};
#endif
