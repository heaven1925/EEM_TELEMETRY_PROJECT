
#include "DS3231.h"



static int bcdToDec(uint8_t val);

#if defined(DEBUG_MODE)

const ds3231_dbg_ops dbg_ops =
{
	DEBUG_TX
};

#endif

const ds3231_ops  ops =
{
		setTime ,
		getTime ,
		printTime ,
		printDate ,
};


#if defined(DEBUG_MODE)

void DEBUG_CTOR(ds3231_dbg * param , UART_HandleTypeDef _huart,ds3231_dbg_ops _ops)
{
	param->ops = _ops;

	param->obj.huart = _huart;

	param->obj.TimeOut=1000;

	memset(&param->obj.txDebug[0],0x00,sizeof(param->obj.txDebug));



}
#endif




void CTOR_DS3231(ds3231_st* param , I2C_HandleTypeDef _hi2c, ds3231_ops _ops, time_st* _time, UART_HandleTypeDef _huart)
{

#if defined(DEBUG_MODE)

	 DEBUG_CTOR(&param->debug, _huart , dbg_ops);


#endif

	param->ops = _ops;

	param->obj.hi2c = _hi2c;

	memcpy(&param->obj.time , _time , sizeof(time_st));

	memset(&param->obj.dateBuffer[0] , 0x00 , sizeof(param->obj.dateBuffer) );
	memset(&param->obj.timeBuffer[0] , 0x00 , sizeof(param->obj.timeBuffer) );
}


void setTime(ds3231_obj* obj)
{
	uint8_t setTime[7];

	memcpy( &setTime[0] , (uint8_t*)&obj->time.seconds , 7 );

	HAL_I2C_Mem_Write(&obj->hi2c , DS3231_ADRESS, 0x00, 1, (uint8_t*)&setTime[0], 7, 1000);
}


time_st getTime(ds3231_obj* obj)
{

	HAL_I2C_Mem_Read(&obj->hi2c, DS3231_ADRESS, 0x00, 1, (uint8_t*)&obj->time.seconds , 7, 1000);

	for(uint8_t loopVal = 0 ; loopVal <= sizeof(time_st) ; loopVal++)
	{
		*( &obj->time.seconds + loopVal ) =  bcdToDec( *( &obj->time.seconds + loopVal ) );
	}

	return obj->time;

}


void printTime(ds3231_obj* obj)
{
	sprintf(&obj->timeBuffer[0], "%02d:%02d:%02d:", obj->time.seconds ,
			                                        obj->time.minutes,
			                                        obj->time.seconds);
}


void printDate(ds3231_obj* obj)
{
	sprintf(&obj->dateBuffer[0], "%02d:%02d:%04d:", obj->time.dayofweek ,
				                                    obj->time.month,
				                                    obj->time.year );
}


// Convert binary coded decimal to normal decimal numbers
static int bcdToDec(uint8_t val)
{
  return (int)( (val/16*10) + (val%16) );
}

/* uint8_t decToBcd(int val)
{
  return (uint8_t)( (val/10*16) + (val%10) );
}*/


#if defined(DEBUG_MODE)

void DEBUG_TX(ds3231_dbg_obj* obj,ds3231_obj * object)
{
	printTime(object);
    sprintf(&obj->txDebug[0],"%s",object->timeBuffer);
	HAL_UART_Transmit(&obj->huart,(uint8_t*)object->timeBuffer,sizeof(obj->txDebug),obj->TimeOut);

	HAL_Delay(1000);

	printDate(object);
	sprintf(&obj->txDebug[0],"%s",object->dateBuffer);
    HAL_UART_Transmit(&obj->huart,(uint8_t*)object->dateBuffer,sizeof(obj->txDebug),obj->TimeOut);


}

#endif

