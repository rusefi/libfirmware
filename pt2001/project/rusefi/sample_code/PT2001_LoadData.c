/*******************************************************************************
* Example Code
*
* Copyright(C) 2023 NXP Semiconductors
* NXP Semiconductors Confidential and Proprietary
*
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* NXP products.  This software is supplied "AS IS" without any warranties
* of any kind, and NXP Semiconductors and its licensor disclaim any and
* all warranties, express or implied, including all implied warranties of
* merchantability, fitness for a particular purpose and non-infringement of
* intellectual property rights.  NXP Semiconductors assumes no responsibility
* or liability for the use of the software, conveys no license or rights
* under any patent, copyright, mask work right, or any other intellectual
* property rights in or to any products. NXP Semiconductors reserves the
* right to make changes in the software without notification. NXP
* Semiconductors also makes no representation or warranty that such
* application will be suitable for the specified use without further testing
* or modification.
*
* IN NO EVENT WILL NXP SEMICONDUCTORS BE LIABLE, WHETHER IN CONTRACT, 
* TORT, OR OTHERWISE, FOR ANY INCIDENTAL, SPECIAL, INDIRECT, CONSEQUENTIAL 
* OR PUNITIVE DAMAGES, INCLUDING, BUT NOT LIMITED TO, DAMAGES FOR ANY 
* LOSS OF USE, LOSS OF TIME, INCONVENIENCE, COMMERCIAL LOSS, OR LOST 
* PROFITS, SAVINGS, OR REVENUES, TO THE FULL EXTENT SUCH MAY BE DISCLAIMED  
* BY LAW. NXP SEMICONDUCTOR’S TOTAL LIABILITY FOR ALL COSTS, DAMAGES, 
* CLAIMS, OR LOSSES WHATSOEVER ARISING OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE IS LIMITED TO THE AGGREGATE AMOUNT PAID BY YOU TO NXP SEMICONDUCTORS
* IN CONNECTION WITH THE SOFTWARE TO WHICH LOSSES OR DAMAGES ARE CLAIMED.
*
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors' and its
* licensor's relevant copyrights in the software, without fee, provided
* that it is used in conjunction with NXP Semiconductors devices.  This
* copyright, permission, and disclaimer notice must appear in all copies
* of this code.
*******************************************************************************/

//==============================================================================
// This file contains data arrays that are used to load the code RAM, data RAM
// and registers on the PT2001.
//==============================================================================

// ECU: IDE Project
// Project: rusefi

#include "PT2001_LoadData.h"

// Data to be loaded into the Code RAM 1 memory space
unsigned short PT2001_code_RAM1[114] =
{
    0x7612, 0x6C57, 0x917F, 0xA514, 0x8DD6, 0xC288, 0x4F9B, 0x1EC9, 0x5C0D, 0xF99D, 
    0x4129, 0x2EEE, 0x97B0, 0x3534, 0x93BA, 0x5D25, 0xEE21, 0x2AAD, 0xE457, 0x2DB8, 
    0xBED3, 0xBEB9, 0x2F08, 0xDA3C, 0x0499, 0x8DDE, 0xB519, 0x8E21, 0xAE4D, 0xF3E1, 
    0x6E41, 0x9F0E, 0x2476, 0xBA8B, 0x4422, 0x0133, 0x6DAC, 0xA368, 0xE91F, 0x5E97, 
    0x7820, 0x4662, 0xFEE0, 0x6F02, 0x8A92, 0x9A83, 0xE194, 0x6FD0, 0x1895, 0x80AB, 
    0x4F93, 0xE1DA, 0x51BF, 0x70D8, 0xF25E, 0x7021, 0x2270, 0xF748, 0x51C5, 0xA4F1, 
    0x329C, 0x5ADC, 0xD84C, 0xF054, 0x6E39, 0x2389, 0xCD76, 0x52F5, 0xF072, 0x8D02, 
    0x4045, 0xDFEA, 0x1D65, 0xAD07, 0x33F3, 0x6650, 0x8854, 0x210D, 0x3A3C, 0xD20B, 
    0x25B3, 0x8090, 0x27DE, 0xDF3E, 0xE928, 0x7D95, 0x83CC, 0xA366, 0x7879, 0x8A2C, 
    0xE2E2, 0x1E41, 0x6530, 0x24F8, 0xB726, 0xF030, 0xCEA7, 0xF3FF, 0x4080, 0xF1DD, 
    0xB433, 0xBFCB, 0x95C2, 0xDEDE, 0x2E14, 0xF672, 0x0567, 0x102E, 0xE0BC, 0xBD5F, 
    0x21BF, 0x4D2B, 0x2ABD, 0x01B5
};

// Data to be loaded into the Code RAM 2 memory space
unsigned short PT2001_code_RAM2[43] =
{
    0x761B, 0x6F45, 0x838D, 0x80B4, 0x53F2, 0x0EBC, 0x8F2D, 0xA78E, 0xE8AB, 0xE3DB, 
    0xF477, 0x800F, 0x2336, 0x2F77, 0x267B, 0xBC19, 0x007E, 0x4E55, 0x28AA, 0x52E4, 
    0x40CF, 0x0AFD, 0x8B32, 0xFF03, 0x3D8E, 0x802E, 0x1340, 0x95D0, 0x1E86, 0x6591, 
    0xDBEB, 0x786D, 0xB2DF, 0xF4BF, 0xBEB2, 0xF1F4, 0x9E53, 0xE743, 0xE842, 0x3DD7, 
    0x3DA2, 0x4663, 0x03AF
};

// Data to be loaded into the Data RAM memory space
unsigned short PT2001_data_RAM[128] =
{
    0x00C0, 0x0092, 0x0049, 0x003C, 0x1068, 0x003C, 0x0168, 0xEA60, 0x0960, 0x0258, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x00C1, 0x00BF, 0x0040, 0x001D, 0x0000, 0x0046,
    0x0037, 0x003C, 0xEA60, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// Data to be loaded into the Main register memory space
unsigned short PT2001_main_config[29] =
{
    0x0003, 0x13FE, 0x0000, 0x1E00, 0x0000, 0x0000, 0x0001, 0x0000, 0x001F, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// Data to be loaded into the CH1 register memory space
unsigned short PT2001_ch1_config[19] =
{
    0x0008, 0x0000, 0x0000, 0x0000, 0x0303, 0x0000, 0x0000, 0x0072, 0x91E7, 0x56D6, 
    0x0000, 0x0039, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// Data to be loaded into the CH2 register memory space
unsigned short PT2001_ch2_config[19] =
{
    0x0008, 0x0000, 0x0000, 0x0000, 0x0C00, 0x0000, 0x0000, 0x002B, 0x218C, 0xDCB6, 
    0x0000, 0x0014, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// Data to be loaded into the IO register memory space
unsigned short PT2001_io_config[53] =
{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0063, 0x018C, 0x0800, 0x0410, 0x0041, 0x0098, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0041, 0x0041, 0x0041, 0x0000, 0x0004, 0x1000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0303, 0x0C0C, 
    0x0030, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000
};

// Data to be loaded into the Diag register memory space
unsigned short PT2001_diag_config[44] =
{
    0x0000, 0x0000, 0x001E, 0x0000, 0x0000, 0x001E, 0x0000, 0x0000, 0x001E, 0x0000, 
    0x0000, 0x001E, 0x0000, 0x0000, 0x001E, 0x0000, 0x0000, 0x001E, 0x001E, 0x0000, 
    0x0000, 0x001E, 0x0000, 0x0000, 0x001E, 0x0000, 0x0000, 0x001E, 0x0000, 0x0000, 
    0x001E, 0x0000, 0x0000, 0x001E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0001
};

