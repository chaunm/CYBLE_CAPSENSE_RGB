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
#include <project.h>
#include "RGB.h"

static uint8 notifyEnable;

void RGB_Init()
{
    PWM_1_Start();
    PWM_2_Start();
    PWM_1_WritePeriod(65025);
    PWM_2_WritePeriod(65025);
    PWM_1_WriteCompare1(0);
    PWM_1_WriteCompare2(0);
    PWM_2_WriteCompare1(0);
}

void RGB_SetHue(HUEVALUE hueData)
{
    CYBLE_GATT_HANDLE_VALUE_PAIR_T rgbHueValue;
    rgbHueValue.attrHandle = CYBLE_RGB_LED_RGB_DATA_CHAR_HANDLE;
    rgbHueValue.value.len = sizeof(HUEVALUE);
    rgbHueValue.value.val = (uint8*)(&hueData);
    CyBle_GattsWriteAttributeValue(&rgbHueValue, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
    if (RGB_IsNotifyEnabled() == 1)
    {
        if (RGB_IsNotifyEnabled() == 1)
           CyBle_GattsNotification(cyBle_connHandle, (CYBLE_GATTS_HANDLE_VALUE_NTF_T*)&rgbHueValue);
    }
    PWM_1_WriteCompare1(((uint16)hueData.red) * hueData.intensity);
    PWM_1_WriteCompare2(((uint16)hueData.green) * hueData.intensity);
    PWM_2_WriteCompare1(((uint16)hueData.blue) * hueData.intensity);
}

void RGB_EnableNotification()
{
    notifyEnable = 1;
}

void RGB_DisableNotification()
{
    notifyEnable = 0;
}

uint8 RGB_IsNotifyEnabled()
{
    return notifyEnable;
}
/* [] END OF FILE */
