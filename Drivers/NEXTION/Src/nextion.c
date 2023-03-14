
#include "nextion.h"


const nextion_ops nexOps =
{
		sendCmd   ,
		sendNum   ,

};




#if defined(DEBUG_MODE)

const ds3231_dbg_ops dbg_ops =
{
	DEBUG_TX
};

#endif



#if defined(DEBUG_MODE)

void DEBUG_CTOR(ds3231_dbg * param , UART_HandleTypeDef _huart,ds3231_dbg_ops _ops)
{
	param->ops = _ops;

	param->obj.huart = _huart;

	param->obj.TimeOut=1000;

	memset(&param->obj.txDebug[0],0x00,sizeof(param->obj.txDebug));



}
#endif




void CTOR_nextion(nextion_St* param , UART_HandleTypeDef _huart, nextion_ops _ops)
{

#if defined(DEBUG_MODE)

	 DEBUG_CTOR(&param->debug, _huart , dbg_ops);


#endif

	param->ops = _ops;

	param->obj.huart=_huart;


	memset(&param->obj.txCommand , 0x00 , sizeof(param->obj.txCommand));

}


void sendCmd(nextion_obj*obj , char*cmd)
{
	char lastCmd[3] = {0xFF,0xFF,0xFF};

	memcpy(&obj->txCommand[0],cmd,strlen(cmd));


	HAL_UART_Transmit(&obj->huart, (uint8_t*)obj->txCommand, sizeof(obj->txCommand), obj->nxTımeout);

	HAL_UART_Transmit(&obj->huart, (uint8_t*)lastCmd, sizeof(obj->txCommand), obj->nxTımeout);
}


void sendNum(nextion_obj* obj , char*cmd , uint16_t num)
{
	char lastCmd[3] = {0xFF,0xFF,0xFF};

	char cmdCpy[15];

	memcpy(&obj->txCommand[0],cmd,strlen(cmd));


	sprintf(cmdCpy,"%s=%d",obj->txCommand,num);


	HAL_UART_Transmit(&obj->huart, (uint8_t*)cmdCpy, sizeof(obj->txCommand), obj->nxTımeout);

	HAL_UART_Transmit(&obj->huart, (uint8_t*)lastCmd, sizeof(obj->txCommand), obj->nxTımeout);

}

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

