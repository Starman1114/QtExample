//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Upchirp.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 24-Apr-2018 22:58:27
//

// Include Files
#include "rt_nonfinite.h"
#include "Upchirp.h"

// Function Definitions

//
// UNTITLED3 此处显示有关此函数的摘要
//    此处显示详细说明
//  Up_chirp=chirp(t,fL,T,fH);
// Arguments    : double fL
//                double fH
//                const double t[882]
//                double T2
//                double Up_chirp[882]
// Return Type  : void
//
void Upchirp(double fL, double fH, const double *t, double T2,double* Up_chirp)
{
  double b;
  double B;
  int k;
  b = fH - fL;
  B = 2.0 * T2;
  for (k = 0; k < 882; k++) {
    Up_chirp[k] = sin(6.2831853071795862 * (fL * t[k] + t[k] * t[k] * b / B));
  }
}

//
// File trailer for Upchirp.cpp
//
// [EOF]
//
