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

#include "ModuleCAN_private.h"

/************************** DEFINES ********************************************/
#define	MODULECAN_MAIN_THREAD

ModuleCAN_MAIN_State_et ModuleCAN_MAIN_State = ModuleCAN_MAIN_State_IDLE;


#if 1	/* Init Functions */

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void ModuleCAN_HWInit(void)
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
void ModuleCAN_SWInit(void)
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
void ModuleCAN_StartUP(void)
{
	ModuleCAN_HWInit();
	ModuleCAN_SWInit();
}


#endif


#if 1	/* Application Functions */


#endif


#ifdef MODULECAN_MAIN_THREAD

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleCAN_MAIN_Routine(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleCAN_MAIN_Process(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleCAN_MAIN(void)
{
	ModuleCAN_StartUP();


		switch(ModuleCAN_MAIN_State)
		{
		    case ModuleCAN_MAIN_State_IDLE:
		    	//@INFO: IDLE Operations ..
		    	ModuleCAN_MAIN_State = ModuleCAN_MAIN_State_ROUTINE;
		    break;

		    case ModuleCAN_MAIN_State_ROUTINE:

		    	ModuleCAN_MAIN_Routine();
		    break;

		    case ModuleCAN_MAIN_State_PROCESS:

		    	ModuleCAN_MAIN_Process();

		    break;

		    case ModuleCAN_MAIN_State_SUSPEND:
		    	ModuleCAN_MAIN_State = ModuleCAN_MAIN_State_IDLE;
		    break;

		    default:
		    	ModuleCAN_MAIN_State = ModuleCAN_MAIN_State_SUSPEND;
		    break;

		}

}


#endif

