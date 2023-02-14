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
	
#endif /*__TELEMETRY_MODULE_PRIVATE_H__ */	

/*********************** END OF FILE ********************************************/
















































