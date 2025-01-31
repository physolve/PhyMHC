#include "ICPDAS_USBIO.h"


#ifdef __cplusplus
extern "C" {
#endif

_EXP_ICPDAS_USBIO BYTE __stdcall ListDevice(WORD* o_wDID, BYTE* o_byBID);
_EXP_ICPDAS_USBIO int __stdcall ScanDevice(void);

_EXP_ICPDAS_USBIO ICPDAS_USBIO* __stdcall CreateInstance();
_EXP_ICPDAS_USBIO void __stdcall DisposeInstance(ICPDAS_USBIO* pInstance);

// SYSTEM
_EXP_ICPDAS_USBIO int __stdcall OpenDevice(ICPDAS_USBIO* pInstance, WORD wUSBIO_DID, BYTE byUSBIO_BID);
_EXP_ICPDAS_USBIO int __stdcall CloseDevice(ICPDAS_USBIO* pInstance);
_EXP_ICPDAS_USBIO int __stdcall SYNCDevice(ICPDAS_USBIO* pInstance);
_EXP_ICPDAS_USBIO int __stdcall SetCommTimeout(ICPDAS_USBIO* pInstance, DWORD i_dwCommTimeout);
_EXP_ICPDAS_USBIO int __stdcall GetCommTimeout(ICPDAS_USBIO* pInstance, DWORD* o_dwCommTimeout);
_EXP_ICPDAS_USBIO int __stdcall SetAutoResetWDT(ICPDAS_USBIO* pInstance, BOOL i_bEnable);

// DEVICE (Get)
_EXP_ICPDAS_USBIO int __stdcall RefreshDeviceInfo(ICPDAS_USBIO* pInstance);
_EXP_ICPDAS_USBIO int __stdcall GetSoftWDTTimeout(ICPDAS_USBIO* pInstance, DWORD* o_dwSoftWDTTimeout);
_EXP_ICPDAS_USBIO int __stdcall GetDeviceID(ICPDAS_USBIO* pInstance, DWORD* o_dwDeviceID);
_EXP_ICPDAS_USBIO int __stdcall GetFwVer(ICPDAS_USBIO* pInstance, WORD* o_wFwVer);
_EXP_ICPDAS_USBIO int __stdcall GetDeviceNickName(ICPDAS_USBIO* pInstance, BYTE* o_byDeviceNickName);
_EXP_ICPDAS_USBIO int __stdcall GetDeviceSN(ICPDAS_USBIO* pInstance, BYTE* o_byDeviceSN);
_EXP_ICPDAS_USBIO int __stdcall GetSupportIOMask(ICPDAS_USBIO* pInstance, BYTE* o_bySupportIOMask);
_EXP_ICPDAS_USBIO int __stdcall GetDITotal(ICPDAS_USBIO* pInstance, BYTE* o_byDITotal);
_EXP_ICPDAS_USBIO int __stdcall GetDOTotal(ICPDAS_USBIO* pInstance, BYTE* o_byDOTotal);
_EXP_ICPDAS_USBIO int __stdcall GetAITotal(ICPDAS_USBIO* pInstance, BYTE* o_byAITotal);
_EXP_ICPDAS_USBIO int __stdcall GetAOTotal(ICPDAS_USBIO* pInstance, BYTE* o_byAOTotal);
_EXP_ICPDAS_USBIO int __stdcall GetPITotal(ICPDAS_USBIO* pInstance, BYTE* o_byPITotal);
_EXP_ICPDAS_USBIO int __stdcall GetPOTotal(ICPDAS_USBIO* pInstance, BYTE* o_byPOTotal);
// DEVICE (Set)
_EXP_ICPDAS_USBIO int __stdcall SetUserDefinedBoardID(ICPDAS_USBIO* pInstance, BYTE i_byBID);
_EXP_ICPDAS_USBIO int __stdcall SetDeviceNickName(ICPDAS_USBIO* pInstance, BYTE* i_byDeviceNickName);
_EXP_ICPDAS_USBIO int __stdcall SetSoftWDTTimeout(ICPDAS_USBIO* pInstance, DWORD i_dwSoftWDTTimeout);
_EXP_ICPDAS_USBIO int __stdcall LoadDefault(ICPDAS_USBIO* pInstance);

// CALLBACK REGISTRATION
_EXP_ICPDAS_USBIO int __stdcall RegisterEmergencyPktEventHandle(ICPDAS_USBIO* pInstance,
                                              OnEmergencyPktArriveEvent i_evtHandle);
// Get DO configuration and data
_EXP_ICPDAS_USBIO int __stdcall DO_GetPowerOnEnable(ICPDAS_USBIO* pInstance, BYTE* o_byPowerOnEnable);
_EXP_ICPDAS_USBIO int __stdcall DO_GetSafetyEnable(ICPDAS_USBIO* pInstance, BYTE* o_bySafetyEnable);
_EXP_ICPDAS_USBIO int __stdcall DO_GetSafetyValue(ICPDAS_USBIO* pInstance, BYTE* o_bySafetyValue);
_EXP_ICPDAS_USBIO int __stdcall DO_GetDigitalOutputInverse(ICPDAS_USBIO* pInstance, DWORD* o_dwInverse);
_EXP_ICPDAS_USBIO int __stdcall DO_ReadValue(ICPDAS_USBIO* pInstance, BYTE* o_byDOValue);
// Set DO configuration and data
_EXP_ICPDAS_USBIO int __stdcall DO_SetPowerOnEnable(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, BYTE i_byPowerOnEnable);
_EXP_ICPDAS_USBIO int __stdcall DO_SetPowerOnEnables(ICPDAS_USBIO* pInstance, BYTE* i_byPowerOnEnables);
_EXP_ICPDAS_USBIO int __stdcall DO_SetSafetyEnable(ICPDAS_USBIO* pInstance, BYTE* i_bySafetyEnable);
_EXP_ICPDAS_USBIO int __stdcall DO_SetSafetyValue(ICPDAS_USBIO* pInstance, BYTE* i_bySafetyValue);
_EXP_ICPDAS_USBIO int __stdcall DO_SetDigitalOutputInverse(ICPDAS_USBIO* pInstance, DWORD i_dwInverse);
_EXP_ICPDAS_USBIO int __stdcall DO_WriteValue(ICPDAS_USBIO* pInstance, BYTE* i_byDOValue);
_EXP_ICPDAS_USBIO int __stdcall DO_WriteChannelValue(ICPDAS_USBIO* pInstance, BYTE i_byChannel, BYTE i_byValue);

// Get DI configuration and data
_EXP_ICPDAS_USBIO int __stdcall DI_GetDigitalFilterWidth(ICPDAS_USBIO* pInstance, WORD* o_wFilterWidth);
_EXP_ICPDAS_USBIO int __stdcall DI_GetDigitalValueInverse(ICPDAS_USBIO* pInstance, DWORD* o_dwInverse);
_EXP_ICPDAS_USBIO int __stdcall DI_GetCntEdgeTrigger(ICPDAS_USBIO* pInstance, DWORD* o_dwEdgeTrig);
_EXP_ICPDAS_USBIO int __stdcall DI_ReadValue(ICPDAS_USBIO* pInstance, BYTE* o_byDIValue);
_EXP_ICPDAS_USBIO int __stdcall DI_ReadCounterValue(ICPDAS_USBIO* pInstance, DWORD* o_dwDICntValue);
// Set DI configuration and data
_EXP_ICPDAS_USBIO int __stdcall DI_SetDigitalFilterWidth(ICPDAS_USBIO* pInstance, WORD i_wFilterWidth);
_EXP_ICPDAS_USBIO int __stdcall DI_SetDigitalValueInverse(ICPDAS_USBIO* pInstance, DWORD i_dwInverse);
_EXP_ICPDAS_USBIO int __stdcall DI_SetCntEdgeTrigger(ICPDAS_USBIO* pInstance, DWORD i_dwEdgeTrig);
_EXP_ICPDAS_USBIO int __stdcall DI_WriteClearCounter(ICPDAS_USBIO* pInstance, BYTE i_byChToClr);
_EXP_ICPDAS_USBIO int __stdcall DI_WriteClearCounters(ICPDAS_USBIO* pInstance, DWORD i_dwCntClrMask);

// Get AI configuration and data
_EXP_ICPDAS_USBIO int __stdcall AI_GetTotalSupportType( ICPDAS_USBIO* pInstance, BYTE* o_byTotalSupportType );
_EXP_ICPDAS_USBIO int __stdcall AI_GetSupportTypeCode( ICPDAS_USBIO* pInstance, BYTE* o_bySupportTypeCode );
_EXP_ICPDAS_USBIO int __stdcall AI_GetTypeCode(ICPDAS_USBIO* pInstance, BYTE* o_byTypeCode);
_EXP_ICPDAS_USBIO int __stdcall AI_GetChCJCOffset(ICPDAS_USBIO* pInstance, float* o_fChCJCOffset);
_EXP_ICPDAS_USBIO int __stdcall AI_GetChEnable(ICPDAS_USBIO* pInstance, BYTE* o_byChEnable);
//_EXP_ICPDAS_USBIO int __stdcall AI_GetDataFormat(ICPDAS_USBIO* pInstance, BYTE* o_byDataFormat);
_EXP_ICPDAS_USBIO int __stdcall AI_GetFilterRejection(ICPDAS_USBIO* pInstance, BYTE* o_byFilterRejection);
_EXP_ICPDAS_USBIO int __stdcall AI_GetCJCOffset(ICPDAS_USBIO* pInstance, float* o_fCJCOffset);
_EXP_ICPDAS_USBIO int __stdcall AI_GetCJCEnable(ICPDAS_USBIO* pInstance, BYTE* o_byCJCEnable);
_EXP_ICPDAS_USBIO int __stdcall AI_GetWireDetectEnable(ICPDAS_USBIO* pInstance, BYTE* o_byWireDetectEnable);
_EXP_ICPDAS_USBIO int __stdcall AI_GetResolution(ICPDAS_USBIO* pInstance, BYTE* o_byResolution);
_EXP_ICPDAS_USBIO int __stdcall AI_ReadValueDigital(ICPDAS_USBIO* pInstance, DWORD* o_dwAIValue);
_EXP_ICPDAS_USBIO int __stdcall AI_ReadValueDigitalWithChSta(ICPDAS_USBIO* pInstance, DWORD* o_dwAIValue, BYTE* o_byAIChStatus);
_EXP_ICPDAS_USBIO int __stdcall AI_ReadValueAnalog(ICPDAS_USBIO* pInstance, float* o_fAIValue);
_EXP_ICPDAS_USBIO int __stdcall AI_ReadValueAnalogWithChSta(ICPDAS_USBIO* pInstance, float* o_fAIValue, BYTE* o_byAIChStatus);
_EXP_ICPDAS_USBIO int __stdcall AI_ReadBulkValue(ICPDAS_USBIO* pInstance,
                               BYTE i_byStartCh,
                               BYTE i_byChTotal,
                               DWORD i_dwSampleWidth,
                               float i_fSampleRate,
                               DWORD i_dwBufferWidth,
                               DWORD* o_dwDataBuffer,
                               OnBulkValueFinishEvent i_CBFunc);
_EXP_ICPDAS_USBIO int __stdcall AI_ReadCJCValue(ICPDAS_USBIO* pInstance, float* o_fCJCValue);
_EXP_ICPDAS_USBIO int __stdcall AI_GetChSampleRate(ICPDAS_USBIO* pInstance, DWORD* i_dwSampleRate);


// Set AI configuration
_EXP_ICPDAS_USBIO int __stdcall AI_SetTypeCode(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, BYTE i_byTypeCode);
_EXP_ICPDAS_USBIO int __stdcall AI_SetTypeCodes(ICPDAS_USBIO* pInstance, BYTE* i_byTypeCodes);
_EXP_ICPDAS_USBIO int __stdcall AI_SetChCJCOffset(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, float i_fChCJCOffset);
_EXP_ICPDAS_USBIO int __stdcall AI_SetChCJCOffsets(ICPDAS_USBIO* pInstance, float* i_fChCJCOffsets);
_EXP_ICPDAS_USBIO int __stdcall AI_SetChEnable(ICPDAS_USBIO* pInstance, BYTE* i_byChEnable);
//_EXP_ICPDAS_USBIO int __stdcall AI_SetDataFormat(ICPDAS_USBIO* pInstance, BYTE i_byDataFormat);
_EXP_ICPDAS_USBIO int __stdcall AI_SetFilterRejection(ICPDAS_USBIO* pInstance, BYTE i_byFilterRejection);
_EXP_ICPDAS_USBIO int __stdcall AI_SetCJCOffset(ICPDAS_USBIO* pInstance, float i_fCJCOffset);
_EXP_ICPDAS_USBIO int __stdcall AI_SetCJCEnable(ICPDAS_USBIO* pInstance, BYTE i_byCJCEnable);
_EXP_ICPDAS_USBIO int __stdcall AI_SetWireDetectEnable(ICPDAS_USBIO* pInstance, BYTE i_byWireDetectEnable);
_EXP_ICPDAS_USBIO int __stdcall AI_SetChSampleRate(ICPDAS_USBIO* pInstance, DWORD* i_dwSampleRate);
// Get AO configuration and data
_EXP_ICPDAS_USBIO int __stdcall AO_GetTotalSupportType( ICPDAS_USBIO* pInstance, BYTE* o_byTotalSupportType );
_EXP_ICPDAS_USBIO int __stdcall AO_GetSupportTypeCode( ICPDAS_USBIO* pInstance, BYTE* o_bySupportTypeCode );
_EXP_ICPDAS_USBIO int __stdcall AO_GetTypeCode( ICPDAS_USBIO* pInstance, BYTE* o_byTypeCode );
_EXP_ICPDAS_USBIO int __stdcall AO_GetChEnable( ICPDAS_USBIO* pInstance, BYTE* o_byChEnable );
_EXP_ICPDAS_USBIO int __stdcall AO_GetResolution( ICPDAS_USBIO* pInstance, BYTE* o_byResolution);
_EXP_ICPDAS_USBIO int __stdcall AO_ReadExpValueDigital( ICPDAS_USBIO* pInstance, DWORD* o_dwAOExpValue );
_EXP_ICPDAS_USBIO int __stdcall AO_ReadExpValueAnalog( ICPDAS_USBIO* pInstance, float* o_fAOExpValue );
_EXP_ICPDAS_USBIO int __stdcall AO_ReadCurValueDigital( ICPDAS_USBIO* pInstance, DWORD* o_dwAOCurValue );
_EXP_ICPDAS_USBIO int __stdcall AO_ReadCurValueAnalog( ICPDAS_USBIO* pInstance, float* o_fAOCurValue );
_EXP_ICPDAS_USBIO int __stdcall AO_GetPowerOnEnable( ICPDAS_USBIO* pInstance, BYTE* o_byPowerOnEnable );
_EXP_ICPDAS_USBIO int __stdcall AO_GetSafetyEnable( ICPDAS_USBIO* pInstance, BYTE* o_bySafetyEnable );
_EXP_ICPDAS_USBIO int __stdcall AO_GetPowerOnValueDigital(ICPDAS_USBIO* pInstance, DWORD* o_dwPwrOnValue);
_EXP_ICPDAS_USBIO int __stdcall AO_GetPowerOnValueAnalog(ICPDAS_USBIO* pInstance, float* o_fPwrOnValue);
_EXP_ICPDAS_USBIO int __stdcall AO_GetSafetyValueDigital(ICPDAS_USBIO* pInstance, DWORD* o_dwSafetyValue);
_EXP_ICPDAS_USBIO int __stdcall AO_GetSafetyValueAnalog(ICPDAS_USBIO* pInstance, float* o_fSafetyValue);
_EXP_ICPDAS_USBIO int __stdcall AO_GetSlewRate(ICPDAS_USBIO* pInstance, BYTE* o_bySlewRate);
// Set AO configuration and data
_EXP_ICPDAS_USBIO int __stdcall AO_SetTypeCode( ICPDAS_USBIO* pInstance, BYTE i_byChToSet, BYTE i_byTypeCode );
_EXP_ICPDAS_USBIO int __stdcall AO_SetTypeCodes( ICPDAS_USBIO* pInstance, BYTE* i_byTypeCodes );
_EXP_ICPDAS_USBIO int __stdcall AO_SetChEnable( ICPDAS_USBIO* pInstance, BYTE* i_byChEnable );
_EXP_ICPDAS_USBIO int __stdcall AO_WriteChannelValueDigital( ICPDAS_USBIO* pInstance, BYTE i_byChToSet, DWORD i_dwAOVal );
_EXP_ICPDAS_USBIO int __stdcall AO_WriteValueDigital( ICPDAS_USBIO* pInstance, DWORD* i_dwAOValue );
								
_EXP_ICPDAS_USBIO int __stdcall AO_WriteChannelValueAnalog( ICPDAS_USBIO* pInstance, BYTE i_byChToSet, float i_fAOExpValue );
_EXP_ICPDAS_USBIO int __stdcall AO_WriteValueAnalog( ICPDAS_USBIO* pInstance, float* i_fAOExpValue );
_EXP_ICPDAS_USBIO int __stdcall AO_SetPowerOnEnable( ICPDAS_USBIO* pInstance, BYTE* i_byPowerOnEnable );
_EXP_ICPDAS_USBIO int __stdcall AO_SetSafetyEnable( ICPDAS_USBIO* pInstance, BYTE* i_bySafetyEnable );
_EXP_ICPDAS_USBIO int __stdcall AO_SetPowerOnValueDigital(ICPDAS_USBIO* pInstance, DWORD* i_dwPwrOnValue);
_EXP_ICPDAS_USBIO int __stdcall AO_SetPowerOnChannelValueDigital(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, DWORD i_dwPwrOnValue);
_EXP_ICPDAS_USBIO int __stdcall AO_SetPowerOnValueAnalog(ICPDAS_USBIO* pInstance, float* i_fPwrOnValue);
_EXP_ICPDAS_USBIO int __stdcall AO_SetPowerOnChannelValueAnalog(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, float i_fPwrOnValue);
_EXP_ICPDAS_USBIO int __stdcall AO_SetSafetyValueDigital(ICPDAS_USBIO* pInstance, DWORD* i_dwSafetyValue);
_EXP_ICPDAS_USBIO int __stdcall AO_SetSafetyChannelValueDigital(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, DWORD i_dwSafetyValue);
_EXP_ICPDAS_USBIO int __stdcall AO_SetSafetyValueAnalog(ICPDAS_USBIO* pInstance, float* i_fSafetyValue);
_EXP_ICPDAS_USBIO int __stdcall AO_SetSafetyChannelValueAnalog(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, float i_fSafetyValue);
_EXP_ICPDAS_USBIO int __stdcall AO_SetSlewRate(ICPDAS_USBIO* pInstance, BYTE* i_bySlewRate);

// Get PI configuration and data
_EXP_ICPDAS_USBIO int __stdcall PI_GetTotalSupportType( ICPDAS_USBIO* pInstance, BYTE* o_byTotalSupportType );
_EXP_ICPDAS_USBIO int __stdcall PI_GetSupportTypeCode( ICPDAS_USBIO* pInstance, BYTE* o_bySupportTypeCode );
_EXP_ICPDAS_USBIO int __stdcall PI_GetTypeCode(ICPDAS_USBIO* pInstance, BYTE* o_byTypeCode);
_EXP_ICPDAS_USBIO int __stdcall PI_GetTriggerMode(ICPDAS_USBIO* pInstance, BYTE* o_byTriggerMode);
_EXP_ICPDAS_USBIO int __stdcall PI_GetChIsolatedFlag(ICPDAS_USBIO* pInstance, BYTE* o_byChIsolatedFlag);
_EXP_ICPDAS_USBIO int __stdcall PI_GetLPFilterEnable(ICPDAS_USBIO* pInstance, BYTE* o_byLPFilterEnable);
_EXP_ICPDAS_USBIO int __stdcall PI_GetLPFilterWidth(ICPDAS_USBIO* pInstance, WORD* o_wLPFilterWidth);
_EXP_ICPDAS_USBIO int __stdcall PI_ReadValue(ICPDAS_USBIO* pInstance, DWORD* o_dwCntValue, BYTE* o_byChStatus);
_EXP_ICPDAS_USBIO int __stdcall PI_ReadCntValue(ICPDAS_USBIO* pInstance, DWORD* o_dwCntValue, BYTE* o_byChStatus);
_EXP_ICPDAS_USBIO int __stdcall PI_ReadFreqValue(ICPDAS_USBIO* pInstance, float* o_fFreqValue, BYTE* o_byChStatus);
_EXP_ICPDAS_USBIO int __stdcall PI_ReadBulkValue(ICPDAS_USBIO* pInstance,
                               BYTE i_byStartCh,
                               BYTE i_byChTotal,
                               DWORD i_dwSampleWidth,
                               float i_fSampleRate,
                               DWORD i_dwBufferWidth,
                               DWORD* o_dwDataBuffer,
                               OnBulkValueFinishEvent i_CBFunc);
// Set PI configuration
_EXP_ICPDAS_USBIO int __stdcall PI_SetTypeCode(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, BYTE i_byTypeCode);
_EXP_ICPDAS_USBIO int __stdcall PI_SetTypeCodes(ICPDAS_USBIO* pInstance, BYTE* i_byTypeCodes);
_EXP_ICPDAS_USBIO int __stdcall PI_ClearSingleChCount(ICPDAS_USBIO* pInstance, BYTE i_byChToClr);
_EXP_ICPDAS_USBIO int __stdcall PI_ClearChCount(ICPDAS_USBIO* pInstance, BYTE* i_byClrMask);
_EXP_ICPDAS_USBIO int __stdcall PI_ClearSingleChStatus(ICPDAS_USBIO* pInstance, BYTE i_byChToClr);
_EXP_ICPDAS_USBIO int __stdcall PI_ClearChStatus(ICPDAS_USBIO* pInstance, BYTE* i_byClrMask);

//int __stdcall PI_ClearAllChCount(ICPDAS_USBIO* pInstance);
_EXP_ICPDAS_USBIO int __stdcall PI_SetTriggerMode(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, BYTE i_byTriggerMode);
_EXP_ICPDAS_USBIO int __stdcall PI_SetTriggerModes(ICPDAS_USBIO* pInstance, BYTE* i_byTriggerModes);
_EXP_ICPDAS_USBIO int __stdcall PI_SetChIsolatedFlag(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, BOOL i_bChIsolatedFlag);
_EXP_ICPDAS_USBIO int __stdcall PI_SetChIsolatedFlags(ICPDAS_USBIO* pInstance, BYTE* i_byChIsolatedFlag);
_EXP_ICPDAS_USBIO int __stdcall PI_SetLPFilterEnable(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, BOOL i_bLPFilterEnable);
_EXP_ICPDAS_USBIO int __stdcall PI_SetLPFilterEnables(ICPDAS_USBIO* pInstance, BYTE* i_byLPFilterEnables);
_EXP_ICPDAS_USBIO int __stdcall PI_SetLPFilterWidth(ICPDAS_USBIO* pInstance, BYTE i_byChToSet, WORD i_wLPFilterWidth);
_EXP_ICPDAS_USBIO int __stdcall PI_SetLPFilterWidths(ICPDAS_USBIO* pInstance, WORD* i_wLPFilterWidths);

#ifdef __cplusplus
}
#endif