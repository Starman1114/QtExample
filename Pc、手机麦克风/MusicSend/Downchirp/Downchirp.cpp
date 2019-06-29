//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Downchirp.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 24-Apr-2018 23:46:22
//

// Include Files
#include "rt_nonfinite.h"
#include "Downchirp.h"

// Function Definitions

//
// Arguments    : double fL
//                double fH
//                const double t[882]
//                double T2
//                double Down_chirp[882]
// Return Type  : void
//
void Downchirp(double fL, double fH, const double *t, double T2,double* Down_chirp)
{
  double b;
  double B;
  int k;
  b = fH - fL;
  B = 2.0 * T2;
  for (k = 0; k < 882; k++) {
    Down_chirp[k] = sin(6.2831853071795862 * (fH * t[k] + t[k] * t[k] * b /B));
  }
}

//
// File trailer for Downchirp.cpp
//
// [EOF]
//
