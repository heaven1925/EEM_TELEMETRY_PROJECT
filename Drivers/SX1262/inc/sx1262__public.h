#ifndef __SX1262__PUBLIC_H__
#define	 __SX1262__PUBLIC_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include 		"sx1262__definition.h"
#include		"sys_rfAdaptor__public.h"

extern 	RadioPacketTypes_t 					PacketType			;
extern	RadioOperatingModes_t				operatingMode		;
extern	bool_t 									ImageCalibrated ;

//@NEW: aertekin //@INFO: 1262 driver functions exclusion	
extern const	typedef_sx1262_ops_st				typdef_sx1262_ops		;

//@INFO: FSK Bandwidths
extern SX126xFskBandwidth_t SX126xFskBandwidths[];

/******************************************************************************/

#if 1 //@INFO: Temel fonksiyonlar

extern	uint8_t														SX126xReadRegister								( uint16_t 	address	);
																																								
extern	err_t 															SX126xWriteRegister								( uint16_t 	address	 ,
																																									uint8_t 	  value		 );
																																																				 
extern 	err_t															SX126xWriteRegisters							( uint16_t 	address	 ,
																																									uint8_t* 	buffer	 ,
																																									size_t		size			 );
																																								
extern	err_t															SX126xReadRegisters								( uint16_t 	address	,
																																									uint8_t*	buffer		,
																																									size_t	size				);
#endif

extern uint32_t														SX126xGetDio1PinState							( void );







#ifdef __cplusplus
}
#endif

#endif // __SX1262_DEFINITION_H__
/* */
