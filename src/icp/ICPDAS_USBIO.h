/**
 * @file ICPDAS_USBIO.h
 *
 * 
 *
 * @author DukeYang
 *
 * 
 */

#ifdef ICPDAS_USBIO_EXPORTS
#define _EXP_ICPDAS_USBIO __declspec(dllexport)
#else
#define _EXP_ICPDAS_USBIO __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C" {
#endif
void  Log(char *msg );
//extern _EXP_ICPDAS_USBIO BYTE __stdcall ListDevice(WORD* o_wDID, BYTE* o_byBID);
//extern _EXP_ICPDAS_USBIO int __stdcall ScanDevice(void);

#define USBIO_MAX_SUPPORT_TYPE 50
#define USBIO_DO_MAX_CHANNEL 32
#define USBIO_DI_MAX_CHANNEL 32
#define USBIO_AI_MAX_CHANNEL 16
#define USBIO_AO_MAX_CHANNEL 16
#define USBIO_PI_MAX_CHANNEL 16
#define USBIO_NICKNAME_LENGTH 32
#define USBIO_SN_LENGTH 32

#define USBIO_MAX_PACKET_LENGTH 1024
#define USBIO_HEADER_LENGTH 10

#define SUPPORT_DO(SupportMask) ((SupportMask & 0x1) > 0)
#define SUPPORT_DI(SupportMask) ((SupportMask & 0x2) > 0)
#define SUPPORT_AO(SupportMask) ((SupportMask & 0x4) > 0)
#define SUPPORT_AI(SupportMask) ((SupportMask & 0x8) > 0)
#define SUPPORT_PO(SupportMask) ((SupportMask & 0x10) > 0)
#define SUPPORT_PI(SupportMask) ((SupportMask & 0x20) > 0)
  
typedef struct USBIO_DO_Info_St
{
  BYTE  PowerOnEnable[USBIO_DO_MAX_CHANNEL];
  BYTE  PowerOnValue[(USBIO_DO_MAX_CHANNEL + 7) / 8];
  BYTE  SafetyEnable[(USBIO_DO_MAX_CHANNEL + 7) / 8];
  BYTE  SafetyValue[(USBIO_DO_MAX_CHANNEL + 7) / 8];
  DWORD DOOutputInverse;
}USBIO_DO_Info_St;

typedef struct USBIO_DI_Info_St
{
  WORD  DigitalFilterWidth;
  DWORD DIValueInverse;
  DWORD DICounterEdgeTrig;
}USBIO_DI_Info_St;

typedef struct USBIO_AI_Info_St
{
  BYTE  TotalSupportType;
  BYTE  SupportTypeCode[USBIO_MAX_SUPPORT_TYPE];
  float AITypeLowUpLimitTable[USBIO_MAX_SUPPORT_TYPE][2];
  float AIChLowUpLomit[USBIO_AI_MAX_CHANNEL][2];
  BYTE	TypeCode[USBIO_AI_MAX_CHANNEL];
  SHORT	ChCJCOffset[USBIO_AI_MAX_CHANNEL];
  BYTE	ChEnable[(USBIO_AI_MAX_CHANNEL + 7) / 8];
  BYTE	DataFormat;
  BYTE	FilterRejection;
  SHORT	CJCOffset;
  BYTE	CJCEnable;
  BYTE	WireDetectEnable;
  BYTE	Resolution[USBIO_AI_MAX_CHANNEL];
  DWORD ChSampleRate[USBIO_AI_MAX_CHANNEL];
}USBIO_AI_Info_St;

typedef struct USBIO_AO_Info_St
{
  BYTE  TotalSupportType;
  BYTE  SupportTypeCode[USBIO_MAX_SUPPORT_TYPE];
  BYTE	TypeCode[USBIO_AO_MAX_CHANNEL];
  BYTE	ChEnable[(USBIO_AO_MAX_CHANNEL + 7) / 8];
  BYTE	Resolution[USBIO_AO_MAX_CHANNEL];
  float AOTypeLowUpLimitTable[USBIO_MAX_SUPPORT_TYPE][2];
  float AOChLowUpLomit[USBIO_AO_MAX_CHANNEL][2];
  BYTE	WireDetectEnable;
  BYTE  PowerOnEnable[USBIO_AO_MAX_CHANNEL];
  DWORD PowerOnValue[USBIO_AO_MAX_CHANNEL];
  BYTE  SafetyEnable[(USBIO_AO_MAX_CHANNEL + 7) / 8];
  DWORD SafetyValue[USBIO_AO_MAX_CHANNEL];
  BYTE  SlewRate[USBIO_AO_MAX_CHANNEL];
}USBIO_AO_Info_St;

typedef struct USBIO_PI_Info_St
{
  BYTE  TotalSupportType;
  BYTE  SupportTypeCode[USBIO_MAX_SUPPORT_TYPE];
  BYTE	TypeCode[USBIO_PI_MAX_CHANNEL];
  BYTE	TriggerMode[USBIO_PI_MAX_CHANNEL];
  BYTE  ChIsolatedFlag[(USBIO_PI_MAX_CHANNEL + 7) / 8];
  BYTE	LPFilterEnable[(USBIO_PI_MAX_CHANNEL + 7) / 8];
  WORD	LPFilterWidth[USBIO_PI_MAX_CHANNEL];
}USBIO_PI_Info_St;

typedef void (*OnBulkValueFinishEvent)(DWORD dwCount);
typedef void (*OnEmergencyPktArriveEvent)(BYTE* byData, BYTE byLen);



/**
 * @brief ICPDAS_USBIO class
 *
 * 
 */
class _EXP_ICPDAS_USBIO ICPDAS_USBIO {
  // Constructor and Destructor
public:
  ICPDAS_USBIO(void);
  virtual ~ICPDAS_USBIO(){};

  // Members
public:
	BOOL m_bDeviceOpened;
private:
  // For callback
  BYTE m_byNormalPkt[USBIO_MAX_PACKET_LENGTH];
  BYTE m_byNormalPktArrive;
  WORD m_wCurrentAccessObj;
  HANDLE hLogPIPktThread;
  HANDLE hLogAIPktThread;
  HANDLE hDevMonitorThread;

  // For device monitor
  BOOL m_bStopDevMonitorThread;
  BOOL m_bAutoRstWDT;
  DWORD m_dwLastCmdTime;

  // For bulk data (Log)
  LPVOID m_byActivePkt;
  DWORD m_dwActivePktIn;
  DWORD m_dwActivePktOut;

  OnEmergencyPktArriveEvent onEmergencyPktEventHandle;

  // Flag
  
  BYTE m_bySupportIOMask;
  BOOL m_bDeviceComm;

  // System information
  LPVOID USB_DEV;
  USBIO_DO_Info_St DO_Info;
  USBIO_DI_Info_St DI_Info;
  USBIO_AI_Info_St AI_Info;
  USBIO_AO_Info_St AO_Info;
  USBIO_PI_Info_St PI_Info;

  // Device information
  DWORD m_dwmsCommTimeout;
  DWORD m_dwmsSoftWDTTimeout;
  DWORD m_dwDeviceID;
  WORD m_wFwVer;
  BYTE m_byDeviceNickName[USBIO_NICKNAME_LENGTH];
  BYTE m_byDeviceSN[USBIO_SN_LENGTH];
  BYTE m_byBoardID;

  // IOs information
  BYTE m_byDITotal;
  BYTE m_byDOTotal;
  BYTE m_byAITotal;
  BYTE m_byAOTotal;
  BYTE m_byPITotal;
  BYTE m_byPOTotal;

  // Methods
private:
  int Write(BYTE* USBIO_wData, DWORD wData_Len);
  int Read(BYTE* USBIO_rData);
  int RefreshDO_Info(void);
  int RefreshDI_Info(void);
  int RefreshPI_Info(void);
  int RefreshAI_Info(void);
  int RefreshAO_Info(void);
  int USBIO_Send_Recv(BYTE* i_bySend, WORD wData_Len, BYTE* o_byRecv);
  int PingDevice(WORD i_wUSBIO_DID, BYTE i_byUSBIO_BID);
  void VarInit(void);

public:
  // INTERNAL USE
  WORD GetCurrentAccessObj(void);
  void SetNormalPktByteArray(BYTE* byArray, WORD usLen);
  void SetActivePktByteArray(BYTE* byArray, WORD usLen);
  void ClearActivePktBuffer();
  void GetActivePktByteArray(BYTE** byArray, WORD* wLen);
  void SetNormalPktEvent(void);
  void StopDevMonitorThread();
  BOOL IsDevMonitorThreadStop();
  BOOL IsCommWithDevice();
  BOOL IsAutoResetWDT();
  DWORD GetLastCmdTime();

  // SYSTEM
  int OpenDevice(WORD i_wUSBIO_DID, BYTE i_byUSBIO_BID);
  int CloseDevice(void);
  int SYNCDevice(void);
  int SetCommTimeout(DWORD i_dwCommTimeout);
  int GetCommTimeout(DWORD* o_dwCommTimeout);
  int SetAutoResetWDT(BOOL i_bEnable);

  // DEVICE
  int RefreshDeviceInfo();
  // DEVICE (Get)
  int GetSoftWDTTimeout(DWORD* o_dwSoftWDTTimeout);
  int GetDeviceID(DWORD* o_dwDeviceID);
  int GetFwVer(WORD* o_wFwVer);
  int GetDeviceNickName(BYTE* o_byDeviceNickName);
  int GetDeviceSN(BYTE* o_byDeviceSN);
  int GetSupportIOMask(BYTE* o_bySupportIOMask);
  int GetDITotal(BYTE* o_byDITotal);
  int GetDOTotal(BYTE* o_byDOTotal);
  int GetAITotal(BYTE* o_byAITotal);
  int GetAOTotal(BYTE* o_byAOTotal);
  int GetPITotal(BYTE* o_byPITotal);
  int GetPOTotal(BYTE* o_byPOTotal);
  // DEVICE (Set)
  int SetUserDefinedBoardID(BYTE i_byBID);
  int SetDeviceNickName(BYTE* i_byDeviceNickName);
  int SetSoftWDTTimeout(DWORD i_dwSoftWDTTimeout);
  int LoadDefault();
  int StopBulk();

  // CALLBACK REGISTRATION
  int RegisterEmergencyPktEventHandle(OnEmergencyPktArriveEvent i_evtHandle);
  
  // Get DO configuration and data
  int DO_GetPowerOnEnable(BYTE* o_byPowerOnEnable);
  int DO_GetSafetyEnable(BYTE* o_bySafetyEnable);
  int DO_GetSafetyValue(BYTE* o_bySafetyValue);
  int DO_GetDigitalOutputInverse(DWORD* o_dwInverse);
  int DO_ReadValue(BYTE* o_byDOValue);
  // Set DO configuration and data
  int DO_SetPowerOnEnable(BYTE i_byChToSet, BYTE i_byPowerOnEnable);
  int DO_SetPowerOnEnable(BYTE* i_byPowerOnEnables);
  int DO_SetSafetyEnable(BYTE* i_bySafetyEnable);
  int DO_SetSafetyValue(BYTE* i_bySafetyValue);
  int DO_SetDigitalOutputInverse(DWORD i_dwInverse);
  int DO_WriteValue(BYTE* i_byDOValue);
  int DO_WriteValue(BYTE i_byChannel, BYTE i_byValue);

  // Get DI configuration and data
  int DI_GetDigitalFilterWidth(WORD* o_wFilterWidth);
  int DI_GetDigitalValueInverse(DWORD* o_dwInverse);
  int DI_GetCntEdgeTrigger(DWORD* o_dwEdgeTrig);
  int DI_ReadValue(BYTE* o_byDIValue);
  int DI_ReadCounterValue(DWORD* o_dwDICntValue);
  // Set DI configuration and data
  int DI_SetDigitalFilterWidth(WORD i_wFilterWidth);
  int DI_SetDigitalValueInverse(DWORD i_dwInverse);
  int DI_SetCntEdgeTrigger(DWORD i_dwEdgeTrig);
  int DI_WriteClearCounter(BYTE i_byChToClr);
  int DI_WriteClearCounters(DWORD i_dwCntClrMask);

  // Get AI configuration and data
  int AI_GetTotalSupportType(BYTE* o_byTotalSupportType);
  int AI_GetSupportTypeCode(BYTE* o_bySupportTypeCode);
  int AI_GetTypeCode(BYTE* o_byTypeCode);
  int AI_GetChCJCOffset(float* o_fChCJCOffset);
  int AI_GetChEnable(BYTE* o_byChEnable);
  int AI_GetFilterRejection(BYTE* o_byFilterRejection);
  int AI_GetCJCOffset(float* o_fCJCOffset);
  int AI_GetCJCEnable(BYTE* o_byCJCEnable);
  int AI_GetWireDetectEnable(BYTE* o_byWireDetectEnable);
  int AI_GetResolution(BYTE* o_byResolution);
  int AI_ReadValue(DWORD* o_dwAIValue);
  int AI_ReadValue(DWORD* o_dwAIValue, BYTE* o_byChStatus);
  int AI_ReadValue(float* o_fAIValue);
  int AI_ReadValue(float* o_fAIValue, BYTE* o_byChStatus);
  int AI_GetChSampleRate(DWORD* o_dwSample);
  int AI_ReadBulkValue(BYTE i_byStartCh,
                       BYTE i_byChTotal,
                       DWORD i_dwSampleWidth,
                       float i_fSampleRate,
                       DWORD i_dwBufferWidth,
                       DWORD* o_dwDataBuffer,
                       OnBulkValueFinishEvent i_CBFunc);
  int AI_ReadCJCValue(float* o_fCJCValue);
  // Set AI configuration
  int AI_SetTypeCode(BYTE i_byChToSet, BYTE i_byTypeCode);
  int AI_SetTypeCode(BYTE* i_byTypeCodes);
  int AI_SetChCJCOffset(BYTE i_byChToSet, float i_fChCJCOffset);
  int AI_SetChCJCOffset(float* i_fChCJCOffsets);
  int AI_SetChEnable(BYTE* i_byChEnable);
  int AI_SetFilterRejection(BYTE i_byFilterRejection);
  int AI_SetCJCOffset(float i_fCJCOffset);
  int AI_SetCJCEnable(BYTE i_byCJCEnable);
  int AI_SetWireDetectEnable(BYTE i_byWireDetectEnable);
  int AI_SetChSampleRate( DWORD* i_dwSample);
  // Get AO configuration and data
  int AO_GetTotalSupportType(BYTE* o_byTotalSupportType);
  int AO_GetSupportTypeCode(BYTE* o_bySupportTypeCode);
  int AO_GetTypeCode(BYTE* o_byTypeCode);
  int AO_GetChEnable(BYTE* o_byChEnable);
  /*int AO_GetWireDetectEnable(BYTE* o_byWireDetectEnable);*/
  int AO_GetResolution(BYTE* o_byResolution);
  int AO_ReadExpValue(DWORD* o_dwAOExpValue); 
  int AO_ReadExpValue(float* o_fAOExpValue); 
  int AO_ReadCurValue(DWORD* o_dwAOCurValue); 
  int AO_ReadCurValue(float* o_fAOCurValue); 
  int AO_GetPowerOnEnable( BYTE* o_byPowerOnEnable );
  int AO_GetSafetyEnable( BYTE* o_bySafetyEnable );
  int AO_GetPowerOnValue(DWORD* o_dwPwrOnValue);
  int AO_GetPowerOnValue(float* o_fPwrOnValue);
  int AO_GetSafetyValue(DWORD* o_dwSafetyValue);
  int AO_GetSafetyValue(float* o_fSafetyValue);
  int AO_GetSlewRate(BYTE* o_bySlewRate);
  //Set AO configuration and data
  int AO_SetTypeCode(BYTE i_byChToSet, BYTE i_byTypeCode);
  int AO_SetTypeCode(BYTE* i_byTypeCodes);
  int AO_SetChEnable(BYTE* i_byChEnable);
  int AO_WriteValue(BYTE i_byChToSet, DWORD i_dwAOVal); 
  int AO_WriteValue(DWORD* i_dwAOValue);   
  int AO_WriteValue(BYTE i_byChToSet, float i_fAOExpValue);
  int AO_WriteValue(float* i_fAOExpValue); 
  int AO_ValueTrim(BYTE i_byChToSet, WORD i_wTrimVal);
  int AO_SetPowerOnEnable( BYTE* i_byPowerOnEnable );// set all
  int AO_SetSafetyEnable( BYTE* i_bySafetyEnable );
  int AO_SetPowerOnValue(DWORD* i_dwPwrOnValue);
  int AO_SetPowerOnValue(BYTE i_byChToSet, DWORD i_dwPwrOnValue);
  int AO_SetPowerOnValue(float* i_fPwrOnValue);
  int AO_SetPowerOnValue(BYTE i_byChToSet, float i_fPwrOnValue);
  int AO_SetSafetyValue(DWORD* i_dwSafetyValue);
  int AO_SetSafetyValue(BYTE i_byChToSet, DWORD i_dwSafetyValue);
  int AO_SetSafetyValue(float* i_fSafetyValue);
  int AO_SetSafetyValue(BYTE i_byChToSet, float i_fSafetyValue);
  int AO_SetSlewRate(BYTE* i_bySlewRate);

  // Get PI configuration and data
  int PI_GetTotalSupportType(BYTE* o_byTotalSupportType);
  int PI_GetSupportTypeCode(BYTE* o_bySupportTypeCode);
  int PI_GetTypeCode(BYTE* o_byTypeCode);
  int PI_GetTriggerMode(BYTE* o_byTriggerMode);
  int PI_GetChIsolatedFlag(BYTE* o_byChIsolatedFlag);
  int PI_GetLPFilterEnable(BYTE* o_byLPFilterEnable);
  int PI_GetLPFilterWidth(WORD* o_wLPFilterWidth);
  int PI_ReadValue(DWORD* o_dwPIValue, BYTE* o_byChStatus);
  int PI_ReadCntValue(DWORD* o_dwCntValue, BYTE* o_byChStatus);
  int PI_ReadFreqValue(float* o_fFreqValue, BYTE* o_byChStatus);
  int PI_ReadBulkValue(BYTE i_byStartCh,
                       BYTE i_byChTotal,
                       DWORD i_dwSampleWidth,
                       float i_fSampleRate,
                       DWORD i_dwBufferWidth,
                       DWORD* o_dwDataBuffer,
                       OnBulkValueFinishEvent i_CBFunc);
  // Set PI configuration
  int PI_SetTypeCode(BYTE i_byChToSet, BYTE i_byTypeCode);
  int PI_SetTypeCode(BYTE* i_byTypeCodes);
  int PI_ClearChCount(BYTE* i_byClrMask);
  int PI_ClearSingleChCount(BYTE i_byChToClr);
  int PI_ClearChStatus(BYTE* i_byClrMask);
  int PI_ClearSingleChStatus(BYTE i_byChToClr);
  int PI_SetTriggerMode(BYTE i_byChToSet, BYTE i_byTriggerMode);
  int PI_SetTriggerMode(BYTE* i_byTriggerModes);
  int PI_SetChIsolatedFlag(BYTE i_byChToSet, BOOL i_bChIsolatedFlag);
  int PI_SetChIsolatedFlag(BYTE* i_byChIsolatedFlags);
  int PI_SetLPFilterEnable(BYTE i_byChToSet, BOOL i_bLPFilterEnable);
  int PI_SetLPFilterEnable(BYTE* i_byLPFilterEnables);
  int PI_SetLPFilterWidth(BYTE i_byChToSet, WORD i_wLPFilterWidth);
  int PI_SetLPFilterWidth(WORD* i_wLPFilterWidths);
};

/* USBIO Device-ID */
#define	USBIO_MINPID  0x0400
#define BiggerBoard   100
#define	USB2019       (USBIO_MINPID+19)
#define USB2026       (USBIO_MINPID+26)
#define	USB2045       (USBIO_MINPID+45)
#define	USB2051       (USBIO_MINPID+51)
#define	USB2055       (USBIO_MINPID+55)
#define	USB2060       (USBIO_MINPID+60)
#define	USB2064       (USBIO_MINPID+64)
#define USB2084       (USBIO_MINPID+84)
#define USB2055_32		 (USBIO_MINPID + BiggerBoard)
#define USB2068_18       (USBIO_MINPID + BiggerBoard + 1)
#define USB2045_32       (USBIO_MINPID + BiggerBoard + 2)
#define USB2051_32       (USBIO_MINPID + BiggerBoard + 3)
#define USB2060_24       (USBIO_MINPID + BiggerBoard + 4)
#define USB2064_16       (USBIO_MINPID + BiggerBoard + 5)
#define USB2069_18       (USBIO_MINPID + BiggerBoard + 6)


#define DEV_RETURN_ERR_CODE_BASE  0
#define DEVLIB_ERR_CODE_BASE      0x10000
#define IOLIB_ERR_CODE_BASE       0x10100

#define ERR_NO_ERR                0

/* USBDEV Error Codes */
#define ERR_USBDEV_INVALID_DEV      (DEVLIB_ERR_CODE_BASE + 0)
#define ERR_USBDEV_DEV_OPENED       (DEVLIB_ERR_CODE_BASE + 1)
#define ERR_USBDEV_DEVNOTEXISTS     (DEVLIB_ERR_CODE_BASE + 2)
#define ERR_USBDEV_GETDEVINFO       (DEVLIB_ERR_CODE_BASE + 3)
#define ERR_USBDEV_ERROR_PKTSIZE    (DEVLIB_ERR_CODE_BASE + 4)
#define ERR_USBDEV_ERROR_WRITEFILE  (DEVLIB_ERR_CODE_BASE + 5)

/* USBIO Error Codes */
#define ERR_USBIO_COMM_TIMEOUT      (IOLIB_ERR_CODE_BASE + 0)
#define ERR_USBIO_DEV_OPENED        (IOLIB_ERR_CODE_BASE + 1)
#define ERR_USBIO_DEV_NOTOPEN       (IOLIB_ERR_CODE_BASE + 2)
#define ERR_USBIO_INVALID_RESP      (IOLIB_ERR_CODE_BASE + 3)
#define ERR_USBIO_IO_NOTSUPPORT     (IOLIB_ERR_CODE_BASE + 4)
#define ERR_USBIO_PARA_ERROR        (IOLIB_ERR_CODE_BASE + 5)
#define ERR_USBIO_BULKVALUE_ERR     (IOLIB_ERR_CODE_BASE + 6)
#define ERR_USBIO_GETDEVINFO        (IOLIB_ERR_CODE_BASE + 7)

/* Channel Status */
#define CHSTA_GOOD            0
#define CHSTA_OVER            1
#define CHSTA_UNDER           2
#define CHSTA_OPEN            3
#define CHSTA_CLOSE           4
#define CHSTA_TYPENOTSUPPORT  5

#ifdef __cplusplus
}
#endif