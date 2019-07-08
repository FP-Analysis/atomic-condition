#include "fpUtil.h"

double fpUtil::i64ToDouble(uint64_t i) {
    return *(double*)(&i);
}

uint64_t fpUtil::doubleToI64(double d) {
    return *(uint64_t*)(&d);
}

float fpUtil::i32ToFloat(uint32_t i) {
    return *(float*)(&i);
}

uint32_t fpUtil::floatToI32(float f) {
    return *(uint32_t*)(&f);
}

uint64_t fpUtil::getDoubleSign(double d) {
    uint64_t i = doubleToI64(d);
    return (i & DBL_SIGNMASK) >> 63;
}

uint64_t fpUtil::getDoubleExpo(double d) {
    uint64_t i = doubleToI64(d);
    return (i & DBL_EXPOMASK) >> 52;
}

uint64_t fpUtil::getDoubleFrac(double d) {
    uint64_t i = doubleToI64(d);
    return (i & DBL_FRACMASK);
}

uint32_t fpUtil::getFloatSign(float f) {
    uint32_t i = floatToI32(f);
    return (i & FLT_SIGNMASK) >> 31;
}

uint32_t fpUtil::getFloatExpo(float f) {
    uint32_t i = floatToI32(f);
    return (i & FLT_EXPOMASK) >> 23;
}

uint32_t fpUtil::getFloatFrac(float f) {
    uint32_t i = floatToI32(f);
    return (i & FLT_FRACMASK);
}

double fpUtil::buildDouble(uint64_t sign, uint64_t expo, uint64_t frac) {
    uint64_t bits;
    bits  = (sign << 63) & DBL_SIGNMASK;
    bits |= (expo << 52) & DBL_EXPOMASK;
    bits |= (frac & DBL_FRACMASK);
    return i64ToDouble(bits);
}

float fpUtil::buildFloat(uint32_t sign, uint32_t expo, uint32_t frac) {
    uint32_t bits;
    bits  = (sign << 31) & FLT_SIGNMASK;
    bits |= (expo << 23) & FLT_EXPOMASK;
    bits |= (frac & FLT_FRACMASK);
    return i32ToFloat(bits);
}

double fpUtil::doubleULP(double d) {
    uint64_t bits = doubleToI64(d);
    // make it positive.
    bits = bits & (DBL_EXPOMASK | DBL_FRACMASK);
    d = i64ToDouble(bits);
    double d_plus = i64ToDouble(bits+1);
    return d_plus - d;
}

float fpUtil::floatULP(float f) {
    uint32_t bits = floatToI32(f);
    // make it positive.
    bits = bits & (FLT_EXPOMASK | FLT_FRACMASK);
    f = i32ToFloat(bits);
    float f_plus = i32ToFloat(bits+1);
    return f_plus - f;
}

uint64_t fpUtil::doubleDist(double d1, double d2) {
    uint64_t dist, bits1, bits2;
    bits1 = doubleToI64(d1) & (DBL_EXPOMASK | DBL_FRACMASK);
    bits2 = doubleToI64(d2) & (DBL_EXPOMASK | DBL_FRACMASK);
    if ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) {
        dist = bits1 + bits2;
    }
    else {
        if (bits1 > bits2)
            dist = bits1 - bits2;
        else
            dist = bits2 - bits1;
    }
    return dist;
}

uint32_t fpUtil::floatDist(float f1, float f2) {
    uint32_t dist, bits1, bits2;
    bits1 = doubleToI64(f1) & (FLT_EXPOMASK | FLT_FRACMASK);
    bits2 = doubleToI64(f2) & (FLT_EXPOMASK | FLT_FRACMASK);
    if ((f1 > 0 && f2 < 0) || (f1 < 0 && f2 > 0)) {
        dist = bits1 + bits2;
    }
    else {
        if (bits1 > bits2)
            dist = bits1 - bits2;
        else
            dist = bits2 - bits1;
    }
    return dist;
}

uint64_t fpUtil::rand64() {
    // important to make the generator 'static' here.
    static std::mt19937_64 mt_generator_64(0xdeadbeef);
    return mt_generator_64();
}

//mindis not included,maxdis included.
double fpUtil::randNeighbor(double x,uint64_t mindis,uint64_t maxdis){
    uint64_t tmp;
    uint64_t bits = 0;
    uint64_t sign = fpUtil::getDoubleSign(x);
    uint64_t expo = fpUtil::getDoubleExpo(x);
    uint64_t frac = fpUtil::getDoubleFrac(x);
    uint64_t newfrac;
    
    //buggy
    //uint64_t nlower = fmax(0,frac - maxdis);
    //uint64_t nupper = fmax(0,frac - mindis);

    uint64_t nlower = frac < maxdis ? 0 : frac-maxdis;
    uint64_t nupper = frac < mindis ? 0 : frac-mindis;

    uint64_t nrange = nupper-nlower;
    uint64_t plower = fmin(DBL_FRACMASK,frac + mindis);
    uint64_t pupper = fmin(DBL_FRACMASK,frac + maxdis);
    uint64_t prange = pupper - plower;
    assert(nrange+prange > 1);
    //use rand64(?)
    uint64_t r = rand64()%(nrange+prange);
    if(r<nrange)
        newfrac = r + nlower;
    else
        newfrac = (r-nrange) + plower + 1;
    if(newfrac > frac)assert(newfrac-frac >= mindis && newfrac-frac <= maxdis);
    else assert(frac-newfrac >= mindis && frac-newfrac <= maxdis);
    return fpUtil::buildDouble(sign,expo,newfrac);
}

uint32_t fpUtil::rand32() {
    // important to make the generator 'static' here.
    static std::mt19937 mt_generator_32(0xdeadbeef);
    return mt_generator_32();
}

double fpUtil::randDouble() {
    return i64ToDouble(rand64());
}

float fpUtil::randFloat() {
    return i32ToFloat(rand32());
}

double fpUtil::rand01()
{
    return fabs(fpUtil::randDouble()/fpUtil::DBL_POSINF);
}

double fpUtil::revisedCondition(uint64_t opcode, double lhs, double rhs) {
    double cond1, cond2;
    double dzdist;
    switch(opcode) {
        case OP_ADD:
            dzdist = fabs(lhs+rhs);
            cond1 = fabs(lhs) / dzdist;
            cond2 = fabs(rhs) / dzdist;
            return cond1 + cond2 - dzdist;
        case OP_SUB:
            dzdist = fabs(lhs-rhs);
            cond1 = fabs(lhs) / dzdist;
            cond2 = fabs(rhs) / dzdist;
            return cond1 + cond2 - dzdist;
        case OP_SIN:
            // cond1 = fabs(lhs / tan(lhs));
            // x \to n*pi, n \in Z.
            cond1 = 1 / fabs(remainder(lhs, fpUtil::PI));
            return cond1;
        case OP_COS:
            // cond1 = fabs(lhs * tan(lhs));
            // x \to n*pi + pi/2, n \in Z.
            cond1 = 1 / fabs(remainder((remainder(lhs, fpUtil::PI)-fpUtil::PI_2),fpUtil::PI));
            return cond1;
        case OP_TAN:
            // cond1 = fabs(lhs / (sin(lhs) * cos(lhs)));
            // x \to n*pi/2, n \in Z.
            cond1 = 1 / fabs(remainder(lhs, fpUtil::PI_2));
            return cond1;
        case OP_ASIN:
            cond1 = fabs(lhs / (sqrt(1-lhs*lhs) * asin(lhs)));
            return cond1;
        case OP_ACOS:
            cond1 = fabs(lhs / (sqrt(1-lhs*lhs) * acos(lhs)));
            return cond1;
        case OP_SINH:
            cond1 = fabs(lhs / tanh(lhs));
            return cond1;
        case OP_COSH:
            cond1 = fabs(lhs * tanh(lhs));
            return cond1;
        case OP_LOG:
            dzdist = fabs(lhs - 1);
            cond1 = fabs(1 / log(lhs));
            return cond1 - dzdist;
        case OP_LOG10:
            dzdist = fabs(lhs - 1);
            cond1 = fabs(1 / log(lhs));
            return cond1 - dzdist;
        case OP_POW:
            cond1 = fabs(rhs);
            cond2 = fabs(rhs * log(lhs));
            return cond1 + cond2;
        default:
            return -DBL_MAX;
    }
    return -DBL_MAX;
}

double fpUtil::rawCondition(uint64_t opcode, double lhs, double rhs) {
    double cond1, cond2, dzdist;
    switch(opcode) {
        case OP_ADD:
            dzdist = fabs(lhs+rhs);
            cond1 = fabs(lhs) / dzdist;
            cond2 = fabs(rhs) / dzdist;
            return cond1 + cond2;
        case OP_SUB:
            dzdist = fabs(lhs-rhs);
            cond1 = fabs(lhs) / dzdist;
            cond2 = fabs(rhs) / dzdist;
            return cond1 + cond2;
        case OP_SIN:
            cond1 = fabs(lhs / tan(lhs));
            return cond1;
        case OP_COS:
            cond1 = fabs(lhs * tan(lhs));
            return cond1;
        case OP_TAN:
            cond1 = fabs(lhs / (sin(lhs) * cos(lhs)));
            return cond1;
        case OP_ASIN:
            cond1 = fabs(lhs / (sqrt(1-lhs*lhs) * asin(lhs)));
            return cond1;
        case OP_ACOS:
            cond1 = fabs(lhs / (sqrt(1-lhs*lhs) * acos(lhs)));
            return cond1;
        case OP_SINH:
            cond1 = fabs(lhs / tanh(lhs));
            return cond1;
        case OP_COSH:
            cond1 = fabs(lhs * tanh(lhs));
            return cond1;
        case OP_LOG:
            dzdist = fabs(lhs - 1);
            cond1 = fabs(1 / log(lhs));
            return cond1;
        case OP_LOG10:
            dzdist = fabs(lhs - 1);
            cond1 = fabs(1 / log(lhs));
            return cond1;
        case OP_POW:
            cond1 = fabs(rhs);
            cond2 = fabs(rhs * log(lhs));
            return cond1 + cond2;
        default:
            return 1;
    }
    return 1;
}

double fpUtil::negInvRevisedCondition(uint64_t opcode, double lhs, double rhs){
    return -1.0/(revisedCondition(opcode,lhs,rhs));
}