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

#include "ModuleRTC_private.h"

/************************** DEFINES ********************************************/
#define	MODULERTC_MAIN_THREAD

ModuleRTC_MAIN_State_et ModuleRTC_MAIN_State = ModuleRTC_MAIN_State_IDLE;


#if 1	/* Init Functions */

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void ModuleRTC_HWInit(void)
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
void ModuleRTC_SWInit(void)
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
void ModuleRTC_StartUP(void)
{
	ModuleRTC_HWInit();
	ModuleRTC_SWInit();
}


#endif


#if 1	/* Application Functions */


#endif


#ifdef MODULERTC_MAIN_THREAD

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleRTC_MAIN_Routine(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleRTC_MAIN_Process(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleRTC_MAIN(void)
{
	switch(ModuleRTC_MAIN_State)
	{
	    case ModuleRTC_MAIN_State_IDLE:
	    	//@INFO: IDLE Operations ..
	    	ModuleRTC_MAIN_State = ModuleRTC_MAIN_State_ROUTINE;
	    break;

	    case ModuleRTC_MAIN_State_ROUTINE:

	    	ModuleRTC_MAIN_Routine();
	    break;

	    case ModuleRTC_MAIN_State_PROCESS:

	    	ModuleRTC_MAIN_Process();

	    break;

	    case ModuleRTC_MAIN_State_SUSPEND:
	    	ModuleRTC_MAIN_State = ModuleRTC_MAIN_State_IDLE;
	    break;

	    default:
	    	ModuleRTC_MAIN_State = ModuleRTC_MAIN_State_SUSPEND;
	    break;

	}
}


#endif

