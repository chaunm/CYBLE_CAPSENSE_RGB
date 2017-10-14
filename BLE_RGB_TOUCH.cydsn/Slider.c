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
#include "Slider.h"

static uint8 sliderNotifyEnable = 0;

void Slider_Init()
{
    CapSense_Start();
    //CapSense_Enable();
    /* Initialize baselines */
    CapSense_InitializeEnabledBaselines();
    CapSense_EnableWidget(CapSense_SLIDER_0__LS);
    CapSense_ScanWidget(CapSense_SLIDER_0__LS);
}

uint16 Slider_GetValue()
{
    CYBLE_GATT_HANDLE_VALUE_PAIR_T sliderDataHandle;
    uint16 capSenseData;
    uint8 sliderPos;
    if (CapSense_IsBusy() == 0)
    {
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanWidget(CapSense_SLIDER_0__LS);
    }
    capSenseData =  CapSense_GetCentroidPos(CapSense_SLIDER_0__LS);
    if (capSenseData != 0xFFFF)
    {
        sliderPos = (uint8)capSenseData;
        sliderDataHandle.attrHandle = CYBLE_CAPSLIDER_SLIDER_POS_CHAR_HANDLE;
        sliderDataHandle.value.len = sizeof(uint8);
        sliderDataHandle.value.val = &sliderPos;
        // update gatt database
        CyBle_GattsWriteAttributeValue(&sliderDataHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    }
    if ((Slider_IsNotifyEnabled() == 1) && (capSenseData != 0xFFFF))
    {        
        // Send Notification
        CyBle_GattsNotification(cyBle_connHandle, (CYBLE_GATTS_HANDLE_VALUE_NTF_T*)&sliderDataHandle);
    }
    return capSenseData;
}

void Slider_EnableNotification()
{
    sliderNotifyEnable = 1;
}

void Slider_DisableNotification()
{
    sliderNotifyEnable = 0;
}

uint8 Slider_IsNotifyEnabled()
{
    return sliderNotifyEnable;
}

/* [] END OF FILE */
