/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleSDCard_definition.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil SDCard Module
********************************************************************************/

#ifndef __SD_CARD_MODULE_DEFINITION_H__
#define	__SD_CARD_MODULE_DEFINITION_H__

	
	
/*********************** INCLUDES **********************************************/

#include "types.h"


/*********************** DEFINES ***********************************************/
typedef enum
{
        ModuleSDCard_MAIN_State_IDLE = 0,
		ModuleSDCard_MAIN_State_ROUTINE ,
		ModuleSDCard_MAIN_State_PROCESS ,
		ModuleSDCard_MAIN_State_SUSPEND ,

}ModuleSDCard_MAIN_State_et;



typedef enum
{
	ModuleSDCard_ROUTINE_State_WRITE  = 0,
	ModuleSDCard_ROUTINE_State_READ      ,

}ModuleSDCard_ROUTINE_State_et;


	

/********************** FUNCTION PROTOTYPE **************************************/	
	

	
	
	
	
#endif /*__SD_CARD_MODULE_DEFINITION_H__*/

/*********************** END OF FILE ********************************************/
















































