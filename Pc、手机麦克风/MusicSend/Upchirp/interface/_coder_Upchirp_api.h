/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_Upchirp_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 24-Apr-2018 22:58:27
 */

#ifndef _CODER_UPCHIRP_API_H
#define _CODER_UPCHIRP_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Upchirp_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void Upchirp(real_T fL, real_T fH, real_T t[882], real_T T2, real_T
                    Up_chirp[882]);
extern void Upchirp_api(const mxArray *prhs[4], const mxArray *plhs[1]);
extern void Upchirp_atexit(void);
extern void Upchirp_initialize(void);
extern void Upchirp_terminate(void);
extern void Upchirp_xil_terminate(void);

#endif

/*
 * File trailer for _coder_Upchirp_api.h
 *
 * [EOF]
 */
