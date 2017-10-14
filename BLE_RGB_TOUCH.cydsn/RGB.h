/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef __RGB_H__
#define __RGB_H__
#include <cytypes.h>
    
#pragma pack(1)
typedef struct tagHueValue {
    uint8 red;
    uint8 green;
    uint8 blue;
    uint8 intensity;
} HUEVALUE, *PHUEVALUE;

void RGB_Init();
void RGB_SetHue(HUEVALUE hueData);
void RGB_EnableNotification();
void RGB_DisableNotification();
uint8 RGB_IsNotifyEnabled();

#endif // __RGB_H__
/* [] END OF FILE */
