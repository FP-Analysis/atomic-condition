# Detecting Floating-Point Errors via Atomic Conditions

## Setup
The `docker` folder contains a Dockerfile that can be used to build our implementation.
```
docker build -t atomic .
docker run -it atomic /bin/bash
```
It may takes a few minutes for installing the necessary packages and compiling the whole GSL Library.

## Usage
After entering the interactive container, the working directory is at `/atom`.

### Play with Small examples
Run on the small example `foo`, defined in `src/targetExample.c`:
```
make
bin/gslSolver.out example
```

If you want to play with your own function, just modify the `foo` in `src/targetExample.c`, then
```
make
bin/gslSolver.out example
```

To run on more functions, define the functions in `src/targetExample.c`,
also changes correspondingly in `src/target.h` and `simpleFuncList` in `src/fpInterface.h`, then
```
make
bin/gslSolver.out example
```

### Run on GSL Functions
```
make
bin/gslSolver.out gsl <function_index>
```

#### Compute Relative Error (Only support GSL functions for now)
Using the oracle from `mpmath` to compute the relative error:
```
make
bin/gslSolver.out gsl <function_index> && python3 script/oracleMpmath.py
```

## GSL Function List and mpmath Support
| GSL Function Name           | Index | mpmath  support? |
|-----------------------------|-------|------------------|
| gsl_sf_airy_Ai              | 0     |:heavy_check_mark:|
| gsl_sf_airy_Bi              | 1     |:heavy_check_mark:|
| gsl_sf_airy_Ai_scaled       | 2     |:heavy_check_mark:|
| gsl_sf_airy_Bi_scaled       | 3     |:heavy_check_mark:|
| gsl_sf_airy_Ai_deriv        | 4     |:heavy_check_mark:|
| gsl_sf_airy_Bi_deriv        | 5     |:heavy_check_mark:|
| gsl_sf_airy_Ai_deriv_scaled | 6     |:heavy_check_mark:|
| gsl_sf_airy_Bi_deriv_scaled | 7     |:heavy_check_mark:|
| gsl_sf_bessel_J0            | 8     |:heavy_check_mark:|
| gsl_sf_bessel_J1            | 9     |:heavy_check_mark:|
| gsl_sf_bessel_Y0            | 10    |:heavy_check_mark:|
| gsl_sf_bessel_Y1            | 11    |:heavy_check_mark:|
| gsl_sf_bessel_I0            | 12    |:heavy_check_mark:|
| gsl_sf_bessel_I1            | 13    |:heavy_check_mark:|
| gsl_sf_bessel_I0_scaled     | 14    |:heavy_check_mark:|
| gsl_sf_bessel_I1_scaled     | 15    |:heavy_check_mark:|
| gsl_sf_bessel_K0            | 16    |:heavy_check_mark:|
| gsl_sf_bessel_K1            | 17    |:heavy_check_mark:|
| gsl_sf_bessel_K0_scaled     | 18    |:heavy_check_mark:|
| gsl_sf_bessel_K1_scaled     | 19    |:heavy_check_mark:|
| gsl_sf_bessel_j0            | 20    |:heavy_check_mark:|
| gsl_sf_bessel_j1            | 21    |:heavy_check_mark:|
| gsl_sf_bessel_j2            | 22    |:heavy_check_mark:|
| gsl_sf_bessel_y0            | 23    |:heavy_check_mark:|
| gsl_sf_bessel_y1            | 24    |:heavy_check_mark:|
| gsl_sf_bessel_y2            | 25    |:heavy_check_mark:|
| gsl_sf_bessel_i0_scaled     | 26    |:heavy_check_mark:|
| gsl_sf_bessel_i1_scaled     | 27    |:heavy_check_mark:|
| gsl_sf_bessel_i2_scaled     | 28    |:heavy_check_mark:|
| gsl_sf_bessel_k0_scaled     | 29    |:heavy_check_mark:|
| gsl_sf_bessel_k1_scaled     | 30    |:heavy_check_mark:|
| gsl_sf_bessel_k2_scaled     | 31    |:heavy_check_mark:|
| gsl_sf_clausen              | 32    |:heavy_check_mark:|
| gsl_sf_dawson               | 33    |                  |
| gsl_sf_debye_1              | 34    |                  |
| gsl_sf_debye_2              | 35    |                  |
| gsl_sf_debye_3              | 36    |                  |
| gsl_sf_debye_4              | 37    |                  |
| gsl_sf_debye_5              | 38    |                  |
| gsl_sf_debye_6              | 39    |                  |
| gsl_sf_dilog                | 40    |:heavy_check_mark:|
| gsl_sf_ellint_Kcomp         | 41    |:heavy_check_mark:|
| gsl_sf_ellint_Ecomp         | 42    |:heavy_check_mark:|
| gsl_sf_ellint_Dcomp         | 43    |                  |
| gsl_sf_erfc                 | 44    |:heavy_check_mark:|
| gsl_sf_log_erfc             | 45    |:heavy_check_mark:|
| gsl_sf_erf                  | 46    |:heavy_check_mark:|
| gsl_sf_erf_Z                | 47    |:heavy_check_mark:|
| gsl_sf_erf_Q                | 48    |:heavy_check_mark:|
| gsl_sf_hazard               | 49    |:heavy_check_mark:|
| gsl_sf_exp                  | 50    |:heavy_check_mark:|
| gsl_sf_expm1                | 51    |:heavy_check_mark:|
| gsl_sf_exprel               | 52    |:heavy_check_mark:|
| gsl_sf_exprel_2             | 53    |:heavy_check_mark:|
| gsl_sf_expint_E1            | 54    |:heavy_check_mark:|
| gsl_sf_expint_E2            | 55    |:heavy_check_mark:|
| gsl_sf_expint_E1_scaled     | 56    |:heavy_check_mark:|
| gsl_sf_expint_E2_scaled     | 57    |:heavy_check_mark:|
| gsl_sf_expint_Ei            | 58    |:heavy_check_mark:|
| gsl_sf_expint_Ei_scaled     | 59    |:heavy_check_mark:|
| gsl_sf_Shi                  | 60    |:heavy_check_mark:|
| gsl_sf_Chi                  | 61    |:heavy_check_mark:|
| gsl_sf_expint_3             | 62    |                  |
| gsl_sf_Si                   | 63    |:heavy_check_mark:|
| gsl_sf_Ci                   | 64    |:heavy_check_mark:|
| gsl_sf_atanint              | 65    |                  |
| gsl_sf_fermi_dirac_m1       | 66    |:heavy_check_mark:|
| gsl_sf_fermi_dirac_0        | 67    |:heavy_check_mark:|
| gsl_sf_fermi_dirac_1        | 68    |:heavy_check_mark:|
| gsl_sf_fermi_dirac_2        | 69    |:heavy_check_mark:|
| gsl_sf_fermi_dirac_mhalf    | 70    |:heavy_check_mark:|
| gsl_sf_fermi_dirac_half     | 71    |:heavy_check_mark:|
| gsl_sf_fermi_dirac_3half    | 72    |:heavy_check_mark:|
| gsl_sf_lngamma              | 73    |:heavy_check_mark:|
| gsl_sf_gamma                | 74    |:heavy_check_mark:|
| gsl_sf_gammastar            | 75    |                  |
| gsl_sf_gammainv             | 76    |:heavy_check_mark:|
| gsl_sf_lambert_W0           | 77    |:heavy_check_mark:|
| gsl_sf_lambert_Wm1          | 78    |:heavy_check_mark:|
| gsl_sf_legendre_P1          | 79    |:heavy_check_mark:|
| gsl_sf_legendre_P2          | 80    |:heavy_check_mark:|
| gsl_sf_legendre_P3          | 81    |:heavy_check_mark:|
| gsl_sf_legendre_Q0          | 82    |:heavy_check_mark:|
| gsl_sf_legendre_Q1          | 83    |:heavy_check_mark:|
| gsl_sf_log                  | 84    |:heavy_check_mark:|
| gsl_sf_log_abs              | 85    |:heavy_check_mark:|
| gsl_sf_log_1plusx           | 86    |:heavy_check_mark:|
| gsl_sf_log_1plusx_mx        | 87    |:heavy_check_mark:|
| gsl_sf_psi                  | 88    |:heavy_check_mark:|
| gsl_sf_psi_1piy             | 89    |                  |
| gsl_sf_psi_1                | 90    |:heavy_check_mark:|
| gsl_sf_sin_pi               | 91    |                  |
| gsl_sf_cos_pi               | 92    |                  |
| gsl_sf_synchrotron_1        | 93    |                  |
| gsl_sf_synchrotron_2        | 94    |:heavy_check_mark:|
| gsl_sf_transport_2          | 95    |                  |
| gsl_sf_transport_3          | 96    |                  |
| gsl_sf_transport_4          | 97    |                  |
| gsl_sf_transport_5          | 98    |                  |
| gsl_sf_sin                  | 99    |:heavy_check_mark:|
| gsl_sf_cos                  | 100   |:heavy_check_mark:|
| gsl_sf_sinc                 | 101   |:heavy_check_mark:|
| gsl_sf_lnsinh               | 102   |:heavy_check_mark:|
| gsl_sf_lncosh               | 103   |:heavy_check_mark:|
| gsl_sf_zeta                 | 104   |:heavy_check_mark:|
| gsl_sf_zetam1               | 105   |:heavy_check_mark:|
| gsl_sf_eta                  | 106   |:heavy_check_mark:|

