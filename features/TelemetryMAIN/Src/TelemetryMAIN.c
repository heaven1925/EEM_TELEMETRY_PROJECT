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

#include "TelemetryMAIN_private.h"
#include "types.h"

/************************** DEFINES ********************************************/
#define	TELEMETRY_MAIN_THREAD

TelemetryMain_MAIN_State_et TelemetryMain_MAIN_State = TelemetryMain_MAIN_State_IDLE;



#if 1 /* Protocol Base Functions */





#endif


#if 1	/* Init Functions */

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void TelemetryMain_HWInit(void)
{
	//@INFO: Telemetry thread'ine ait donanımsal init fonksiyonları
	/*@LATER: Rf Adaptor Constructor here */
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void TelemetryMain_SWInit(void)
{
	//@INFO: Telemetry thread'ine ait yazilimsal init fonksiyonları
	//EEM_RFProtocol_CTOR(&__GL.main.protocol);
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void TelemetryMain_StartUP(void)
{
	TelemetryMain_HWInit();
	TelemetryMain_SWInit();
}


#endif


#if 1	/* Application Functions */


#endif


#ifdef TELEMETRY_MAIN_THREAD

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void TelemetryMain_MAIN_Routine(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void TelemetryMain_MAIN_Process(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void TelemetyMain_MAIN(void)
{

	switch(TelemetryMain_MAIN_State)
	{
	    case TelemetryMain_MAIN_State_IDLE:
	    	//@INFO: IDLE Operations ..
	    	TelemetryMain_MAIN_State = TelemetryMain_MAIN_State_ROUTINE;
	    break;

	    case TelemetryMain_MAIN_State_ROUTINE:

	    	TelemetryMain_MAIN_Routine();

	    break;

	    case TelemetryMain_MAIN_State_PROCESS:

	    	TelemetryMain_MAIN_Process();

	    break;

	    case TelemetryMain_MAIN_State_SUSPEND:
	    	TelemetryMain_MAIN_State = TelemetryMain_MAIN_State_IDLE;
	    break;

	    default:
	    	TelemetryMain_MAIN_State = TelemetryMain_MAIN_State_SUSPEND;
	    break;

	}

}


#endif

