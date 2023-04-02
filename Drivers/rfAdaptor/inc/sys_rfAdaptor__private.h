/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    sys_rfAdaptor__private.h
  * @author	 Muhammet EFE , Atakan ERTEKiN
  * @version V1.0.0
  * @date		 16.09.2022
  * @rev     V1.0.0
  * @brief	 
********************************************************************************/
/************************************DEFINES***********************************/
#ifndef	__SYS_RFADAPTOR__PRIVATE_H__
#define __SYS_RFADAPTOR__PRIVATE_H__
/************************************INCLUDES***********************************/
#include "sys_global__top.h"
#include "sys_rfAdaptor__definition.h"
#include "user_init.h"
#include "spi.h"

#include "sys_buzzer__public.h"
#include "sys_main__public.h"
#include "sys_pulseIn__public.h"
#include "sys_flash__public.h"
#include "sys_rtc__public.h"
#include "sys_lorawan__public.h"
#include "sys_valve__public.h"
#include "sys_main__public.h"
#include "sys_wmBus__public.h" 	//@ADD aertekin 5.09.2022
#include "sys_rfMode__public.h" //@ADD aertekin 15.11.2022

#include "LmHandler.h"					
#include "sx1262__public.h"			//@ADD aertekin 
#include "radio.h"							//@ADD aertekin	

/******************************************************************************/
rt_uint8_t syncWordTx[8] 		 = { 0x54, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
rt_uint8_t syncWordRx[8] 		 = { 0x54, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
/******************************************************************************/

/******************************************************************************/
//@INFO: RFAdaptor Temel Tanimlamalari

sys_rfAdaptor_generalflags_ut	sys_rfAdaptor_generalflags;

sys_rfAdaptor_RFSTATUS_st 			sys_rfAdaptor_RFSTATUS											=	{0}							;
rt_uint32_t											sys_rfAdaptor_delayCounter									=	0								;

struct rt_spi_device 						rt_spi_rfAdaptor														= { RT_NULL	}			;

typdef_rfAdaptor_irqHandlers		sys_rfAdaptor_irqHandlers										= { 0 }						;

typedef_rfAdaptor_device_st			typdef_rfAdaptor_dev 												;
/******************************************************************************/

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[					
//@NOTICE: Public Function Decleration
/******************************************************************************/
//@INFO: RFAdaptor Read-Write Tanimlamalari
rt_err_t 				sys_rfAdaptor_writeCommand							( RadioCommands_t command  						, 
																													rt_uint8_t *buffer			 						, 
																													rt_uint16_t size 				 						);
rt_err_t 				sys_rfAdaptor_readStatus								( rt_uint8_t *buffer 									);
rt_err_t 				sys_rfAdaptor_readCommand								( RadioCommands_t command							, 
																													rt_uint8_t *buffer									, 
																													rt_size_t size 											);
rt_err_t				sys_rfAdaptor_writeRegisters						( rt_uint16_t 	address								,
																													rt_uint8_t* 	buffer								,
																													rt_size_t		size										);
rt_err_t 				sys_rfAdaptor_writeRegister							( rt_uint16_t 	address								,
																													rt_uint8_t 	value										);
rt_err_t				sys_rfAdaptor_readRegisters							( rt_uint16_t 	address								,
																													rt_uint8_t*	buffer									,
																													rt_size_t	size											);
rt_uint8_t			sys_rfAdaptor_readRegister							( rt_uint16_t 	address								);

rt_err_t				sys_rfAdaptor_writeBuffer								( rt_uint8_t *buffer									, 
																													rt_size_t size 											);
rt_err_t				sys_rfAdaptor_readBuffer								( rt_uint8_t *buffer									, 
																													rt_size_t size 											,
																													rt_size_t	offset										);
void 						sys_rfAdaptor_setOperatingMode					( rt_uint8_t mode 										);
rt_uint8_t 			sys_rfAdaptor_getOperatingMode					( void 																);
//@INFO: RFAdaptor Init/Config for Modules
typedef_rfAdaptor_device_st		sys_rfAdaptor_driverInit	(	void 																);

rt_err_t 				sys_rfAdaptor_changeChipMode		 				( rt_uint8_t mode									 		, 
																													rt_uint8_t modeConfig					 			, 
																													rt_uint32_t timeout							 		);
																													
rt_err_t 				sys_rfAdaptor_specificSettings	 				( rt_uint8_t rfMode 									, 
																													rt_uint8_t mode 										,
																													rt_uint8_t direction								);
																													
rt_err_t 				sys_rfAdaptor_defaultParameters	 				( void 														 		);
rt_err_t 				sys_rfAdaptor_init							 				(	rt_uint8_t mode											);
rt_err_t				sys_rfAdaptor_deInit						 				( void 														 		);																				
rt_err_t 				sys_rfAdaptor_initConfig				 				( void 														 		);


//@INFO: RFAdaptor Blocking Delay / irqRead
void 						DelayMs																	( rt_uint32_t delayTime 							);
rt_bool_t 			sys_rfAdaptor_readPin										( void 																);
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
																													
																													
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[				
//@NOTICE: Private Function Decleration
/******************************************************************************/
//@INFO: RFAdaptor Base Init Functions
rt_err_t 				sys_rfAdaptor_gpioInit					 				( void																);
rt_err_t 				sys_rfAdaptor_spiInit						 				( void																);
rt_err_t 				sys_rfAdaptor_HW_Init						 				( void																);
rt_err_t 				sys_rfAdaptor_HW_deInit					 				( void																);
																													
/******************************************************************************/
//@INFO: RF Adaptor Interrupt Config / Functions
rt_err_t			  sys_rfAdaptor_tcxoInit					 				( void 															 	);
rt_err_t			  sys_rfAdaptor_setDio3AsTcxoCtrl	 				( RadioTcxoCtrlVoltage_t tcxoVoltage 	, 
																													rt_uint32_t timeout 							 	);					
rt_err_t				sys_rfAdaptor_rfSwitchInit							( void 															 	);
rt_err_t				sys_rfAdaptor_setDio2AsRfSwitchCtrl			( rt_bool_t enable 									 	);

rt_err_t 				sys_rfAdaptor_wmBusIRQHandler						(	rt_uint16_t irqStatus								);
rt_err_t				sys_rfAdaptor_txDoneIRQHandler					(	void																);
rt_err_t				sys_rfAdaptor_rxDoneIRQHandler					(	void																);
rt_err_t				sys_rfAdaptor_timeOutIRQHandler					(	void																);
rt_err_t				sys_rfAdaptor_preambleDetectedIRQHandler(	void																);
rt_err_t				sys_rfAdaptor_syncWordValidIRQHandler		(	void																);
rt_err_t				sys_rfAdaptor_crcError_IRQHandler				(	void																);
/******************************************************************************/
//@INFO: HW Timer  Functions
rt_device_t 		sys_adaptor_hwTimer = RT_NULL  ; //@INFO: HW-Timer Device

rt_err_t 				sys_rfAdaptor_hardwareTimerInit	 				( rt_uint32_t timeMS 							 		);
rt_err_t 				sys_rfAdaptor_btimerInit				 				( rt_uint32_t timeMS 							 		);
rt_err_t 				sys_rfAdaptor_btimerStart				 				( void 														 		);
rt_err_t				sys_rfAdaptor_btimerStop				 				( void 														 		);
void 						sys_rfAdaptor_delayMsBlocking		 				( rt_uint32_t delayTime 					 		);
/******************************************************************************/           		
//@INFO: Operating Mode  Functions                                                         		
rt_err_t				sys_rfAdaptor_checkDeviceReady	 				( void 														 		);
rt_err_t 			 	sys_rfAdaptor_waitOnBusy				 				( void 														 		);
rt_err_t				sys_rfAdaptor_chipReset					 				( void 														 		);
void 						sys_rfAdaptor_powerON						 				( void 														 		);
void 						sys_rfAdaptor_powerOFF					 				( void 														 		);
rt_err_t				sys_rfAdaptor_wakeUp				 						( void 														 		);
rt_err_t				sys_rfAdaptor_antSwMode			 						( void 														 		);		 																								
/******************************************************************************/           		
//@INFO: Init Routine Functions  

rt_err_t 				sys_rfAdaptor_wmBusInitConfig						( rt_uint8_t wmBusMode 								, 
																													rt_uint8_t mode											);
																													
void		 				sys_rfAdaptor_BT2ModeTxConfig						( typedef_rfAdaptor_device_st* dev		);
void		 				sys_rfAdaptor_BT2ModeRxConfig						( typedef_rfAdaptor_device_st* dev		);
/******************************************************************************/ 
//@INFO: wmBus Mode Init
rt_err_t 				sys_rfAdaptor_ModeBT2										( typedef_rfAdaptor_device_st* dev						, 
																													rt_uint8_t mode															);

/******************************************************************************/ 		
//@NEW: develop @INFO: RF-Mode Functions 
rt_err_t 				sys_rfAdaptor_pcInitConfig							(rt_uint8_t pcMode 		,  rt_uint8_t mode );

void				sys_rfAdaptor_bootModeRxConfig					(typedef_rfAdaptor_device_st* dev);
void				sys_rfAdaptor_bootModeTxConfig					(typedef_rfAdaptor_device_st* dev);
void				sys_rfAdaptor_valveModeTxConfig					(typedef_rfAdaptor_device_st* dev);
void				sys_rfAdaptor_valveModeRxConfig					(typedef_rfAdaptor_device_st* dev);
void				sys_rfAdaptor_logModeTxConfig						(typedef_rfAdaptor_device_st* dev);
void				sys_rfAdaptor_logModeRxConfig						(typedef_rfAdaptor_device_st* dev);





//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#endif //end __SYS_RFADAPTOR__PRIVATE_H__
/***********************************END OF FILE********************************/
