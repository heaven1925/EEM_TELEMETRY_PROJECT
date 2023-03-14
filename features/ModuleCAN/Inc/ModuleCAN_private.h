/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleCAN_private.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __CAN_MODULE_PRIVATE_H__
#define	__CAN_MODULE_PRIVATE_H__

	
	
/*********************** INCLUDES **********************************************/

#include "ModuleCAN_definition.h"

#include "ModuleNEXTION_public.h"
#include "ModuleRTC_public.h"
#include "ModuleSDCard_public.h"
#include "TelemetryMAIN_public.h"
#include "ModuleWIFI_public.h"



/*********************** DEFINES ***********************************************/


	
	
/********************** FUNCTION PROTOTYPE **************************************/	
	
 void ModuleCAN_HWInit(void);
 void ModuleCAN_SWInit(void);
 void ModuleCAN_MAIN_Process(void);
 void ModuleCAN_MAIN_Routine(void);

 //@INFO: Public function, private decleration
 void ModuleCAN_StartUP(void);
 void ModuleCAN_MAIN(void);
	
	
	

#endif /*__CAN_MODULE_PRIVATE_H__ */	

/*********************** END OF FILE ********************************************/
















































