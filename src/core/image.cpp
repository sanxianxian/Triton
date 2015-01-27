
#include "pin.H"
#include "Triton.h"



VOID Image(IMG img, VOID *v)
{
  RTN unlockRTN = RTN_FindByName(img, KnobStartAnalysis.Value().c_str());
  RTN taintParamsRTN = RTN_FindByName(img, "check"); /* TODO: generique */


  if (RTN_Valid(unlockRTN)){
    RTN_Open(unlockRTN);
    RTN_InsertCall(unlockRTN,
                   IPOINT_BEFORE,
                   (AFUNPTR)unlockAnalysis,
                   IARG_PTR,
                   &_analysisStatus,
                   IARG_END);

    RTN_InsertCall(unlockRTN,
                   IPOINT_AFTER,
                   (AFUNPTR)lockAnalysis,
                   IARG_PTR,
                   &_analysisStatus,
                   IARG_END);

    RTN_Close(unlockRTN);
  }

  if (RTN_Valid(taintParamsRTN)){
    RTN_Open(taintParamsRTN);
    RTN_InsertCall(taintParamsRTN,
                   IPOINT_BEFORE,
                   (AFUNPTR)taintParams,
                   IARG_CONTEXT,
                   IARG_PTR,
                   taintEngine,
                   IARG_END);
    RTN_Close(taintParamsRTN);
  }
}

