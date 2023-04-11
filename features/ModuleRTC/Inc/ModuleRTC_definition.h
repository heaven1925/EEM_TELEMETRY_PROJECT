/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleRTC_definition.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __RTC_MODULE_DEFINITION_H__
#define	__RTC_MODULE_DEFINITION_H__

	
	
/*********************** INCLUDES **********************************************/
#include <stdint.h>



/*********************** DEFINES ***********************************************/
typedef enum
{
	ModuleRTC_MAIN_State_IDLE = 0,
	ModuleRTC_MAIN_State_ROUTINE ,
	ModuleRTC_MAIN_State_PROCESS ,
	ModuleRTC_MAIN_State_SUSPEND ,

}ModuleRTC_MAIN_State_et;


typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;

}ModuleRTC_MAIN_st;
	
	
/********************** FUNCTION PROTOTYPE **************************************/	
	

	
	
	
	
#endif /*__RTC_MODULE_DEFINITION_H__ */	

/*********************** END OF FILE ********************************************/
















































