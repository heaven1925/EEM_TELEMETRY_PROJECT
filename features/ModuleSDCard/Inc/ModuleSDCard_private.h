/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleSDCard_private.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __SD_CARD_MODULE_PRIVATE_H__
#define	__SD_CARD_MODULE_PRIVATE_H__

	
	
/*********************** INCLUDES **********************************************/

#include "ModuleSDCard_definition.h"

#include "ModuleNEXTION_public.h"
#include "ModuleRTC_public.h"
#include "ModuleCAN_public.h"
#include "TelemetryMAIN_public.h"
#include "ModuleWIFI_public.h"


/*********************** DEFINES ***********************************************/


	
	
/********************** FUNCTION PROTOTYPE **************************************/	
	
 void ModuleSDCard_HWInit(void);
 void ModuleSDCard_SWInit(void);
 void ModuleSDCard_MAIN_Process(void);
 void ModuleSDCard_MAIN_Routine(void);

 //@INFO: Public function, private decleration
 void ModuleSDCard_StartUP(void);
 void ModuleSDCard_MAIN(void);
	
	
	
	
#endif /*__SD_CARD_MODULE_PRIVATE_H__ */	

/*********************** END OF FILE ********************************************/
















































