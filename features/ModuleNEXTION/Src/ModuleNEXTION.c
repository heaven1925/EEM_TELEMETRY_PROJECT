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

#include "ModuleNEXTION_private.h"

/************************** DEFINES ********************************************/
#define	MODULENEXTION_MAIN_THREAD

ModuleNEXTION_MAIN_State_et ModuleNEXTION_MAIN_State = ModuleNEXTION_MAIN_State_IDLE;

#if 1	/* Init Functions */

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void ModuleNEXTION_HWInit(void)
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
void ModuleNEXTION_SWInit(void)
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
void ModuleNEXTION_StartUP(void)
{
	ModuleNEXTION_HWInit();
	ModuleNEXTION_SWInit();
}


#endif


#if 1	/* Application Functions */


#endif


#ifdef MODULENEXTION_MAIN_THREAD

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleNEXTION_MAIN_Routine(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleNEXTION_MAIN_Process(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleNEXTION_MAIN(void)
{
	switch(ModuleNEXTION_MAIN_State)
	{
	    case ModuleNEXTION_MAIN_State_IDLE:
	    	//@INFO: IDLE Operations ..
	    	ModuleNEXTION_MAIN_State = ModuleNEXTION_MAIN_State_ROUTINE;
	    break;

	    case ModuleNEXTION_MAIN_State_ROUTINE:

	    	ModuleNEXTION_MAIN_Routine();
	    break;

	    case ModuleNEXTION_MAIN_State_PROCESS:

	    	ModuleNEXTION_MAIN_Process();

	    break;

	    case ModuleNEXTION_MAIN_State_SUSPEND:
	    	ModuleNEXTION_MAIN_State = ModuleNEXTION_MAIN_State_IDLE;
	    break;

	    default:
	    	ModuleNEXTION_MAIN_State = ModuleNEXTION_MAIN_State_SUSPEND;
	    break;

	}

}


#endif

