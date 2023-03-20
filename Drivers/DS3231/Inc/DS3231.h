#ifndef DS3231_H_
#define DS3231_H_


/*******************INCLUDES************************/

#include "stdarg.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "stdint.h"

#include "stm32f4xx_hal.h"

/*******************DEFINES*************************/

#define   DS3231_ADRESS      0xD0



typedef struct __packed{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;
}time_st;


typedef struct {
	I2C_HandleTypeDef  hi2c;
	time_st			   time;
	char 			   timeBuffer[15];
	char 			   dateBuffer[15];
}ds3231_obj;


typedef struct
{
	void  	 (*setTime)(ds3231_obj* obj);
	time_st  (*getTime)(ds3231_obj* obj);
	void	 (*printTime)(ds3231_obj* obj);
	void	 (*printDate)(ds3231_obj* obj);
}ds3231_ops;


#if defined(DEBUG_MODE)

typedef struct
{
	UART_HandleTypeDef huart;
	uint16_t TimeOut;
	char txDebug[15];

}ds3231_dbg_obj;

typedef struct
{
	void (*DEBUG_TX)(ds3231_dbg_obj* obj,ds3231_obj * object);

}ds3231_dbg_ops;


typedef struct
{
	ds3231_dbg_obj obj;
	ds3231_dbg_ops ops;
}ds3231_dbg;


void DEBUG_TX(ds3231_dbg_obj* obj,ds3231_obj * object);

#endif


typedef struct
{
	ds3231_obj 	obj;
	ds3231_ops ops;
#if defined(DEBUG_MODE)
	ds3231_dbg	debug;
#endif
}ds3231_st;

/*******************FUNCTIONS DECLARATION*************************/


void CTOR_DS3231(ds3231_st* param , I2C_HandleTypeDef _hi2c, ds3231_ops _ops, time_st* _time, UART_HandleTypeDef _huart );
#if defined(DEBUG_MODE)
void DEBUG_CTOR(ds3231_dbg * param , UART_HandleTypeDef _huart,ds3231_dbg_ops _ops);
#endif
void 	setTime(ds3231_obj* obj);
time_st getTime(ds3231_obj* obj);
void 	printTime(ds3231_obj* obj);
void 	printDate(ds3231_obj* obj);


/*******************EXTERN VARIABLES *************************/

extern const ds3231_ops  ops ;


#if defined(DEBUG_MODE)
extern const ds3231_dbg_ops dbg_ops;
#endif

#endif  /* DS3231_H_ */

 
