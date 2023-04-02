#ifndef __SX1262__PRIVATE_H__
#define	 __SX1262__PRIVATE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "sys_global__top.h"
#include "user_init.h"

#include "sx1262__definition.h"
#include "sys_rfAdaptor__public.h"

//#include "sys_buzzer__public.h"
//#include "sys_main__public.h"
//#include "sys_pulseIn__public.h"
//#include "sys_flash__public.h"
//#include "sys_rtc__public.h"
//#include "sys_lorawan__public.h"
//#include "sys_main__public.h"

RadioPacketTypes_t 					PacketType			;
RadioOperatingModes_t				operatingMode		;	
bool_t 							ImageCalibrated = RT_FALSE;

volatile 							RadioLoRaPacketLengthsMode_t LoRaHeaderType;
volatile 	uint32_t 			FrequencyError = 0;

//@INFO: SX1262 R/W Functions
err_t 						SetPacketType							( RadioPacketTypes_t packetType );
RadioPacketTypes_t 				GetPacketType							( void 										);
err_t 						SetTxParams								( int8_t power							,
																		 RadioRampTimes_t rampTime 					);
																										
err_t 						SetModulationParams	 					( ModulationParams_t *modulationParams 		);
err_t 						SetPacketParams							( PacketParams_t *packetParams 				);
err_t 						SetCadParams						 	( RadioLoRaCadSymbols_t cadSymbolNum		,
																		  uint8_t cadDetPeak						,
																		  uint8_t cadDetMin						,
																		  RadioCadExitModes_t cadExitMode	 		,
																		  uint32_t cadTimeout 					);
//@INFO: Buffer Base Functions																						 
err_t 						SetBufferBaseAddress					( uint8_t txBaseAddress					,
																		  uint8_t rxBaseAddress 					);
err_t 						GetRxBufferStatus						( uint8_t *payloadLength					,
																		  uint8_t *rxStartBufferPointer);
err_t 						GetPacketStatus							( PacketStatus_t *pktStatus 				);
//@INFO: SX1262 Special Functions
uint32_t					GetBoardTcxoWakeupTime						( void 										);
err_t 						SetRfFrequency							( uint32_t frequency 						);
err_t  					SetRfTxPower								( int8_t power 							);
err_t						SetLoRaSymbNumTimeout					( uint8_t symbNum 						);
err_t						CalibrateImage							( uint32_t freq 							);
err_t						SetSyncWord								( uint8_t * syncWord						);
err_t						SetCrcSeed								( uint16_t seed 							);
err_t						SetCrcPolynomial						( uint16_t polynomial 					);
err_t						SetWhiteningSeed						( uint16_t seed			 				);
uint32_t 				GetRandom									( void 										);
RadioError_t 				GetDeviceErrors								( void 										);
err_t 						ClearDeviceErrors						( void										);
uint32_t 				ConvertFreqInHzToPllStep					( uint32_t freqInHz 						);
uint8_t					RadioGetFskBandwidthRegValue				( uint32_t bandwidth 					);
RadioStatus_t 			GetStatus										( void										);
int8_t 					GetRssiInst									( void 										);
void 								AddRegisterToRetentionList			( uint16_t registerAddress 					);
err_t						WorkAround								( uint8_t mode							,
																		  uint8_t bandwidth 						);
//@INFO: Working Modes
err_t						SetFs									( void 										);
err_t						SetTx									( uint32_t timeout 					    );
err_t						SetRx									( uint32_t timeout 					    );
err_t						SetRxBoosted							( uint32_t timeout			 			);
err_t 						SetRxDutyCycle							( uint32_t rxTime						,
																	  uint32_t sleepTime 					);
err_t 						SetCad									( void 									   	);
err_t 						SetTxContinuousWave						( void 									   	);
err_t 						SetTxInfinitePreamble					( void 									   	);
err_t 						SetStopRxTimerOnPreambleDetect			( bool_t enable 						   	);
err_t 						SetRegulatorMode						( RadioRegulatorMode_t mode 			   	);
err_t 						SetPaConfig								( RadioPaCommand_t param				   	);
err_t 						SetRxTxFallbackMode						( uint8_t fallbackMode 				   	);
err_t						SetStandby								( uint8_t standbyTemp 				   	);
err_t						SetSleep								( uint8_t sleepTemp 					   	);
//@INFO: DIO IRQ Configurations
err_t	 					SetDioIrqParams							( uint16_t irqMask						,
																	  uint16_t dio1Mask					    ,
																	  uint16_t dio2Mask					    ,
																	  uint16_t dio3Mask 					    );
uint16_t 					GetIrqStatus				 			( void 													);
err_t						ClearIrqStatus							( uint16_t irq 							);
//@INFO: Payload Configurations
err_t						SetPayload								( uint8_t* payload						,
																	  size_t size							);
err_t 						GetPayload								( uint8_t *buffer						,
																	  uint8_t *size							,
																	  uint8_t maxSize 							);
err_t						SendPayload								( uint8_t 	*payload					,
																		  uint8_t 	size						,
																		  uint32_t timeout 						);

//SX126x_t 										SX126x ;	

//@NEW: aertekin //@INFO: sx1262 driver implementation 
const typedef_sx1262_ops_st typdef_sx1262_ops = {
	SetPacketType									,
	GetPacketType					        ,
	SetTxParams										,								
	SetModulationParams		        ,                	
	SetPacketParams				        ,                 	
	SetCadParams									,																																																			                           
	SetBufferBaseAddress		      ,                	
	GetRxBufferStatus				      ,                 		
	GetPacketStatus					      ,                 		
	GetBoardTcxoWakeupTime	      ,                  		
	SetRfFrequency					      ,                  		
	SetRfTxPower						      ,                  		
	SetLoRaSymbNumTimeout		      ,                  		
	CalibrateImage					      ,                 		
	SetSyncWord							      ,                  		
	SetCrcSeed							      ,                 		
	SetCrcPolynomial				      ,                 		
	SetWhiteningSeed				      ,                 		
	GetRandom								      ,                 		
	GetDeviceErrors					      ,                		
	ClearDeviceErrors							,
	ConvertFreqInHzToPllStep	 	  ,
	RadioGetFskBandwidthRegValue	,	
	GetStatus								      ,                   	
	GetRssiInst							      ,                   	
	AddRegisterToRetentionList	  ,                          	
	WorkAround										,										
	SetFs										      ,                		
	SetTx									        ,               	
	SetRx												  ,
	SetRxBoosted						      ,
	SetRxDutyCycle								,							
	SetCad								        ,
	SetTxContinuousWave		        ,
	SetTxInfinitePreamble	        ,
	SetStopRxTimerOnPreambleDetect, 
	SetRegulatorMode			        ,
	SetPaConfig						        ,
	SetRxTxFallbackMode		        ,
	SetStandby						        ,
	SetSleep							        ,
	SetDioIrqParams				        ,
	GetIrqStatus					        ,
	ClearIrqStatus				        ,
	SetPayload										,									
	GetPayload						        ,
	SendPayload						        ,
};

//@INFO: sx1262 bandwidth 
SX126xFskBandwidth_t SX126xFskBandwidths[] =	{
    { 4800  , 0x1F },
    { 5800  , 0x17 },
    { 7300  , 0x0F },
    { 9700  , 0x1E },
    { 11700 , 0x16 },
    { 14600 , 0x0E },
    { 19500 , 0x1D },
    { 23400 , 0x15 },
    { 29300 , 0x0D },
    { 39000 , 0x1C },
    { 46900 , 0x14 },
    { 58600 , 0x0C },
    { 78200 , 0x1B },
    { 93800 , 0x13 },
    { 117300, 0x0B },
    { 156200, 0x1A },
    { 187200, 0x12 },
    { 234300, 0x0A },
    { 312000, 0x19 },
    { 373600, 0x11 },
    { 467000, 0x09 },
    { 500000, 0x00 }, // Invalid Bandwidth
		};

#ifdef __cplusplus
}
#endif

#endif // __SX1262__PRIVATE_H__
/* */
