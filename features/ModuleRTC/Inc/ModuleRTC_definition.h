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


typedef struct __attribute__((__packed__))
{
	uint8_t seconds;	 	/* 1 */
	uint8_t minutes;		/* 1 */
	uint8_t hour;           /* 1 */
	uint8_t dayofweek;      /* 1 */
	uint8_t dayofmonth;     /* 1 */
	uint8_t month;          /* 1 */
	uint8_t year;           /* 1 */

}ModuleRTC_MAIN_st;
	
	
/********************** FUNCTION PROTOTYPE **************************************/	
	

	
	
	
	
#endif /*__RTC_MODULE_DEFINITION_H__ */	

/*********************** END OF FILE ********************************************/
















































