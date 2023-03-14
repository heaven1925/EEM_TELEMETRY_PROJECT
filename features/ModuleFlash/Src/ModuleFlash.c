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

#include "ModuleFLASH_private.h"
#include "ee.h"

/************************** DEFINES ********************************************/
#define	MODULEFLASH_MAIN_THREAD

ModuleFlash_MAIN_State_et ModuleFlash_MAIN_State = ModuleFlash_MAIN_State_IDLE;


#if 1	/* Init Functions */

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void ModuleFlash_HWInit(void)
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
void ModuleFlash_SWInit(void)
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
void ModuleFlash_StartUP(void)
{
	ModuleFlash_HWInit();
	ModuleFlash_SWInit();
}


#endif


#if 1	/* Application Functions */


#endif


#ifdef MODULEFLASH_MAIN_THREAD

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleFlash_MAIN_Routine(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleFlash_MAIN_Process(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleFlash_MAIN(void)
{

	switch(ModuleFlash_MAIN_State)
	{
	    case ModuleFlash_MAIN_State_IDLE:
	    	//@INFO: IDLE Operations ..
	    	ModuleFlash_MAIN_State = ModuleFlash_MAIN_State_ROUTINE;
	    break;

	    case ModuleFlash_MAIN_State_ROUTINE:

	    	ModuleFlash_MAIN_Routine();
	    break;

	    case ModuleFlash_MAIN_State_PROCESS:

	    	ModuleFlash_MAIN_Process();

	    break;

	    case ModuleFlash_MAIN_State_SUSPEND:
	    	ModuleFlash_MAIN_State = ModuleFlash_MAIN_State_IDLE;
	    break;

	    default:
	    	ModuleFlash_MAIN_State = ModuleFlash_MAIN_State_SUSPEND;
	    break;

	}

}


#endif

