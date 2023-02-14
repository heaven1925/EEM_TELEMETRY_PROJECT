/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

/************************** INCLUDES *******************************************/

#include "ModuleSDCard_private.h"

/************************** DEFINES ********************************************/
#define	MODULESDCARD_MAIN_THREAD

ModuleSDCard_MAIN_State_et ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_IDLE;


#if 1	/* Init Functions */

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void ModuleSDCard_HWInit(void)
{
	//@INFO: WIFI thread'ine ait donanımsal init fonksiyonları
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleSDCard_SWInit(void)
{
	//@INFO: WIFI thread'ine ait yazilimsal init fonksiyonları
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleSDCard_StartUP(void)
{
	ModuleSDCard_HWInit();
	ModuleSDCard_SWInit();
}


#endif


#if 1	/* Application Functions */


#endif


#ifdef MODULESDCARD_MAIN_THREAD

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleSDCard_MAIN_Routine(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleSDCard_MAIN_Process(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleSDCard_MAIN(void)
{
	switch(ModuleSDCard_MAIN_State)
	{
	    case ModuleSDCard_MAIN_State_IDLE:
	    	//@INFO: IDLE Operations ..
	    	ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_ROUTINE;
	    break;

	    case ModuleSDCard_MAIN_State_ROUTINE:

	    	ModuleSDCard_MAIN_Routine();
	    break;

	    case ModuleSDCard_MAIN_State_PROCESS:

	    	ModuleSDCard_MAIN_Process();

	    break;

	    case ModuleSDCard_MAIN_State_SUSPEND:
	    	ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_IDLE;
	    break;

	    default:
	    	ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_SUSPEND;
	    break;

	}

}


#endif

