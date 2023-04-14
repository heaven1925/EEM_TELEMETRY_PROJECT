/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    TelemetryMAIN_private.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __TELEMETRY_MODULE_PRIVATE_H__
#define	__TELEMETRY_MODULE_PRIVATE_H__

	
	
/*********************** INCLUDES **********************************************/

#include "TelemetryMAIN_definition.h"

#include "ModuleNEXTION_public.h"
#include "ModuleRTC_public.h"
#include "ModuleSDCard_public.h"
#include "ModuleCAN_public.h"
#include "ModuleWIFI_public.h"


/*********************** DEFINES ***********************************************/


	
	
/********************** FUNCTION PROTOTYPE **************************************/	
	
//@INFO: Private Function Decleration
 void TelemetryMain_HWInit(void);
 void TelemetryMain_SWInit(void);
 void TelemetryMain_MAIN_Process(void);
 void TelemetryMain_MAIN_Routine(void);


//@INFO: Public function, private decleration
void TelemetryMain_StartUP(void);
void TelemetyMain_MAIN(void);	//@INFO: Main Thread Function


//@INFO: RF protocol Functions
tlm_err_t EEM_RFProtocol_CTOR(EEM_RFProtocol_st* self);
tlm_err_t EEM_RFProtocol_TX(EEM_RFProtocol_st* self , broadcastMode_Type mode/* @LATER: , typedef_rfAdaptor_device_st* dev */ );
tlm_err_t EEM_RFProtocol_RX(EEM_RFProtocol_st* self /* @LATER: , typedef_rfAdaptor_device_st* dev */ , );

tlm_err_t EEM_RFProtocol_CheckCRC(EEM_RFProtocol_st* self);
tlm_err_t EEM_RFProtocol_CheckTime(EEM_RFProtocol_st* self, ModuleRTC_MAIN_st* param);

EEM_RFProtocol_st EEM_RFProtocol_PrepareTxData(EEM_RFProtocol_st* self , ModuleRTC_MAIN_st* param /* @LATER */ );
EEM_RFProtocol_st EEM_RFProtocol_GetRxData(/* @LATER: , typedef_rfAdaptor_device_st* dev */ void/*@DEL*/);

#endif /*__TELEMETRY_MODULE_PRIVATE_H__ */	

/*********************** END OF FILE ********************************************/
















































