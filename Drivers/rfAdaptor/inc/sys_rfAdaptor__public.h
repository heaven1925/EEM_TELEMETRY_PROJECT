/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    sys_rfAdaptor__public.h
  * @author	 Muhammet EFE , Atakan ERTEKiN
  * @version V1.0.0
  * @date		 16.09.2022
  * @rev     V1.0.0
  * @brief	 
********************************************************************************/
/************************************DEFINES***********************************/
#ifndef	__SYS_RFADAPTOR__PUBLIC_H__
#define __SYS_RFADAPTOR__PUBLIC_H__
/************************************INCLUDES***********************************/
#include "sys_rfAdaptor__definition.h"
#include "sys_rtc__definition.h"
#include "sx1262__definition.h"

/******************************************************************************/
//@NOTICE: Degisken Tanimlamalar //@LATER: Bir kismi UW'den kalmistir.
extern  sys_rfAdaptor_RFSTATUS_st 				sys_rfAdaptor_RFSTATUS;

extern 	sys_rfAdaptor_generalflags_ut			sys_rfAdaptor_generalflags;

extern	rt_uint32_t												sys_rfAdaptor_delayCounter		;

extern 	rt_uint16_t												irqStatus											;

//@NEW: aertekin //@INFO: Kutuphane parametre ve fonksiyonlarina kapali erisim yapisi exclusuion
extern 	typedef_rfAdaptor_device_st				typdef_rfAdaptor_dev;

/******************************************************************************/
//@INFO: RFAdaptor Read-Write Tanimlamalari
extern	rt_err_t 				sys_rfAdaptor_writeCommand							( RadioCommands_t command  						, 
																																	rt_uint8_t *buffer			 						, 
																																	rt_uint16_t size 				 						);
extern	rt_err_t 				sys_rfAdaptor_readStatus								( rt_uint8_t *buffer 									);
extern	rt_err_t 				sys_rfAdaptor_readCommand								( RadioCommands_t command							, 
																																	rt_uint8_t *buffer									, 
																																	rt_size_t size 											);
extern	rt_err_t				sys_rfAdaptor_writeRegisters						( rt_uint16_t 	address								,
																																	rt_uint8_t* 	buffer								,
																																	rt_size_t		size										);
extern	rt_err_t 				sys_rfAdaptor_writeRegister							( rt_uint16_t 	address								,
																																	rt_uint8_t 	value										);
extern	rt_err_t				sys_rfAdaptor_readRegisters							( rt_uint16_t 	address								,
																																	rt_uint8_t*	buffer									,
																																	rt_size_t	size											);
extern	rt_uint8_t			sys_rfAdaptor_readRegister							( rt_uint16_t 	address								);

extern	rt_err_t				sys_rfAdaptor_writeBuffer								( rt_uint8_t *buffer									, 
																																	rt_size_t size 											);
extern	rt_err_t				sys_rfAdaptor_readBuffer								( rt_uint8_t *buffer									, 
																																	rt_size_t size 											,
																																	rt_size_t	offset										);
extern	void 						sys_rfAdaptor_setOperatingMode					( rt_uint8_t mode 										);
extern	rt_uint8_t 			sys_rfAdaptor_getOperatingMode					( void 																);
//@INFO: RFAdaptor Init/Config for Modules
extern	typedef_rfAdaptor_device_st		sys_rfAdaptor_driverInit	(	void 																);

extern	rt_err_t 				sys_rfAdaptor_changeChipMode		 				( rt_uint8_t mode									 		, 
																																	rt_uint8_t modeConfig					 			, 
																																	rt_uint32_t timeout							 		);
																													
extern	rt_err_t 				sys_rfAdaptor_specificSettings	 				( rt_uint8_t rfMode 									, 
																																	rt_uint8_t mode 										,
																																	rt_uint8_t direction								);
																													
extern	rt_err_t 				sys_rfAdaptor_defaultParameters	 				( void 														 		);
extern	rt_err_t 				sys_rfAdaptor_init							 				(	rt_uint8_t mode											);
extern	rt_err_t				sys_rfAdaptor_deInit						 				( void 														 		);																				
extern	rt_err_t 				sys_rfAdaptor_initConfig				 				( void 														 		);

//@INFO: RFAdaptor Blocking Delay / irqRead
extern	void 						DelayMs																	( rt_uint32_t delayTime 							);
extern	rt_bool_t 			sys_rfAdaptor_readPin										( void 																);


extern	void						sys_rfAdaptor_bootModeRxConfig					(typedef_rfAdaptor_device_st* dev);
extern	void						sys_rfAdaptor_bootModeTxConfig					(typedef_rfAdaptor_device_st* dev);
extern	void						sys_rfAdaptor_valveModeTxConfig					(typedef_rfAdaptor_device_st* dev);
extern	void						sys_rfAdaptor_valveModeRxConfig					(typedef_rfAdaptor_device_st* dev);
extern	void						sys_rfAdaptor_logModeTxConfig						(typedef_rfAdaptor_device_st* dev);
extern	void						sys_rfAdaptor_logModeRxConfig						(typedef_rfAdaptor_device_st* dev);



#endif //end __SYS_RFADAPTOR__PUBLIC_H__
