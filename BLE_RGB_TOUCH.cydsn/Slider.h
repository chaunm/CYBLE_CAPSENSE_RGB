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

#ifndef __SLIDER_H__
#define __SLIDER_H__
#include <cytypes.h>
    void Slider_Init();
    uint16 Slider_GetValue();
    void Slider_EnableNotification();
    void Slider_DisableNotification();
    uint8 Slider_IsNotifyEnabled();
#endif // __SLIDER_H__

/* [] END OF FILE */
