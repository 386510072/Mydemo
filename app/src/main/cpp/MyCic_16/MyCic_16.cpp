//
// File: MyCic_16.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 07-Apr-2018 10:30:54
//

// Include Files
#include "rt_nonfinite.h"
#include "MyCic_16.h"

// Type Definitions
typedef struct {
  unsigned int f1[8];
} cell_wrap_3;

#ifndef struct_dsp_Delay_3
#define struct_dsp_Delay_3

struct dsp_Delay_3
{
  int S0_isInitialized;
  int W0_CIRC_BUF_IDX;
  long long W1_IC_BUFF[17];
  int W2_PrevNumChan;
  boolean_T W3_NeedsToInit;
  long long P0_IC;
};

#endif                                 //struct_dsp_Delay_3

typedef struct {
  int isInitialized;
  dsp_Delay_3 cDelay;
} dsp_private_FIRCombFilter;

#ifndef struct_dsp_Delay_4
#define struct_dsp_Delay_4

struct dsp_Delay_4
{
  int S0_isInitialized;
  int W0_CIRC_BUF_IDX;
  long long W1_IC_BUFF[17];
  int W2_PrevNumChan;
  boolean_T W3_NeedsToInit;
  long long P0_IC;
};

#endif                                 //struct_dsp_Delay_4

typedef struct {
  int isInitialized;
  dsp_Delay_4 cDelay;
} dsp_private_FIRCombFilter_1;

#ifndef struct_dsp_Delay_5
#define struct_dsp_Delay_5

struct dsp_Delay_5
{
  int S0_isInitialized;
  int W0_CIRC_BUF_IDX;
  long long W1_IC_BUFF[17];
  int W2_PrevNumChan;
  boolean_T W3_NeedsToInit;
  long long P0_IC;
};

#endif                                 //struct_dsp_Delay_5

typedef struct {
  int isInitialized;
  dsp_Delay_5 cDelay;
} dsp_private_FIRCombFilter_2;

#ifndef struct_dsp_private_Integrator_0
#define struct_dsp_private_Integrator_0

struct dsp_private_Integrator_0
{
  int S0_isInitialized;
  long long W0_states;
  long long O0_Y0[6000];
};

#endif                                 //struct_dsp_private_Integrator_0

#ifndef struct_dsp_private_Integrator_1
#define struct_dsp_private_Integrator_1

struct dsp_private_Integrator_1
{
  int S0_isInitialized;
  long long W0_states;
  long long O0_Y0[6000];
};

#endif                                 //struct_dsp_private_Integrator_1

#ifndef struct_dsp_private_Integrator_2
#define struct_dsp_private_Integrator_2

struct dsp_private_Integrator_2
{
  int S0_isInitialized;
  long long W0_states;
  long long O0_Y0[6000];
};

#endif                                 //struct_dsp_private_Integrator_2

typedef struct {
  int isInitialized;
  cell_wrap_3 inputVarSize[1];
  dsp_private_FIRCombFilter cCmbStage1;
  dsp_private_Integrator_0 cIntgStage1;
  dsp_private_FIRCombFilter_1 cCmbStage2;
  dsp_private_Integrator_1 cIntgStage2;
  dsp_private_FIRCombFilter_2 cCmbStage3;
  dsp_private_Integrator_2 cIntgStage3;
} dsp_CICDecimator;

// Function Declarations
static void CICDecimator_stepImpl(dsp_CICDecimator *obj, const int in[6000],
  long long out[375]);
static void FIRCombFilter_stepImpl(dsp_private_FIRCombFilter *obj, const long
  long in[375], long long out[375]);
static void InitializeConditions(dsp_private_Integrator_0 *obj);
static void SystemCore_step(dsp_CICDecimator *obj, const int varargin_1[6000],
  long long varargout_1[375]);
static void accumneg(const long long a[375], const long long b[375], long long
                     c[375]);
static void b_FIRCombFilter_stepImpl(dsp_private_FIRCombFilter_1 *obj, const
  long long in[375], long long out[375]);
static void b_InitializeConditions(dsp_private_Integrator_1 *obj);
static void b_SystemCore_step(dsp_private_FIRCombFilter *obj, const long long
  varargin_1[375], long long varargout_1[375]);
static void c_FIRCombFilter_stepImpl(dsp_private_FIRCombFilter_2 *obj, const
  long long in[375], long long out[375]);
static void c_InitializeConditions(dsp_private_Integrator_2 *obj);
static void c_SystemCore_step(dsp_private_FIRCombFilter_1 *obj, const long long
  varargin_1[375], long long varargout_1[375]);
static void d_InitializeConditions(dsp_Delay_3 *obj);
static void d_SystemCore_step(dsp_private_FIRCombFilter_2 *obj, const long long
  varargin_1[375], long long varargout_1[375]);
static void e_InitializeConditions(dsp_Delay_4 *obj);
static void f_InitializeConditions(dsp_Delay_5 *obj);

// Function Definitions

//
// Arguments    : dsp_CICDecimator *obj
//                const int in[6000]
//                long long out[375]
// Return Type  : void
//
static void CICDecimator_stepImpl(dsp_CICDecimator *obj, const int in[6000],
  long long out[375])
{
  int i;
  dsp_private_Integrator_0 *b_obj;
  int b_y1[6000];
  int j;
  long long i0;
  dsp_private_Integrator_1 *c_obj;
  long long y[6000];
  dsp_private_Integrator_2 *d_obj;
  long long b_y[375];
  for (i = 0; i < 6000; i++) {
    b_y1[i] = in[i];
  }

  b_obj = &obj->cIntgStage1;
  if (b_obj->S0_isInitialized != 1) {
    b_obj->S0_isInitialized = 1;

    // System object Initialization function: dsp.private.Integrator
    b_obj->W0_states = 0LL;
  }

  // System object Outputs function: dsp.private.Integrator
  i = 0;
  for (j = 0; j < 6000; j++) {
    b_obj->O0_Y0[i] = b_obj->W0_states;
    i0 = b_obj->W0_states + b_y1[i];
    if ((i0 & 72057594037927936LL) != 0LL) {
      b_obj->W0_states = i0 | -72057594037927936LL;
    } else {
      b_obj->W0_states = i0 & 72057594037927935LL;
    }

    i++;
  }

  for (i = 0; i < 6000; i++) {
    y[i] = b_obj->O0_Y0[i];
  }

  c_obj = &obj->cIntgStage2;
  if (c_obj->S0_isInitialized != 1) {
    c_obj->S0_isInitialized = 1;

    // System object Initialization function: dsp.private.Integrator
    c_obj->W0_states = 0LL;
  }

  // System object Outputs function: dsp.private.Integrator
  i = 0;
  for (j = 0; j < 6000; j++) {
    c_obj->O0_Y0[i] = c_obj->W0_states;
    i0 = c_obj->W0_states + y[i];
    if ((i0 & 72057594037927936LL) != 0LL) {
      c_obj->W0_states = i0 | -72057594037927936LL;
    } else {
      c_obj->W0_states = i0 & 72057594037927935LL;
    }

    i++;
  }

  for (i = 0; i < 6000; i++) {
    y[i] = c_obj->O0_Y0[i];
  }

  d_obj = &obj->cIntgStage3;
  if (d_obj->S0_isInitialized != 1) {
    d_obj->S0_isInitialized = 1;

    // System object Initialization function: dsp.private.Integrator
    d_obj->W0_states = 0LL;
  }

  // System object Outputs function: dsp.private.Integrator
  i = 0;
  for (j = 0; j < 6000; j++) {
    d_obj->O0_Y0[i] = d_obj->W0_states;
    i0 = d_obj->W0_states + y[i];
    if ((i0 & 72057594037927936LL) != 0LL) {
      d_obj->W0_states = i0 | -72057594037927936LL;
    } else {
      d_obj->W0_states = i0 & 72057594037927935LL;
    }

    i++;
  }

  for (i = 0; i < 6000; i++) {
    y[i] = d_obj->O0_Y0[i];
  }

  for (i = 0; i < 375; i++) {
    b_y[i] = y[i << 4];
  }

  b_SystemCore_step(&obj->cCmbStage1, b_y, out);
  memcpy(&b_y[0], &out[0], 375U * sizeof(long long));
  c_SystemCore_step(&obj->cCmbStage2, b_y, out);
  memcpy(&b_y[0], &out[0], 375U * sizeof(long long));
  d_SystemCore_step(&obj->cCmbStage3, b_y, out);
}

//
// Arguments    : dsp_private_FIRCombFilter *obj
//                const long long in[375]
//                long long out[375]
// Return Type  : void
//
static void FIRCombFilter_stepImpl(dsp_private_FIRCombFilter *obj, const long
  long in[375], long long out[375])
{
  dsp_Delay_3 *b_obj;
  int curCircBuff;
  int k;
  long long varargout_1[375];
  b_obj = &obj->cDelay;
  if (b_obj->S0_isInitialized != 1) {
    b_obj->S0_isInitialized = 1;
    d_InitializeConditions(b_obj);
  }

  // System object Outputs function: dsp.Delay
  curCircBuff = b_obj->W0_CIRC_BUF_IDX;
  for (k = 0; k < 17 - curCircBuff; k++) {
    varargout_1[k] = b_obj->W1_IC_BUFF[curCircBuff + k];
  }

  for (k = 0; k < curCircBuff; k++) {
    varargout_1[(k - curCircBuff) + 17] = b_obj->W1_IC_BUFF[k];
  }

  memcpy(&varargout_1[17], &in[0], 358U * sizeof(long long));

  // System object Update function: dsp.Delay
  for (k = 0; k < 17; k++) {
    b_obj->W1_IC_BUFF[k] = in[k + 358];
  }

  b_obj->W0_CIRC_BUF_IDX = 0;
  accumneg(in, varargout_1, out);
}

//
// Arguments    : dsp_private_Integrator_0 *obj
// Return Type  : void
//
static void InitializeConditions(dsp_private_Integrator_0 *obj)
{
  // System object Initialization function: dsp.private.Integrator
  obj->W0_states = 0LL;
}

//
// Arguments    : dsp_CICDecimator *obj
//                const int varargin_1[6000]
//                long long varargout_1[375]
// Return Type  : void
//
static void SystemCore_step(dsp_CICDecimator *obj, const int varargin_1[6000],
  long long varargout_1[375])
{
  dsp_CICDecimator *b_obj;
  int k;
  boolean_T exitg1;
  cell_wrap_3 varSizes[1];
  static const short inSize[8] = { 6000, 1, 1, 1, 1, 1, 1, 1 };

  static const short iv1[8] = { 6000, 1, 1, 1, 1, 1, 1, 1 };

  dsp_private_FIRCombFilter *c_obj;
  dsp_private_FIRCombFilter_1 *d_obj;
  dsp_private_FIRCombFilter_2 *e_obj;
  if (obj->isInitialized != 1) {
    b_obj = obj;
    b_obj->isInitialized = 1;
    for (k = 0; k < 8; k++) {
      varSizes[0].f1[k] = (unsigned int)inSize[k];
    }

    b_obj->inputVarSize[0] = varSizes[0];

    // System object Constructor function: dsp.private.Integrator
    b_obj->cIntgStage1.S0_isInitialized = 0;

    // System object Constructor function: dsp.private.Integrator
    b_obj->cIntgStage2.S0_isInitialized = 0;

    // System object Constructor function: dsp.private.Integrator
    b_obj->cIntgStage3.S0_isInitialized = 0;
    b_obj->cCmbStage1.isInitialized = 0;
    b_obj->cCmbStage2.isInitialized = 0;
    b_obj->cCmbStage3.isInitialized = 0;
    if (b_obj->cIntgStage1.S0_isInitialized == 1) {
      InitializeConditions(&b_obj->cIntgStage1);
    }

    c_obj = &b_obj->cCmbStage1;
    if ((b_obj->cCmbStage1.isInitialized == 1) &&
        (c_obj->cDelay.S0_isInitialized == 1)) {
      d_InitializeConditions(&c_obj->cDelay);
    }

    if (b_obj->cIntgStage2.S0_isInitialized == 1) {
      b_InitializeConditions(&b_obj->cIntgStage2);
    }

    d_obj = &b_obj->cCmbStage2;
    if ((b_obj->cCmbStage2.isInitialized == 1) &&
        (d_obj->cDelay.S0_isInitialized == 1)) {
      e_InitializeConditions(&d_obj->cDelay);
    }

    if (b_obj->cIntgStage3.S0_isInitialized == 1) {
      c_InitializeConditions(&b_obj->cIntgStage3);
    }

    e_obj = &b_obj->cCmbStage3;
    if ((b_obj->cCmbStage3.isInitialized == 1) &&
        (e_obj->cDelay.S0_isInitialized == 1)) {
      f_InitializeConditions(&e_obj->cDelay);
    }
  }

  b_obj = obj;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 8)) {
    if (b_obj->inputVarSize[0].f1[k] != (unsigned int)iv1[k]) {
      for (k = 0; k < 8; k++) {
        b_obj->inputVarSize[0].f1[k] = (unsigned int)inSize[k];
      }

      exitg1 = true;
    } else {
      k++;
    }
  }

  CICDecimator_stepImpl(obj, varargin_1, varargout_1);
}

//
// Arguments    : const long long a[375]
//                const long long b[375]
//                long long c[375]
// Return Type  : void
//
static void accumneg(const long long a[375], const long long b[375], long long
                     c[375])
{
  int i;
  long long i1;
  for (i = 0; i < 375; i++) {
    i1 = a[i] - b[i];
    if ((i1 & 72057594037927936LL) != 0LL) {
      c[i] = i1 | -72057594037927936LL;
    } else {
      c[i] = i1 & 72057594037927935LL;
    }
  }
}

//
// Arguments    : dsp_private_FIRCombFilter_1 *obj
//                const long long in[375]
//                long long out[375]
// Return Type  : void
//
static void b_FIRCombFilter_stepImpl(dsp_private_FIRCombFilter_1 *obj, const
  long long in[375], long long out[375])
{
  dsp_Delay_4 *b_obj;
  int curCircBuff;
  int k;
  long long varargout_1[375];
  b_obj = &obj->cDelay;
  if (b_obj->S0_isInitialized != 1) {
    b_obj->S0_isInitialized = 1;
    e_InitializeConditions(b_obj);
  }

  // System object Outputs function: dsp.Delay
  curCircBuff = b_obj->W0_CIRC_BUF_IDX;
  for (k = 0; k < 17 - curCircBuff; k++) {
    varargout_1[k] = b_obj->W1_IC_BUFF[curCircBuff + k];
  }

  for (k = 0; k < curCircBuff; k++) {
    varargout_1[(k - curCircBuff) + 17] = b_obj->W1_IC_BUFF[k];
  }

  memcpy(&varargout_1[17], &in[0], 358U * sizeof(long long));

  // System object Update function: dsp.Delay
  for (k = 0; k < 17; k++) {
    b_obj->W1_IC_BUFF[k] = in[k + 358];
  }

  b_obj->W0_CIRC_BUF_IDX = 0;
  accumneg(in, varargout_1, out);
}

//
// Arguments    : dsp_private_Integrator_1 *obj
// Return Type  : void
//
static void b_InitializeConditions(dsp_private_Integrator_1 *obj)
{
  // System object Initialization function: dsp.private.Integrator
  obj->W0_states = 0LL;
}

//
// Arguments    : dsp_private_FIRCombFilter *obj
//                const long long varargin_1[375]
//                long long varargout_1[375]
// Return Type  : void
//
static void b_SystemCore_step(dsp_private_FIRCombFilter *obj, const long long
  varargin_1[375], long long varargout_1[375])
{
  dsp_private_FIRCombFilter *b_obj;
  if (obj->isInitialized != 1) {
    b_obj = obj;
    b_obj->isInitialized = 1;

    // System object Constructor function: dsp.Delay
    b_obj->cDelay.S0_isInitialized = 0;
    b_obj->cDelay.P0_IC = 0LL;
    if (b_obj->cDelay.S0_isInitialized == 1) {
      d_InitializeConditions(&b_obj->cDelay);
    }
  }

  FIRCombFilter_stepImpl(obj, varargin_1, varargout_1);
}

//
// Arguments    : dsp_private_FIRCombFilter_2 *obj
//                const long long in[375]
//                long long out[375]
// Return Type  : void
//
static void c_FIRCombFilter_stepImpl(dsp_private_FIRCombFilter_2 *obj, const
  long long in[375], long long out[375])
{
  dsp_Delay_5 *b_obj;
  int curCircBuff;
  int k;
  long long varargout_1[375];
  b_obj = &obj->cDelay;
  if (b_obj->S0_isInitialized != 1) {
    b_obj->S0_isInitialized = 1;
    f_InitializeConditions(b_obj);
  }

  // System object Outputs function: dsp.Delay
  curCircBuff = b_obj->W0_CIRC_BUF_IDX;
  for (k = 0; k < 17 - curCircBuff; k++) {
    varargout_1[k] = b_obj->W1_IC_BUFF[curCircBuff + k];
  }

  for (k = 0; k < curCircBuff; k++) {
    varargout_1[(k - curCircBuff) + 17] = b_obj->W1_IC_BUFF[k];
  }

  memcpy(&varargout_1[17], &in[0], 358U * sizeof(long long));

  // System object Update function: dsp.Delay
  for (k = 0; k < 17; k++) {
    b_obj->W1_IC_BUFF[k] = in[k + 358];
  }

  b_obj->W0_CIRC_BUF_IDX = 0;
  accumneg(in, varargout_1, out);
}

//
// Arguments    : dsp_private_Integrator_2 *obj
// Return Type  : void
//
static void c_InitializeConditions(dsp_private_Integrator_2 *obj)
{
  // System object Initialization function: dsp.private.Integrator
  obj->W0_states = 0LL;
}

//
// Arguments    : dsp_private_FIRCombFilter_1 *obj
//                const long long varargin_1[375]
//                long long varargout_1[375]
// Return Type  : void
//
static void c_SystemCore_step(dsp_private_FIRCombFilter_1 *obj, const long long
  varargin_1[375], long long varargout_1[375])
{
  dsp_private_FIRCombFilter_1 *b_obj;
  if (obj->isInitialized != 1) {
    b_obj = obj;
    b_obj->isInitialized = 1;

    // System object Constructor function: dsp.Delay
    b_obj->cDelay.S0_isInitialized = 0;
    b_obj->cDelay.P0_IC = 0LL;
    if (b_obj->cDelay.S0_isInitialized == 1) {
      e_InitializeConditions(&b_obj->cDelay);
    }
  }

  b_FIRCombFilter_stepImpl(obj, varargin_1, varargout_1);
}

//
// Arguments    : dsp_Delay_3 *obj
// Return Type  : void
//
static void d_InitializeConditions(dsp_Delay_3 *obj)
{
  int j;
  int delayIdx;

  // System object Initialization function: dsp.Delay
  obj->W0_CIRC_BUF_IDX = 0;
  j = 0;
  for (delayIdx = 0; delayIdx < 17; delayIdx++) {
    obj->W1_IC_BUFF[j] = obj->P0_IC;
    j++;
  }
}

//
// Arguments    : dsp_private_FIRCombFilter_2 *obj
//                const long long varargin_1[375]
//                long long varargout_1[375]
// Return Type  : void
//
static void d_SystemCore_step(dsp_private_FIRCombFilter_2 *obj, const long long
  varargin_1[375], long long varargout_1[375])
{
  dsp_private_FIRCombFilter_2 *b_obj;
  if (obj->isInitialized != 1) {
    b_obj = obj;
    b_obj->isInitialized = 1;

    // System object Constructor function: dsp.Delay
    b_obj->cDelay.S0_isInitialized = 0;
    b_obj->cDelay.P0_IC = 0LL;
    if (b_obj->cDelay.S0_isInitialized == 1) {
      f_InitializeConditions(&b_obj->cDelay);
    }
  }

  c_FIRCombFilter_stepImpl(obj, varargin_1, varargout_1);
}

//
// Arguments    : dsp_Delay_4 *obj
// Return Type  : void
//
static void e_InitializeConditions(dsp_Delay_4 *obj)
{
  int j;
  int delayIdx;

  // System object Initialization function: dsp.Delay
  obj->W0_CIRC_BUF_IDX = 0;
  j = 0;
  for (delayIdx = 0; delayIdx < 17; delayIdx++) {
    obj->W1_IC_BUFF[j] = obj->P0_IC;
    j++;
  }
}

//
// Arguments    : dsp_Delay_5 *obj
// Return Type  : void
//
static void f_InitializeConditions(dsp_Delay_5 *obj)
{
  int j;
  int delayIdx;

  // System object Initialization function: dsp.Delay
  obj->W0_CIRC_BUF_IDX = 0;
  j = 0;
  for (delayIdx = 0; delayIdx < 17; delayIdx++) {
    obj->W1_IC_BUFF[j] = obj->P0_IC;
    j++;
  }
}

//
// Arguments    : const int I[6000]
//                double II[375]
// Return Type  : void
//
void MyCic_16(const int I[6000], double II[375])
{
  static dsp_CICDecimator hd;
  long long iv0[375];
  int i;
  dsp_private_Integrator_0 *obj;
  dsp_private_Integrator_1 *b_obj;
  dsp_private_Integrator_2 *c_obj;
  dsp_Delay_3 *d_obj;
  dsp_Delay_4 *e_obj;
  dsp_Delay_5 *f_obj;
  hd.isInitialized = 0;
  SystemCore_step(&hd, I, iv0);
  for (i = 0; i < 375; i++) {
    II[i] = (double)iv0[i];
  }

  obj = &hd.cIntgStage1;

  // System object Destructor function: dsp.private.Integrator
  if (obj->S0_isInitialized == 1) {
    obj->S0_isInitialized = 2;
  }

  b_obj = &hd.cIntgStage2;

  // System object Destructor function: dsp.private.Integrator
  if (b_obj->S0_isInitialized == 1) {
    b_obj->S0_isInitialized = 2;
  }

  c_obj = &hd.cIntgStage3;

  // System object Destructor function: dsp.private.Integrator
  if (c_obj->S0_isInitialized == 1) {
    c_obj->S0_isInitialized = 2;
  }

  d_obj = &hd.cCmbStage1.cDelay;

  // System object Destructor function: dsp.Delay
  if (d_obj->S0_isInitialized == 1) {
    d_obj->S0_isInitialized = 2;
  }

  e_obj = &hd.cCmbStage2.cDelay;

  // System object Destructor function: dsp.Delay
  if (e_obj->S0_isInitialized == 1) {
    e_obj->S0_isInitialized = 2;
  }

  f_obj = &hd.cCmbStage3.cDelay;

  // System object Destructor function: dsp.Delay
  if (f_obj->S0_isInitialized == 1) {
    f_obj->S0_isInitialized = 2;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void MyCic_16_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void MyCic_16_terminate()
{
  // (no terminate code required)
}

//
// File trailer for MyCic_16.cpp
//
// [EOF]
//
