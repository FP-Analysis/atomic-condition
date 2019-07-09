#ifndef FPINTERFACE_H
#define FPINTERFACE_H

#include "communicator.h"
#include <functional>
#include <gsl/gsl_sf.h>
#include "target.h"

const std::vector<std::function<double(double)>> simpleFuncList = {
    foo,
};

const std::vector<std::function<int(double, gsl_sf_result*)>> GSLFuncList = {
    // gsl_sf_airy.h
    std::bind(gsl_sf_airy_Ai_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    std::bind(gsl_sf_airy_Bi_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    std::bind(gsl_sf_airy_Ai_scaled_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    std::bind(gsl_sf_airy_Bi_scaled_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    std::bind(gsl_sf_airy_Ai_deriv_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    std::bind(gsl_sf_airy_Bi_deriv_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    std::bind(gsl_sf_airy_Ai_deriv_scaled_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    std::bind(gsl_sf_airy_Bi_deriv_scaled_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    // gsl_sf_bessel.h
    gsl_sf_bessel_J0_e,
    gsl_sf_bessel_J1_e,
    gsl_sf_bessel_Y0_e,
    gsl_sf_bessel_Y1_e,
    gsl_sf_bessel_I0_e,
    gsl_sf_bessel_I1_e,
    gsl_sf_bessel_I0_scaled_e,
    gsl_sf_bessel_I1_scaled_e,
    gsl_sf_bessel_K0_e,
    gsl_sf_bessel_K1_e,
    gsl_sf_bessel_K0_scaled_e,
    gsl_sf_bessel_K1_scaled_e,
    gsl_sf_bessel_j0_e,
    gsl_sf_bessel_j1_e,
    gsl_sf_bessel_j2_e,
    gsl_sf_bessel_y0_e,
    gsl_sf_bessel_y1_e,
    gsl_sf_bessel_y2_e,
    gsl_sf_bessel_i0_scaled_e,
    gsl_sf_bessel_i1_scaled_e,
    gsl_sf_bessel_i2_scaled_e,
    gsl_sf_bessel_k0_scaled_e,
    gsl_sf_bessel_k1_scaled_e,
    gsl_sf_bessel_k2_scaled_e,
    // gsl_sf_clausen.h
    gsl_sf_clausen_e,
    // gsl_sf_coulomb.h
    // gsl_sf_coupling.h
    // gsl_sf_dawson.h
    gsl_sf_dawson_e,
    // gsl_sf_debye.h
    gsl_sf_debye_1_e,
    gsl_sf_debye_2_e,
    gsl_sf_debye_3_e,
    gsl_sf_debye_4_e,
    gsl_sf_debye_5_e,
    gsl_sf_debye_6_e,
    // gsl_sf_dilog.h
    gsl_sf_dilog_e,
    // gsl_sf_elementary.h
    // gsl_sf_ellint.h
    std::bind(gsl_sf_ellint_Kcomp_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    std::bind(gsl_sf_ellint_Ecomp_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    std::bind(gsl_sf_ellint_Dcomp_e, std::placeholders::_1, GSL_PREC_DOUBLE, std::placeholders::_2),
    // gsl_sf_elljac.h
    // gsl_sf_erf.h
    gsl_sf_erfc_e,
    gsl_sf_log_erfc_e,
    gsl_sf_erf_e,
    gsl_sf_erf_Z_e,
    gsl_sf_erf_Q_e,
    gsl_sf_hazard_e,
    // gsl_sf_exp.h
    gsl_sf_exp_e,
    gsl_sf_expm1_e,
    gsl_sf_exprel_e,
    gsl_sf_exprel_2_e,
    // gsl_sf_expint.h
    gsl_sf_expint_E1_e,
    gsl_sf_expint_E2_e,
    gsl_sf_expint_E1_scaled_e,
    gsl_sf_expint_E2_scaled_e,
    gsl_sf_expint_Ei_e,
    gsl_sf_expint_Ei_scaled_e,
    gsl_sf_Shi_e,
    gsl_sf_Chi_e,
    gsl_sf_expint_3_e,
    gsl_sf_Si_e,
    gsl_sf_Ci_e,
    gsl_sf_atanint_e,
    // gsl_sf_fermi_dirac.h
    gsl_sf_fermi_dirac_m1_e,
    gsl_sf_fermi_dirac_0_e,
    gsl_sf_fermi_dirac_1_e,
    gsl_sf_fermi_dirac_2_e,
    gsl_sf_fermi_dirac_mhalf_e,
    gsl_sf_fermi_dirac_half_e,
    gsl_sf_fermi_dirac_3half_e,
    // gsl_sf_gamma.h
    gsl_sf_lngamma_e,
    gsl_sf_gamma_e,
    gsl_sf_gammastar_e,
    gsl_sf_gammainv_e,
    // gsl_sf_gegenbauer.h
    // gsl_sf_hermite.h
    // gsl_sf_hyperg.h
    // gsl_sf_laguerre.h
    // gsl_sf_lambert.h
    gsl_sf_lambert_W0_e,
    gsl_sf_lambert_Wm1_e,
    // gsl_sf_legendre.h
    gsl_sf_legendre_P1_e,
    gsl_sf_legendre_P2_e,
    gsl_sf_legendre_P3_e,
    gsl_sf_legendre_Q0_e,
    gsl_sf_legendre_Q1_e,
    // gsl_sf_log.h
    gsl_sf_log_e,
    gsl_sf_log_abs_e,
    gsl_sf_log_1plusx_e,
    gsl_sf_log_1plusx_mx_e,
    // gsl_sf_mathieu.h
    // gsl_sf_pow_int.h
    // gsl_sf_psi.h
    gsl_sf_psi_e,
    gsl_sf_psi_1piy_e,
    gsl_sf_psi_1_e,
    // gsl_sf_sincos_pi.h
    gsl_sf_sin_pi_e,
    gsl_sf_cos_pi_e,
    // gsl_sf_synchrotron.h
    gsl_sf_synchrotron_1_e,
    gsl_sf_synchrotron_2_e,
    // gsl_sf_transport.h
    gsl_sf_transport_2_e,
    gsl_sf_transport_3_e,
    gsl_sf_transport_4_e,
    gsl_sf_transport_5_e,
    // gsl_sf_trig.h
    gsl_sf_sin_e,
    gsl_sf_cos_e,
    gsl_sf_sinc_e,
    gsl_sf_lnsinh_e,
    gsl_sf_lncosh_e,
    // gsl_sf_zeta.h
    gsl_sf_zeta_e,
    gsl_sf_zetam1_e,
    gsl_sf_eta_e
};

class FloatingPointFunction {
public:
    virtual void call(double x) = 0;
    virtual double getResult() = 0;
    virtual double callAndGetResult(double x) = 0;
    virtual bool isSuccess() = 0;
    std::vector<InstInfo> getInstInfoList() {
        return comm.getInstInfoList();
    }
    FloatingPointFunction() : comm( Communicator::getInstance() ) {
        comm.initComm();
    }
protected:
    double in, out;
    int status;
    Communicator &comm;
};


class GSLFunction : public FloatingPointFunction {
public:
    GSLFunction(int index) {
        gsl_set_error_handler_off();

        if (index < 0 || index >= GSLFuncList.size()) {
            std::cout << "Invalid index in [GSLFunction]: " << index << '\n';
            GSLFuncRef = GSLFuncList[0];
            return;
        }
        GSLFuncRef = GSLFuncList[index];
        return;
    }

    void call(double x) {
        comm.clear();
        in = x;
        status = GSLFuncRef(in, &gslres);
        out = gslres.val;
    }

    double callAndGetResult(double x) {
        call(x);
        return out;
    }

    double getResult() { return out; }
    bool isSuccess() { return (status == GSL_SUCCESS); }

private:
    std::function<int(double, gsl_sf_result*)> GSLFuncRef;
    gsl_sf_result gslres;
};

class SimpleFunction : public FloatingPointFunction {
public:
    SimpleFunction(int index) {
        if (index < 0 || index >= simpleFuncList.size()) {
            std::cout << "Invalid index in [SimpleFunction]: " << index << '\n';
            funcRef = simpleFuncList[0];
            return;
        }
        funcRef = simpleFuncList[index];
    }
    void call(double x) {
        comm.clear();
        in = x;
        out = funcRef(x);
        if (std::isnan(out)) {
            status = -1;
        }
        else {
            status = 0;
        }
    }

    double callAndGetResult(double x) {
        call(x);
        return out;
    }

    double getResult() { return out; }
    bool isSuccess() { return (status == 0); }

private:
    std::function<double(double)> funcRef;
};

#endif