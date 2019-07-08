#include <math.h>

double foo(double x) {
    // This function calculate LegendreP3:
    // See details at: http://mathworld.wolfram.com/LegendrePolynomial.html

    // It triggers significant error near x->0.7745967,
    // which is about the sqrt(0.6);
    double val = 0.5 * x * (5.0 * x * x - 3.0);
    return val;
}

