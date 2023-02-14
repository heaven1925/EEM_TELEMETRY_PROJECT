/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleRTC_private.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __RTC_MODULE_PRIVATE_H__
#define	__RTC_MODULE_PRIVATE_H__

	
	
/*********************** INCLUDES **********************************************/

#include "ModuleRTC_definition.h"

#include "ModuleNEXTION_public.h"
#include "ModuleSDCard_public.h"
#include "ModuleCAN_public.h"
#include "TelemetryMAIN_public.h"
#include "ModuleWIFI_public.h"



/*********************** DEFINES ***********************************************/


	
	
/********************** FUNCTION PROTOTYPE **************************************/	
	
 void ModuleRTC_HWInit(void);
 void ModuleRTC_SWInit(void);
 void ModuleRTC_MAIN_Process(void);
 void ModuleRTC_MAIN_Routine(void);

 //@INFO: Public function, private decleration
 void ModuleRTC_StartUP(void);
 void ModuleRTC_MAIN(void);

	
	
	
	
#endif /*__RTC_MODULE_PRIVATE_H__ */	

/*********************** END OF FILE ********************************************/
















































