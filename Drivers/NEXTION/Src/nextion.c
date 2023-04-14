
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


	memset(&param->obj.txCommand,0x00,sizeof(param->obj.txCommand));

	memset(&param->obj.txBuffCmd,0x00,sizeof(param->obj.txBuffCmd));

}


void sendCmd(nextion_obj*obj,char*cmd, bool status)
{
	char lastCmd[4] = {0xFF,0xFF,0xFF};

	memcpy(&obj->txCommand[0],cmd,strlen(cmd));

	sprintf(obj->txBuffCmd,"%s.val=%d",cmd,status); // MAKRO İLE SET RESET EDILECEK


	HAL_UART_Transmit(&obj->huart, (uint8_t*)obj->txBuffCmd, strlen(obj->txBuffCmd),obj->nxTımeout);

	HAL_UART_Transmit(&obj->huart, (uint8_t*)lastCmd, strlen(lastCmd), obj->nxTımeout);

	memset(obj->txCommand , 0x00 , sizeof(obj->txCommand));

    memset(obj->txBuffCmd,0x00,sizeof(obj->txBuffCmd));
}


void sendNum(nextion_obj* obj , char*cmd , uint16_t num)
{
	char lastCmd[4] = {0xFF,0xFF,0xFF};

	memcpy(&obj->txCommand[0],cmd,strlen(cmd));

	sprintf(obj->txBuffCmd,"%s.val=%d",cmd,num);

	HAL_UART_Transmit(&obj->huart, (uint8_t*)obj->txBuffCmd, sizeof(obj->txCommand), obj->nxTımeout);

	HAL_UART_Transmit(&obj->huart, (uint8_t*)lastCmd, sizeof(obj->txCommand), obj->nxTımeout);

	memset(obj->txCommand , 0x00 , sizeof(obj->txCommand));

    memset(obj->txBuffCmd,0x00,sizeof(obj->txBuffCmd));

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

