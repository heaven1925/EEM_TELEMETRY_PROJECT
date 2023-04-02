#ifndef DS3231_H_
#define DS3231_H_


/*******************INCLUDES************************/

#include "stdarg.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

#include "stm32f4xx_hal.h"

/*******************DEFINES*************************/



typedef struct {
	UART_HandleTypeDef  huart;
	char   nxTımeout;
	char   txCommand[20];
	char   txBuffCmd[20];
}nextion_obj;


typedef struct
{
	void  	 (*sendCmd)(nextion_obj * obj,char*cmd,bool status);
	void     (*sendNum)(nextion_obj * obj,char*cmd,uint16_t num);

}nextion_ops;


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
	nextion_obj obj;
	nextion_ops ops;
#if defined(DEBUG_MODE)
	nextion_dbg	debug;
#endif
}nextion_St;

/*******************FUNCTIONS DECLARATION*************************/


void CTOR_nextion(nextion_St* param , UART_HandleTypeDef _huart, nextion_ops _ops);
#if defined(DEBUG_MODE)
void DEBUG_CTOR(ds3231_dbg * param , UART_HandleTypeDef _huart,ds3231_dbg_ops _ops);
#endif
void sendCmd(nextion_obj*obj , char*cmd, bool status);
void sendNum(nextion_obj* obj , char*cmd , uint16_t num);


/*******************EXTERN VARIABLES *************************/


extern const nextion_ops nexOps;

#if defined(DEBUG_MODE)
extern const ds3231_dbg_ops dbg_ops;
#endif

#endif  /* DS3231_H_ */


