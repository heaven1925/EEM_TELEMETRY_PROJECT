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
#include "types.h"

#include "DS3231.h"

/************************** DEFINES ********************************************/
#define	MODULERTC_MAIN_THREAD

ModuleRTC_MAIN_State_et ModuleRTC_MAIN_State = ModuleRTC_MAIN_State_IDLE;

ds3231_st ds3231={0};

time_st timeTemp;

time_st iniTime={.seconds=10,.minutes=10,.hour=10,.dayofweek=10,.dayofmonth=10,.month=10,.year=10};

decToBcd_ut  bcdFormat;


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

	CTOR_DS3231(&ds3231,
			      hi2c1,
			        ops,
			    &iniTime,
				 huart2);


	//@INFO: RTC thread'ine ait donanımsal init fonksiyonları
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO	  :
********************************************************************************/
void ModuleRTC_SWInit(void)
{

	ds3231.ops.setTime(&ds3231.obj,&bcdFormat);

	//@INFO: RTC thread'ine ait yazilimsal init fonksiyonları
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
	 @INFO	  :
********************************************************************************/

void ModuleRTC_MAIN_Routine(void)
{

	//@BACK @BACK @BACK

    uint8_t*rtcPtrGL=(uint8_t*)&__GL.rtc.main;
    uint8_t*rtcPtr=(uint8_t*)&timeTemp;

    timeTemp=ds3231.ops.getTime(&ds3231.obj,&bcdFormat);


    for(int i=0;i<sizeof(timeTemp);i++)
    {
     *rtcPtrGL=*rtcPtr;
      rtcPtr++;
      rtcPtrGL++;
    }

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

