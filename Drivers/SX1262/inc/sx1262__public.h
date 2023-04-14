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
extern	sx1262_bool_t 						ImageCalibrated ;

//@NEW: aertekin //@INFO: 1262 driver functions exclusion	
extern const	typedef_sx1262_ops_st		typdef_sx1262_ops	;

//@INFO: FSK Bandwidths
extern SX126xFskBandwidth_t SX126xFskBandwidths[];

/******************************************************************************/

#if 1 //@INFO: Temel fonksiyonlar

extern	sx1262_uint8_t		SX126xReadRegister			( sx1262_uint16_t 	address	);

extern	sx1262_err_t 		SX126xWriteRegister			( sx1262_uint16_t 	address	 ,
														  sx1262_uint8_t 	value	);

extern 	sx1262_err_t		SX126xWriteRegisters		( sx1262_uint16_t 	address	 ,
														  sx1262_uint8_t* 	buffer	 ,
														  sx1262_size_t		size	 );

extern	sx1262_err_t		SX126xReadRegisters			( sx1262_uint16_t 	address	,
														  sx1262_uint8_t*	buffer	,
														  sx1262_size_t		size	);
#endif

extern uint32_t				SX126xGetDio1PinState		( void );







#ifdef __cplusplus
}
#endif

#endif // __SX1262_DEFINITION_H__
/* */
