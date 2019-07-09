import io
import mpmath
import signal
import json
import struct
import math

def f0(x):
    # airy_Ai
    return mpmath.airyai(x)
def f1(x):
    # airy_Bi
    return mpmath.airybi(x)
def f2(x):
    # airy_Ai_scaled
    scale = mpmath.exp(mpmath.mpf(2)/mpmath.mpf(3)*mpmath.sqrt(x)*x)
    y = mpmath.airyai(x)
    if x > 0.0:
        y = y * scale
    return y
def f3(x):
    # airy_Bi_scaled
    scale = mpmath.exp(-mpmath.mpf(2)/mpmath.mpf(3)*mpmath.sqrt(x)*x)
    y = mpmath.airybi(x)
    if x > 0.0:
        y = y * scale
    return y
def f4(x):
    # airy_Ai_deriv
    return mpmath.airyai(x, derivative=1)
def f5(x):
    # airy_Bi_deriv
    return mpmath.airybi(x, derivative=1)
def f6(x):
    # airy_Ai_deriv_scaled
    scale = mpmath.exp(mpmath.mpf(2)/mpmath.mpf(3)*mpmath.sqrt(x)*x)
    y = mpmath.airyai(x, derivative=1)
    if x > 0.0:
        y = y * scale
    return y
def f7(x):
    # airy_Bi_deriv_scaled
    scale = mpmath.exp(-mpmath.mpf(2)/mpmath.mpf(3)*mpmath.sqrt(x)*x)
    y = mpmath.airybi(x, derivative=1)
    if x > 0.0:
        y = y * scale
    return y
def f8(x):
    # bessel_J0
    return mpmath.besselj(0,x)
def f9(x):
    # bessel_J1
    return mpmath.besselj(1,x)
def f10(x):
    # bessel_Y0
    return mpmath.bessely(0,x)
def f11(x):
    # bessel_Y1
    return mpmath.bessely(1,x)
def f12(x):
    # bessel_I0
    return mpmath.besseli(0,x)
def f13(x):
    # bessel_I1
    return mpmath.besseli(1,x)
def f14(x):
    # bessel_I0_scaled
    scale = mpmath.exp(-abs(x))
    y = mpmath.besseli(0,x) * scale
    return y
def f15(x):
    # bessel_I1_scaled
    scale = mpmath.exp(-abs(x))
    y = mpmath.besseli(1,x) * scale
    return y
def f16(x):
    # bessel_K0
    return mpmath.besselk(0,x)
def f17(x):
    # bessel_K1
    return mpmath.besselk(1,x)
def f18(x):
    # bessel_K0_scaled
    scale = mpmath.exp(x)
    return mpmath.besselk(0,x)*scale
def f19(x):
    # bessel_K1_scaled
    scale = mpmath.exp(x)
    return mpmath.besselk(1,x)*scale
def f20(x):
    # bessel_j0
    x = mpmath.mpf(x)
    return mpmath.sin(x) / x
def f21(x):
    # bessel_j1
    x = mpmath.mpf(x)
    y = (mpmath.sin(x)/x - mpmath.cos(x)) / x
    return y
def f22(x):
    # bessel_j2
    x = mpmath.mpf(x)
    y = ((3/(x*x)-1) * mpmath.sin(x) - 3*mpmath.cos(x)/x) / x
    return y
def f23(x):
    # bessel_y0
    x = mpmath.mpf(x)
    return -mpmath.cos(x)/x
def f24(x):
    # bessel_y1
    x = mpmath.mpf(x)
    return -(mpmath.cos(x)/x + mpmath.sin(x)) / x
def f25(x):
    # bessel_y2
    x = mpmath.mpf(x)
    y = (-3/(x*x*x)+1/x)*mpmath.cos(x)-(3/(x*x))*mpmath.sin(x)
    return y
def f26(x):
    # bessel_i0_scaled
    x = mpmath.mpf(x)
    y = mpmath.sqrt(mpmath.pi/(2*x)) * mpmath.besseli(0.5,x) * mpmath.exp(-abs(x))
    return y
def f27(x):
    # bessel_i1_scaled
    x = mpmath.mpf(x)
    y = mpmath.sqrt(mpmath.pi/(2*x)) * mpmath.besseli(1.5,x) * mpmath.exp(-abs(x))
    return y
def f28(x):
    # bessel_i2_scaled
    x = mpmath.mpf(x)
    y = mpmath.sqrt(mpmath.pi/(2*x)) * mpmath.besseli(2.5,x) * mpmath.exp(-abs(x))
def f29(x):
    # bessel_k0_scaled
    x = mpmath.mpf(x)
    y = mpmath.sqrt(mpmath.pi/(2*x)) * mpmath.besselk(0.5,x) * mpmath.exp(x)
    return y
def f30(x):
    # bessel_k1_scaled
    x = mpmath.mpf(x)
    y = mpmath.sqrt(mpmath.pi/(2*x)) * mpmath.besselk(1.5,x) * mpmath.exp(x)
    return y
def f31(x):
    # bessel_k2_scaled
    x = mpmath.mpf(x)
    y = mpmath.sqrt(mpmath.pi/(2*x)) * mpmath.besselk(2.5,x) * mpmath.exp(x)
    return y
def f32(x):
    # clausen
    return mpmath.clsin(2,x)
def f40(x):
    # dilog
    return mpmath.polylog(2,x)
def f41(x):
    # ellint_Kcomp
    x = mpmath.mpf(x)
    return mpmath.ellipk(x*x)
def f42(x):
    # ellint_Ecomp
    x = mpmath.mpf(x)
    return mpmath.ellipe(x*x)
def f44(x):
    # erfc
    return mpmath.erfc(x)
def f45(x):
    # log_erfc
    return mpmath.log(mpmath.erfc(x))
def f46(x):
    # erf
    return mpmath.erf(x)
def f47(x):
    # erf_Z
    return mpmath.npdf(x)
def f48(x):
    # erf_Q
    return 1-mpmath.ncdf(x)
def f49(x):
    # hazard
    return mpmath.npdf(x) / (1-mpmath.ncdf(x))
def f50(x):
    # exp
    return mpmath.exp(x)
def f51(x):
    # expm1
    return mpmath.expm1(x)
def f52(x):
    # exprel
    x = mpmath.mpf(x)
    return mpmath.expm1(x)/x
def f53(x):
    # exprel_2
    x = mpmath.mpf(x)
    y = 2*(mpmath.expm1(x)-x)/(x*x)
    return y
def f54(x):
    # expint_E1
    return mpmath.expint(1, x)
def f55(x):
    # expint_E2
    return mpmath.expint(2, x)
def f56(x):
    # expint_E1_scaled
    return mpmath.expint(1, x) * mpmath.exp(x)
def f57(x):
    # expint_E2_scaled
    return mpmath.expint(2, x) * mpmath.exp(x)
def f58(x):
    # expint_Ei
    return mpmath.ei(x)
def f59(x):
    # expint_Ei_scaled
    return mpmath.ei(x) * mpmath.exp(-x)
def f60(x):
    # Shi
    return mpmath.shi(x)
def f61(x):
    # Chi
    return mpmath.chi(x)
def f63(x):
    # Si
    return mpmath.si(x)
def f64(x):
    # Ci
    return mpmath.ci(x)
def f66(x):
    # fermi_dirac_m1
    return -mpmath.polylog(0, -mpmath.exp(x))
def f67(x):
    # fermi_dirac_0
    return -mpmath.polylog(1, -mpmath.exp(x))
def f68(x):
    # fermi_dirac_1
    return -mpmath.polylog(2, -mpmath.exp(x))
def f69(x):
    # fermi_dirac_2
    return -mpmath.polylog(3, -mpmath.exp(x))
def f70(x):
    # fermi_dirac_mhalf
    return -mpmath.polylog(0.5, -mpmath.exp(x))
def f71(x):
    # fermi_dirac_half
    try:
        return -mpmath.polylog(1.5, -mpmath.exp(x))
    except:
        return None
def f72(x):
    # fermi_dirac_3half
    try:
        return -mpmath.polylog(2.5, -mpmath.exp(x))
    except:
        return None
def f73(x):
    # lngamma
    try:
        return mpmath.loggamma(x)
    except:
        return None
def f74(x):
    # gamma
    try:
        return mpmath.gamma(x)
    except:
        return None
def f76(x):
    # gammainv
    try:
        return mpmath.rgamma(x)
    except:
        return None
def f77(x):
    # lambert_W0
    return mpmath.lambertw(x)
def f78(x):
    # lambert_Wm1
    if x >= 0:
        return mpmath.lambertw(x)
    else:
        return mpmath.lambertw(x, -1)
def f79(x):
    # legendre_P1
    return mpmath.legendre(1,x)
def f80(x):
    # legendre_P2
    return mpmath.legendre(2,x)
def f81(x):
    # legendre_P3
    return mpmath.legendre(3,x)
def f82(x):
    # legendre_Q0
    return mpmath.legenq(0,0,x)
def f83(x):
    # legendre_Q1
    return mpmath.legenq(1,0,x)
def f84(x):
    # log
    return mpmath.log(x)
def f85(x):
    # log_abs
    return mpmath.log(abs(x))
def f86(x):
    # log_1plusx
    return mpmath.log1p(x)
def f87(x):
    # log_1plusx_mx
    x = mpmath.mpf(x)
    return mpmath.log1p(x)-x
def f88(x):
    # psi
    if abs(x) > 1e100:
        return None
    try:
        return mpmath.psi(0,x)
    except:
        return None
def f90(x):
    # psi_1
    if abs(x) > 1e100:
        return None
    try:
        return mpmath.psi(1,x)
    except:
        return None
def f94(x):
    # synchrotron_2
    x = mpmath.mpf(x)
    coff=mpmath.mpf(2)/mpmath.mpf(3)
    return x * mpmath.besselk(coff, x)
def f99(x):
    # sin
    return mpmath.sin(x)
def f100(x):
    # cos
    return mpmath.cos(x)
def f101(x):
    # sinc
    return mpmath.sincpi(x)
def f102(x):
    # lnsinh
    return mpmath.log(mpmath.sinh(x))
def f103(x):
    # lncosh
    return mpmath.log(mpmath.cosh(x))
def f104(x):
    # zeta
    return mpmath.zeta(x)
def f105(x):
    # zetam1
    return mpmath.zeta(x)-1
def f106(x):
    # eta
    return mpmath.altzeta(x)

funcDict = {
    0: {"direct_support": True , "support": True , "func": f0},
    1: {"direct_support": True , "support": True , "func": f1},
    2: {"direct_support": False, "support": True , "func": f2},
    3: {"direct_support": False, "support": True , "func": f3},
    4: {"direct_support": True , "support": True , "func": f4},
    5: {"direct_support": True , "support": True , "func": f5},
    6: {"direct_support": False, "support": True , "func": f6},
    7: {"direct_support": False, "support": True , "func": f7},
    8: {"direct_support": True , "support": True , "func": f8},
    9: {"direct_support": True , "support": True , "func": f9},
    10: {"direct_support": True , "support": True , "func": f10},
    11: {"direct_support": True , "support": True , "func": f11},
    12: {"direct_support": True , "support": True , "func": f12},
    13: {"direct_support": True , "support": True , "func": f13},
    14: {"direct_support": False, "support": True , "func": f14},
    15: {"direct_support": False, "support": True , "func": f15},
    16: {"direct_support": True , "support": True , "func": f16},
    17: {"direct_support": True , "support": True , "func": f17},
    18: {"direct_support": False, "support": True , "func": f18},
    19: {"direct_support": False, "support": True , "func": f19},
    20: {"direct_support": False, "support": True , "func": f20},
    21: {"direct_support": False, "support": True , "func": f21},
    22: {"direct_support": False, "support": True , "func": f22},
    23: {"direct_support": False, "support": True , "func": f23},
    24: {"direct_support": False, "support": True , "func": f24},
    25: {"direct_support": False, "support": True , "func": f25},
    26: {"direct_support": False, "support": True , "func": f26},
    27: {"direct_support": False, "support": True , "func": f27},
    28: {"direct_support": False, "support": True , "func": f28},
    29: {"direct_support": False, "support": True , "func": f29},
    30: {"direct_support": False, "support": True , "func": f30},
    31: {"direct_support": False, "support": True , "func": f31},
    32: {"direct_support": True , "support": True , "func": f32},
    33: {"direct_support": False, "support": False},
    34: {"direct_support": False, "support": False},
    35: {"direct_support": False, "support": False},
    36: {"direct_support": False, "support": False},
    37: {"direct_support": False, "support": False},
    38: {"direct_support": False, "support": False},
    39: {"direct_support": False, "support": False},
    40: {"direct_support": True , "support": True , "func": f40},
    41: {"direct_support": True , "support": True , "func": f41},
    42: {"direct_support": True , "support": True , "func": f42},
    43: {"direct_support": False, "support": False},
    44: {"direct_support": True , "support": True , "func": f44},
    45: {"direct_support": False, "support": True , "func": f45},
    46: {"direct_support": True , "support": True , "func": f46},
    47: {"direct_support": True , "support": True , "func": f47},
    48: {"direct_support": True , "support": True , "func": f48},
    49: {"direct_support": False, "support": True , "func": f49},
    50: {"direct_support": True , "support": True , "func": f50},
    51: {"direct_support": True , "support": True , "func": f51},
    52: {"direct_support": False, "support": True , "func": f52},
    53: {"direct_support": False, "support": True , "func": f53},
    54: {"direct_support": True , "support": True , "func": f54},
    55: {"direct_support": True , "support": True , "func": f55},
    56: {"direct_support": False, "support": True , "func": f56},
    57: {"direct_support": False, "support": True , "func": f57},
    58: {"direct_support": True , "support": True , "func": f58},
    59: {"direct_support": False, "support": True , "func": f59},
    60: {"direct_support": True , "support": True , "func": f60},
    61: {"direct_support": True , "support": True , "func": f61},
    62: {"direct_support": False, "support": False},
    63: {"direct_support": True , "support": True , "func": f63},
    64: {"direct_support": True , "support": True , "func": f64},
    65: {"direct_support": False, "support": False},
    66: {"direct_support": False, "support": True , "func": f66},
    67: {"direct_support": False, "support": True , "func": f67},
    68: {"direct_support": False, "support": True , "func": f68},
    69: {"direct_support": False, "support": True , "func": f69},
    70: {"direct_support": False, "support": True , "func": f70},
    71: {"direct_support": False, "support": True , "func": f71},
    72: {"direct_support": False, "support": True , "func": f72},
    73: {"direct_support": True , "support": True , "func": f73},
    74: {"direct_support": True , "support": True , "func": f74},
    75: {"direct_support": False, "support": False},
    76: {"direct_support": True , "support": True , "func": f76},
    77: {"direct_support": True , "support": True , "func": f77},
    78: {"direct_support": True , "support": True , "func": f78},
    79: {"direct_support": True , "support": True , "func": f79},
    80: {"direct_support": True , "support": True , "func": f80},
    81: {"direct_support": True , "support": True , "func": f81},
    82: {"direct_support": True , "support": True , "func": f82},
    83: {"direct_support": True , "support": True , "func": f83},
    84: {"direct_support": True , "support": True , "func": f84},
    85: {"direct_support": False, "support": True , "func": f85},
    86: {"direct_support": True , "support": True , "func": f86},
    87: {"direct_support": False, "support": True , "func": f87},
    88: {"direct_support": True , "support": True , "func": f88},
    89: {"direct_support": False, "support": False},
    90: {"direct_support": True , "support": True , "func": f90},
    91: {"direct_support": False, "support": False},
    92: {"direct_support": False, "support": False},
    93: {"direct_support": False, "support": False},
    94: {"direct_support": False, "support": True , "func": f94},
    95: {"direct_support": False, "support": False},
    96: {"direct_support": False, "support": False},
    97: {"direct_support": False, "support": False},
    98: {"direct_support": False, "support": False},
    99: {"direct_support": True , "support": True , "func": f99},
    100: {"direct_support": True , "support": True , "func": f100},
    101: {"direct_support": True , "support": True , "func": f101},
    102: {"direct_support": False, "support": True , "func": f102},
    103: {"direct_support": False, "support": True , "func": f103},
    104: {"direct_support": True , "support": True , "func": f104},
    105: {"direct_support": False, "support": True , "func": f105},
    106: {"direct_support": True , "support": True , "func": f106},
}

class GetOracle:
    def __init__(self):
        # Set mpmath precision
        mpmath.mp.prec=512
    def getOracleValue(self, funcIndex, inputX):
        funcIndex = int(funcIndex)
        # print("Func: ", funcIndex, "Input: ", inputX)
        if funcIndex not in funcDict:
            print("Function Index Error")
            return None
        if funcDict[funcIndex]['support'] == False:
            print("Function not supported by mpmath")
            return None
        inputX = mpmath.mpf(inputX)
        func = funcDict[funcIndex]['func']
        outY = func(inputX)
        if outY == None:
            return None
        outY = outY.real
        return outY
    def calcRelativeError(self, oracle, output):
        oracle = mpmath.mpf(oracle)
        output = mpmath.mpf(output)
        delta = abs(output-oracle)
        if delta == 0:
            return 0
        try:
            return abs(delta / oracle)
        except:
            return float("inf")

class OutputParser:
    def __init__(self):
        self.outputFile="tempOutput.out"
        self.writeToFile="Output.out"
        with io.open(self.outputFile) as f:
            self.rawData = f.readlines()
        self.data = {}
        self.oracleMod = GetOracle()
    def readAndCalculate(self):
        valid = True
        for line in self.rawData:
            # Determine whether valid
            if line.startswith('------------------'):
                valid = True
                continue
            if valid == False:
                continue

            # Read only for valid index.
            if line.startswith("Function Index"):
                curIndex = int(line.split(":")[1])
                if funcDict[curIndex]['support'] == False:
                    # Read Until next
                    valid = False
                    continue
                self.data[curIndex] = {}
                continue
            if line.startswith("Execution Time"):
                curTime = float(line.split(":")[1].split()[0])
                self.data[curIndex]['time'] = curTime
                continue
            if line.startswith("**************"):
                self.printInfo(curIndex)
                # Wait for input, system('pause')
                # input()
                continue
            if line.startswith("Format:"):
                self.data[curIndex]['input_list'] = []
            # Format: InstID, OpCode, MaxAtomCond, Input, Output, CountToEnd, ConditionToEnd
            if line.startswith("Data:"):
                inputInfo = {}
                terms = line.split(":")[1]
                terms = terms.split(',')
                inputInfo['inst_id'] = int(terms[0])
                inputInfo['op_code'] = int(terms[1])
                inputInfo['atom_cond'] = float(terms[2])
                # Input / Output
                inputX = float(terms[3])
                outputY = float(terms[4])
                if math.isfinite(inputX) == False or math.isfinite(outputY) == False:
                    continue
                inputInfo['input'] = inputX
                inputInfo['output'] = outputY
                # print(inputX, outputY)
                # Data for priorization
                countToEnd = int(terms[5])
                conditionToEnd = float(terms[6])
                inputInfo['count_to_end'] = countToEnd
                inputInfo['condition_to_end'] = conditionToEnd

                # Calculate Oracle
                oracleVal = self.oracleMod.getOracleValue(curIndex, inputX)
                if oracleVal == None:
                    print("On function:", curIndex)
                    print("Mpmath not support input: ", inputX)
                    continue

                relativeErr = self.oracleMod.calcRelativeError(oracleVal, outputY)
                inputInfo['oracle'] = oracleVal
                inputInfo['relative_err'] = relativeErr
                self.data[curIndex]['input_list'].append(inputInfo)
                continue
    def printInfo(self, index):
        print("------------------------")
        info = self.data[index]
        print("Function Index:", index)
        inputinfo = info['input_list']
        relList = sorted(inputinfo, key=lambda x: x['relative_err'], reverse=True)
        print("Max Relative Error:")
        for item in relList[:1]:
            print("  Input: ", format(float(item['input']), '.15e'))
            print("  Output:", format(float(item['output']), '.15e'))
            print("  Oracle:", format(float(item['oracle']), '.15e'))
            print("        Relative Error:", format(float(item['relative_err']), '.5e'))
        print("------------------------")

def main():
    op = OutputParser()
    op.readAndCalculate()


if __name__ == '__main__':
    main()

