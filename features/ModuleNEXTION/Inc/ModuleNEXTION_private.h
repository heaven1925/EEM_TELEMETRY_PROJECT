/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleRF_private.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __NEXTION_MODULE_PRIVATE_H__
#define	__NEXTION_MODULE_PRIVATE_H__

	
	
/*********************** INCLUDES **********************************************/

#include "ModuleNEXTION_definition.h"

#include "ModuleRTC_public.h"
#include "ModuleSDCard_public.h"
#include "ModuleCAN_public.h"
#include "TelemetryMAIN_public.h"
#include "ModuleWIFI_public.h"


/*********************** DEFINES ***********************************************/



/********************** FUNCTION PROTOTYPE **************************************/	
	
 void ModuleNEXTION_HWInit(void);
 void ModuleNEXTION_SWInit(void);
 void ModuleNEXTION_MAIN_Process(void);
 void ModuleNEXTION_MAIN_Routine(void);

 //@INFO: Public function, private decleration
 void ModuleNEXTION_StartUP(void);
 void ModuleNEXTION_MAIN(void)	;
	

#endif /*__NEXTION_MODULE_PRIVATE_H__ */	

/*********************** END OF FILE ********************************************/
