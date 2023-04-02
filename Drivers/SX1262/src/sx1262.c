
#include "sx1262__private.h"
//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
#if 1 //@INFO: SX1262 Temel fonksiyonlar //@NOTICE: rfAdaptor SPI Implementation
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 		SX126xWriteCommand								( RadioCommands_t command				, 
																								uint8_t *buffer						, 
																								uint16_t size 							){
	err_t	result = RT_EOK;
	
	result = sys_rfAdaptor_writeCommand(command , buffer , size );
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
err_t 		SX126xReadCommand									( RadioCommands_t command				, 
																									uint8_t *buffer					, 
																									size_t size 							){
	err_t	result = RT_EOK;
																										
	result = sys_rfAdaptor_readCommand(command , buffer , size);
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
err_t 		SX126xWriteRegister								( uint16_t 	address					,
																								uint8_t 	  value						){
																				 
	err_t	result = RT_EOK;
																			 
	result = sys_rfAdaptor_writeRegister(address , value);
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
rt_uint8_t	SX126xReadRegister								( uint16_t 	address					){
	
	uint8_t data;

	data = sys_rfAdaptor_readRegister(address);
	
	return data;
	
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t		SX126xWriteRegisters							( uint16_t 	address					,
																								uint8_t* 	buffer					,
																								size_t		size							){
	err_t result = RT_EOK;
	
	result = sys_rfAdaptor_writeRegisters(address , buffer , size);
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
err_t		SX126xReadRegisters								( uint16_t 	address					,
																								uint8_t*	buffer						,
																								size_t	size								){
	err_t result = RT_EOK;
	
	result = sys_rfAdaptor_readRegisters(address , buffer , size);
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
err_t		SX126xWriteBuffer									( uint8_t *buffer						,
                                              	size_t  size 							){
																									
	err_t result = RT_EOK;
	
	result = sys_rfAdaptor_writeBuffer(buffer , size);
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
err_t		SX126xReadBuffer									( uint8_t *buffer						, 
																								size_t size 								,
																								size_t	offset							){

	err_t result = RT_EOK;
	
	result = sys_rfAdaptor_readBuffer(buffer , size , offset);
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
void 				SX126xSetOperatingMode						( RadioOperatingModes_t mode 		){
	
	sys_rfAdaptor_setOperatingMode(mode);
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
RadioOperatingModes_t SX126xGetOperatingMode	( void 													){
	
	RadioOperatingModes_t tempMode ;
	
	tempMode = (RadioOperatingModes_t)sys_rfAdaptor_getOperatingMode();
	
	return tempMode;
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
uint32_t	SX126xGetDio1PinState							( void 													){
	
	bool_t result = RT_TRUE;
	
	result = sys_rfAdaptor_readPin();
	
	return (uint32_t)result;
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t		SX126xReadStatus									( uint8_t *buffer 						){
	
	err_t	result = RT_EOK;
																			 
	result = sys_rfAdaptor_readStatus(buffer);
	if(result != RT_EOK) return RT_ERROR;																		 
																			 
	return result;	
	
	
}

#endif
/*******************************************************************************/
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#if 1 //@INFO:  R/W Functions
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					 SetPacketType							( RadioPacketTypes_t packetType ){
	
	err_t result = RT_EOK;
	
	// Save packet type internally to avoid questioning the radio
  PacketType = packetType;
  result = SX126xWriteCommand( RADIO_SET_PACKETTYPE, ( rt_uint8_t* )&packetType, 1 );
	if(result != RT_EOK) return RT_ERROR;			
	
	return result ;
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
RadioPacketTypes_t GetPacketType							( void 													){
	
	return PacketType;	
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					 SetTxParams								( int8_t power								, 
																								RadioRampTimes_t rampTime 		){
																			
		//@NOTICE:  1262 kullanildigi icin 1261 ayari kaldirilmistir !
		err_t result = RT_EOK;
		uint8_t buf[2];
		
		// WORKAROUND - Better Resistance of the SX1262 Tx to Antenna Mismatch, see DS_SX1261-2_V1.2 datasheet chapter 15.2		
		result = SX126xWriteRegister(  REG_TX_CLAMP_CFG																									, 
																(  SX126xReadRegister( REG_TX_CLAMP_CFG ) | ( 0x0F << 1 ) ) );
		
		if(result != RT_EOK) return RT_ERROR;																																		
		// WORKAROUND END
		/* rt_err_t sys_rfAdaptor_setPaConfig( rt_uint8_t paDutyCycle, rt_uint8_t hpMax, rt_uint8_t deviceSel, rt_uint8_t paLut ) */
			
		result = SetPaConfig( (RadioPaCommand_t)RADIO_OUTPUTPOWER_14DBM );
		if(result != RT_EOK) return RT_ERROR;		
																			
		if( power > 22 )
		{
				power = 22;
		}
		else if( power < -9 )
		{
				power = -9;
		}
		
    buf[0] = power;
    buf[1] = ( rt_uint8_t )rampTime;
		
    result = SX126xWriteCommand( RADIO_SET_TXPARAMS, buf, 2 );

		return result;
										
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					 SetModulationParams	 			( ModulationParams_t *modulationParams ){
	
		err_t result = RT_EOK;

    uint32_t tempVal = RT_NULL;
    uint8_t buf[8] = { NOP_MSG };

    // Check if required configuration corresponds to the stored packet type
    // If not, silently update radio packet type
    if( PacketType != modulationParams->PacketType )
    {
        result = SetPacketType( modulationParams->PacketType );
    }

    switch( modulationParams->PacketType )
    {
    case PACKET_TYPE_GFSK:
		//@INFO: GFSK Paketi seçimi yapildiysa,	
        tempVal = ( uint32_t )( 32 * SX126X_XTAL_FREQ / modulationParams->Params.Gfsk.BitRate );
        buf[0]  = ( tempVal >> 16 ) & 0xFF;
        buf[1]  = ( tempVal >> 8 ) & 0xFF;
        buf[2]  = tempVal & 0xFF;
        buf[3]  = modulationParams->Params.Gfsk.ModulationShaping;
        buf[4]  = modulationParams->Params.Gfsk.Bandwidth;
        tempVal = ConvertFreqInHzToPllStep( modulationParams->Params.Gfsk.Fdev );
        buf[5]  = ( tempVal >> 16 ) & 0xFF;
        buf[6]  = ( tempVal >> 8 ) & 0xFF;
        buf[7]  = ( tempVal & 0xFF );
		
        result = SX126xWriteCommand( RADIO_SET_MODULATIONPARAMS, buf, 8 );
				if(result != RT_EOK) return RT_ERROR;
		
        break;
		
    case PACKET_TYPE_LORA:
		//@INFO: Lora Paketi seçimi yapildiysa,	
        buf[0] = modulationParams->Params.LoRa.SpreadingFactor;
        buf[1] = modulationParams->Params.LoRa.Bandwidth;
        buf[2] = modulationParams->Params.LoRa.CodingRate;
        buf[3] = modulationParams->Params.LoRa.LowDatarateOptimize;

        result = SX126xWriteCommand( RADIO_SET_MODULATIONPARAMS, buf, 4);
				if(result != RT_EOK) return RT_ERROR;
		
        break;
    default:
			
    case PACKET_TYPE_NONE:
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
err_t 					 SetPacketParams						( PacketParams_t *packetParams 	){
		err_t result = RT_EOK;
	
	  uint8_t n;
    uint8_t crcVal = RT_NULL;
    uint8_t buf[9] = { RT_NULL };

    // Check if required configuration corresponds to the stored packet type
    // If not, silently update radio packet type
    if( PacketType != packetParams->PacketType )
    {
        result = SetPacketType( packetParams->PacketType );
				if(result != RT_EOK) return RT_ERROR;
    }

    switch( packetParams->PacketType )
    {
    case PACKET_TYPE_GFSK:
        if( packetParams->Params.Gfsk.CrcLength == RADIO_CRC_2_BYTES_IBM )
        {
            result = SetCrcSeed( CRC_IBM_SEED );
						if(result != RT_EOK) return RT_ERROR;
					
            result = SetCrcPolynomial( CRC_POLYNOMIAL_IBM );
            if(result != RT_EOK) return RT_ERROR;
					
						crcVal = RADIO_CRC_2_BYTES;
        }
        else if( packetParams->Params.Gfsk.CrcLength == RADIO_CRC_2_BYTES_CCIT )
        {
            result = SetCrcSeed( CRC_CCITT_SEED );
						if(result != RT_EOK) return RT_ERROR;
					
            result = SetCrcPolynomial( CRC_POLYNOMIAL_CCITT );
						if(result != RT_EOK) return RT_ERROR;
					
            crcVal = RADIO_CRC_2_BYTES_INV;
        }
        else
        {
            crcVal = packetParams->Params.Gfsk.CrcLength;
        }
				
				
        n = 9;
        buf[0] = ( packetParams->Params.Gfsk.PreambleLength >> 8 ) & 0xFF;
        buf[1] = packetParams->Params.Gfsk.PreambleLength;
        buf[2] = packetParams->Params.Gfsk.PreambleMinDetect;
        buf[3] = ( packetParams->Params.Gfsk.SyncWordLength /*<< 3*/ ); // convert from byte to bit
        buf[4] = packetParams->Params.Gfsk.AddrComp;
        buf[5] = packetParams->Params.Gfsk.HeaderType;
        buf[6] = packetParams->Params.Gfsk.PayloadLength;
        buf[7] = crcVal;
        buf[8] = packetParams->Params.Gfsk.DcFree;
				
        break;
				
    case PACKET_TYPE_LORA:
			
        n = 6;
        buf[0] = ( packetParams->Params.LoRa.PreambleLength >> 8 ) & 0xFF;
        buf[1] = packetParams->Params.LoRa.PreambleLength;
        buf[2] = LoRaHeaderType = packetParams->Params.LoRa.HeaderType;
        buf[3] = packetParams->Params.LoRa.PayloadLength;
        buf[4] = packetParams->Params.LoRa.CrcMode;
        buf[5] = packetParams->Params.LoRa.InvertIQ;
		
        break;
    default:
    case PACKET_TYPE_NONE:
        return RT_ERROR;
    }
		
    result = SX126xWriteCommand( RADIO_SET_PACKETPARAMS, buf, n );

		return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					 SetCadParams						 		( RadioLoRaCadSymbols_t cadSymbolNum, 
																						 uint8_t cadDetPeak						 , 
																						 uint8_t cadDetMin						 , 
																						 RadioCadExitModes_t cadExitMode	     , 
																						 uint32_t cadTimeout 					){
																			 
		err_t result = RT_EOK;
																			 
		uint8_t buf[7];
	buf[0] = ( uint8_t )cadSymbolNum;
    buf[1] = cadDetPeak;
    buf[2] = cadDetMin;
    buf[3] = ( rt_uint8_t )cadExitMode;
    buf[4] = ( rt_uint8_t )( ( cadTimeout >> 16 ) & 0xFF );
    buf[5] = ( rt_uint8_t )( ( cadTimeout >> 8 ) 	& 0xFF );
    buf[6] = ( rt_uint8_t )( 	 cadTimeout 				& 0xFF );
																			 
    result = SX126xWriteCommand( RADIO_SET_CADPARAMS, buf, 7 );
    if(result != RT_EOK) return RT_ERROR;
																			 
		SX126xSetOperatingMode( MODE_CAD );																																				 

		return result;																	 
}

//@INFO: Buffer Base Functions
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					 SetBufferBaseAddress				( uint8_t txBaseAddress			,
																								uint8_t rxBaseAddress 			){
    err_t result = RT_EOK;
																			 
	  uint8_t buf[2];
    buf[0] = txBaseAddress;
    buf[1] = rxBaseAddress;
																			 
    result = SX126xWriteCommand( RADIO_SET_BUFFERBASEADDRESS, buf, 2 );
																			 
		return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					 GetRxBufferStatus					( uint8_t *payloadLength			, 
																								uint8_t *rxStartBufferPointer){
		err_t result = RT_EOK;																
																		
    uint8_t status[2];

    result = SX126xReadCommand( RADIO_GET_RXBUFFERSTATUS, &status[0], 2 );
			if(result != RT_EOK) return RT_ERROR;		

    // In case of LORA fixed header, the payloadLength is obtained by reading
    // the register REG_LR_PAYLOADLENGTH
    if( ( GetPacketType() == PACKET_TYPE_LORA ) && 
				( LoRaHeaderType == LORA_PACKET_FIXED_LENGTH 				) 	 )		
    {
        *payloadLength = SX126xReadRegister( REG_LR_PAYLOADLENGTH );
    }
    else
    {
        *payloadLength = status[0];
    }
    *rxStartBufferPointer = status[1];
		
		return result;
		
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					 GetPacketStatus						( PacketStatus_t *pktStatus 		){
		err_t result = RT_EOK;
	
    uint8_t status[3];

    result = SX126xReadCommand( RADIO_GET_PACKETSTATUS, &status[0], 3 );
		if(result != RT_EOK) return RT_ERROR;			
	
    pktStatus->PacketType = GetPacketType( );
	
    switch( pktStatus->PacketType )
    {
        case PACKET_TYPE_GFSK:
            pktStatus->Params.Gfsk.RxStatus = status[0];
            pktStatus->Params.Gfsk.RssiSync = -status[1] >> 1;
            pktStatus->Params.Gfsk.RssiAvg = -status[2] >> 1;
            pktStatus->Params.Gfsk.FreqError = 0;
            break;

        case PACKET_TYPE_LORA:
            pktStatus->Params.LoRa.RssiPkt = -status[0] >> 1;
            // Returns SNR value [dB] rounded to the nearest integer value
            pktStatus->Params.LoRa.SnrPkt = ( ( ( int8_t )status[1] ) + 2 ) >> 2;
            pktStatus->Params.LoRa.SignalRssiPkt = -status[2] >> 1;
            pktStatus->Params.LoRa.FreqError = FrequencyError;
            break;

        default:
        case PACKET_TYPE_NONE:
            // In that specific case, we set everything in the pktStatus to zeros
            // and reset the packet type accordingly
            memset( pktStatus, 0, sizeof( PacketStatus_t ) );
            pktStatus->PacketType = PACKET_TYPE_NONE;
            break;
    }
		
		return result;
		
}
#endif

#if 1 //@INFO: SX1262 Special Functions
/********************START OF RF ADAPTOR SPECIAL FUNCTIONS**********************/
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
uint32_t				GetBoardTcxoWakeupTime		( void 													){
	return	BOARD_TCXO_WAKEUP_TIME;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					SetRfFrequency						( uint32_t frequency 						){
	
		err_t result = RT_EOK;
	  uint8_t buf[4];

    if( ImageCalibrated == RT_FALSE )
    {
        result = CalibrateImage( frequency );
				if( result != RT_EOK ) return RT_ERROR;
			
        ImageCalibrated = RT_TRUE;
    }

    rt_uint32_t freqInPllSteps = ConvertFreqInHzToPllStep( frequency );

    buf[0] = ( uint8_t )( ( freqInPllSteps >> 24 ) & 0xFF );
    buf[1] = ( uint8_t )( ( freqInPllSteps >> 16 ) & 0xFF );
    buf[2] = ( uint8_t )( ( freqInPllSteps >> 8 ) 	& 0xFF );
    buf[3] = ( uint8_t )( 	 freqInPllSteps 				& 0xFF );
    	
		result = SX126xWriteCommand( RADIO_SET_RFFREQUENCY, buf, 4 );
	
		return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t  				SetRfTxPower							( int8_t power 							){
		err_t result = RT_EOK;
	
	result = SetTxParams( power, RADIO_RAMP_40_US );	//@BACK: 1276'da 100us olmaktadir.
	
		return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetLoRaSymbNumTimeout			( uint8_t symbNum 						){
	
	err_t result = RT_EOK;
	
  uint8_t mant = ( ( ( symbNum > SX126X_MAX_LORA_SYMB_NUM_TIMEOUT ) ?
													SX126X_MAX_LORA_SYMB_NUM_TIMEOUT : 
													symbNum ) + 1 ) >> 1;
	
  uint8_t exp  = 0;
  uint8_t reg  = 0;

  while( mant > 31 )
  {
      mant = ( mant + 3 ) >> 2;
      exp++;
  }

  reg = mant << ( 2 * exp + 1 );
  result = SX126xWriteCommand( RADIO_SET_LORASYMBTIMEOUT, &reg, 1 );
  if(result != RT_EOK) return RT_ERROR;
	
  if( symbNum != 0 )
  {
      reg = exp + ( mant << 3 );
      result = SX126xWriteRegister( REG_LR_SYNCH_TIMEOUT, reg );
			if(result != RT_EOK) return RT_ERROR;
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
err_t					CalibrateImage						( uint32_t freq 							){
	
	  err_t	result = RT_EOK;
	  uint8_t calFreq[2];

    if( freq > 900000000 )
    {
        calFreq[0] = 0xE1;
        calFreq[1] = 0xE9;
    }
    else if( freq > 850000000 )
    {
        calFreq[0] = 0xD7;
        calFreq[1] = 0xDB;
    }
    else if( freq > 770000000 )
    {
        calFreq[0] = 0xC1;
        calFreq[1] = 0xC5;
    }
    else if( freq > 460000000 )
    {
        calFreq[0] = 0x75;
        calFreq[1] = 0x81;
    }
    else if( freq > 425000000 )
    {
        calFreq[0] = 0x6B;
        calFreq[1] = 0x6F;
    }
    
		result = SX126xWriteCommand( RADIO_CALIBRATEIMAGE, calFreq, 2 );

		return result;
}

/*******************************************************************************
  @func    : 
  @param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetSyncWord								( uint8_t * syncWord					){
	err_t result = RT_EOK;
	
	result = SX126xWriteRegisters( REG_LR_SYNCWORDBASEADDRESS, syncWord, 8 );
	
	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetCrcSeed								( uint16_t seed 							){
		err_t result = RT_EOK;
	
	  uint8_t buf[2];

    buf[0] = ( uint8_t )( ( seed >> 8 ) & 0xFF );
    buf[1] = ( uint8_t )( 	 seed 			 & 0xFF );

    switch( GetPacketType() )
    {
		//@INFO: GFSK Paket tipi için CRC SEED
      case PACKET_TYPE_GFSK:
				
        result = SX126xWriteRegisters( REG_LR_CRCSEEDBASEADDR, buf, 2 );
			  if(result != RT_EOK) return RT_ERROR;	
			
      break;
		//@INFO: Hatali paket tipi 
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
err_t					SetCrcPolynomial					( uint16_t polynomial 				){
		err_t result = RT_EOK;
	  
		uint8_t buf[2];

    buf[0] = ( uint8_t )( ( polynomial >> 8 ) & 0xFF );
    buf[1] = ( uint8_t )( polynomial & 0xFF );

    switch( GetPacketType() )
    {
		//@INFO: GFSK Paket tipi için CRC Poly
			case PACKET_TYPE_GFSK:
				
        result = SX126xWriteRegisters( REG_LR_CRCPOLYBASEADDR, buf, 2 );
				if(result != RT_EOK) return RT_ERROR;
			
      break;
	  //@INFO: Hatali paket tipi CRC Poly
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
err_t					SetWhiteningSeed					( uint16_t seed			 				){
		
		err_t	result = RT_EOK;
	  uint8_t regValue = 0;
    
    switch( GetPacketType() )
    {
        case PACKET_TYPE_GFSK:
            regValue = (uint8_t)( SX126xReadRegister( REG_LR_WHITSEEDBASEADDR_MSB ) & 0xFE );
            regValue = (uint8_t)(( ( seed >> 8 ) & 0x01 ) | regValue );
				
            result = SX126xWriteRegister( REG_LR_WHITSEEDBASEADDR_MSB, regValue ); // only 1 bit.
						if(result != RT_EOK) return RT_ERROR;
				
            result = SX126xWriteRegister( REG_LR_WHITSEEDBASEADDR_LSB, ( uint8_t )seed );
						if(result != RT_EOK) return RT_ERROR;
				
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
rt_uint32_t 			GetRandom									( void 													){
	
		uint32_t number = 0;
    uint8_t regAnaLna = 0;
    uint8_t regAnaMixer = 0;

    regAnaLna = SX126xReadRegister( REG_ANA_LNA );
    SX126xWriteRegister( REG_ANA_LNA, regAnaLna & ~( 1 << 0 ) );

    regAnaMixer = SX126xReadRegister( REG_ANA_MIXER );
    SX126xWriteRegister( REG_ANA_MIXER, regAnaMixer & ~( 1 << 7 ) );

    // Set radio in continuous reception
    SetRx( 0xFFFFFF ); // Rx Continuous

    SX126xReadRegisters( RANDOM_NUMBER_GENERATORBASEADDR, ( uint8_t* )&number, 4 );

    SetStandby( STDBY_RC );

    SX126xWriteRegister( REG_ANA_LNA, regAnaLna );
    SX126xWriteRegister( REG_ANA_MIXER, regAnaMixer );

    return number;
	
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
RadioError_t 			GetDeviceErrors						( void 													){
	
	uint8_t err[] = { 0, 0 };
  RadioError_t error = { .Value = 0 };	//@BACK: Value degeri farklilik gosterebilir

	SX126xReadCommand( RADIO_GET_ERROR, ( uint8_t* )err, 2 );
	
  error.Fields.PaRamp     = ( err[0] & ( 1 << 7 ) ) >> 7;		//@BACK
  error.Fields.PllLock    = ( err[1] & ( 1 << 6 ) ) >> 6;
  error.Fields.XoscStart  = ( err[1] & ( 1 << 5 ) ) >> 5;
  error.Fields.ImgCalib   = ( err[1] & ( 1 << 4 ) ) >> 4;
  error.Fields.AdcCalib   = ( err[1] & ( 1 << 3 ) ) >> 3;
  error.Fields.PllCalib   = ( err[1] & ( 1 << 2 ) ) >> 2;
  error.Fields.Rc13mCalib = ( err[1] & ( 1 << 1 ) ) >> 1;
  error.Fields.Rc64kCalib = ( err[1] & ( 1 << 0 ) ) >> 0;
	
  return error;
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					ClearDeviceErrors					( void													){
	
	    err_t result = RT_EOK;
		uint8_t buf[2] = { RT_NULL };
		
    result = SX126xWriteCommand( RADIO_CLR_ERROR, buf, 2 );
		
		return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
uint32_t 			ConvertFreqInHzToPllStep	( uint32_t freqInHz 					){
    uint32_t stepsInt;
    uint32_t stepsFrac;

    // pllSteps = freqInHz / (SX126X_XTAL_FREQ / 2^19 )
    // Get integer and fractional parts of the frequency computed with a PLL step scaled value
    stepsInt = freqInHz / SX126X_PLL_STEP_SCALED;
    stepsFrac = freqInHz - ( stepsInt * SX126X_PLL_STEP_SCALED );
    
    // Apply the scaling factor to retrieve a frequency in Hz (+ ceiling)
    return ( stepsInt << SX126X_PLL_STEP_SHIFT_AMOUNT ) + 
           ( ( ( stepsFrac << SX126X_PLL_STEP_SHIFT_AMOUNT ) + ( SX126X_PLL_STEP_SCALED >> 1 ) ) /
             SX126X_PLL_STEP_SCALED );
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
uint8_t				RadioGetFskBandwidthRegValue( uint32_t bandwidth 			){
	
	
		uint8_t i;

    if( bandwidth == 0 )
    {
        return( 0x1F );
    }

    for( i = 0; i < ( sizeof( SX126xFskBandwidths ) / sizeof( SX126xFskBandwidth_t ) ) - 1; i++ )
    {
        if( ( bandwidth >= SX126xFskBandwidths[i].bandwidth ) && ( bandwidth < SX126xFskBandwidths[i + 1].bandwidth ) )
        {
            return SX126xFskBandwidths[i+1].RegValue;
        }
    }
	
		return 0x1F;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
RadioStatus_t 		GetStatus									( void													){
	
	  uint8_t stat = 0;
	
    RadioStatus_t status ;			
		status.value = RT_NULL;
		
		SX126xReadStatus( &stat );
		
    status.Fields.CmdStatus = ( stat & ( 0x07 << 1 ) ) >> 1;
    status.Fields.ChipMode 	= ( stat & ( 0x07 << 4 ) ) >> 4;
		
    return status;
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
int8_t 				GetRssiInst								( void 													){
	
    uint8_t buf = 0;
    int8_t 	rssi = 0;

    SX126xReadCommand( RADIO_GET_RSSIINST, &buf, 1 );
    rssi = -buf >> 1;
	
    return rssi;
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
void 							AddRegisterToRetentionList( uint16_t registerAddress 			){
    uint8_t buffer[9];

    // Read the address and registers already added to the list
    SX126xReadRegisters( REG_RETENTION_LIST_BASE_ADDRESS, buffer, 9 );

    const uint8_t nbOfRegisters = buffer[0];
    uint8_t* registerList   = &buffer[1];

    // Check if the register given as parameter is already added to the list
    for( uint8_t i = 0; i < nbOfRegisters; i++ )
    {
        if( registerAddress == ( ( uint16_t ) registerList[2 * i] << 8 ) + registerList[2 * i + 1] )
        {
            return;
        }
    }

    if( nbOfRegisters < MAX_NB_REG_IN_RETENTION )
    {
        buffer[0] += 1;
        registerList[2 * nbOfRegisters]     = ( uint8_t )( registerAddress >> 8 );
        registerList[2 * nbOfRegisters + 1] = ( uint8_t )( registerAddress >> 0 );

        // Update radio with modified list
        SX126xWriteRegisters( REG_RETENTION_LIST_BASE_ADDRESS, buffer, 9 );
    }
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 	radio.c dosyasindaki yapi tasindi.
							Before any packet transmission, bit #2 at address 0x0889 shall be set to:
							• 0 if the LoRa BW = 500 kHz
							• 1 for any other LoRa BW
							• 1 for any (G)FSK configuration
							
********************************************************************************/
err_t					WorkAround								( uint8_t mode								, 
																								uint8_t bandwidth 					){
	
	err_t 		result = 	RT_EOK;
	uint8_t 	regVal = 	RT_NULL;
	
	if( mode == RF_SETTINGS_LORA 																			&&		/* @INFO: Lora modu seciliyse 				*/ 
		  typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.Bandwidth == LORA_BW_500 		)		/* @INFO: Lora bant genisligi 500 ise */
	{	
		regVal = SX126xReadRegister( (uint16_t)REG_TX_MODULATION ); //@INFO:	REG_TX_MODULATION okunuyor.
		regVal = (uint8_t)RESET_WORKAROUND_BIT(regVal);						 //@INFO: WorkAround biti Reset yapiliyor.
		
		result = SX126xWriteRegister( (uint16_t)REG_TX_MODULATION ,
																	 regVal											   );	//@INFO: WorkAround Reset yapilmis ayar tekrar yukleniyor.
		if(result != RT_EOK) return RT_ERROR;
		
	}
	else	//@INFO: 500kHz Lora-BW disindaki tum Lora ve tum GFSK modlarinda kullanilmaktadir.
	{	
		regVal = SX126xReadRegister( (uint16_t)REG_TX_MODULATION ); //@INFO:	REG_TX_MODULATION okunuyor.
		regVal = (uint8_t)SET_WORKAROUND_BIT(regVal);                       //@INFO: WorkAround biti Set yapiliyor.
		                                                                       
		result = SX126xWriteRegister( (uint16_t)REG_TX_MODULATION , 
																	 regVal											  );	//@INFO: WorkAround Set yapilmis ayar tekrar yukleniyor.
		if(result != RT_EOK) return RT_ERROR;
	}
	
	return result;
}

//@INFO: Working Modes
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetFs											( void 													){
	
	err_t result = RT_EOK;
	
	result = SX126xWriteCommand(RADIO_SET_FS , RT_NULL , RT_NULL );
	if(result != RT_EOK) return RT_ERROR;
	
	SX126xSetOperatingMode( MODE_FS );
	
	return result;
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetTx											( uint32_t timeout 					){
	
	err_t result = RT_EOK;

	uint8_t buf[3];
	
	buf[0] = ( rt_uint8_t )( ( timeout >> 16 ) 	& 0xFF );
	buf[1] = ( rt_uint8_t )( ( timeout >> 8 ) 	& 0xFF );
	buf[2] = ( rt_uint8_t )( 		timeout 				& 0xFF );
	
	result = SX126xWriteCommand( RADIO_SET_TX, buf, 3 );
	if(result != RT_EOK) return RT_ERROR;
	
	SX126xSetOperatingMode( MODE_TX );
	
	return result;
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetRx											( uint32_t timeout 					){
	
	err_t result = RT_EOK;

	result = SX126xWriteRegister( REG_RX_GAIN, 0x94 ); // default gain
	if(result != RT_EOK) return RT_ERROR;	
	
	uint8_t buf[3];
  buf[0] = ( uint8_t )( ( timeout >> 16 ) & 0xFF );
  buf[1] = ( uint8_t )( ( timeout >> 8 ) & 0xFF );
  buf[2] = ( uint8_t )( timeout & 0xFF );
	
  result = SX126xWriteCommand( RADIO_SET_RX, buf, 3 );
	if(result != RT_EOK) return RT_ERROR;
	
	SX126xSetOperatingMode( MODE_RX );
	
	return result;
	
}

/*******************************************************************************
  @func    : 
  @param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetRxBoosted							( uint32_t timeout			 			){
	
	err_t result = RT_EOK;

  result = SX126xWriteRegister( REG_RX_GAIN, 0x96 ); // max LNA gain, increase current by ~2mA for around ~3dB in sensitivity
	if(result != RT_EOK) return RT_ERROR;
	
	uint8_t buf[3];
  buf[0] = ( uint8_t )( ( timeout >> 16 ) & 0xFF );
  buf[1] = ( uint8_t )( ( timeout >> 8 	) & 0xFF );
  buf[2] = ( uint8_t )( 	timeout 				& 0xFF );
	
    result = SX126xWriteCommand( RADIO_SET_RX, buf, 3 );
	if(result != RT_EOK) return RT_ERROR;
	
	SX126xSetOperatingMode( MODE_RX );
			
	return result;
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/

err_t 					SetRxDutyCycle						( uint32_t rxTime						, 
																							uint32_t sleepTime 				){
	 err_t result = RT_EOK;
	
   uint8_t buf[6];
	
   buf[0] = ( uint8_t )( ( rxTime >> 16 ) & 0xFF );
   buf[1] = ( uint8_t )( ( rxTime >> 8  ) & 0xFF );
   buf[2] = ( uint8_t )( 	rxTime 				 & 0xFF );
	
   buf[3] = ( uint8_t )( ( sleepTime >> 16 ) & 0xFF );
   buf[4] = ( uint8_t )( ( sleepTime >> 8 	) & 0xFF );
   buf[5] = ( uint8_t )( 	sleepTime 				& 0xFF );
	
   result = SX126xWriteCommand( RADIO_SET_RXDUTYCYCLE, buf, 6 );
	 if(result != RT_EOK) return RT_ERROR;
	
   SX126xSetOperatingMode( MODE_RX_DC );
	
	 return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					SetCad										( void 													){
	
	err_t result = RT_EOK;
	
	result = SX126xWriteCommand( RADIO_SET_CAD, RT_NULL, RT_NULL );
	if(result != RT_EOK) return RT_ERROR;
	
    SX126xSetOperatingMode( MODE_CAD );
	
	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					SetTxContinuousWave				( void 													){
	
	err_t result = RT_EOK;
	
	result = SX126xWriteCommand( RADIO_SET_TXCONTINUOUSWAVE, RT_NULL, RT_NULL );
	if(result != RT_EOK) return RT_ERROR;
	
    SX126xSetOperatingMode( MODE_TX );
	
	return result;	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					SetTxInfinitePreamble			( void 													){
	
	err_t result = RT_EOK;
	
	result = SX126xWriteCommand( RADIO_SET_TXCONTINUOUSPREAMBLE, RT_NULL, RT_NULL );
	if(result != RT_EOK) return RT_ERROR;
	
    SX126xSetOperatingMode( MODE_TX );
	
	return result;		
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					SetStopRxTimerOnPreambleDetect( bool_t enable 					){
	err_t result = RT_EOK;
	
  result = SX126xWriteCommand( RADIO_SET_STOPRXTIMERONPREAMBLE, ( uint8_t* )&enable, 1 );
  if(result != RT_EOK) return RT_ERROR;  
	
	SX126xSetOperatingMode( MODE_RX );
	
	return result;		
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					SetRegulatorMode					( RadioRegulatorMode_t mode 		){
	
	err_t result = RT_EOK;	
	
	result = SX126xWriteCommand( RADIO_SET_REGULATORMODE, ( uint8_t* )&mode, 1 );

	return result;
}



/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					SetPaConfig								(	RadioPaCommand_t param				){
	//@BACK @NOTICE @INFO: S1k1nt1 var, uretici ile gorusuluyor! @alkim.gokcen
	err_t result = RT_EOK;
	
  uint8_t buf[4];
  buf[0] = param.paDutyCycle;
  buf[1] = param.hpMax;
  buf[2] = param.deviceSel;
  buf[3] = param.paLut;
	
  result = SX126xWriteCommand( RADIO_SET_PACONFIG, buf, 4 );
	
	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					SetRxTxFallbackMode				( uint8_t fallbackMode 			){
	err_t result = RT_EOK;
	
	result = SX126xWriteCommand( RADIO_SET_TXFALLBACKMODE, &fallbackMode, 1 );
	
	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetStandby								( uint8_t standbyTemp ){
	
	err_t result = RT_EOK;
	
	RadioStandbyModes_t standbyConfig = (RadioStandbyModes_t)standbyTemp;
	
	result = SX126xWriteCommand( RADIO_SET_STANDBY , (uint8_t*)&standbyConfig , 1);
	if(result != RT_EOK) return RT_ERROR;
	
  ( (RadioStandbyModes_t)standbyConfig == STDBY_RC ) 			? 
	SX126xSetOperatingMode(MODE_STDBY_RC)						:  
	SX126xSetOperatingMode(MODE_STDBY_XOSC) 				;
	

	return result;
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetSleep									( uint8_t sleepTemp ){
	
	err_t result = RT_EOK;
	typdef_unionSleepParams_t sleepConfig;
	
	sleepConfig.Value = sleepTemp;
	//@INFO: Sleep config op-param uygun olacak sekilde ayarlaniyor.
  uint8_t value = ( ( ( uint8_t )sleepConfig.Fields.WarmStart 	<< 2 ) |
											 ( ( uint8_t )sleepConfig.Fields.Reset 			<< 1 ) |
											 ( ( uint8_t )sleepConfig.Fields.WakeUpRTC 		 	 ) );

  if( sleepConfig.Fields.WarmStart == 0 )
  {
      // Force image calibration
      ImageCalibrated = RT_FALSE;
  }

	//@INFO: Uyku moduna girmesini saglayan opCode isleniyor.		
  result = SX126xWriteCommand( RADIO_SET_SLEEP, &value, 1 );
  if( result != RT_EOK ) return RT_ERROR;
	
	//@INFO: Global operating mode degiskeni sleep ayarlaniyor.		
	SX126xSetOperatingMode( MODE_SLEEP );
		
	
	return result;
	
}

//@INFO: DIO IRQ Configurations
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t	 				SetDioIrqParams						( uint16_t irqMask						, 
																							uint16_t dio1Mask					, 
																							uint16_t dio2Mask					, 
																							uint16_t dio3Mask 					){
	
	err_t result = RT_EOK;
	
	uint8_t buf[8];
  buf[0] = ( uint8_t )( ( irqMask >> 8 ) & 0x00FF );
  buf[1] = ( uint8_t )( irqMask & 0x00FF );
  buf[2] = ( uint8_t )( ( dio1Mask >> 8 ) & 0x00FF );
  buf[3] = ( uint8_t )( dio1Mask & 0x00FF );
  buf[4] = ( uint8_t )( ( dio2Mask >> 8 ) & 0x00FF );
  buf[5] = ( uint8_t )( dio2Mask & 0x00FF );
  buf[6] = ( uint8_t )( ( dio3Mask >> 8 ) & 0x00FF );
  buf[7] = ( uint8_t )( dio3Mask & 0x00FF );
	
  result = SX126xWriteCommand( RADIO_CFG_DIOIRQ, &buf[0] , 8 );

	return result;
}

/*******************************************************************************
  @func    : 
  @param   : 
  @return  : 
  @date	   : 
  @INFO	   : 
********************************************************************************/
uint16_t 			GetIrqStatus							( void 													){
	
	err_t result = RT_EOK;
	
	uint8_t irqStatus[2];

    result = SX126xReadCommand( RADIO_GET_IRQSTATUS, irqStatus, 2 );
	if(result != RT_EOK) return (err_t)RT_ERROR;
	
  return ( irqStatus[0] << 8 ) | irqStatus[1];
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					ClearIrqStatus						( uint16_t irq 							){
	
	
		err_t result = RT_EOK;
	  uint8_t buf[2];

    buf[0] = ( uint8_t )( ( 	( uint16_t )irq >> 8 ) 	& 0x00FF );
    buf[1] = ( uint8_t )( 		( uint16_t )irq 				& 0x00FF );
	
    result = SX126xWriteCommand( RADIO_CLR_IRQSTATUS, buf, 2 );
		
		return result;
}

//@INFO: Payload Configurations
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SetPayload								( uint8_t* payload						, 
																								size_t size								){
	
	err_t result = RT_EOK;
	
	result = SX126xWriteBuffer(payload , size);
	
	return result;
	
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t 					GetPayload								( uint8_t *buffer						, 
																								uint8_t *size							,  
																								uint8_t maxSize 							){
	
	err_t 		result = RT_EOK;
	uint8_t 	offset = 0;
	
	result = GetRxBufferStatus(size, &offset);
	if(result != RT_EOK) return RT_ERROR;
	
	if( *size > maxSize ) return RT_ERROR;
	
	result = SX126xReadBuffer( buffer , *size, 0); //@BACK: Offset zero
	
	return result;	
}

/*******************************************************************************
  @func    : 
  @param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
err_t					SendPayload								( uint8_t 	*payload					, 
																							uint8_t 	size							, 
																							uint32_t timeout 					){
	
	err_t result = RT_EOK;
	
	result = SetPayload(payload , size);
	if(result != RT_EOK) return RT_ERROR;
	
	result = SetTx(timeout);
	
	return result;
	
}

/********************END OF RF ADAPTOR SPECIAL FUNCTIONS**********************/
#endif



/* END OF FILE */



