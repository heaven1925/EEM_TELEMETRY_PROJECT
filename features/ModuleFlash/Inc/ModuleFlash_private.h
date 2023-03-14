/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleFlash_private.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __FLASH_MODULE_PRIVATE_H__
#define	__FLASH_MODULE_PRIVATE_H__

	
	
/*********************** INCLUDES **********************************************/

#include "ModuleFlash_definition.h"

#include "ModuleRTC_public.h"
#include "ModuleSDCard_public.h"
#include "ModuleCAN_public.h"
#include "TelemetryMAIN_public.h"
#include "ModuleWIFI_public.h"
#include "ModuleNEXTION_public.h"


/*********************** DEFINES ***********************************************/


	
	
/********************** FUNCTION PROTOTYPE **************************************/	

 void ModuleFlash_HWInit(void);
 void ModuleFlash_SWInit(void);
 void ModuleFlash_MAIN_Process(void);
 void ModuleFlash_MAIN_Routine(void);

 //@INFO: Public function, private decleration
 void ModuleFlash_StartUP(void);
 void ModuleFlash_MAIN(void);
	
	
	
	
#endif /*__FLASH_MODULE_PRIVATE_H__ */	

/*********************** END OF FILE ********************************************/
















































