/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    sys_rfAdaptor.c
  * @author	 Muhammet EFE , Ata Aybars G�K, Atakan ERTEKiN
  * @version V1.0.0
  * @date		 02.08.2022
  * @rev     V1.0.0
  * @brief	 RF Adaptor, SX1262 ayarlamalarini icermektedir.
********************************************************************************/
/************************************DEFINES***********************************/
#define RFADAPTOR_MAIN

#define WMBUS_EN	//
#define LORA_EN	
//#define PC_EN	


/************************************INCLUDES***********************************/
#include "sys_rfAdaptor__private.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#if 1 //@INFO: RF Adaptor IRQ handler'lar
/********************START OF RFADAPTOR IRQ HANDLERS***************************/
/*******************************************************************************
	@func    : BTIM_IRQHandler
	@param   : rt_device_t dev, rt_size_t size
  @return  : void
  @date	   : 
  @INFO		 : Hardware timer callback fonksiyonu, Ayarlanan HW timer dolunca
						 bu kesmeye girilecektir.
						 ##############################################################
					   Time Server i�in kesmeye girelecegi zaman hesaplanip hesaplanan
						 s�re sonunda kesmeye girilecektir.
********************************************************************************/
err_t			HW_IRQHandler(device_t dev, size_t size){
		
		if(sys_adaptor_hwTimer != RT_NULL) device_close(sys_adaptor_hwTimer);
	
		SYS_RFADAPTOR_PARAM_RESET(SYS_RFADAPTOR_HWTIM);
		return RT_EOK;
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void 	sys_rfAdaptor_DioIsrHandler(void *param){

	err_t result = RT_EOK;	

	//@INFO: Irq s�reci tamamlandi animasyon yapilabilir.
	SYS_MAIN_RTOSFLAG_PARAM_SET(GENERAL_RTOSFLAG_ARROWANIMATION_EN);
	
	if( SYS_RF_STATUS_PARAM( sys_rfAdaptor_WMBUS ) || SYS_RF_STATUS_PARAM( sys_rfAdaptor_PC ) )
	{	
		#ifdef SX1262_EN	
		result = ( sys_rfAdaptor_irqHandlers.wmBus_irqHandler( typdef_rfAdaptor_dev.ops.GetIrqStatus() ) );	
		if( result != RT_EOK )	return;	
		#endif	/* SX1262_EN */
	}
	else
	{
		RadioOnDioIrq( RT_NULL ); 
		sys_lora_runCmdProcess();	
	}
	
}

#if 1 //@INFO: wmBus IRQ Handlers
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t sys_rfAdaptor_wmBusIRQHandler(uint16_t irqStatus){
	
	err_t result = RT_EOK;
	
	result = typdef_rfAdaptor_dev.ops.ClearIrqStatus( (RadioIrqMasks_t)irqStatus ) ;
	
	switch(irqStatus)
	{
		case	IRQ_TX_DONE :
			#ifndef DEBUG_RF
			rt_kprintf("WMBUS-TX DONE \n");	
		  #endif
			result = sys_rfAdaptor_irqHandlers.txDone_irqHandler() ;
		break;
		case	IRQ_RX_DONE :
			result = sys_rfAdaptor_irqHandlers.rxDone_irqHandler();
			#ifndef DEBUG_RF
			rt_kprintf("WMBUS-RX DONE \n");	
			#endif
		break;		
		case	IRQ_RX_TX_TIMEOUT :
			#ifndef DEBUG_RF
			rt_kprintf("WMBUS-RX/TX TIMEOUT \n");
			#endif
			result = sys_rfAdaptor_irqHandlers.timeOut_irqHandler();
		break;
		case	IRQ_PREAMBLE_DETECTED :
			#ifndef DEBUG_RF
			rt_kprintf("WMBUS-PREAMBLE DETECT \n");		
			#endif
			result = sys_rfAdaptor_irqHandlers.preambleDetected_irqHandler();
		break;
		case	IRQ_SYNCWORD_VALID :
			#ifndef DEBUG_RF
			rt_kprintf("WMBUS-SYNCWORD VALID \n");			
			#endif
			result = sys_rfAdaptor_irqHandlers.syncWordValid_irqHandler();
		break;
		case	IRQ_CRC_ERROR :
			#ifndef DEBUG_RF
			rt_kprintf("WMBUS-CRC ERROR \n");		
			#endif
			result = sys_rfAdaptor_irqHandlers.crcError_irqHandler();

		break;

		default:
			result = RT_ERROR;
		break;		
	}
	
	return result;

}




/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t sys_rfAdaptor_txDoneIRQHandler(void){
	
	err_t result = RT_EOK;
	
	if( SYS_RF_STATUS_PARAM( sys_rfAdaptor_WMBUS ) )
	{	//@INFO: TX-Done kesmesi WMBUS		
		if( !SYS_WMBUS_GENERAL_PARAM( SYS_WMBUS_GENERAL_RX_ECHO ) )
		{
			SYS_WMBUS_GENERAL_PARAM_SET(SYS_WMBUS_GENERAL_TX_DONE);
		}
		else
		{ //@INFO: Echo yayinin sonunda TX-DONE geldiyse,
			SYS_WMBUS_GENERAL_PARAM_SET(SYS_WMBUS_GENERAL_ECHOTX_DONE);
		}
	}
	else if(SYS_RF_STATUS_PARAM( sys_rfAdaptor_PC ))
	{
		SYS_RFMODE_PARAM_SET(SYS_RFMODE_BOOT_START_TX);
		SYS_RFMODE_PARAM_SET(SYS_RFMODE_BOOT_TXDONE);
	}
	else
	{
		result = RT_ERROR;
	}	
	
	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t sys_rfAdaptor_rxDoneIRQHandler(void){
	
	err_t result = RT_EOK;
	
	if( SYS_RF_STATUS_PARAM( sys_rfAdaptor_WMBUS ) )
	{	
		SYS_WMBUS_GENERAL_PARAM_SET(SYS_WMBUS_GENERAL_RX_DONE	 );			//@INFO: Rx alindi.	
	}
	else if(SYS_RF_STATUS_PARAM( sys_rfAdaptor_PC ))
	{
		SYS_RFMODE_PARAM_SET(SYS_RFMODE_BOOT_RXDONE);
	}
	else
	{
		result = RT_ERROR;
	}
	
	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t sys_rfAdaptor_timeOutIRQHandler(void){
	
	err_t result = RT_EOK;
	
	SYS_WMBUS_GENERAL_PARAM_SET( SYS_WMBUS_GENERAL_TIMEOUT );	
	
	sys_wmBus_sleep();	
			
	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t sys_rfAdaptor_preambleDetectedIRQHandler(void){
	err_t result = RT_EOK;
	
	//@INFO: Reserved for future
	
	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t sys_rfAdaptor_syncWordValidIRQHandler(void){
	err_t result = RT_EOK;
	
	//@INFO: Reserved for future
	
	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t sys_rfAdaptor_crcError_IRQHandler(void){
	err_t result = RT_EOK;
	
	//@INFO: Reserved for future
	
	return result;
}








#endif
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
bool_t 		sys_rfAdaptor_readPin( void ){
		
	//@INFO: Interrupt'a girildiyse DIO1 pin'i okunmus demektir.
	
	
	if( SYS_RFADAPTOR_PARAM(SYS_RFADAPTOR_DIO0_IRQ))
	{
		return RT_TRUE;
	}
	else
	{
		return RT_FALSE;
	}
	
}


/******************************************************************************/
/**********************END OF RFADAPTOR IRQ HANDLERS***************************/
#endif
#if 1 //@INFO: RF ADAPTOR HW Timer Config
/*******************************************************************************
	@func    : sys_rfAdaptor_btimerInit
	@param   : timeMS
  @return  : err_t
  @date	   : 
  @INFO		 : 

 rt_device_t 	sys_adaptor_hwTimer 					= 	RT_NULL  ; 		
char	        rfAdaptor_HWTIMER_DEV_NAME[]	=		"timer0" ;

********************************************************************************/
err_t sys_rfAdaptor_hwInit(uint32_t timeMS){
	
	err_t result	= RT_EOK;
	
	//@INFO: HW Timer mode, One-Shot ayarlaniyor.
	rt_hwtimer_mode_t 	mode	=	HWTIMER_MODE_ONESHOT;
	//@INFO: Timer dolma s�resi timeout degiskeni tanimlaniyor.
	rt_hwtimerval_t 		timeout = {0};
	//	rt_uint32_t				 	freq = 0; 		//@LATER: Freq ayarlanma hazir degil !
	
	//@INFO: Daha �nce kurulan bir timer yoksa;
	if( sys_adaptor_hwTimer == RT_NULL )
	{
		//@INFO: Timer bulunuyor.
		sys_adaptor_hwTimer = rt_device_find( HW_TIMER1_NAME );
		
    if (sys_adaptor_hwTimer == RT_NULL)
    {		//@INFO: Timer bulunamadi !
				rt_kprintf("hwtimer can't find : %s \n", HW_TIMER1_NAME);
        return RT_ERROR;
    }
	}
	
	//@INFO: RW Modunda timer aciliyor.
	result = rt_device_open(sys_adaptor_hwTimer, RT_DEVICE_OFLAG_RDWR);
	
	if (result != RT_EOK)
	{		//@INFO: Timer acilamadi !
			rt_kprintf("open %s device failed!\n", HW_TIMER1_NAME);
			return result;
	}
	
	//@INFO: Timer IRQ fonksiyonu belirtiliyor. Indicate function-pointer parametre almaktadir.
	/* t_err_t rt_device_set_rx_indicate(rt_device_t dev																			,
																			 rt_err_t (*rx_ind)(rt_device_t dev, rt_size_t size)  ) */
	
	
	//rt_kprintf("HW_IRQHandler func IRQ indicate ediliyor ! \n");
	//@NOTICE: Eger Hardware Interrupt Handler'a dallanmak isteniliyorsa, define yapilmalidir.
	rt_device_set_rx_indicate(sys_adaptor_hwTimer, HW_IRQHandler);
	
	//@INFO: Timer One-Shot Modunda ayarlaniyor.
	mode = HWTIMER_MODE_ONESHOT;
	
	//@INFO: Sayma frekansi ayarlaniyor. Tek-Atim modu oldugu icin,
	/*  HWTIMER_CTRL_MODE_SET            // Setting the timing mode(oneshot/period) */
	result = rt_device_control(sys_adaptor_hwTimer, HWTIMER_CTRL_MODE_SET, &mode);
	
	if (result != RT_EOK)
	{		//@INFO: Timer Modu Ayarlanamadi !
			rt_kprintf("set mode failed! ret is :%d\n", result);
			return result;
	}
		
	//@INFO: Timer timeout degeri set ediliyor.
	timeout.sec  = 0;      				/* second */
  timeout.usec = timeMS * 1000; /* microsecond */
	
	/*rt_size_t rt_device_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size);*/
	
	if ( rt_device_write( sys_adaptor_hwTimer									, 
											  0																		, 
												&timeout														, 
												sizeof(timeout)) != sizeof(timeout)	)
	{
			//@INFO: Time-out hatasi !
			rt_kprintf("set timeout value failed\n");
			return RT_ERROR;
	}
	
	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t sys_rfAdaptor_hwStart(void){

	err_t result	= RT_EOK;
	result = rt_device_control( sys_adaptor_hwTimer, HWTIMER_CTRL_FREQ_SET, RT_NULL );
	if (result != RT_EOK)
	{
			rt_kprintf("%s timer freq set failed! ret is :%d\n", HW_TIMER1_NAME, result);
	}

	return result;
		
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t sys_rfAdaptor_hwStop(void){
	
	err_t result	= RT_EOK;
	result = rt_device_control( sys_adaptor_hwTimer, HWTIMER_CTRL_STOP, RT_NULL );
	if (result != RT_EOK)
	{
			rt_kprintf("%s timer stop failed! ret is :%d\n", HW_TIMER1_NAME, result);
	}

	if(sys_adaptor_hwTimer != RT_NULL) rt_device_close(sys_adaptor_hwTimer);
	
	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void sys_rfAdaptor_delayMsBlocking(rt_uint32_t delayTime){
	
	uint32_t timeoutCounter = 0, timeoutValue = 0;
	SYS_RFADAPTOR_PARAM_SET(SYS_RFADAPTOR_HWTIM);
	
	uint8_t level = __get_PRIMASK( );
  __enable_irq( );
	timeoutValue = (uint32_t)( ((float)(delayTime) /11.0) / (1000.0/(float)(Sysctrl_GetHClkFreq())) ); //@INFO : Timeout suresini dinamik yapiyorum. Boylece gelen bekleme suresinden biraz azi kadar bekleme yapacak. Kesme gelmezse boylece yaklasik verilen deger kadar kalmis olacak
	sys_rfAdaptor_hwInit(delayTime);
//	sys_rfAdaptor_btimerStart();
		
	while( SYS_RFADAPTOR_PARAM(SYS_RFADAPTOR_HWTIM) )
	{
		if( ++timeoutCounter > timeoutValue ) //@INFO : Yazilimin sonsuz dongude kalmamasi icin onlem alindi.
		{
			sys_rfAdaptor_delayCounter = 0;
			break;
		}
	}
	
	__set_PRIMASK( level );
	sys_rfAdaptor_hwStop();
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void DelayMs(rt_uint32_t delayTime){ 
	sys_rfAdaptor_delayMsBlocking( delayTime );
}
#endif

#if 1 //@INFO: RF ADAPTOR SPIConfig
/******************START OF RF ADAPTOR SPI/WRITE/READ**************************/
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 	 sys_rfAdaptor_spiInit(void){

	struct rt_spi_device *spi_dev_rfAdaptor;
		
	rt_pin_write( RFADAPTOR_NSS, PIN_HIGH );
	
	spi_dev_rfAdaptor = (struct rt_spi_device *)rt_device_find(RFADAPTOR_DEVNAME); 
	
			//@INFO : Daha onceden kayit olmus lora device var mi bakiliyor
		if( spi_dev_rfAdaptor == RT_NULL ) //@INFO : Kurulu bir flash device yoksa
		{	//@NEWFEATURE: SX1262 SPI2 i
			if( rt_hw_spi_device_attach(RT_SPI_BUS_NAME_0, &rt_spi_rfAdaptor, RFADAPTOR_DEVNAME, RFADAPTOR_NSS) != RT_EOK ) 
			return RT_ERROR; //@INFO : attach yapilamazsa yazma ya da okuma islemi de yapilamaz
		
			struct rt_spi_configuration cfg = RFADAPTOR_CONFIG_DEFAULT;
		
			if( rt_spi_configure(&rt_spi_rfAdaptor, &cfg) != RT_EOK )
			return RT_ERROR; //@INFO : config ayarlari yapilamazsa yazma ya da okuma yapilamaz
		
		}
		else
		{	
			struct rt_spi_configuration cfgDef = RFADAPTOR_CONFIG_DEFAULT;
			if( rt_spi_configure(&rt_spi_rfAdaptor, &cfgDef) != RT_EOK )
				return RT_ERROR; //@INFO : config ayarlari yapilamazsa yazma ya da okuma yapilamaz
		}
		
		rt_pin_write(RFADAPTOR_NSS, PIN_HIGH);
		return RT_EOK;
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 	  sys_rfAdaptor_checkDeviceRegister(void){
	
	struct rt_spi_device *spi_dev_lora;
	spi_dev_lora = (struct rt_spi_device *)rt_device_find( RFADAPTOR_DEVNAME ); 
	if( spi_dev_lora == RT_NULL ) 
	{
		if( sys_rfAdaptor_spiInit() != RT_EOK )
			return RT_ERROR;
	}
	
	return RT_EOK;
}

/********************END OF RF ADAPTOR SPI/WRITE/READ***************************/
#endif

#if 1 //@INFO: RF ADAPTOR Sx1262 R/W Config

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 			sys_rfAdaptor_writeCommand				( RadioCommands_t command, 
																									uint8_t *buffer, 
																									uint16_t size ){
		
	err_t 	result 		 = RT_EOK , result2 = RT_EOK ;
	
	//@INFO: Mod�l verileri almaya hazir mi?
	result = sys_rfAdaptor_checkDeviceReady();
	if(result != RT_EOK)
	{
		return RT_ERROR;
	}		
	if( buffer != RT_NULL)
	{
		uint8_t *opBuf = malloc(size+1);
		
		uint32_t opBuffAdress = 0;
		opBuffAdress = (uint32_t)opBuf;
		
		if( ( opBuffAdress & 0x20000000 ) == RT_NULL ) 
		{

			return RT_ERROR;
		}
		opBuf[0] = (uint8_t)command;
		memcpy(&opBuf[1], &buffer[0], size);
		
		result  = spi_send(	&rt_spi_rfAdaptor			,
																			&opBuf[0]		,
																			(size + 1)	);
		
		result = ( result == (size + 1) )? RT_EOK : RT_ERROR;
		
		rt_free(opBuf);
	}
	else
	{
		uint8_t opBuf = (uint8_t)command;
		result = ( rt_spi_send(&rt_spi_rfAdaptor , &opBuf, SIZE_OF_OPCODE	) == SIZE_OF_OPCODE ) ? RT_EOK : RT_ERROR;
	}


	//@INFO: RADIO_SET_SLEEP Komutu g�nderilecekse, BUSY Beklenmez !
	result2 = ( command != RADIO_SET_SLEEP ) ?  sys_rfAdaptor_waitOnBusy() : RT_EOK ;
		if(result != RT_EOK || result2 != RT_EOK)
	{

		return RT_ERROR;
	}

	/* The total calibration time if all blocks are calibrated is 3.5 ms. 
	 The calibration must be launched in STDBY_RC mode and 
		the BUSY pins will be high during the calibration process. 
		A falling edge of BUSY indicates the end of the procedure.	*/

#ifdef GET_WRCMD_STATUS	
	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	RadioStatus_t status ;							//@...	
	status = sys_rfAdaptor_getStatus();				//@...
	
	if(   status.Fields.CmdStatus == 0x5 	||	/* Failure to execute command*/
				status.Fields.CmdStatus == 0x4	||	/* Command processing error */
				status.Fields.CmdStatus == 0x3  ) 	/* Command timeout */
	{
		if(  command == RADIO_CFG_DIOIRQ 		||  /* IRQ Function BUSY D�nd�rmez */
				 command == RADIO_GET_IRQSTATUS || 
				 command == RADIO_CLR_IRQSTATUS	)
		{
			return RT_EOK;
		}
		else
		{
			return RT_ERROR;
		}
	}			
	//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
	DelayMs(1);
#endif
	
	return RT_EOK;
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 			sys_rfAdaptor_readStatus					( uint8_t *buffer ){
	
	//@INFO: Kurulu bi SPI birimi yoksa error d�n�yor.
	err_t result = RT_EOK , result2 = RT_EOK;
	
	//@INFO: Mod�l verileri almaya hazir mi?
	result = sys_rfAdaptor_checkDeviceReady();
	if(result != RT_EOK)
	{
		
		*buffer = 0xFF;
		return RT_ERROR;
	}

	//@INFO: Opcode'un tutulacagi dizi ayarlaniyor.
	uint8_t opBuf[ 2 ] = { RT_NULL };
	opBuf[ 0 ] = (uint8_t)RADIO_GET_STATUS;
	
	result = rt_spi_send_then_recv(&rt_spi_rfAdaptor			,
																 &opBuf[ 0 ]						,
																 1											,
																 &opBuf[ 1 ]						,
																 1											);
	
	result2 = sys_rfAdaptor_waitOnBusy();	

	if(result != RT_EOK || result2 != RT_EOK) 
	{
		
		*buffer = 0xFF;
		return RT_ERROR;
	}
		
	*buffer = opBuf[ 1 ];
	
	return result;
	

}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/

err_t 			sys_rfAdaptor_readCommand					( RadioCommands_t command	, 
																									uint8_t *buffer			, 
																									size_t size 					){
	
	//@INFO: Kurulu bi SPI birimi yoksa error d�n�yor.
	err_t result = RT_EOK , result2 = RT_EOK;
	
	//@INFO: Mod�l verileri almaya hazir mi?
	result = sys_rfAdaptor_checkDeviceReady();
	if(result != RT_EOK)
	{
		return RT_ERROR;
	}

	//@INFO: Opcode'un tutulacagi dizi ayarlaniyor.
	uint8_t opBuf[SIZE_OF_READCMD] = { RT_NULL };
	opBuf[INDEX_OF_OPCODE]		 	= (uint8_t)command;
	opBuf[INDEX_OF_READCMD_NOP] = (uint8_t)NOP_MSG;
	
	result = rt_spi_send_then_recv(&rt_spi_rfAdaptor			,
																 &opBuf[ 0 ]						,
																 SIZE_OF_READCMD				,
																 &buffer[ 0 ]						,
																 size										);
	
	result2 = sys_rfAdaptor_waitOnBusy();	

	if(result != RT_EOK || result2 != RT_EOK) 
	{
		return RT_ERROR;
	}
		
	
	return result;
	
}



/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t			sys_rfAdaptor_writeRegisters			( uint16_t 	address,
																									uint8_t* 	buffer		,
																									size_t			size				){
	err_t 	 result = RT_ERROR , result2 = RT_EOK;
	
	//@INFO: Mod�l verileri almaya hazir mi?
	result = sys_rfAdaptor_checkDeviceReady();
	if(result != RT_EOK)
	{
		return RT_ERROR;	
	}
if( buffer != RT_NULL)
	{
		uint8_t *opBuf = rt_malloc(size+3);
		
		uint32_t opBuffAdress = 0;
		opBuffAdress = (uint32_t)opBuf;
		
		if( ( opBuffAdress & 0x20000000 ) == RT_NULL )
		{
			return RT_ERROR;
		}
		opBuf[0] = (uint8_t)RADIO_WRITE_REGISTER;
		opBuf[1] = (uint8_t)(( address & 0xFF00 ) >> 8 );
		opBuf[2] = (uint8_t)(  address & 0x00FF );
		memcpy(&opBuf[3], &buffer[0], size);
		
		result  = rt_spi_send(	&rt_spi_rfAdaptor			,
																			&opBuf[0]		,
																			(size + 3)	);
		
		result = ( result == (size + 3) )? RT_EOK : RT_ERROR;
		
		rt_free(opBuf);
	}
	//@INFO: RADIO_SET_SLEEP Komutu g�nderilecekse, BUSY Beklenmez !
	result2 = sys_rfAdaptor_waitOnBusy();
		
	if(result != RT_EOK || result2 != RT_EOK)
	{
		return RT_ERROR;
	}				
															
	return result;
}
																			 
/*******************************************************************************
  @func    : 
  @param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 			sys_rfAdaptor_writeRegister				( uint16_t 	address,
																									uint8_t 	value				){
																				 
	err_t	result = RT_EOK;
																			 
	result = sys_rfAdaptor_writeRegisters( address , &value , 1);
	if(result != RT_EOK) 
	{
		return RT_ERROR;				
	}
	
																		 
	return RT_EOK;					 
																			 																			 
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t			sys_rfAdaptor_readRegisters				( uint16_t 	address,
																									uint8_t*	buffer				,
																									size_t	size						){

	err_t 	 result = RT_EOK, result2 = RT_EOK;
	
	//@INFO: Mod�l verileri almaya hazir mi?
	result = sys_rfAdaptor_checkDeviceReady();
	if(result != RT_EOK)
	{
		return RT_ERROR;
	}
																		 
	uint8_t opBuf[SIZE_OF_READREG_CMD] = { RT_NULL };
	//@INFO: WriteRegister OPCode'u ayarlanir sendBuffer ilk indisine yerlestirilir.
	opBuf[INDEX_OF_OPCODE] = (uint8_t)RADIO_READ_REGISTER;		
	//@INFO: Yazma yapilacak register adresi ayarlanir.
	opBuf[INDEX_OF_16BITREG_MSB] = (uint8_t)(( address & 0xFF00 ) >> 8 );
	opBuf[INDEX_OF_16BITREG_LSB] = (uint8_t)(  address & 0x00FF );																				 
	opBuf[INDEX_OF_READREG_NOP]  = (uint8_t)NOP_MSG;
																				 
	result = rt_spi_send_then_recv(&rt_spi_rfAdaptor			,
																 &opBuf[0]							,
																 SIZE_OF_READREG_CMD 		,
																 &buffer[0]							,
																 size										);
																				 
	result2 = sys_rfAdaptor_waitOnBusy();	
	if(result != RT_EOK || result2 != RT_EOK) 
	{
		return RT_ERROR;
	}
	
	
	return result;
	
}
																				
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 :

@WARNING:The data buffer is cleared when the device is put into Sleep mode 
(implying no access). The data is retained in all other modes of operation.
********************************************************************************/
uint8_t		sys_rfAdaptor_readRegister				( uint16_t 	address	){
	
	uint8_t data;

	sys_rfAdaptor_readRegisters(address, &data , 1 );
	
	return data;
	
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 

@WARNING:The data buffer is cleared when the device is put into Sleep mode 
(implying no access). The data is retained in all other modes of operation.
********************************************************************************/
err_t			sys_rfAdaptor_writeBuffer					( uint8_t *buffer	,
																									size_t  size 		){	
	err_t 	 result = RT_ERROR, result2 = RT_EOK;
	
	//@INFO: Mod�l verileri almaya hazir mi?
	result = sys_rfAdaptor_checkDeviceReady();
	if(result != RT_EOK)
	{
		return RT_ERROR;
	}
																				
if( buffer != RT_NULL)
	{
		uint8_t *opBuf = rt_malloc(size+2);
		uint32_t opBuffAdress = 0;
		opBuffAdress = (rt_uint32_t)opBuf;
		if( ( opBuffAdress & 0x20000000 ) == RT_NULL )
		{
			return RT_ERROR;
		}
		opBuf[0] = (uint8_t)(RADIO_WRITE_BUFFER);
		opBuf[1] = 0;
 		memcpy(&opBuf[2], &buffer[0], size);
		
		result  = spi_send(	&rt_spi_rfAdaptor			,
																			&opBuf[0]		,
																			(size + 2)	);
		
		result = ( result == (size + 2) )? RT_EOK : RT_ERROR;
		
		rt_free(opBuf);
	}
	//@INFO: RADIO_SET_SLEEP Komutu g�nderilecekse, BUSY Beklenmez !
	result2 = sys_rfAdaptor_waitOnBusy();
		
	if(result != RT_EOK || result2 != RT_EOK)
	{
		return RT_ERROR;
	}	
	
	return result;
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t			sys_rfAdaptor_readBuffer					( uint8_t *buffer				, 
																  size_t size 					,
																  size_t offset					){

    err_t 	 result = RT_EOK, result2 = RT_EOK;
	
	//@INFO: Mod�l verileri almaya hazir mi?
	result = sys_rfAdaptor_checkDeviceReady();
	if(result != RT_EOK)
	{
		return RT_ERROR;
	}
																		
	uint8_t opBuf[SIZE_OF_READBUF_CMD] = { RT_NULL };
	opBuf[INDEX_OF_OPCODE]								= (uint8_t)(RADIO_READ_BUFFER);
	opBuf[INDEX_OF_BUFFEROFFSET]					= offset;
  opBuf[INDEX_OF_READBUF_NOP]						=	(uint8_t)NOP_MSG;																			
																			
	result = rt_spi_send_then_recv(&rt_spi_rfAdaptor			,
																 opBuf									,
																 SIZE_OF_READBUF_CMD 		,
																 buffer									,
																 size										);
																			
	result2 = sys_rfAdaptor_waitOnBusy();
	if(result != RT_EOK || result2 != RT_EOK)
	{
		return RT_ERROR;
	}
	
	return result;

}



#endif	

#if 1 //@INFO: RF ADAPTOR Init
/*******************************************************************************
	@func    : sys_rfAdaptor_gpioInit
	@param   : void
  @return  : void
  @date	   : 03.08.2022
  @INFO		 : LORAWAN_LIB_VANGO'de kullanilan SX1262 formatina uygun Handle
						 structure'a output konfig�rasyonlari tasiniyor.

						 GPIO Init'ler RT-Thread'e gore gerceklestiriliyor.

						 DIO0 i�in Interrupt kuruluyor.

						 @NOTICE: Tanimli pin makrolari
						#define RFADAPTOR_VCC  				GET_PIN(D, 4)
						#define RFADAPTOR_RESET  			GET_PIN(D, 3)
						#define RFADAPTOR_BUSY  			GET_PIN(D, 2)		
						#define RFADAPTOR_MOSI				GET_PIN(C, 3)		
						#define RFADAPTOR_MISO				GET_PIN(C, 2)			
						#define RFADAPTOR_SCLK				GET_PIN(C, 1)		
						#define RFADAPTOR_NSS				GET_PIN(C, 0)		
						#define RFADAPTOR_DIO0				GET_PIN(A, 13)	
						
********************************************************************************/

err_t 			sys_rfAdaptor_gpioInit						( void ){		
	
	rt_pin_mode ( RFADAPTOR_VCC , PIN_MODE_OUTPUT	);						//@INFO : VCC
	rt_pin_write( RFADAPTOR_VCC , PIN_HIGH 				);		
	
	rt_pin_mode ( RFADAPTOR_RESET , PIN_MODE_OUTPUT );					//@INFO : Reset
	rt_pin_write( RFADAPTOR_RESET , PIN_LOW 			  );	
		
	rt_pin_mode ( RFADAPTOR_MOSI , PIN_MODE_OUTPUT);						//@INFO : MOSI
	rt_pin_write( RFADAPTOR_MOSI , PIN_LOW );
	
	rt_pin_mode			 ( RFADAPTOR_MISO, PIN_MODE_INPUT_PULLUP); //@INFO : MISO
    rt_pin_irq_enable( RFADAPTOR_MISO, PIN_IRQ_DISABLE			); //@INFO : Interrupt Disable
	
	rt_pin_mode	( RFADAPTOR_NSS, PIN_MODE_OUTPUT );						 //@INFO : NSS
	rt_pin_write( RFADAPTOR_NSS, PIN_HIGH				 );	
	
	rt_pin_mode			 (RFADAPTOR_BUSY , PIN_MODE_INPUT 	); //@INFO : Busy Pin
	rt_pin_irq_enable(RFADAPTOR_BUSY , PIN_IRQ_DISABLE	); //@INFO : Interrupt Disable
	
	rt_pin_mode ( RFADAPTOR_SCLK , PIN_MODE_OUTPUT );					 //@INFO : CLOCK
	rt_pin_write( RFADAPTOR_SCLK , PIN_LOW 				 );
	
	rt_err_t result = RT_EOK;	//@NEW: aertekin //@INFO: IRQ kurulumlarini dogrulugu sebebiyle eklenmistir.
	
	//@NEWFEATURE: DIO0 IRQ Enable
	rt_pin_mode			 ( RFADAPTOR_DIO, PIN_MODE_INPUT ); //@INFO : DIO0 IRQ Pin
	
	result = rt_pin_attach_irq( RFADAPTOR_DIO, PIN_IRQ_MODE_RISING, sys_rfAdaptor_DioIsrHandler, RT_NULL);
	if(result != RT_EOK) return RT_ERROR;
		
	result = rt_pin_irq_enable( RFADAPTOR_DIO, PIN_IRQ_ENABLE);
	if(result != RT_EOK) return RT_ERROR;
	

	return result;

}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 			sys_rfAdaptor_HW_Init							( void ){	
	
	err_t result = RT_EOK;
	
	result = sys_rfAdaptor_gpioInit(); //@INFO : Portlar ayarlaniyor
	if(result != RT_EOK) return RT_ERROR;
	
	result = sys_rfAdaptor_spiInit();	//@INFO : SPI Ayarlaniyor.
	if(result != RT_EOK) return RT_ERROR;
	
	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 			sys_rfAdaptor_HW_deInit						( void ){
	
	err_t result = RT_EOK;
	
	sys_rfAdaptor_powerOFF();
	 //@INFO : Akim t�ketimi i�in spi �evre bileseni kapatilip pinler low a �ekiliyor.
	//@LATER
	//@LATER
	//@LATER
	//@LATER
	//@LATER
	
	//@LATER: duruma g�re spi ve gpio deInit yapilabilir?
	
	return result;
}


/*******************************************************************************
  @func    : 
  @param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t			sys_rfAdaptor_deInit							( void ){
	
	err_t result = RT_EOK;
	
	result = sys_rfAdaptor_HW_deInit();
	if(result != RT_EOK) return RT_ERROR;
	
	//@LATER: Temizlenmesi gereken flag varsa temizlenecek
	
	return result;
}

#endif

#if 1 //@INFO: RF Adaptor temel fonksiyonlar
//@INFO: Operating Mode Special Functions
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void 					sys_rfAdaptor_setOperatingMode		( uint8_t mode ){
	//@INFO: Global tanimli calisma modu ayarlaniyor !
	operatingMode = (RadioOperatingModes_t)mode;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
uint8_t 		sys_rfAdaptor_getOperatingMode		( void ){
	//@INFO: Global tanimli calisma modunu dondurur !
	return (uint8_t)operatingMode ;
}

/*******************************************************************************
  @func    : 
  @param   : 
  @return  : 
  @date	   : 
  @INFO	   : 
********************************************************************************/
err_t 			sys_rfAdaptor_changeChipMode			( uint8_t mode				, 
																									uint8_t modeConfig	, 
																									uint32_t timeout		){
																																																			
	err_t result = RT_EOK;
	
	switch(mode)
	{
		//@INFO: Uyku moduna aliniyor.
		case MODE_SLEEP:
			result = typdef_rfAdaptor_dev.ops.SetSleep( modeConfig );
			if(result != RT_EOK) return RT_ERROR;
		break;
		//@INFO: RC Stdby moduna aliniyor.
		case MODE_STDBY_RC:
			result = typdef_rfAdaptor_dev.ops.SetStandby( (rt_uint8_t)STDBY_RC );
			if(result != RT_EOK) return RT_ERROR;
		break;
		//@INFO: XOSC Stdby moduna aliniyor.
		case MODE_STDBY_XOSC:
			result = typdef_rfAdaptor_dev.ops.SetStandby( (rt_uint8_t)STDBY_XOSC );
			if(result != RT_EOK) return RT_ERROR;
		break;
		//@INFO: Frequency Switch  moduna aliniyor.
		case MODE_FS:
			result = typdef_rfAdaptor_dev.ops.SetFs();
			if(result != RT_EOK) return RT_ERROR;
		break;
		
		case MODE_TX:
			result = typdef_rfAdaptor_dev.ops.SetTx(timeout);
			if(result != RT_EOK) return RT_ERROR;
		break;
		
		case MODE_RX:
			result = typdef_rfAdaptor_dev.ops.SetRx(timeout);
			if(result != RT_EOK) return RT_ERROR;
		break;
		
		case MODE_RX_DC:
			//@LATER: G�ncellenmedi !
		break;
		
		case MODE_CAD:
			//@LATER: G�ncellenmedi !
		break;
		
		default:
			
		break;	
		
	}
	
	return result;

}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t			sys_rfAdaptor_antSwMode						( void ){

	return sys_rfAdaptor_setDio2AsRfSwitchCtrl( RT_TRUE );
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t			sys_rfAdaptor_checkDeviceReady		( void ){
	
	err_t result = RT_EOK;
	uint8_t tempMode;
	
	tempMode = sys_rfAdaptor_getOperatingMode();
	
	if( ( tempMode == MODE_SLEEP ) || ( tempMode == MODE_RX_DC  ) )
	{
		result = sys_rfAdaptor_wakeUp();
		if(result != RT_EOK) return RT_ERROR;
		
		result = sys_rfAdaptor_antSwMode( );
		if(result != RT_EOK) return RT_ERROR;
	}
	
	result = sys_rfAdaptor_waitOnBusy();
	
	return result;
}

/*******************************************************************************
	@func    : 
  @param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t  		sys_rfAdaptor_waitOnBusy					( void ){
	err_t result = RT_EOK;
	uint32_t 	waitLimit	= 0 ;
	
	while( 1 )
	{	//@INFO: Busy pini set duruma gelene kadar bekleniyor.
		if( !rt_pin_read_fast( RFADAPTOR_BUSY_PORT, RFADAPTOR_BUSY_PIN ) )
		{
			result = RT_EOK; //@INFO: Busy Set duruma geldi
			break;
		}
		else
		{
			if( ++waitLimit > 1000000 )
			{
				result = RT_ERROR;	//@INFO: Busy belli bir sebepten set olamazsa timeout ve error donecek !
				break;
			}
		}
	}
	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 			sys_rfAdaptor_chipReset						( void ){

	RFADAPTOR_RST_LOW;	
	DelayMs(1);	
	RFADAPTOR_RST_HIGH;	
	DelayMs(1);
	sys_rfAdaptor_setOperatingMode( MODE_SLEEP ) ;
	
	return RT_EOK;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t	sys_rfAdaptor_restartRF(void){
	
	err_t result = RT_EOK;
	
	result = sys_rfAdaptor_chipReset();
	if(result != RT_EOK ) return RT_ERROR ;
	
	result = sys_rfAdaptor_tcxoInit();
	if(result != RT_EOK ) return RT_ERROR ;
	
	result = sys_rfAdaptor_rfSwitchInit();
	if(result != RT_EOK ) return RT_ERROR ;
	
	
	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : Status byte donus parametresi bitleriyle anlam icermektedir.
							[7-0] -> Reserved
							[6:4] -> Chip Mode
							[3:1] -> Command Status

						  [6:4] i�in;				[3:1] i�in;
							0x0 Unused				 0x0 Reserverd
							---------          -------------
							0x2	STBY_RC        0x2 Data is available to host
							0x3	STBY_XOSC      0x3 Command Timeout
							0x4 FS             0x4 Command processing error
							0x5	RX             0x5 Failure to execute command
							0x6	TX             0x6 Command TX done.

**** Bu fonksiyon ilk cagirildiginde 0x2A donmektedir. 0 b 0 0 1 0 1 0 1 0
																														 ----- ***** 
																											@INFO: STBY_RC - Failure execute command
																											
********************************************************************************/
void sys_rfAdaptor_readAllRegs( void ); //@DEL
err_t			sys_rfAdaptor_wakeUp							( void ){
	
	err_t 	result 			= RT_EOK;
	size_t resultSize  = 0;
	
	uint8_t opBuf[2] = { RT_NULL };
	opBuf[0] = (rt_uint8_t)RADIO_GET_STATUS ;
	opBuf[1] = (rt_uint8_t)NOP_MSG ;
	
	resultSize = rt_spi_send( &rt_spi_rfAdaptor 	,
													  &opBuf[0] 	 				,		
														2							 	 		);
	if(resultSize != 2 ) return RT_ERROR ;

	result = sys_rfAdaptor_waitOnBusy();	
	if(result != RT_EOK ) return RT_ERROR ;
	
	//@INFO: Wakeup modu ayarlandiktan sonra STDBY_RC Modunda oldugu kayit ediliyor.
	sys_rfAdaptor_setOperatingMode( MODE_STDBY_RC ) ;

	
	return RT_EOK;
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void 					sys_rfAdaptor_powerON							( void ){

	RFADAPTOR_VCC_ON;
	RFADAPTOR_RST_HIGH;
	DelayMs(10);
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void 					sys_rfAdaptor_powerOFF						( void ){

	RFADAPTOR_VCC_OFF;
	RFADAPTOR_RST_LOW;
	
}


//@INFO: TXCO Configurations
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
    err_t			sys_rfAdaptor_tcxoCalibrate				( CalibrationParams_t calibParam ){
	err_t result = RT_EOK;
	
	uint8_t	value = ( (     ( uint8_t )calibParam.Fields.ImgEnable 		 << 6 ) |
                      ( 	( uint8_t )calibParam.Fields.ADCBulkPEnable << 5 ) |
                      ( 	( uint8_t )calibParam.Fields.ADCBulkNEnable << 4 ) |
                      ( 	( uint8_t )calibParam.Fields.ADCPulseEnable << 3 ) |
                      ( 	( uint8_t )calibParam.Fields.PLLEnable 		 << 2 ) |
                      ( 	( uint8_t )calibParam.Fields.RC13MEnable 	 << 1 ) |
                      ( 	( uint8_t )calibParam.Fields.RC64KEnable 				)	);
	
	result = sys_rfAdaptor_writeCommand( RADIO_CALIBRATE 		,
																			 &value							,
																			 1									);
	

	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t			sys_rfAdaptor_setDio3AsTcxoCtrl		( RadioTcxoCtrlVoltage_t tcxoVoltage , 
																								uint32_t timeout 																			){
	err_t result = RT_EOK;
	
	uint8_t buf[4] = { RT_NULL };
	
  buf[0] = tcxoVoltage & 0x07;
  buf[1] = ( rt_uint8_t )( ( 	timeout >> 16 ) & 0xFF );
  buf[2] = ( rt_uint8_t )( ( 	timeout >> 8 	) & 0xFF );
  buf[3] = ( rt_uint8_t )( 		timeout 				& 0xFF );
	
	
	result = sys_rfAdaptor_writeCommand( RADIO_SET_TCXOMODE	,
																			 buf								,
																			 4									);
	
	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t			sys_rfAdaptor_tcxoInit						( void ){
	
	err_t result = RT_EOK;
	
	CalibrationParams_t	calibParam;
	calibParam.Value = 0x7F;	
	
	result = sys_rfAdaptor_setDio3AsTcxoCtrl( TCXO_CTRL_1_6V /*TCXO_CTRL_1_6V*/ 															,
																					 ((uint32_t)( BOARD_TCXO_WAKEUP_TIME << 6 )) );
	if(result != RT_EOK) return RT_ERROR;
	
	result = sys_rfAdaptor_tcxoCalibrate( calibParam );

	return result;
	
}

//@INFO: RF Switch Configurations
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 			sys_rfAdaptor_setDio2AsRfSwitchCtrl( rt_bool_t enable ){
	
	rt_err_t result = RT_EOK;
	
	rt_uint8_t status = (rt_uint8_t)enable;
	result = sys_rfAdaptor_writeCommand( RADIO_SET_RFSWITCHMODE, &status, 1 );
	
	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
rt_err_t			sys_rfAdaptor_rfSwitchInit				( void ){
	
	rt_err_t result = RT_EOK;
	
	result = sys_rfAdaptor_setDio2AsRfSwitchCtrl( RT_TRUE );
	
	return result;
}

#endif

#ifdef RFADAPTOR_MAIN
#if 1 //@INFO: Init temel fonksiyonlari

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
typedef_rfAdaptor_device_st		sys_rfAdaptor_driverInit		(	void ){
		
	//@INFO: rfAdaptor IRQ rutinleri i�in matching
	sys_rfAdaptor_irqHandlers.wmBus_irqHandler 						= &sys_rfAdaptor_wmBusIRQHandler						;
	sys_rfAdaptor_irqHandlers.txDone_irqHandler						= &sys_rfAdaptor_txDoneIRQHandler           ;
	sys_rfAdaptor_irqHandlers.rxDone_irqHandler						= &sys_rfAdaptor_rxDoneIRQHandler           ;
	sys_rfAdaptor_irqHandlers.timeOut_irqHandler          = &sys_rfAdaptor_timeOutIRQHandler          ;
	sys_rfAdaptor_irqHandlers.preambleDetected_irqHandler = &sys_rfAdaptor_preambleDetectedIRQHandler ;
	sys_rfAdaptor_irqHandlers.syncWordValid_irqHandler    = &sys_rfAdaptor_syncWordValidIRQHandler    ;
	sys_rfAdaptor_irqHandlers.crcError_irqHandler         = &sys_rfAdaptor_crcError_IRQHandler        ;
	
	typedef_rfAdaptor_device_st		typdef_rfAdaptor_devHandle = { {RT_NULL} , typdef_sx1262_ops };
	
	return typdef_rfAdaptor_devHandle;
}
/******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
rt_err_t 			sys_rfAdaptor_initConfig					( void ){
	
	rt_err_t result = RT_EOK;
	
	result = sys_rfAdaptor_chipReset(); 				//@INFO: Baslangicta chip reset atilamazsa kurulum yapilamayacak!
	if( result != RT_EOK ) return RT_ERROR;
	
	result = sys_rfAdaptor_wakeUp();
	if( result != RT_EOK ) return RT_ERROR;
	
	result = sys_rfAdaptor_defaultParameters();	 //@INFO: RF icin default ayarlamalar
	if( result != RT_EOK ) return RT_ERROR;	
	
	result = sys_rfAdaptor_tcxoInit();
	if( result != RT_EOK ) return RT_ERROR;
		
	result = sys_rfAdaptor_rfSwitchInit();	
	if( result != RT_EOK ) return RT_ERROR;		

	result = typdef_rfAdaptor_dev.ops.SetRegulatorMode( USE_DCDC ) ;
	if( result != RT_EOK ) return RT_ERROR;	

	result = typdef_rfAdaptor_dev.ops.SetBufferBaseAddress( 0x00, 0x00 );
	if( result != RT_EOK ) return RT_ERROR;	
	
	ImageCalibrated = RT_TRUE;
	
	return result;
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
rt_err_t 			sys_rfAdaptor_init								( rt_uint8_t mode ){
	
	rt_err_t result = RT_EOK;
	
	result	= sys_rfAdaptor_HW_Init();					//@INFO: rfAdaptor HW Init
	if( result != RT_EOK ) return RT_ERROR;																																																	
	
	sys_rfAdaptor_powerON();										//@INFO: rfAdaptor pwr
	
	result	= sys_rfAdaptor_initConfig();				//@INFO: reset-wakeup-setStndby-tcxo-rf
	if( result != RT_EOK ) return RT_ERROR;	

	switch(mode)	//@INFO: rfAdaptor mode ozel init ayarlamalari
	{
		//@INFO: Lora'ya ozel init ayarlamalari
		case RF_SETTINGS_LORA: 
			#ifndef DEBUG_RF 
			rt_kprintf("RFADAPTOR LORA INIT %u mode \n", mode); //@DEL
			#endif
		
			result = sys_rfAdaptor_specificSettings( (rt_uint8_t)RF_SETTINGS_LORA , RT_NULL , RT_NULL);
			if( result != RT_EOK ) return RT_ERROR;	
		break;
	
		//@INFO: PC'ye ozel init ayarlamalari
		case RF_SETTINGS_PC: 	
			#ifndef DEBUG_RF			
			rt_kprintf("RFADAPTOR PC INIT %u mode \n", mode); //@DEL
			#endif
		
			result = sys_rfAdaptor_defaultParameters();		//@INFO: RF icin default ayarlamalar
			if( result != RT_EOK ) return RT_ERROR;	
			
			result =typdef_rfAdaptor_dev.ops.SetBufferBaseAddress( 0x00, 0x00 ); // @BACK @INFO : Struct yapisi eklenecek suanda 1262 den direk �ekiliyor 
			if( result != RT_EOK ) return RT_ERROR;

			result = sys_rfAdaptor_specificSettings( (rt_uint8_t)RF_SETTINGS_PC 																 , 
																								typdef_flash_configGeneralPacket.meter.rfBroadCastMode 		 ,
																								typdef_flash_configGeneralPacket.meter.rfBroadCastDirection);
			if( result != RT_EOK ) return RT_ERROR;	
		
		break;
		
		//@INFO: wmBus'a ozel init ayarlamalari
		case RF_SETTINGS_WMBUS:	
			#ifndef DEBUG_RF			
			rt_kprintf("RFADAPTOR WMBUS INIT %u mode \n", mode); //@DEL
			#endif
		
			result = sys_rfAdaptor_defaultParameters();		//@INFO: RF icin default ayarlamalar
			if( result != RT_EOK ) return RT_ERROR;		
			
			result = typdef_rfAdaptor_dev.ops.SetBufferBaseAddress( 0x00, 0x00 );   // @BACK @INFO : Struct yapisi eklenecek suanda 1262 den direk �ekiliyor 
			if( result != RT_EOK ) return RT_ERROR;	
		
			result = sys_rfAdaptor_specificSettings( (rt_uint8_t)RF_SETTINGS_WMBUS , 0/* wmBus_mode*/ , RT_NULL);
			if( result != RT_EOK ) return RT_ERROR;	
		break;
		
	}
	
	return result;
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 

	//sys_rfAdaptor_writeData(SX1276_REG_LNA, RF_LNA_BOOST_OFF | RF_LNA_GAIN_G1); 
	
	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	// RSSI -> Alinan sinyal g�c� g�stergesi (Received signal strength indication)
	// @NEW: a.ertekin @NOTICE @INFO : Alinan sinyalin gucunu cip otomatik hesapliyor getRssiInsant ile analiz edilebilir.
	// .../sx1272.c/ rt_int8_t SX126xGetRssiInst( void )
	//sys_rfAdaptor_writeData(SX1276_REG_RSSICOLLISION, 	0x0F); //@INFO: UW SX1276
	//sys_rfAdaptor_writeData(SX1276_REG_RSSITHRESH, 			0x10); //@INFO: UW SX1276 
	//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

		
//@NEW: a.ertekin @NOTICE @INFO : RSSI Ayarlarini otomatik yapiyor	
//	sys_rfAdaptor_writeData(SX1276_REG_RSSICONFIG, 			RF_RSSICONFIG_SMOOTHING_8);
//	sys_rfAdaptor_writeData(SX1276_REG_RSSICOLLISION, 	0x0F); 
//	sys_rfAdaptor_writeData(SX1276_REG_RSSITHRESH, 			0x10);

//@NEW: a.ertekin @NOTICE @INFO :	
//@INFO: StopTimerOnPreamble disable ise Syncword veya header tespit edildiginde timer durdurulur.
//@INFO: StopTimerOnPreamble enable  ise PREAMBLE tespit edildiginde timer durdurulur.
//	sys_rfAdaptor_writeData(SX1276_REG_PREAMBLEDETECT, 	RF_PREAMBLEDETECT_DETECTOR_ON | RF_PREAMBLEDETECT_DETECTORSIZE_2 | RF_PREAMBLEDETECT_DETECTORTOL_10);

	
//@NEW: a.ertekin @NOTICE @INFO : RxTimeout ayarlamalari, RxMode ge�iste Opcode ile birlikte ayarlaniyor.
//	sys_rfAdaptor_writeData(SX1276_REG_RXTIMEOUT1, 			RF_RXTIMEOUT1_TIMEOUTRXRSSI);
//	sys_rfAdaptor_writeData(SX1276_REG_RXTIMEOUT2, 			RF_RXTIMEOUT2_TIMEOUTRXPREAMBLE);
//	sys_rfAdaptor_writeData(SX1276_REG_RXTIMEOUT3, 			RF_RXTIMEOUT3_TIMEOUTSIGNALSYNC);
	
//@NEW: a.ertekin @NOTICE @INFO : Paket delay i�eriden kendisi yapiyor.
//sys_rfAdaptor_writeData(SX1276_REG_RXDELAY, 				RF_RXDELAY_INTERPACKETRXDELAY);

//@NEW: a.ertekin @NOTICE @INFO : CLK ayari XTAL ve RC olarak STDBY Modu ile ayarlaniyor.
//sys_rfAdaptor_writeData(SX1276_REG_OSC, 							RF_OSC_CLKOUT_OFF);

//@INFO: Broadcast address ve Node Addr default olarak 0x00 yukarida ayarlaniyor.
//sys_rfAdaptor_writeData(SX1276_REG_NODEADRS, 				0x00); //@INFO : DEFAULT
//sys_rfAdaptor_writeData(SX1276_REG_BROADCASTADRS, 	0x00); //@INFO : DEFAULT
	

********************************************************************************/
rt_err_t 			sys_rfAdaptor_defaultParameters		( void ){

	rt_err_t result 		= RT_EOK;

	rt_memset( &typdef_rfAdaptor_dev.drvObj , 0, sizeof(typdef_rfAdaptor_dev.drvObj) );
	
#ifndef OCP_DEFAULT	
	OverCurrent_t overCurrentVal = (OverCurrent_t)sys_rfAdaptor_readRegister( ( rt_uint16_t )REG_OCP );	//@INFO : Read Current overcurrent val
	if( overCurrentVal != REG_OCP_100 ) overCurrentVal = REG_OCP_100;																									//@INFO: OverCurrent ayari 100mA degilse 100mA Ayarla
	result = sys_rfAdaptor_writeRegister( ( rt_uint16_t )REG_OCP , ( rt_uint8_t )REG_OCP_100 );												//@INFO : Enables overload current protection, 100mA
	if( result != RT_EOK ) return RT_ERROR;	
#else
	//@INFO: Default durumda ne olursa olsun 60mA ayarlanmaktadir.
	result = sys_rfAdaptor_writeRegister( ( rt_uint16_t )REG_OCP , ( rt_uint8_t )REG_OCP_60 );
#endif	
	
	//@INFO: whiteseed sikinti cikartiyordu.
	
	//@NOTICE @INFO : Datasheet Default Register Degerleri Guncelleniyor !
	//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
	//@INFO: REG_LR_WHITSEEDBASEADDR_MSB register default value 
//	result = sys_rfAdaptor_writeRegister( ( rt_uint16_t )REG_LR_WHITSEEDBASEADDR_MSB 					, 
//																				( rt_uint8_t  )REG_LR_WHITSEEDBASEADDR_MSB_DEFAULT 	); 
//	if( result != RT_EOK ) return RT_ERROR;	
//	
//	//@INFO: REG_LR_WHITSEEDBASEADDR_MSB register default value 
//	result = sys_rfAdaptor_writeRegister( ( rt_uint16_t )REG_LR_WHITSEEDBASEADDR_MSB 					, 
//																				( rt_uint8_t  )REG_LR_WHITSEEDBASEADDR_LSB_DEFAULT ); 
//	if( result != RT_EOK ) return RT_ERROR;	
//	
//	//@INFO: REG_LR_CRCSEEDBASEADDR register default value 	
//	result = sys_rfAdaptor_writeRegister( ( rt_uint16_t )REG_LR_CRCSEEDBASEADDR 							,	 
//																				( rt_uint8_t  )REG_LR_CRCSEEDBASEADDR_DEFAULT 			); 
//	if( result != RT_EOK ) return RT_ERROR;		
//	
//	//@INFO: REG_LR_CRCSEEDBASEADDR[0] ve REG_LR_CRCSEEDBASEADDR[1] register default value 		
//	rt_uint8_t crcDefBuf[2] = { (rt_uint8_t)( ( REG_LR_CRCSEEDBASEADDR_DEFAULT >> 8 ) & 0xFF) ,
//															(rt_uint8_t)(   REG_LR_CRCSEEDBASEADDR_DEFAULT 			  & 0xFF) };
//	
//	result = sys_rfAdaptor_writeRegisters( ( rt_uint16_t )REG_LR_CRCSEEDBASEADDR , 
//																					crcDefBuf														 , 
//																					2 																	 );
//	if( result != RT_EOK ) return RT_ERROR;	
//	
//	//@INFO: REG_BROADCAST_ADDRESS register default value 																	
//	result = sys_rfAdaptor_writeRegister( ( rt_uint16_t )REG_BROADCAST_ADDRESS 				 ,	 
//																				( rt_uint8_t  )REG_BROADCAST_ADDRESS_DEFAULT ); 
//	if( result != RT_EOK ) return RT_ERROR;															
//															
//	//@INFO: REG_LR_SYNCWORD[0] ve REG_LR_SYNCWORD[1] register default value 		
//	rt_uint8_t loraSycWordDefBuf[2] = { (rt_uint8_t)( ( REG_LR_SYNCWORD_DEFAULT >> 8 ) & 0xFF) ,
//																			(rt_uint8_t)(   REG_LR_SYNCWORD_DEFAULT 			 & 0xFF) };
//	
//	result = sys_rfAdaptor_writeRegisters( ( rt_uint16_t )REG_LR_SYNCWORD , 
//																					loraSycWordDefBuf							, 
//																					2 														);
//	if( result != RT_EOK ) return RT_ERROR;													

	//@INFO: REG_RX_GAIN register default value 																	
//	result = sys_rfAdaptor_writeRegister( ( rt_uint16_t )REG_RX_GAIN 				 ,	 
//																				( rt_uint8_t  )REG_RX_GAIN_DEFAULT ); 
//	if( result != RT_EOK ) return RT_ERROR;																			
	
	if( operatingMode == MODE_STDBY_XOSC )
	{
			//@INFO: REG_LR_SYNCWORD[0] ve REG_LR_SYNCWORD[1] register default value 		
			rt_uint8_t xtaTrimDefBuf[2] = { (rt_uint8_t)( ( REG_XTA_TRIM_DEFAULT >> 8 ) & 0xFF) ,
																			(rt_uint8_t)(   REG_XTA_TRIM_DEFAULT 			  & 0xFF) };
	
			result = sys_rfAdaptor_writeRegisters( ( rt_uint16_t )REG_XTA_TRIM , 
																							xtaTrimDefBuf							, 
																							2 														);
			if( result != RT_EOK ) return RT_ERROR;
		
		
	}
														
	return result;											
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
rt_err_t			sys_rfAdaptor_specificSettings		( rt_uint8_t rfMode , rt_uint8_t mode , rt_uint8_t direction){
	
	rt_err_t result = RT_EOK;

	switch(rfMode)
	{	
		case RF_SETTINGS_LORA :
//		  result = sys_rfAdaptor_loraInitConfig(); //@ASK: LoraInit'te mi cagirilacak yoksa buradan mi?
			setLoraDefaultParams();	
		break;

		case RF_SETTINGS_PC 	 : //@INFO: mode: BOOT-VANA-LOG i�in kullaniliyor.
			#ifndef DEBUG_RF
			rt_kprintf("PC INIT %d mode \n", mode); //@DEL	
			#endif
			result = sys_rfAdaptor_pcInitConfig( mode , direction );	
		break;

		case RF_SETTINGS_WMBUS : //@INFO: mode: WMBUS Rx ve WMBUS Tx i�in kullaniliyor.
			#ifndef DEBUG_RF
			rt_kprintf("WMBUS INIT %d mode \n", mode); //@DEL
			#endif			
			result = sys_rfAdaptor_wmBusInitConfig( RF_WMBUS_MODE_BT2MODE , mode );
		break;
		
		default:
			result = RT_ERROR;
		break;
	}

	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
rt_err_t sys_rfAdaptor_pcInitConfig( rt_uint8_t mode , rt_uint8_t direction ){
	rt_err_t result = RT_EOK;
		
	switch(mode)
	{
		case RF_MODE_CHANNEL_BOOT:
			#ifndef DEBUG_RF
			rt_kprintf("PC-BOOT INIT %d direction \n",direction); //@DEL
		  #endif
			result = sys_rfMode_bootModeInit(&typdef_rfAdaptor_dev ,direction);  
		break;
		
		case RF_MODE_CHANNEL_VANA:
			#ifndef DEBUG_RF
			rt_kprintf("PC-VALVE INIT %d direction \n",direction); //@DEL
		  #endif
			result = sys_rfMode_valveModeInit(&typdef_rfAdaptor_dev ,direction); 
		break;
		
		case RF_MODE_CHANNEL_LOG:
			#ifndef DEBUG_RF
			rt_kprintf("PC-LOG INIT %d direction \n",direction); //@DEL		
		  #endif
			result = sys_rfMode_logModeInit(&typdef_rfAdaptor_dev ,direction);		
		break;
		
		default:
			result = RT_ERROR;
		break;
		
	}
	
	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void		sys_rfAdaptor_bootModeRxConfig(typedef_rfAdaptor_device_st* dev){
			/*
		Radio.SetRxConfig(MODEM_FSK, 100000, 100000, 0, 83333, 5, 200, true, 16, true, false, 0, false, false);
	
		void RadioSetRxConfig( 	RadioModems_t modem, 			--------> MODEM_FSK
														uint32_t bandwidth,       --------> 100000			= FSK_BT2MODE_BANDWIDTH << 1
														uint32_t datarate,        --------> 100000			= FSK_BT2MODE_DATARATE
														uint8_t coderate,         --------> 0
														uint32_t bandwidthAfc,    --------> 83333
														uint16_t preambleLen,     --------> 5
														uint16_t symbTimeout,     --------> 200
														bool fixLen,              --------> true
														uint8_t payloadLen,       --------> 16
														bool crcOn,               --------> true	 
														bool freqHopOn,           --------> false
														uint8_t hopPeriod,        --------> 0
														bool iqInverted,          --------> false
														bool rxContinuous )	      --------> false
	//@BACK: AK311 Eski koda g�re kontrol edilecek 	*/

	dev->drvObj.ModulationParams.Params.Gfsk.BitRate 						= (rt_uint32_t)SYS_RFADAPTOR_BT2MODE_DATARATE 																											;	 
	dev->drvObj.ModulationParams.Params.Gfsk.Fdev 							= (rt_uint32_t)SYS_RFADAPTOR_BT2MODE_FDEV  																													; 
	dev->drvObj.ModulationParams.Params.Gfsk.ModulationShaping 	= MOD_SHAPING_OFF																																				;	 
	dev->drvObj.ModulationParams.Params.Gfsk.Bandwidth 					= (rt_uint8_t)dev->ops.RadioGetFskBandwidthRegValue( ((uint32_t)SYS_RFADAPTOR_BT2MODE_BANDWIDTH<<1) ) 	; 
	//@INFO: Paket parametreleri ayarlaniyor.
	dev->drvObj.PacketParams.Params.Gfsk.PreambleLength 				= BYTE2BIT( SYS_RFADAPTOR_BT2MODE_PREAMBLE_LENGTH )																			;	
	dev->drvObj.PacketParams.Params.Gfsk.PreambleMinDetect 			= RADIO_PREAMBLE_DETECTOR_08_BITS 																																	; 
	dev->drvObj.PacketParams.Params.Gfsk.SyncWordLength 				= BYTE2BIT( SYS_RFADAPTOR_BT2MODE_SYNCWORD_LENGTH_RX )																	;	
	dev->drvObj.PacketParams.Params.Gfsk.HeaderType 						= RADIO_PACKET_FIXED_LENGTH /*RADIO_PACKET_VARIABLE_LENGTH*/														;	
	dev->drvObj.PacketParams.Params.Gfsk.AddrComp	 							= RADIO_ADDRESSCOMP_FILT_OFF																														;	
	dev->drvObj.PacketParams.Params.Gfsk.PayloadLength					= 8; //(rt_uint8_t)SYS_RFADAPTOR_BT2MODE_PAYLOAD_LENGTH_RX																								;	//@INFO: 16 BYTE PAYLOAD
	dev->drvObj.PacketParams.Params.Gfsk.CrcLength							=	RADIO_CRC_OFF																																					;	//@INFO: 2 BYTE CRC VAR.
	dev->drvObj.PacketParams.Params.Gfsk.DcFree									= RADIO_DC_FREE_OFF 																																		;
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void	sys_rfAdaptor_bootModeTxConfig(typedef_rfAdaptor_device_st* dev){
	
		/*
		Radio.SetTxConfig(MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 100000, FSK_DATARATE, 0, FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON, false, 0, 0, 0, 100);
	
		void RadioSetTxConfig( 	RadioModems_t modem,		----->	MODEM_FSK
														int8_t power						----->	TX_OUTPUT_POWER	-> 22dBm
														uint32_t fdev,          ----->	FSK_FDEV				-> 50e3
														uint32_t bandwidth,     ----->	100000
														uint32_t datarate,      ----->	FSK_DATARATE		-> 100e3 
														uint8_t coderate,       ----->	0
														uint16_t preambleLen,   ----->	FSK_PREAMBLE_LENGTH
														bool fixLen,            ----->	FSK_FIX_LENGTH_PAYLOAD_ON
														bool crcOn,             ----->	false
														bool freqHopOn,         ----->	0
														uint8_t hopPeriod,      ----->	0
														bool iqInverted,        ----->	0
														uint32_t timeout )      ----->	100
		//@BACK: AK311 Eski koda g�re kontrol edilecek */

	dev->drvObj.ModulationParams.Params.Gfsk.BitRate						= (rt_uint32_t)SYS_RFADAPTOR_BT2MODE_DATARATE 					;	  
	dev->drvObj.ModulationParams.Params.Gfsk.Fdev 							= (rt_uint32_t)SYS_RFADAPTOR_BT2MODE_FDEV  							; 
	dev->drvObj.ModulationParams.Params.Gfsk.ModulationShaping 	= MOD_SHAPING_G_BT_05												;	 
	dev->drvObj.ModulationParams.Params.Gfsk.Bandwidth 					= (rt_uint8_t)dev->ops.RadioGetFskBandwidthRegValue(((uint32_t)SYS_RFADAPTOR_BT2MODE_BANDWIDTH<<1)); // @INFO: param->ModulationParams.Bandwidth //@BACK: UW Ayari yapilmiyor?		
							//@INFO: Paket parametreleri ayarlaniyor.
	dev->drvObj.PacketParams.Params.Gfsk.PreambleLength 				= BYTE2BIT( SYS_RFADAPTOR_BT2MODE_PREAMBLE_LENGTH )			;		//@INFO: 5 -> (40)d = (0x28)h
	dev->drvObj.PacketParams.Params.Gfsk.PreambleMinDetect 			= RADIO_PREAMBLE_DETECTOR_08_BITS 											;		
	dev->drvObj.PacketParams.Params.Gfsk.SyncWordLength 				= BYTE2BIT( SYS_RFADAPTOR_BT2MODE_SYNCWORD_LENGTH_TX )	;		//@INFO: 2 -> (16)d = (0x10)h	
	dev->drvObj.PacketParams.Params.Gfsk.HeaderType 						= RADIO_PACKET_FIXED_LENGTH 								; 	
	dev->drvObj.PacketParams.Params.Gfsk.AddrComp	 							= RADIO_ADDRESSCOMP_FILT_OFF								; 	
	dev->drvObj.PacketParams.Params.Gfsk.PayloadLength					= (rt_uint8_t)SYS_RFADAPTOR_8BYTE_MODE_PAYLOAD_LENGTH_TX		;		
	dev->drvObj.PacketParams.Params.Gfsk.CrcLength							=	RADIO_CRC_OFF															;		
	dev->drvObj.PacketParams.Params.Gfsk.DcFree									= RADIO_DC_FREE_OFF 												;	
	
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void	sys_rfAdaptor_valveModeTxConfig(typedef_rfAdaptor_device_st* dev){
	
	/*
		Radio.SetTxConfig(MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 100000, FSK_DATARATE, 0, FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON, false, 0, 0, 0, 100);
	
		void RadioSetTxConfig( 	RadioModems_t modem,		----->	MODEM_FSK
														int8_t power						----->	TX_OUTPUT_POWER	-> 22dBm
														uint32_t fdev,          ----->	FSK_FDEV				-> 50e3
														uint32_t bandwidth,     ----->	100000
														uint32_t datarate,      ----->	FSK_DATARATE		-> 100e3 
														uint8_t coderate,       ----->	0
														uint16_t preambleLen,   ----->	FSK_PREAMBLE_LENGTH
														bool fixLen,            ----->	FSK_FIX_LENGTH_PAYLOAD_ON
														bool crcOn,             ----->	false
														bool freqHopOn,         ----->	0
														uint8_t hopPeriod,      ----->	0
														bool iqInverted,        ----->	0
														uint32_t timeout )      ----->	100
		//@BACK: AK311 Eski koda g�re kontrol edilecek */

	//@LATER:
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void	sys_rfAdaptor_valveModeRxConfig(typedef_rfAdaptor_device_st* dev){
			/*
		Radio.SetRxConfig(MODEM_FSK, 100000, 100000, 0, 83333, 5, 200, true, 16, true, false, 0, false, false);
	
		void RadioSetRxConfig( 	RadioModems_t modem, 			--------> MODEM_FSK
														uint32_t bandwidth,       --------> 100000			= FSK_BT2MODE_BANDWIDTH << 1
														uint32_t datarate,        --------> 100000			= FSK_BT2MODE_DATARATE
														uint8_t coderate,         --------> 0
														uint32_t bandwidthAfc,    --------> 83333
														uint16_t preambleLen,     --------> 5
														uint16_t symbTimeout,     --------> 200
														bool fixLen,              --------> true
														uint8_t payloadLen,       --------> 16
														bool crcOn,               --------> true	 
														bool freqHopOn,           --------> false
														uint8_t hopPeriod,        --------> 0
														bool iqInverted,          --------> false
														bool rxContinuous )	      --------> false
		//@BACK: AK311 Eski koda g�re kontrol edilecek 	*/
	
	//@LATER:
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void	sys_rfAdaptor_logModeTxConfig(typedef_rfAdaptor_device_st* dev){
	/*
		Radio.SetTxConfig(MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 100000, FSK_DATARATE, 0, FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON, false, 0, 0, 0, 100);
	
		void RadioSetTxConfig( 	RadioModems_t modem,		----->	MODEM_FSK
														int8_t power						----->	TX_OUTPUT_POWER	-> 22dBm
														uint32_t fdev,          ----->	FSK_FDEV				-> 50e3
														uint32_t bandwidth,     ----->	100000
														uint32_t datarate,      ----->	FSK_DATARATE		-> 100e3 
														uint8_t coderate,       ----->	0
														uint16_t preambleLen,   ----->	FSK_PREAMBLE_LENGTH
														bool fixLen,            ----->	FSK_FIX_LENGTH_PAYLOAD_ON
														bool crcOn,             ----->	false
														bool freqHopOn,         ----->	0
														uint8_t hopPeriod,      ----->	0
														bool iqInverted,        ----->	0
														uint32_t timeout )      ----->	100
	//@BACK: AK311 Eski koda g�re kontrol edilecek	*/

	//@LATER:
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void	sys_rfAdaptor_logModeRxConfig(typedef_rfAdaptor_device_st* dev){
			/*
		Radio.SetRxConfig(MODEM_FSK, 100000, 100000, 0, 83333, 5, 200, true, 16, true, false, 0, false, false);
	
		void RadioSetRxConfig( 	RadioModems_t modem, 			--------> MODEM_FSK
														uint32_t bandwidth,       --------> 100000			= FSK_BT2MODE_BANDWIDTH << 1
														uint32_t datarate,        --------> 100000			= FSK_BT2MODE_DATARATE
														uint8_t coderate,         --------> 0
														uint32_t bandwidthAfc,    --------> 83333
														uint16_t preambleLen,     --------> 5
														uint16_t symbTimeout,     --------> 200
														bool fixLen,              --------> true
														uint8_t payloadLen,       --------> 16
														bool crcOn,               --------> true	 
														bool freqHopOn,           --------> false
														uint8_t hopPeriod,        --------> 0
														bool iqInverted,          --------> false
														bool rxContinuous )	      --------> false
	//@BACK: AK311 Eski koda g�re kontrol edilecek 	*/
	
	//@LATER:
	
}





#endif

#define WMBUS_EN
#ifdef WMBUS_EN	 //@INFO: wmBus Mode Configurations
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
rt_err_t 			sys_rfAdaptor_wmBusInitConfig			( rt_uint8_t wmBusMode , rt_uint8_t mode ){

	rt_err_t result = RT_EOK;

	switch( wmBusMode )
	{
		case RF_WMBUS_MODE_PC:
			//result = sys_rfAdaptor_wmBusModePC(&wmBusConfig);			//@LATER
		break;
		
		case RF_WMBUS_MODE_BT2MODE:
			result = sys_rfAdaptor_ModeBT2(&typdef_rfAdaptor_dev , mode);
		break;
		
		case RF_WMBUS_MODE_BS2MODE:
			//result = sys_rfAdaptor_ModeBS2(&wmBusConfig);					//@LATER
		break;
		
		case RF_WMBUS_MODE_BT2LITEMODE:
			//result = sys_rfAdaptor_ModeBS2Lite(&wmBusConfig);			//@LATER
		break;
		
		case RF_WMBUS_MODE_RECEIVE:
			//result = sys_rfAdaptor_ModeReceive(&wmBusConfig);			//@LATER
		break;
		
	}
	return result;
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : BT2 Modu icin gerekli ayarlamalarin yapilmasi sirasiyla UV kodundan uyarlamistir.
						 Satir, satir 1276 ile 1262 karsilastirilip duzenlenmistir!

		// sys_rfAdaptor_changeChipMode(RF_OPMODE_SLEEP);//@INFO: Eski kod

	//	sys_rfAdaptor_writeData(SX1276_REG_OPMODE, RF_OPMODE_LONGRANGEMODE_OFF 		| 		//@INFO: Eski kod
	//																						 RF_OPMODE_MODULATIONTYPE_FSK 	|
	//																						 RF_OPMODE_MODULATIONSHAPING_00 |
	//																							RF_OPMODE_SLEEP);	//
	
[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 
// sys_rfAdaptor_writeData(SX1276_REG_BITRATEMSB, 	0x01); 	//@INFO: Eski kod , 
// sys_rfAdaptor_writeData(SX1276_REG_BITRATELSB, 	0x40);	//@INFO: Eski kod
		
	  1276 Bit Rate Ayarlamasi -> BR = FxOSC / ( BitRate(15:0) + (BitrateFrac/16) ) //@INFO: BitrateFrac etki etmez ! 
		BitRate(15:0) = (0x0140)h = (320)d
		BR = (32 * 10^6) / 320 = 10^5
		
		1262 Bit Rate Ayarlamasi -> 
		br = 32 * Fxtal / bit rate
		br = 32 * 32*10^6 / 32768 = (31250)d = (7A12)h

		//@NOTICE: wmBus Datasheet'inde "For mode T1 with a nominal chip rate of 100 kcps, the transmit 
		duration will be 2,9 ms" yazmaktadir 1276'da 1
]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

 [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 	
//	sys_rfAdaptor_writeData(SX1276_REG_FDEVMSB,		 	0x03); //@INFO: Eski kod
//	sys_rfAdaptor_writeData(SX1276_REG_FDEVLSB,			0x33); //@INFO: Eski kod

		1276 Fdev Ayarlamasi -> Fdev = Fstep * Fdev(13:0)			-> Fdev(13:0) = (0333)h = (819)d = (001100110011)b [12bit]
		// STEP Frequency synthesizer step FSTEP = FXOSC/219 - 61.0 - Hz
		Fdev = 819 * 61 = 49959 ~ 50kHz
		
		1276 Fdev Ayarlanmasi -> 
		Fdev = (Frequency Deviation * 2^25) / Fxtal 
		Fdev = (50*10^4 * 2^25) / 32*10^6 = (52428)d = (0xCCCC)h
		//@INFO: .../AK311_LORA_VANGO_RTThread/Docs/SX1262/WMBus/TS_EN_13757_4.pdf -> page 23 'te isaretlenmistir!
		

]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 			
		Power Amplifier Configs ; SX1262'de PA, verimliligi en �st d�zeye �ikarirken maksimum �ikis g�c� i�in optimize edilmistir.
		TXRMP Power amplifier ramping time Programmable 10 - 3400 ?s
		SetTxParams ile ayarlanmaktadir.
		
		Max Power -> default deger -> 22 dBm
	
]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

	// 	  sys_rfAdaptor_writeData(SX1276_REG_PARAMP,			0x06); //@INFO: Eski kod -> //@INFO : Gaussian filter BT = 0.5, Rise/Fall time of ramp up/down in FSK : 100us

[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 		

		TXDRP RF output power drop versus supply voltage	1262'de 22dB sabit Vbat'a g�re zayiflamaktadir.

		TXPRNG RF output power range Programmable in 31 steps, typical value TXOP-31 - TXOP dBm ;
		Programmable in 31 steps, typical value 

					SetPaConfig SPI Transaction
					Byte 				0					1				2				3				4
					host			0x95		pAduty		hpMax			0			always 0x01
					
	14dBm		i�in ->		0x95			0x02		0x02		 0x00			0x01

// 	  sys_rfAdaptor_writeData(SX1276_REG_PACONFIG,		RF_PACONFIG_14DBM_MSB );	//@DEL //@INFO: Eski kod 

]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 	
			sys_rfAdaptor_writeData(SX1276_REG_AFCBW,	0x0B);	/@DEL //@INFO: Eski kod
			//@INFO: AFC -> Automatic Frequency correction 1262'de b�yle bir ayarlama  yok. 1276'da 83kHz i�in TS_RE ? 97us
			sys_rfAdaptor_writeData(SX1276_REG_RXBW,	0x12); //@INFO : BW = 83KHz	 //@DEL //@INFO: Eski kod
			
			Receiver Startup Time Summary
			TS_RX Receiver wake-up time FS to RX - 41 - ?s
			
]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]	

[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 				
			
		1276'da SX1276_REG_PREAMBLEMSB reg adresi 0x25 PreambleSize(15:8)  
		1276'da SX1276_REG_PREAMBLELSB reg adresi 0x26 PreambleSize(7:0) 

			sys_rfAdaptor_writeData(SX1276_REG_PREAMBLEMSB,			0x00);
			sys_rfAdaptor_writeData(SX1276_REG_PREAMBLELSB,			0x05); //@INFO Preamble -> 5 byte
			
		1262'de PacketParams ile birlikte gonderilmesi gerekmektedir. 
		The preamble length is a 16-bit value which represents the number of bytes which will be sent by the radio. 
		Each preamble byte represents an alternate of 0 and 1 and each byte is coded as 0x55.

]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 
		 sys_rfAdaptor_writeData(SX1276_REG_SYNCCONFIG, 			0x91);	/@DEL //@INFO: Eski kod
			
			SX1276_REG_SYNCCONFIG Registeri 1276'da 0x27 adresindedir. (0x91)h = (10010001)b
			7-6 AutoRestartRxMode	----> 10 	-> On, wait for the PLL to lock (frequency changed) 
			5 	PreamblePolarity	----> 0 	-> 0xAA (default)
			4		SyncOn						----> 1 	-> On
			3		reserved
			2-0	SyncSize					----> 1 	->	(SyncSize + 1) bytes --> 2 BYTE
					
]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

 [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 
			sys_rfAdaptor_writeData(SX1276_REG_SYNCVALUE1, 			0x54);	/@DEL //@INFO: Eski kod
			sys_rfAdaptor_writeData(SX1276_REG_SYNCVALUE2, 			0x3D);	/@DEL //@INFO: Eski kod

			1262'de Sync Word dogrudan register uzerinden ayarlanabilmektedir.
]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 			
			//@INFO : Fixed length, Manchester, CRC ON, Auto Clear CRC when CRC check fail, Adrressing OFF, IBM CRC
			sys_rfAdaptor_writeData(SX1276_REG_PACKETCONFIG1, 		0x11); /@DEL //@INFO: Eski kod
			
			1276'da RegPacketConfig1 (0x30) adresinde bulunmaktadir.	-> (0x11)h = (00010001)b
			7 		PacketFormat				----> 	0 	-> Fixed length
			6-5 	DcFree              ---->	 00		-> None (Off)		//@ASK: MEFE //@INFO: UV'da yoruma manchester yazilmis fakat none secilmis !
			4 		CrcOn               ---->	 	1		-> On
			3 		CrcAutoClearOff     ---->		0 	-> Clear FIFO and restart new packet reception
			2-1 	AddressFiltering    ---->		00  -> None (Off)
			0 		CrcWhiteningType    ---->		1 	-> IBM CRC implementation with alternate whitening
			
			sys_rfAdaptor_writeData(SX1276_REG_PACKETCONFIG2, 		0x40); /@DEL //@INFO: Eski kod
			
			1276'da RegPacketConfig2 (0x31) adresinde bulunmaktadir.	-> (0x40)h = (00001000)b
			6 	DataMode							----> 0 		-> Continuous mode
			5 	IoHomeOn              ---->	0 		-> Disabled
			4 	IoHomePowerFrame      ----> reserved
			3 	BeaconOn              ---->	1 		-> Enables the Beacon mode in Fixed packet format
			2-0 PayloadLength(10:8)   ---->	Packet Length Most significant bits
			
]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]	

	//@INFO: The command SetRfFrequency(...) is used to set the frequency of the RF frequency mode. 
	
	RF(31:0) = RFfreq * Fxtal / 2^25
	
[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ 	
	// SX1262 badwidth is double sided
	Normalde girilen BW degerine gore ayarlamayi RadioGetFskBandwidthRegValue( bandwidth << 1 ) , radio.c'de yapmaktadir.
	Radio.c burada cagirilmayacagindan dolayi  bu fonk. sx126x olarak g�ncellendi !

]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

********************************************************************************/
rt_err_t 			sys_rfAdaptor_ModeBT2							( typedef_rfAdaptor_device_st* dev , rt_uint8_t mode){

		rt_err_t result = RT_EOK;
		rt_uint8_t tempRamp;				
	
		//@INFO: Paket tipi GFSK Ayarlaniyor.
		dev->drvObj.PacketParams.PacketType			= PACKET_TYPE_GFSK;			
		dev->drvObj.PacketStatus.PacketType			= PACKET_TYPE_GFSK;		
		dev->drvObj.ModulationParams.PacketType	= PACKET_TYPE_GFSK;		
	
		switch(mode)
		{
			case RF_WMBUS_MODE_TX : 
				
				result = dev->ops.SetRfFrequency( SYS_RFADAPTOR_BT2MODE_TX_FREQUENCY  );		//@INFO: 868.950 Mhz 
				if(result != RT_EOK) return RT_ERROR;	
			
				sys_rfAdaptor_BT2ModeTxConfig(dev);	// @INFO: TX i�in modulation ve packet param degerleri ayarlaniyor.	
				
				result = dev->ops.SetPacketType( PACKET_TYPE_GFSK );
				if(result != RT_EOK) return RT_ERROR;
			
				result = dev->ops.SetModulationParams( &dev->drvObj.ModulationParams  );
				if(result != RT_EOK) return RT_ERROR;
				
				result = dev->ops.SetPacketParams		( &dev->drvObj.PacketParams 			);
				if(result != RT_EOK) return RT_ERROR;	
				
				result = dev->ops.SetRfTxPower( 22 )	;	//@ASK: MEFE @INFO: SX126x k�t�phanesi hert�rl� 40us-22dBm ramp ayarliyor.
				if(result != RT_EOK) return RT_ERROR;	
			
				tempRamp = (rt_uint8_t)RADIO_RAMP_200_US;		 //@NOTICE: 100us olmadigi icin 40us ayarlandi.
				result = sys_rfAdaptor_writeCommand(RADIO_SET_TXPARAMS, (rt_uint8_t *)&tempRamp , 1 );	 //@INFO:  Rise/Fall time of ramp up/down in FSK : 100us
				if(result != RT_EOK) return RT_ERROR;
						
				result = dev->ops.SetPaConfig((RadioPaCommand_t)RADIO_OUTPUTPOWER_17DBM);							
				if(result != RT_EOK) return RT_ERROR;		
				
				result = dev->ops.SetSyncWord( &syncWordTx[0] );
				if(result != RT_EOK) return RT_ERROR;		
				
			
			break;
			
			case RF_WMBUS_MODE_RX :
				
				result = dev->ops.SetRfFrequency( SYS_RFADAPTOR_BT2MODE_RX_FREQUENCY );		//@INFO: 868.210 Mhz 
				if(result != RT_EOK) return RT_ERROR;	
				
				result = dev->ops.SetStopRxTimerOnPreambleDetect( RT_FALSE ); 
				if(result != RT_EOK) return RT_ERROR;	
			
				result = dev->ops.SetStandby( STDBY_RC );
				if(result != RT_EOK) return RT_ERROR;	
				
				result = dev->ops.SetPacketType( PACKET_TYPE_GFSK );
				if(result != RT_EOK) return RT_ERROR;
			
				sys_rfAdaptor_BT2ModeRxConfig(dev);				
			
				result = dev->ops.SetModulationParams( &dev->drvObj.ModulationParams  );
				if(result != RT_EOK) return RT_ERROR;
			
				result = dev->ops.SetPacketParams		( &dev->drvObj.PacketParams 			);
				if(result != RT_EOK) return RT_ERROR;	
				
				result = dev->ops.SetSyncWord( &syncWordRx[0] );
				if(result != RT_EOK) return RT_ERROR;	
		
			break;
		}
	
		

		
		return result;
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void 					sys_rfAdaptor_BT2ModeTxConfig			( typedef_rfAdaptor_device_st* dev){
	
	/*
		Radio.SetTxConfig(MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 100000, FSK_DATARATE, 0, FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON, false, 0, 0, 0, 100);
	
		void RadioSetTxConfig( 	RadioModems_t modem,		----->	MODEM_FSK
														int8_t power						----->	TX_OUTPUT_POWER	-> 22dBm
														uint32_t fdev,          ----->	FSK_FDEV				-> 50e3
														uint32_t bandwidth,     ----->	100000
														uint32_t datarate,      ----->	FSK_DATARATE		-> 100e3 
														uint8_t coderate,       ----->	0
														uint16_t preambleLen,   ----->	FSK_PREAMBLE_LENGTH
														bool fixLen,            ----->	FSK_FIX_LENGTH_PAYLOAD_ON
														bool crcOn,             ----->	false
														bool freqHopOn,         ----->	0
														uint8_t hopPeriod,      ----->	0
														bool iqInverted,        ----->	0
														uint32_t timeout )      ----->	100
	*/
	
	
		//@INFO:  Modulation Parametreleri ayarlaniyor. 
		dev->drvObj.ModulationParams.Params.Gfsk.BitRate						= (rt_uint32_t)SYS_RFADAPTOR_BT2MODE_DATARATE 					;	  
		dev->drvObj.ModulationParams.Params.Gfsk.Fdev 							= (rt_uint32_t)SYS_RFADAPTOR_BT2MODE_FDEV  							; 
		dev->drvObj.ModulationParams.Params.Gfsk.ModulationShaping 	= MOD_SHAPING_G_BT_05												;	 
		dev->drvObj.ModulationParams.Params.Gfsk.Bandwidth 					= (rt_uint8_t)dev->ops.RadioGetFskBandwidthRegValue(((uint32_t)SYS_RFADAPTOR_BT2MODE_BANDWIDTH<<1)); // @INFO: param->ModulationParams.Bandwidth //@BACK: UW Ayari yapilmiyor?		
		//@INFO: Paket parametreleri ayarlaniyor.
		dev->drvObj.PacketParams.Params.Gfsk.PreambleLength 				= BYTE2BIT( SYS_RFADAPTOR_BT2MODE_PREAMBLE_LENGTH )			;		//@INFO: 5 -> (40)d = (0x28)h
		dev->drvObj.PacketParams.Params.Gfsk.PreambleMinDetect 			= RADIO_PREAMBLE_DETECTOR_08_BITS 											;		
		dev->drvObj.PacketParams.Params.Gfsk.SyncWordLength 				= BYTE2BIT( SYS_RFADAPTOR_BT2MODE_SYNCWORD_LENGTH_TX )	;		//@INFO: 2 -> (16)d = (0x10)h	
		dev->drvObj.PacketParams.Params.Gfsk.HeaderType 						= RADIO_PACKET_FIXED_LENGTH 								; 	
		dev->drvObj.PacketParams.Params.Gfsk.AddrComp	 							= RADIO_ADDRESSCOMP_FILT_OFF								; 	
		dev->drvObj.PacketParams.Params.Gfsk.PayloadLength					= (rt_uint8_t)SYS_RFADAPTOR_BT2MODE_PAYLOAD_LENGTH_TX		;		
		dev->drvObj.PacketParams.Params.Gfsk.CrcLength							=	RADIO_CRC_OFF															;		
		dev->drvObj.PacketParams.Params.Gfsk.DcFree									= RADIO_DC_FREE_OFF 												;		

	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void 					sys_rfAdaptor_BT2ModeRxConfig			( typedef_rfAdaptor_device_st* dev){
	
		/*
		Radio.SetRxConfig(MODEM_FSK, 100000, 100000, 0, 83333, 5, 200, true, 16, true, false, 0, false, false);
	
		void RadioSetRxConfig( 	RadioModems_t modem, 			--------> MODEM_FSK
														uint32_t bandwidth,       --------> 100000			= FSK_BT2MODE_BANDWIDTH << 1
														uint32_t datarate,        --------> 100000			= FSK_BT2MODE_DATARATE
														uint8_t coderate,         --------> 0
														uint32_t bandwidthAfc,    --------> 83333
														uint16_t preambleLen,     --------> 5
														uint16_t symbTimeout,     --------> 200
														bool fixLen,              --------> true
														uint8_t payloadLen,       --------> 16
														bool crcOn,               --------> true	 
														bool freqHopOn,           --------> false
														uint8_t hopPeriod,        --------> 0
														bool iqInverted,          --------> false
														bool rxContinuous )	      --------> false
	*/
	
		//@INFO: Modulation Parametreleri ayarlaniyor. 
		dev->drvObj.ModulationParams.Params.Gfsk.BitRate 						= (rt_uint32_t)SYS_RFADAPTOR_BT2MODE_DATARATE 																											;	 
		dev->drvObj.ModulationParams.Params.Gfsk.Fdev 							= (rt_uint32_t)SYS_RFADAPTOR_BT2MODE_FDEV  																													; 
		dev->drvObj.ModulationParams.Params.Gfsk.ModulationShaping 	= MOD_SHAPING_OFF																																				;	 
		dev->drvObj.ModulationParams.Params.Gfsk.Bandwidth 					= (rt_uint8_t)dev->ops.RadioGetFskBandwidthRegValue( ((uint32_t)SYS_RFADAPTOR_BT2MODE_BANDWIDTH<<1) ) 	; 
		//@INFO: Paket parametreleri ayarlaniyor.
		dev->drvObj.PacketParams.Params.Gfsk.PreambleLength 				= 5 << 3/*BYTE2BIT( SYS_RFADAPTOR_BT2MODE_PREAMBLE_LENGTH )*/																				;	
		dev->drvObj.PacketParams.Params.Gfsk.PreambleMinDetect 			= RADIO_PREAMBLE_DETECTOR_08_BITS 																																	; 
		dev->drvObj.PacketParams.Params.Gfsk.SyncWordLength 				= 2 << 3/*BYTE2BIT( SYS_RFADAPTOR_BT2MODE_SYNCWORD_LENGTH_RX )*/																		;	
		dev->drvObj.PacketParams.Params.Gfsk.HeaderType 						= RADIO_PACKET_FIXED_LENGTH /*RADIO_PACKET_VARIABLE_LENGTH*/														;	
		dev->drvObj.PacketParams.Params.Gfsk.AddrComp	 							= RADIO_ADDRESSCOMP_FILT_OFF																														;	
		dev->drvObj.PacketParams.Params.Gfsk.PayloadLength					= (rt_uint8_t)SYS_RFADAPTOR_BT2MODE_PAYLOAD_LENGTH_RX																								;	//@INFO: 16 BYTE PAYLOAD
		dev->drvObj.PacketParams.Params.Gfsk.CrcLength							=	RADIO_CRC_2_BYTES_IBM																																	;	//@INFO: 2 BYTE CRC VAR.
		dev->drvObj.PacketParams.Params.Gfsk.DcFree									= RADIO_DC_FREE_OFF 																																		;		
	
}






#endif





#endif

/***********************************END OF FILE********************************/


