#ifndef DBGMCU_IDCODE_REV_ID_Pos
#define DBGMCU_IDCODE_REV_ID_Pos               (16U)
#endif

#ifndef DBGMCU_IDCODE_REV_ID_Msk
#define DBGMCU_IDCODE_REV_ID_Msk               (0xFFFFUL << DBGMCU_IDCODE_REV_ID_Pos) /*!< 0xFFFF0000 */
#endif

// real stm32F1 would return 0x1001 they say
#define REAL_STM_F1_REV_CODE 0x1001

#define REAL_GD_F1_REV_CODE 0x1303

#define REAL_SOMETHING_F1_ELSE 0x1000

#define REAL_SOMETHING_F1_REV_CODE 0x2003

#define ARM_REV_CODE() ((DBGMCU->IDCODE & DBGMCU_IDCODE_REV_ID_Msk) >> DBGMCU_IDCODE_REV_ID_Pos)
