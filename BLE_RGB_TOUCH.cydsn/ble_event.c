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
#include "ble_event.h"
#include "RGB.h"
#include "slider.h"

void Ble_ProcessGattWriteEvent(void* eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T* writeReqParam;
    CYBLE_GATT_ERR_CODE_T errorCode;
    writeReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T*)eventParam;
    // write RGB daa
    if (writeReqParam->handleValPair.attrHandle == CYBLE_RGB_LED_RGB_DATA_CHAR_HANDLE)
    {
        RGB_SetHue(*((PHUEVALUE)writeReqParam->handleValPair.value.val));
        errorCode = CyBle_GattsWriteAttributeValue(&(writeReqParam->handleValPair), 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
        // send response if no error
        if (errorCode == CYBLE_GATT_ERR_NONE)
            CyBle_GattsWriteRsp(cyBle_connHandle);
    }   
    
    // change RGB notification status
    if (writeReqParam->handleValPair.attrHandle == CYBLE_RGB_LED_RGB_DATA_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE)
    {
        errorCode = CyBle_GattsWriteAttributeValue(&(writeReqParam->handleValPair), 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);        
        if (0 == (writeReqParam->handleValPair.value.val [CYBLE_RGB_LED_RGB_DATA_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX]))
        {
            RGB_DisableNotification();  
        }                        
        else if (1 == (writeReqParam->handleValPair.value.val [CYBLE_RGB_LED_RGB_DATA_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX]))
        {
            RGB_EnableNotification(); 
        }               
        else if (4 <= (writeReqParam->handleValPair.value.val [CYBLE_RGB_LED_RGB_DATA_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX]))
        {
            //Invalid PDU, stop notifications
            RGB_DisableNotification(); 
                        
            //Inform the user that they are being stupid
            CYBLE_GATTS_ERR_PARAM_T error_param;
            error_param.opcode = CYBLE_GATT_WRITE_REQ;
            error_param.attrHandle = writeReqParam->handleValPair.attrHandle;
            error_param.errorCode = 0x04;
            //Send Error Response 
            (void)CyBle_GattsErrorRsp(cyBle_connHandle, &error_param);
                        
        }
        // send response if no error
        if (errorCode == CYBLE_GATT_ERR_NONE)
            CyBle_GattsWriteRsp(cyBle_connHandle);
    }   
    // change CAPSENSE notification status
    if (writeReqParam->handleValPair.attrHandle == CYBLE_CAPSLIDER_SLIDER_POS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE)
    {
        errorCode = CyBle_GattsWriteAttributeValue(&(writeReqParam->handleValPair), 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);        
        if (0 == (writeReqParam->handleValPair.value.val [CYBLE_CAPSLIDER_SLIDER_POS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX]))
        {
            Slider_DisableNotification();  
        }                        
        else if (1 == (writeReqParam->handleValPair.value.val [CYBLE_CAPSLIDER_SLIDER_POS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX]))
        {
            Slider_EnableNotification(); 
        }               
        else if (4 <= (writeReqParam->handleValPair.value.val [CYBLE_CAPSLIDER_SLIDER_POS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX]))
        {
            //Invalid PDU, stop notifications
            Slider_DisableNotification(); 
                        
            //Inform the user that they are being stupid
            CYBLE_GATTS_ERR_PARAM_T error_param;
            error_param.opcode = CYBLE_GATT_WRITE_REQ;
            error_param.attrHandle = writeReqParam->handleValPair.attrHandle;
            error_param.errorCode = 0x04;
            //Send Error Response 
            (void)CyBle_GattsErrorRsp(cyBle_connHandle, &error_param);
                        
        }
        if (errorCode == CYBLE_GATT_ERR_NONE)
            CyBle_GattsWriteRsp(cyBle_connHandle);
    }
}

void Ble_ProcessGappDisconnectedEvent()
{
    CYBLE_GATT_HANDLE_VALUE_PAIR_T attrConfiguration;
    uint16 notifyValue = 0;
    attrConfiguration.attrHandle = CYBLE_RGB_LED_RGB_DATA_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE;
    attrConfiguration.value.len = sizeof(uint16);
    attrConfiguration.value.val = (uint8*)(&notifyValue);
    CyBle_GattsWriteAttributeValue(&attrConfiguration, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    attrConfiguration.attrHandle = CYBLE_CAPSLIDER_SLIDER_POS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE;
    CyBle_GattsWriteAttributeValue(&attrConfiguration, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
    // disable all the notification
    RGB_DisableNotification();
    Slider_DisableNotification();
    // write notification status
}


/* [] END OF FILE */
