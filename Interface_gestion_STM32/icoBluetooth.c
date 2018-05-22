/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter for emWin V5.30.                           *
*        Compiled Jul  1 2015, 10:49:26                              *
*                                                                    *
*        (c) 1998 - 2015 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: icoBluetooth                                          *
* Dimensions:  48 * 48                                               *
* NumColors:   114                                                   *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmicoBluetooth;

/*********************************************************************
*
*       Palette
*
*  Description
*    The following are the entries of the palette table.
*    The entries are stored as a 32-bit values of which 24 bits are
*    actually used according to the following bit mask: 0xBBGGRR
*
*    The lower   8 bits represent the Red   component.
*    The middle  8 bits represent the Green component.
*    The highest 8 bits represent the Blue  component.
*/
static GUI_CONST_STORAGE GUI_COLOR _ColorsicoBluetooth[] = {
  0xFF9400, 0x000000, 0x633900, 0x1E1100,
  0xFFFFFF, 0xEFA43D, 0xE39C3B, 0xFB9912,
  0xA67025, 0x080808, 0x181818, 0xAD7529,
  0xDB8C21, 0x1E1101, 0x261908, 0xFA9914,
  0x7D4F10, 0x855514, 0x8C5B18, 0x8F5E1A,
  0x97641E, 0xF89A19, 0xDD993B, 0x1C1C1C,
  0x221504, 0x282828, 0x2C2C2C, 0x724509,
  0x784B0D, 0x484848, 0x4C4C4C, 0x747474,
  0x7C7C7C, 0xF79919, 0xF5991B, 0xF6991B,
  0xF99A18, 0xCE8520, 0xE89421, 0xED9620,
  0x8F8F8F, 0x939393, 0xD7D7D7, 0xDBDBDB,
  0xEBEBEB, 0xEFEFEF, 0xF3F3F3, 0xF7F7F7,
  0x1F1202, 0x885816, 0xFB9A14, 0x0D0D0D,
  0x0E0E0E, 0x161616, 0x211403, 0x231605,
  0x241706, 0x291C0A, 0x2A1D0B, 0x313131,
  0x7E4F10, 0x4E4E4E, 0x595959, 0x815212,
  0xB27018, 0xB6741A, 0xA97227, 0xB47B2D,
  0xB67C2D, 0x85735B, 0x8F7C63, 0xFC980F,
  0xEF981F, 0xFA9A16, 0xF2991D, 0xF3991D,
  0xF4991C, 0xF59A1C, 0xD18721, 0xD58921,
  0xD68A21, 0xD88B21, 0xDD8E22, 0xCF8F36,
  0xD89539, 0xDF9A3B, 0xE19022, 0xE39122,
  0xE59222, 0xE69322, 0xEB9621, 0xEC9721,
  0xEBA23D, 0xF7A83B, 0xF8A83B, 0xBEA98C,
  0x251807, 0x74480B, 0x75480B, 0x7A4C0E,
  0x7B4D0E, 0x875715, 0x95631D, 0xAD6D16,
  0x9B6720, 0x9C6821, 0x9F6A22, 0xA16C23,
  0xA46E25, 0xB77C2D, 0xFC9810, 0xF0971E,
  0xF1981E, 0xCC8320
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalicoBluetooth = {
  114,  // Number of entries
  0,    // No transparency
  &_ColorsicoBluetooth[0]
};

static GUI_CONST_STORAGE unsigned char _acicoBluetooth[] = {
  0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x2D, 0x29, 0x1E, 0x17, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x17, 0x1E, 0x29, 0x2D, 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
  0x04, 0x04, 0x04, 0x04, 0x2F, 0x20, 0x09, 0x01, 0x01, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x01, 0x09, 
        0x20, 0x2F, 0x04, 0x04, 0x04, 0x04,
  0x04, 0x04, 0x04, 0x2B, 0x1A, 0x01, 0x03, 0x08, 0x16, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x16, 0x08, 0x03, 
        0x01, 0x1A, 0x2B, 0x04, 0x04, 0x04,
  0x04, 0x04, 0x2B, 0x0A, 0x03, 0x11, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 
        0x11, 0x03, 0x0A, 0x2B, 0x04, 0x04,
  0x04, 0x2F, 0x1A, 0x03, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x40, 0x03, 0x1A, 0x2F, 0x04,
  0x04, 0x20, 0x01, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x03, 0x1B, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x11, 0x01, 0x20, 0x04,
  0x2D, 0x09, 0x03, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x03, 0x31, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x23, 0x03, 0x09, 0x2D,
  0x29, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x01, 0x01, 0x03, 0x6C, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x08, 0x01, 0x29,
  0x1E, 0x01, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x3D, 0x33, 0x01, 0x01, 0x18, 0x4F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x16, 0x01, 0x1E,
  0x17, 0x03, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x5F, 0x5E, 0x44, 0x30, 0x01, 0x03, 0x1C, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x0F, 0x03, 0x17,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x15, 0x14, 0x03, 0x01, 0x03, 0x13, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x27, 0x3C, 0x03, 0x01, 0x03, 0x0B, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0E, 0x01, 0x01, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0B, 0x0D, 0x01, 0x03, 0x10, 0x27, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x66, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x3B, 0x01, 0x01, 0x03, 0x14, 0x21, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x01, 0x03, 0x08, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5D, 0x3E, 0x01, 0x01, 0x03, 0x64, 0x5A, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0x3A, 0x01, 0x01, 0x18, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x39, 0x01, 0x01, 0x38, 0x51, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x43, 0x30, 0x01, 0x03, 0x1C, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x3F, 0x03, 0x01, 0x03, 0x42, 0x32, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x14, 0x03, 0x01, 0x03, 0x13, 0x22, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x24, 0x68, 0x03, 0x01, 0x03, 0x12, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5B, 0x10, 0x03, 0x01, 0x0D, 0x0B, 0x07, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x25, 0x36, 0x01, 0x03, 0x62, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0E, 0x01, 0x01, 0x0E, 0x0C, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x57, 0x1B, 0x03, 0x01, 0x18, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0B, 0x0D, 0x01, 0x03, 0x10, 0x46, 0x01, 0x01, 0x45, 0x65, 0x03, 0x01, 0x03, 0x6B, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x13, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x11, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x35, 0x01, 0x01, 0x01, 0x01, 0x34, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x35, 0x01, 0x01, 0x01, 0x01, 0x34, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x13, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x11, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0B, 0x03, 0x01, 0x03, 0x3C, 0x46, 0x01, 0x01, 0x45, 0x31, 0x03, 0x01, 0x03, 0x6A, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x60, 0x01, 0x01, 0x0E, 0x0C, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x57, 0x1B, 0x03, 0x01, 0x18, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5B, 0x10, 0x03, 0x01, 0x0D, 0x0B, 0x07, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x25, 0x36, 0x01, 0x03, 0x61, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x14, 0x03, 0x01, 0x03, 0x13, 0x22, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x24, 0x69, 0x03, 0x01, 0x03, 0x12, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6E, 0x43, 0x0D, 0x01, 0x03, 0x1C, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x3F, 0x03, 0x01, 0x03, 0x42, 0x32, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0x3A, 0x01, 0x01, 0x37, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x39, 0x01, 0x01, 0x38, 0x51, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x03, 0x03, 0x08, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5D, 0x3E, 0x01, 0x01, 0x03, 0x63, 0x5A, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x3B, 0x01, 0x01, 0x03, 0x14, 0x15, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0B, 0x0D, 0x01, 0x03, 0x10, 0x27, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0E, 0x01, 0x01, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x27, 0x10, 0x03, 0x01, 0x0D, 0x0B, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x06, 0x00, 0x00, 0x21, 0x14, 0x03, 0x01, 0x03, 0x13, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x0A, 0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x5F, 0x5E, 0x44, 0x30, 0x01, 0x03, 0x1C, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x07, 0x03, 0x0A,
  0x1D, 0x01, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x3D, 0x33, 0x01, 0x01, 0x37, 0x4F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x16, 0x01, 0x1D,
  0x28, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x01, 0x01, 0x03, 0x08, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x08, 0x01, 0x28,
  0x2C, 0x09, 0x03, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x01, 0x01, 0x03, 0x31, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x15, 0x03, 0x09, 0x2C,
  0x04, 0x1F, 0x01, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x03, 0x1B, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x12, 0x01, 0x1F, 0x04,
  0x04, 0x2E, 0x19, 0x03, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x41, 0x03, 0x19, 0x2E, 0x04,
  0x04, 0x04, 0x2A, 0x0A, 0x03, 0x12, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 
        0x12, 0x03, 0x0A, 0x2A, 0x04, 0x04,
  0x04, 0x04, 0x04, 0x2A, 0x19, 0x01, 0x03, 0x08, 0x55, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x55, 0x08, 0x03, 
        0x01, 0x19, 0x2A, 0x04, 0x04, 0x04,
  0x04, 0x04, 0x04, 0x04, 0x2E, 0x1F, 0x09, 0x01, 0x01, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x01, 0x09, 
        0x1F, 0x2E, 0x04, 0x04, 0x04, 0x04,
  0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x2C, 0x28, 0x1D, 0x0A, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0A, 0x1D, 0x28, 0x2C, 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04
};

GUI_CONST_STORAGE GUI_BITMAP bmicoBluetooth = {
  48, // xSize
  48, // ySize
  48, // BytesPerLine
  8, // BitsPerPixel
  _acicoBluetooth,  // Pointer to picture data (indices)
  &_PalicoBluetooth   // Pointer to palette
};

/*************************** End of file ****************************/
