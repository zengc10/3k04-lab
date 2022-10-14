/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AOO.c
 *
 * Code generated for Simulink model 'AOO'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Oct 13 18:07:33 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "AOO.h"
#include "rtwtypes.h"
#include <math.h>
#include "AOO_types.h"

/* Named constants for Chart: '<Root>/AOO' */
#define AOO_IN_Charging                ((uint8_T)1U)
#define AOO_IN_Discharging             ((uint8_T)2U)

/* Block signals (default storage) */
B_AOO_T AOO_B;

/* Block states (default storage) */
DW_AOO_T AOO_DW;

/* Real-time model */
static RT_MODEL_AOO_T AOO_M_;
RT_MODEL_AOO_T *const AOO_M = &AOO_M_;

/* Model step function */
void AOO_step(void)
{
  /* Chart: '<Root>/AOO' incorporates:
   *  Constant: '<Root>/BPM'
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/PWM'
   *  Constant: '<Root>/msec'
   *  Product: '<Root>/Divide'
   */
  if (AOO_DW.temporalCounter_i1 < MAX_uint32_T) {
    AOO_DW.temporalCounter_i1++;
  }

  if (AOO_DW.is_active_c3_AOO == 0U) {
    AOO_DW.is_active_c3_AOO = 1U;
    AOO_DW.is_c3_AOO = AOO_IN_Charging;
    AOO_DW.temporalCounter_i1 = 0U;
  } else if (AOO_DW.is_c3_AOO == AOO_IN_Charging) {
    if (AOO_DW.temporalCounter_i1 >= (uint32_T)ceil(AOO_P.msec_Value /
         AOO_P.BPM_Value - AOO_P.Constant_Value)) {
      AOO_DW.is_c3_AOO = AOO_IN_Discharging;
      AOO_DW.temporalCounter_i1 = 0U;
    } else {
      AOO_B.IS_CHARGING = true;
      AOO_B.PACING_REF_PWM = AOO_P.PWM_Value;
      AOO_B.PACE_CHARGE_CTRL = true;
      AOO_B.PACE_GND_CTRL = true;
      AOO_B.ATR_PACE_CTRL = false;
      AOO_B.ATR_GND_CTRL = true;
      AOO_B.VENT_PACE_CTRL = false;
      AOO_B.VENT_GND_CTRL = false;
      AOO_B.Z_ATR_CTRL = false;
      AOO_B.Z_VENT_CTRL = false;
    }

    /* case IN_Discharging: */
  } else if (AOO_DW.temporalCounter_i1 >= (uint32_T)ceil(AOO_P.Constant_Value))
  {
    AOO_DW.is_c3_AOO = AOO_IN_Charging;
    AOO_DW.temporalCounter_i1 = 0U;
  } else {
    AOO_B.IS_CHARGING = false;
    AOO_B.PACE_CHARGE_CTRL = false;
    AOO_B.PACE_GND_CTRL = true;
    AOO_B.ATR_PACE_CTRL = true;
    AOO_B.ATR_GND_CTRL = false;
    AOO_B.VENT_PACE_CTRL = false;
    AOO_B.VENT_GND_CTRL = false;
    AOO_B.Z_ATR_CTRL = false;
    AOO_B.Z_VENT_CTRL = false;
  }

  /* End of Chart: '<Root>/AOO' */

  /* MATLABSystem: '<Root>/Digital Write' */
  MW_digitalIO_write(AOO_DW.obj_hb.MW_DIGITALIO_HANDLE, AOO_B.IS_CHARGING);

  /* MATLABSystem: '<Root>/Digital Write1' */
  MW_digitalIO_write(AOO_DW.obj_m.MW_DIGITALIO_HANDLE, AOO_B.PACE_GND_CTRL);

  /* MATLABSystem: '<Root>/Digital Write10' */
  MW_digitalIO_write(AOO_DW.obj_ii.MW_DIGITALIO_HANDLE, AOO_B.ATR_GND_CTRL);

  /* MATLABSystem: '<Root>/Digital Write11' */
  MW_digitalIO_write(AOO_DW.obj_nv.MW_DIGITALIO_HANDLE, AOO_B.VENT_GND_CTRL);

  /* MATLABSystem: '<Root>/Digital Write12' */
  MW_digitalIO_write(AOO_DW.obj_l0.MW_DIGITALIO_HANDLE, AOO_B.FRONTEND_CTRL);

  /* MATLABSystem: '<Root>/Digital Write2' */
  MW_digitalIO_write(AOO_DW.obj_h.MW_DIGITALIO_HANDLE, AOO_B.PACE_CHARGE_CTRL);

  /* MATLABSystem: '<Root>/Digital Write3' */
  MW_digitalIO_write(AOO_DW.obj_j.MW_DIGITALIO_HANDLE, AOO_B.PACING_REF_PWM !=
                     0.0);

  /* MATLABSystem: '<Root>/Digital Write4' */
  MW_digitalIO_write(AOO_DW.obj_b.MW_DIGITALIO_HANDLE, AOO_B.Z_ATR_CTRL);

  /* MATLABSystem: '<Root>/Digital Write5' */
  MW_digitalIO_write(AOO_DW.obj_l.MW_DIGITALIO_HANDLE, AOO_B.VENT_CMP_REF_PWM);

  /* MATLABSystem: '<Root>/Digital Write6' */
  MW_digitalIO_write(AOO_DW.obj_ib.MW_DIGITALIO_HANDLE, AOO_B.ATR_CMP_REF_PWM);

  /* MATLABSystem: '<Root>/Digital Write7' */
  MW_digitalIO_write(AOO_DW.obj_i.MW_DIGITALIO_HANDLE, AOO_B.Z_VENT_CTRL);

  /* MATLABSystem: '<Root>/Digital Write8' */
  MW_digitalIO_write(AOO_DW.obj_n.MW_DIGITALIO_HANDLE, AOO_B.ATR_PACE_CTRL);

  /* MATLABSystem: '<Root>/Digital Write9' */
  MW_digitalIO_write(AOO_DW.obj.MW_DIGITALIO_HANDLE, AOO_B.VENT_PACE_CTRL);
}

/* Model initialize function */
void AOO_initialize(void)
{
  {
    freedomk64f_DigitalWrite_AOO_T *obj;

    /* SystemInitialize for Chart: '<Root>/AOO' */
    AOO_B.FRONTEND_CTRL = true;

    /* Start for MATLABSystem: '<Root>/Digital Write' */
    AOO_DW.obj_hb.matlabCodegenIsDeleted = true;
    AOO_DW.obj_hb.isInitialized = 0;
    AOO_DW.obj_hb.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_hb;
    AOO_DW.obj_hb.isSetupComplete = false;
    AOO_DW.obj_hb.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(42U, 1);
    AOO_DW.obj_hb.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write1' */
    AOO_DW.obj_m.matlabCodegenIsDeleted = true;
    AOO_DW.obj_m.isInitialized = 0;
    AOO_DW.obj_m.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_m;
    AOO_DW.obj_m.isSetupComplete = false;
    AOO_DW.obj_m.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(10U, 1);
    AOO_DW.obj_m.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write10' */
    AOO_DW.obj_ii.matlabCodegenIsDeleted = true;
    AOO_DW.obj_ii.isInitialized = 0;
    AOO_DW.obj_ii.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_ii;
    AOO_DW.obj_ii.isSetupComplete = false;
    AOO_DW.obj_ii.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(11U, 1);
    AOO_DW.obj_ii.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write11' */
    AOO_DW.obj_nv.matlabCodegenIsDeleted = true;
    AOO_DW.obj_nv.isInitialized = 0;
    AOO_DW.obj_nv.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_nv;
    AOO_DW.obj_nv.isSetupComplete = false;
    AOO_DW.obj_nv.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(12U, 1);
    AOO_DW.obj_nv.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write12' */
    AOO_DW.obj_l0.matlabCodegenIsDeleted = true;
    AOO_DW.obj_l0.isInitialized = 0;
    AOO_DW.obj_l0.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_l0;
    AOO_DW.obj_l0.isSetupComplete = false;
    AOO_DW.obj_l0.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(13U, 1);
    AOO_DW.obj_l0.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write2' */
    AOO_DW.obj_h.matlabCodegenIsDeleted = true;
    AOO_DW.obj_h.isInitialized = 0;
    AOO_DW.obj_h.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_h;
    AOO_DW.obj_h.isSetupComplete = false;
    AOO_DW.obj_h.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(2U, 1);
    AOO_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write3' */
    AOO_DW.obj_j.matlabCodegenIsDeleted = true;
    AOO_DW.obj_j.isInitialized = 0;
    AOO_DW.obj_j.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_j;
    AOO_DW.obj_j.isSetupComplete = false;
    AOO_DW.obj_j.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(3U, 1);
    AOO_DW.obj_j.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write4' */
    AOO_DW.obj_b.matlabCodegenIsDeleted = true;
    AOO_DW.obj_b.isInitialized = 0;
    AOO_DW.obj_b.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_b;
    AOO_DW.obj_b.isSetupComplete = false;
    AOO_DW.obj_b.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(4U, 1);
    AOO_DW.obj_b.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write5' */
    AOO_DW.obj_l.matlabCodegenIsDeleted = true;
    AOO_DW.obj_l.isInitialized = 0;
    AOO_DW.obj_l.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_l;
    AOO_DW.obj_l.isSetupComplete = false;
    AOO_DW.obj_l.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(5U, 1);
    AOO_DW.obj_l.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write6' */
    AOO_DW.obj_ib.matlabCodegenIsDeleted = true;
    AOO_DW.obj_ib.isInitialized = 0;
    AOO_DW.obj_ib.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_ib;
    AOO_DW.obj_ib.isSetupComplete = false;
    AOO_DW.obj_ib.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(6U, 1);
    AOO_DW.obj_ib.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write7' */
    AOO_DW.obj_i.matlabCodegenIsDeleted = true;
    AOO_DW.obj_i.isInitialized = 0;
    AOO_DW.obj_i.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_i;
    AOO_DW.obj_i.isSetupComplete = false;
    AOO_DW.obj_i.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(7U, 1);
    AOO_DW.obj_i.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write8' */
    AOO_DW.obj_n.matlabCodegenIsDeleted = true;
    AOO_DW.obj_n.isInitialized = 0;
    AOO_DW.obj_n.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj_n;
    AOO_DW.obj_n.isSetupComplete = false;
    AOO_DW.obj_n.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(8U, 1);
    AOO_DW.obj_n.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write9' */
    AOO_DW.obj.matlabCodegenIsDeleted = true;
    AOO_DW.obj.isInitialized = 0;
    AOO_DW.obj.matlabCodegenIsDeleted = false;
    obj = &AOO_DW.obj;
    AOO_DW.obj.isSetupComplete = false;
    AOO_DW.obj.isInitialized = 1;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(9U, 1);
    AOO_DW.obj.isSetupComplete = true;
  }
}

/* Model terminate function */
void AOO_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Digital Write' */
  if (!AOO_DW.obj_hb.matlabCodegenIsDeleted) {
    AOO_DW.obj_hb.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_hb.isInitialized == 1) && AOO_DW.obj_hb.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_hb.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write1' */
  if (!AOO_DW.obj_m.matlabCodegenIsDeleted) {
    AOO_DW.obj_m.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_m.isInitialized == 1) && AOO_DW.obj_m.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_m.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write1' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write10' */
  if (!AOO_DW.obj_ii.matlabCodegenIsDeleted) {
    AOO_DW.obj_ii.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_ii.isInitialized == 1) && AOO_DW.obj_ii.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_ii.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write10' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write11' */
  if (!AOO_DW.obj_nv.matlabCodegenIsDeleted) {
    AOO_DW.obj_nv.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_nv.isInitialized == 1) && AOO_DW.obj_nv.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_nv.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write11' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write12' */
  if (!AOO_DW.obj_l0.matlabCodegenIsDeleted) {
    AOO_DW.obj_l0.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_l0.isInitialized == 1) && AOO_DW.obj_l0.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_l0.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write12' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write2' */
  if (!AOO_DW.obj_h.matlabCodegenIsDeleted) {
    AOO_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_h.isInitialized == 1) && AOO_DW.obj_h.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_h.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write2' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write3' */
  if (!AOO_DW.obj_j.matlabCodegenIsDeleted) {
    AOO_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_j.isInitialized == 1) && AOO_DW.obj_j.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_j.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write3' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write4' */
  if (!AOO_DW.obj_b.matlabCodegenIsDeleted) {
    AOO_DW.obj_b.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_b.isInitialized == 1) && AOO_DW.obj_b.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_b.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write4' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write5' */
  if (!AOO_DW.obj_l.matlabCodegenIsDeleted) {
    AOO_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_l.isInitialized == 1) && AOO_DW.obj_l.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_l.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write5' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write6' */
  if (!AOO_DW.obj_ib.matlabCodegenIsDeleted) {
    AOO_DW.obj_ib.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_ib.isInitialized == 1) && AOO_DW.obj_ib.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_ib.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write6' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write7' */
  if (!AOO_DW.obj_i.matlabCodegenIsDeleted) {
    AOO_DW.obj_i.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_i.isInitialized == 1) && AOO_DW.obj_i.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_i.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write7' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write8' */
  if (!AOO_DW.obj_n.matlabCodegenIsDeleted) {
    AOO_DW.obj_n.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj_n.isInitialized == 1) && AOO_DW.obj_n.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj_n.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write8' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write9' */
  if (!AOO_DW.obj.matlabCodegenIsDeleted) {
    AOO_DW.obj.matlabCodegenIsDeleted = true;
    if ((AOO_DW.obj.isInitialized == 1) && AOO_DW.obj.isSetupComplete) {
      MW_digitalIO_close(AOO_DW.obj.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write9' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
