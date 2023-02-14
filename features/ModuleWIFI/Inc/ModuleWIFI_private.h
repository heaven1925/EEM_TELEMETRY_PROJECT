/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleWIFI_private.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __WIFI_MODULE_PRIVATE_H__
#define	__WIFI_MODULE_PRIVATE_H__

	
	
/*********************** INCLUDES **********************************************/

#include "ModuleWIFI_definition.h"

#include "ModuleNEXTION_public.h"
#include "ModuleRTC_public.h"
#include "ModuleSDCard_public.h"
#include "ModuleCAN_public.h"
#include "TelemetryMAIN_public.h"



/*********************** DEFINES ***********************************************/


	
	
/********************** FUNCTION PROTOTYPE **************************************/	
	
 void ModuleWIFI_HWInit(void);
 void ModuleWIFI_SWInit(void);
 void ModuleWIFI_MAIN_Process(void);
 void ModuleWIFI_MAIN_Routine(void);

 //@INFO: Public function, private decleration
 void ModuleWIFI_StartUP(void);
 void ModuleWIFI_MAIN(void)	;
	
	
#endif /*__WIFI_MODULE_PRIVATE_H__ */	

/*********************** END OF FILE ********************************************/
