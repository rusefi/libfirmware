/*
 * boards_dictionary.h
 *
 * @date Aug 18, 2023
 * @author Andrey Belomutskiy, (c) 2012-2021
 * @author andreika <prometheus.pcb@gmail.com>
 */

#pragma once

// 61440
#define STATIC_BOARD_ID_BASE 0xF000

#define STATIC_BOARD_ID_48WAY                (STATIC_BOARD_ID_BASE + 0)
#define STATIC_BOARD_ID_ATLAS                (STATIC_BOARD_ID_BASE + 1)
#define STATIC_BOARD_ID_AT_START_F435        (STATIC_BOARD_ID_BASE + 2)
#define STATIC_BOARD_ID_BB_V2                (STATIC_BOARD_ID_BASE + 3)
#define STATIC_BOARD_ID_BB_V3                (STATIC_BOARD_ID_BASE + 4)
#define STATIC_BOARD_ID_CORE8                (STATIC_BOARD_ID_BASE + 5)
#define STATIC_BOARD_ID_HABA208              (STATIC_BOARD_ID_BASE + 6)
#define STATIC_BOARD_ID_F429_DISCOVERY       (STATIC_BOARD_ID_BASE + 7)
#define STATIC_BOARD_ID_ALPHAX_2CHAN         (STATIC_BOARD_ID_BASE + 8)
#define STATIC_BOARD_ID_ALPHAX_4CHAN         (STATIC_BOARD_ID_BASE + 9)
#define STATIC_BOARD_ID_ALPHAX_4CHAN_F7      (STATIC_BOARD_ID_BASE + 10)
#define STATIC_BOARD_ID_ALPHAX_8CHAN         (STATIC_BOARD_ID_BASE + 11)
#define STATIC_BOARD_ID_HARLEY81             (STATIC_BOARD_ID_BASE + 12)
#define STATIC_BOARD_ID_HELLEN_GM_E67        (STATIC_BOARD_ID_BASE + 13)
#define STATIC_BOARD_ID_HELLEN_HONDA_K       (STATIC_BOARD_ID_BASE + 14)
#define STATIC_BOARD_ID_HELLEN_NB1           (STATIC_BOARD_ID_BASE + 15)
#define STATIC_BOARD_ID_HELLEN_121NISSAN     (STATIC_BOARD_ID_BASE + 16)
#define STATIC_BOARD_ID_HELLEN_121VAG        (STATIC_BOARD_ID_BASE + 17)
#define STATIC_BOARD_ID_HELLEN_128           (STATIC_BOARD_ID_BASE + 18)
#define STATIC_BOARD_ID_HELLEN_154_HYUNDAI   (STATIC_BOARD_ID_BASE + 19)
#define STATIC_BOARD_ID_HELLEN_NA6           (STATIC_BOARD_ID_BASE + 20)
#define STATIC_BOARD_ID_HELLEN_72            (STATIC_BOARD_ID_BASE + 21)
#define STATIC_BOARD_ID_HELLEN_81            (STATIC_BOARD_ID_BASE + 22)
#define STATIC_BOARD_ID_HELLEN_88_BMW        (STATIC_BOARD_ID_BASE + 23)
#define STATIC_BOARD_ID_HELLEN_NA8_96        (STATIC_BOARD_ID_BASE + 24)
#define STATIC_BOARD_ID_SMALL_CAN_BOARD      (STATIC_BOARD_ID_BASE + 25)
#define STATIC_BOARD_ID_KIN                  (STATIC_BOARD_ID_BASE + 26)
#define STATIC_BOARD_ID_M74_9                (STATIC_BOARD_ID_BASE + 27)
#define STATIC_BOARD_ID_MRE_F4               (STATIC_BOARD_ID_BASE + 28)
#define STATIC_BOARD_ID_MRE_F7               (STATIC_BOARD_ID_BASE + 29)
#define STATIC_BOARD_ID_NUCLEO_F429          (STATIC_BOARD_ID_BASE + 30)
#define STATIC_BOARD_ID_NUCLEO_F767          (STATIC_BOARD_ID_BASE + 31)
#define STATIC_BOARD_ID_NUCLEO_H743          (STATIC_BOARD_ID_BASE + 32)
#define STATIC_BOARD_ID_PROTEUS_F4           (STATIC_BOARD_ID_BASE + 33)
// 61474
#define STATIC_BOARD_ID_PROTEUS_F7           (STATIC_BOARD_ID_BASE + 34)
#define STATIC_BOARD_ID_PROTEUS_H7           (STATIC_BOARD_ID_BASE + 35)
#define STATIC_BOARD_ID_S105                 (STATIC_BOARD_ID_BASE + 36)
#define STATIC_BOARD_ID_SUBARU_EG33_F7       (STATIC_BOARD_ID_BASE + 37)
#define STATIC_BOARD_ID_TDG_PDM8             (STATIC_BOARD_ID_BASE + 38)
#define STATIC_BOARD_ID_TBG                  (STATIC_BOARD_ID_BASE + 39)
#define STATIC_BOARD_ID_F407_DISCOVERY       (STATIC_BOARD_ID_BASE + 40)
#define STATIC_BOARD_ID_FRANKENSO_NA6        (STATIC_BOARD_ID_BASE + 41)
#define STATIC_BOARD_ID_CYPRESS              (STATIC_BOARD_ID_BASE + 42)
#define STATIC_BOARD_ID_PROMETHEUS_405       (STATIC_BOARD_ID_BASE + 43)
#define STATIC_BOARD_ID_PROMETHEUS_469       (STATIC_BOARD_ID_BASE + 44)

#define STATIC_BOARD_ID_PROTEUS_CANAM        (STATIC_BOARD_ID_BASE + 45)
#define STATIC_BOARD_ID_PROTEUS_SLINGSHOT    (STATIC_BOARD_ID_BASE + 46)
#define STATIC_BOARD_ID_PROTEUS_HARLEY      (STATIC_BOARD_ID_BASE + 47)
#define STATIC_BOARD_ID_HELLEN_MG1          (STATIC_BOARD_ID_BASE + 48)
#define STATIC_BOARD_ID_HELLEN_HD           (STATIC_BOARD_ID_BASE + 49)
#define STATIC_BOARD_ID_MRE_M111            (STATIC_BOARD_ID_BASE + 50)
#define STATIC_BOARD_ID_PROTEUS_SBC         (STATIC_BOARD_ID_BASE + 51)
#define STATIC_BOARD_ID_PROTEUS_M73         (STATIC_BOARD_ID_BASE + 52)
#define STATIC_BOARD_ID_ALPHAX_SILVER       (STATIC_BOARD_ID_BASE + 53)
#define STATIC_BOARD_ID_ALPHAX_GOLD         (STATIC_BOARD_ID_BASE + 54)
#define STATIC_BOARD_ID_HELLEN_POLARIS      (STATIC_BOARD_ID_BASE + 55)
#define STATIC_BOARD_ID_UAEFU121_SBC         (STATIC_BOARD_ID_BASE + 56)
#define STATIC_BOARD_ID_PLATINUM_SBC         (STATIC_BOARD_ID_BASE + 57)
#define STATIC_BOARD_ID_HELLEN_E80         (STATIC_BOARD_ID_BASE + 58)
#define STATIC_BOARD_ID_HELLEN_E92         (STATIC_BOARD_ID_BASE + 59)
#define STATIC_BOARD_ID_CHUMA         (STATIC_BOARD_ID_BASE + 60)
#define STATIC_BOARD_ID_8CHAN_E92        (STATIC_BOARD_ID_BASE + 61)
#define STATIC_BOARD_ID_F746_DISCOVERY       (STATIC_BOARD_ID_BASE + 62)
#define STATIC_BOARD_ID_PROTEUS_SUBARU_2011   (STATIC_BOARD_ID_BASE + 63)
#define STATIC_BOARD_ID_NANO         (STATIC_BOARD_ID_BASE + 64)
#define STATIC_BOARD_ID_SUPER_UAEFI        (STATIC_BOARD_ID_BASE + 65)
#define STATIC_BOARD_ID_PLATINUM_GM_GEN4        (STATIC_BOARD_ID_BASE + 66)
#define STATIC_BOARD_ID_HELLEN_E38          (STATIC_BOARD_ID_BASE + 67)
