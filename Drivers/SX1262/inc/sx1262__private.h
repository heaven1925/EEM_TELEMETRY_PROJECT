#ifndef __SX1262__PRIVATE_H__
#define	 __SX1262__PRIVATE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "sx1262__definition.h"
#include "sys_rfAdaptor__public.h"

RadioPacketTypes_t 					PacketType			;
RadioOperatingModes_t				operatingMode		;	
sx1262_bool_t 						ImageCalibrated = SX1262_FALSE;

volatile 							RadioLoRaPacketLengthsMode_t LoRaHeaderType;
volatile 	sx1262_uint32_t 		FrequencyError = 0;

//@INFO: SX1262 R/W Functions
sx1262_err_t 						SetPacketType							( RadioPacketTypes_t packetType 			);
RadioPacketTypes_t 					GetPacketType							( void 										);
sx1262_err_t 						SetTxParams								( sx1262_int8_t power								,
																		 	  RadioRampTimes_t rampTime 				);
																										
sx1262_err_t 						SetModulationParams	 					( ModulationParams_t *modulationParams 		);
sx1262_err_t 						SetPacketParams							( PacketParams_t *packetParams 				);
sx1262_err_t 						SetCadParams						 	( RadioLoRaCadSymbols_t cadSymbolNum		,
																		      sx1262_uint8_t cadDetPeak					,
																		      sx1262_uint8_t cadDetMin					,
																		      RadioCadExitModes_t cadExitMode	 		,
																		      sx1262_uint32_t cadTimeout 				);
//@INFO: Buffer Base Functions																						 
sx1262_err_t 						SetBufferBaseAddress					( sx1262_uint8_t txBaseAddress				,
																		  	  sx1262_uint8_t rxBaseAddress 				);
sx1262_err_t 						GetRxBufferStatus						( sx1262_uint8_t *payloadLength				,
																		  	  sx1262_uint8_t *rxStartBufferPointer		);
sx1262_err_t 						GetPacketStatus							( PacketStatus_t *pktStatus 				);
//@INFO: SX1262 Special Functions
sx1262_uint32_t						GetBoardTcxoWakeupTime					( void 										);
sx1262_err_t 						SetRfFrequency							( sx1262_uint32_t frequency 				);
sx1262_err_t  						SetRfTxPower							( sx1262_int8_t power 						);
sx1262_err_t						SetLoRaSymbNumTimeout					( sx1262_uint8_t symbNum 					);
sx1262_err_t						CalibrateImage							( sx1262_uint32_t freq 						);
sx1262_err_t						SetSyncWord								( sx1262_uint8_t * syncWord					);
sx1262_err_t						SetCrcSeed								( sx1262_uint16_t seed 						);
sx1262_err_t						SetCrcPolynomial						( sx1262_uint16_t polynomial 				);
sx1262_err_t						SetWhiteningSeed						( sx1262_uint16_t seed			 			);
sx1262_uint32_t 					GetRandom								( void 										);
RadioError_t 						GetDeviceErrors							( void 										);
sx1262_err_t 						ClearDeviceErrors						( void										);
sx1262_uint32_t 					ConvertFreqInHzToPllStep				( sx1262_uint32_t freqInHz 					);
sx1262_uint8_t						RadioGetFskBandwidthRegValue			( sx1262_uint32_t bandwidth 				);
RadioStatus_t 						GetStatus								( void										);
sx1262_int8_t 						GetRssiInst								( void 										);
void 								AddRegisterToRetentionList				( sx1262_uint16_t registerAddress 			);
sx1262_err_t						WorkAround								( sx1262_uint8_t mode						,
																		  	  sx1262_uint8_t bandwidth 					);
//@INFO: Working Modes
sx1262_err_t						SetFs									( void 										);
sx1262_err_t						SetTx									( sx1262_uint32_t timeout 					);
sx1262_err_t						SetRx									( sx1262_uint32_t timeout 					);
sx1262_err_t						SetRxBoosted							( sx1262_uint32_t timeout			 		);
sx1262_err_t 						SetRxDutyCycle							( sx1262_uint32_t rxTime					,
																	  	  	  sx1262_uint32_t sleepTime 				);
sx1262_err_t 						SetCad									( void 									   	);
sx1262_err_t 						SetTxContinuousWave						( void 									   	);
sx1262_err_t 						SetTxInfinitePreamble					( void 									   	);
sx1262_err_t 						SetStopRxTimerOnPreambleDetect			( sx1262_bool_t enable 						);
sx1262_err_t 						SetRegulatorMode						( RadioRegulatorMode_t mode 			   	);
sx1262_err_t 						SetPaConfig								( RadioPaCommand_t param				   	);
sx1262_err_t 						SetRxTxFallbackMode						( sx1262_uint8_t fallbackMode 				);
sx1262_err_t						SetStandby								( sx1262_uint8_t standbyTemp 				);
sx1262_err_t						SetSleep								( sx1262_uint8_t sleepTemp 					);
//@INFO: DIO IRQ Configurations
sx1262_err_t	 					SetDioIrqParams							( sx1262_uint16_t irqMask					,
																	          sx1262_uint16_t dio1Mask					,
																	          sx1262_uint16_t dio2Mask					,
																	          sx1262_uint16_t dio3Mask 					);
sx1262_uint16_t 					GetIrqStatus				 			( void 								);
sx1262_err_t						ClearIrqStatus							( sx1262_uint16_t irq 						);
//@INFO: Payload Configurations
sx1262_err_t						SetPayload								( sx1262_uint8_t* payload					,
																	  	  	  sx1262_size_t size						);
sx1262_err_t 						GetPayload								( sx1262_uint8_t *buffer					,
																	  	  	  sx1262_uint8_t *size						,
																			  sx1262_uint8_t maxSize 					);
sx1262_err_t						SendPayload								( sx1262_uint8_t 	*payload				,
																		  	  sx1262_uint8_t 	size					,
																			  sx1262_uint32_t timeout 					);

//SX126x_t 										SX126x ;	

//@NEW: aertekin //@INFO: sx1262 driver implementation 
const typedef_sx1262_ops_st typdef_sx1262_ops = {
	SetPacketType					,
	GetPacketType					,
	SetTxParams						,
	SetModulationParams		        ,
	SetPacketParams				    ,
	SetCadParams					,
	SetBufferBaseAddress		    ,
	GetRxBufferStatus				,
	GetPacketStatus					,
	GetBoardTcxoWakeupTime	        ,
	SetRfFrequency				 	,
	SetRfTxPower				    ,
	SetLoRaSymbNumTimeout			,
	CalibrateImage					,
	SetSyncWord					    ,
	SetCrcSeed					    ,
	SetCrcPolynomial				,
	SetWhiteningSeed				,
	GetRandom					    ,
	GetDeviceErrors					,
	ClearDeviceErrors			    ,
	ConvertFreqInHzToPllStep	    ,
	RadioGetFskBandwidthRegValue    ,
	GetStatus					    ,
	GetRssiInst					    ,
	AddRegisterToRetentionList	 	,
	WorkAround						,
	SetFs							,
	SetTx							,
	SetRx							,
	SetRxBoosted					,
	SetRxDutyCycle					,
	SetCad							,
	SetTxContinuousWave		        ,
	SetTxInfinitePreamble	        ,
	SetStopRxTimerOnPreambleDetect  ,
	SetRegulatorMode			    ,
	SetPaConfig						,
	SetRxTxFallbackMode		        ,
	SetStandby						,
	SetSleep						,
	SetDioIrqParams				    ,
	GetIrqStatus					,
	ClearIrqStatus				    ,
	SetPayload						,
	GetPayload						,
	SendPayload						,
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
