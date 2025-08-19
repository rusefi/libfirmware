/**
 * see mc33816/rusefi/readme.md
*/

#pragma once

#include <PT2001_dram.h>

enum class MC33816Mem {
    // see dram1.def values
    Iboost = PT2001_D1_Iboost,
    Ipeak = PT2001_D1_Ipeak,
    Ihold = PT2001_D1_Ihold,
    Tpeak_off = PT2001_D1_Tpeak_off,
    Tpeak_tot = PT2001_D1_Tpeak_tot,
    Tbypass = PT2001_D1_Tbypass,
    Thold_off = PT2001_D1_Thold_off,
    Thold_tot = PT2001_D1_Thold_tot,
    Tboost_min = PT2001_D1_Tboost_min,
    Tboost_max = PT2001_D1_Tboost_max,
    Tboost_inj12 = PT2001_D1_Tboost_inj12,
    Tboost_inj34 = PT2001_D1_Tboost_inj34,
    // see dram2.def values, base 64 for channel 2
    Vboost_high = PT2001_D2_Vboost_high,
    Vboost_low = PT2001_D2_Vboost_low,
    Isense4_high = PT2001_D2_Isense4_high,
    Isense4_low = PT2001_D2_Isense4_low,
    HPFP_Ipeak = PT2001_D2_PCV_Ipeak,
    HPFP_Ihold = PT2001_D2_PCV_Ihold,
    HPFP_Thold_off = PT2001_D2_PCV_Thold_off,
    HPFP_Thold_tot = PT2001_D2_PCV_Thold_tot,
};
