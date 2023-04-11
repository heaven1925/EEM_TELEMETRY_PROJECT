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

#include "ModuleWIFI_private.h"
#include "types.h"

/************************** DEFINES ********************************************/
#define	MODULEWIFI_MAIN_THREAD

ModuleWIFI_MAIN_State_et ModuleWIFI_MAIN_State = ModuleWIFI_MAIN_State_IDLE;


#if 1	/* Init Functions */

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void ModuleWIFI_HWInit(void)
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
void ModuleWIFI_SWInit(void)
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
void ModuleWIFI_StartUP(void)
{
	ModuleWIFI_HWInit();
	ModuleWIFI_SWInit();
}


#endif


#if 1	/* Application Functions */


#endif


#ifdef MODULEWIFI_MAIN_THREAD

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleWIFI_MAIN_Routine(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleWIFI_MAIN_Process(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleWIFI_MAIN(void)
{
	switch(ModuleWIFI_MAIN_State)
	{
	    case ModuleWIFI_MAIN_State_IDLE:
	    	//@INFO: IDLE Operations ..
	    	ModuleWIFI_MAIN_State = ModuleWIFI_MAIN_State_ROUTINE;
	    break;

	    case ModuleWIFI_MAIN_State_ROUTINE:

	    	ModuleWIFI_MAIN_Routine();
	    break;

	    case ModuleWIFI_MAIN_State_PROCESS:

	    	ModuleWIFI_MAIN_Process();

	    break;

	    case ModuleWIFI_MAIN_State_SUSPEND:
	    	ModuleWIFI_MAIN_State = ModuleWIFI_MAIN_State_IDLE;
	    break;

	    default:
	    	ModuleWIFI_MAIN_State = ModuleWIFI_MAIN_State_SUSPEND;
	    break;

	}
}


#endif

