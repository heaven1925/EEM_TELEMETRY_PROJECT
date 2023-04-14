
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
sx1262_err_t 		SX126xWriteCommand								( RadioCommands_t command				,
																								sx1262_uint8_t *buffer						,
																								sx1262_uint16_t size 							){
	sx1262_err_t	result = SX1262_EOK;
	
	result = sys_rfAdaptor_writeCommand(command , buffer , size );
	if(result != SX1262_EOK) return SX1262_ERR;
																			 
	return result;
																																																
}
																								
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_err_t 		SX126xReadCommand									( RadioCommands_t command				,
																									sx1262_uint8_t *buffer					,
																									size_t size 							){
	sx1262_err_t	result = SX1262_EOK;
																										
	result = sys_rfAdaptor_readCommand(command , buffer , size);
	if(result != SX1262_EOK) return SX1262_ERR;
																			 
	return result;																									
																									
																									
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_err_t 		SX126xWriteRegister								( sx1262_uint16_t 	address					,
																								sx1262_uint8_t 	  value						){
																				 
	sx1262_err_t	result = SX1262_EOK;
																			 
	result = sys_rfAdaptor_writeRegister(address , value);
	if(result != SX1262_EOK) return SX1262_ERR;
																			 
	return result;					 
																			 																			 
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_uint8_t	SX126xReadRegister								( sx1262_uint16_t 	address					){
	
	sx1262_uint8_t data;

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
sx1262_err_t		SX126xWriteRegisters							( sx1262_uint16_t 	address					,
																								sx1262_uint8_t* 	buffer					,
																								size_t		size							){
	sx1262_err_t result = SX1262_EOK;
	
	result = sys_rfAdaptor_writeRegisters(address , buffer , size);
	if(result != SX1262_EOK) return SX1262_ERR;
																									
	return result;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_err_t		SX126xReadRegisters								( sx1262_uint16_t 	address					,
																								sx1262_uint8_t*	buffer						,
																								size_t	size								){
	sx1262_err_t result = SX1262_EOK;
	
	result = sys_rfAdaptor_readRegisters(address , buffer , size);
	if(result != SX1262_EOK) return SX1262_ERR;
																									
	return result;
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_err_t		SX126xWriteBuffer									( sx1262_uint8_t *buffer						,
                                              	size_t  size 							){
																									
	sx1262_err_t result = SX1262_EOK;
	
	result = sys_rfAdaptor_writeBuffer(buffer , size);
	if(result != SX1262_EOK) return SX1262_ERR;
																									
	return result;
																									
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_err_t		SX126xReadBuffer									( sx1262_uint8_t *buffer						,
																								size_t size 								,
																								size_t	offset							){

	sx1262_err_t result = SX1262_EOK;
	
	result = sys_rfAdaptor_readBuffer(buffer , size , offset);
	if(result != SX1262_EOK) return SX1262_ERR;
																									
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
sx1262_uint32_t	SX126xGetDio1PinState							( void 													){
	
	sx1262_bool_t result = SX1262_TRUE;
	
	result = sys_rfAdaptor_readPin();
	
	return (sx1262_uint32_t)result;
}


/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_err_t		SX126xReadStatus									( sx1262_uint8_t *buffer 						){
	
	sx1262_err_t	result = SX1262_EOK;
																			 
	result = sys_rfAdaptor_readStatus(buffer);
	if(result != SX1262_EOK) return SX1262_ERR;
																			 
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
sx1262_err_t 					 SetPacketType							( RadioPacketTypes_t packetType ){
	
	sx1262_err_t result = SX1262_EOK;
	
	// Save packet type internally to avoid questioning the radio
  PacketType = packetType;
  result = SX126xWriteCommand( RADIO_SET_PACKETTYPE, ( sx1262_uint8_t* )&packetType, 1 );
	if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t 					 SetTxParams								( sx1262_int8_t power				,
																			  RadioRampTimes_t rampTime 		){
																			
		//@NOTICE:  1262 kullanildigi icin 1261 ayari kaldirilmistir !
		sx1262_err_t result = SX1262_EOK;
		sx1262_uint8_t buf[2];
		
		// WORKAROUND - Better Resistance of the SX1262 Tx to Antenna Mismatch, see DS_SX1261-2_V1.2 datasheet chapter 15.2		
		result = SX126xWriteRegister(  REG_TX_CLAMP_CFG																									, 
																(  SX126xReadRegister( REG_TX_CLAMP_CFG ) | ( 0x0F << 1 ) ) );
		
		if(result != SX1262_EOK) return SX1262_ERR;
		// WORKAROUND END
		/* rt_err_t sys_rfAdaptor_setPaConfig( sx1262_uint8_t paDutyCycle, sx1262_uint8_t hpMax, sx1262_uint8_t deviceSel, sx1262_uint8_t paLut ) */
			
		result = SetPaConfig( (RadioPaCommand_t)RADIO_OUTPUTPOWER_14DBM );
		if(result != SX1262_EOK) return SX1262_ERR;
																			
		if( power > 22 )
		{
				power = 22;
		}
		else if( power < -9 )
		{
				power = -9;
		}
		
    buf[0] = power;
    buf[1] = ( sx1262_uint8_t )rampTime;
		
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
sx1262_err_t 					 SetModulationParams	 			( ModulationParams_t *modulationParams ){
	
		sx1262_err_t result = SX1262_EOK;

    sx1262_uint32_t tempVal = SX1262_NULL;
    sx1262_uint8_t buf[8] = { NOP_MSG };

    // Check if required configuration corresponds to the stored packet type
    // If not, silently update radio packet type
    if( PacketType != modulationParams->PacketType )
    {
        result = SetPacketType( modulationParams->PacketType );
    }

    switch( modulationParams->PacketType )
    {
    case PACKET_TYPE_GFSK:
		//@INFO: GFSK Paketi se�imi yapildiysa,	
        tempVal = ( sx1262_uint32_t )( 32 * SX126X_XTAL_FREQ / modulationParams->Params.Gfsk.BitRate );
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
				if(result != SX1262_EOK) return SX1262_ERR;
		
        break;
		
    case PACKET_TYPE_LORA:
		//@INFO: Lora Paketi se�imi yapildiysa,	
        buf[0] = modulationParams->Params.LoRa.SpreadingFactor;
        buf[1] = modulationParams->Params.LoRa.Bandwidth;
        buf[2] = modulationParams->Params.LoRa.CodingRate;
        buf[3] = modulationParams->Params.LoRa.LowDatarateOptimize;

        result = SX126xWriteCommand( RADIO_SET_MODULATIONPARAMS, buf, 4);
				if(result != SX1262_EOK) return SX1262_ERR;
		
        break;
    default:
			
    case PACKET_TYPE_NONE:
        return SX1262_ERR;
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
sx1262_err_t 					 SetPacketParams						( PacketParams_t *packetParams 	){
		sx1262_err_t result = SX1262_EOK;
	
	  sx1262_uint8_t n;
    sx1262_uint8_t crcVal = SX1262_NULL;
    sx1262_uint8_t buf[9] = { SX1262_NULL };

    // Check if required configuration corresponds to the stored packet type
    // If not, silently update radio packet type
    if( PacketType != packetParams->PacketType )
    {
        result = SetPacketType( packetParams->PacketType );
				if(result != SX1262_EOK) return SX1262_ERR;
    }

    switch( packetParams->PacketType )
    {
    case PACKET_TYPE_GFSK:
        if( packetParams->Params.Gfsk.CrcLength == RADIO_CRC_2_BYTES_IBM )
        {
            result = SetCrcSeed( CRC_IBM_SEED );
						if(result != SX1262_EOK) return SX1262_ERR;
					
            result = SetCrcPolynomial( CRC_POLYNOMIAL_IBM );
            if(result != SX1262_EOK) return SX1262_ERR;
					
						crcVal = RADIO_CRC_2_BYTES;
        }
        else if( packetParams->Params.Gfsk.CrcLength == RADIO_CRC_2_BYTES_CCIT )
        {
            result = SetCrcSeed( CRC_CCITT_SEED );
						if(result != SX1262_EOK) return SX1262_ERR;
					
            result = SetCrcPolynomial( CRC_POLYNOMIAL_CCITT );
						if(result != SX1262_EOK) return SX1262_ERR;
					
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
        return SX1262_ERR;
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
sx1262_err_t 					 SetCadParams						 		( RadioLoRaCadSymbols_t cadSymbolNum,
																		sx1262_uint8_t cadDetPeak						 ,
																		sx1262_uint8_t cadDetMin						 ,
																		RadioCadExitModes_t cadExitMode	     ,
																		sx1262_uint32_t cadTimeout 					){
																			 
		sx1262_err_t result = SX1262_EOK;
																			 
		sx1262_uint8_t buf[7];
	buf[0] = ( sx1262_uint8_t )cadSymbolNum;
    buf[1] = cadDetPeak;
    buf[2] = cadDetMin;
    buf[3] = ( sx1262_uint8_t )cadExitMode;
    buf[4] = ( sx1262_uint8_t )( ( cadTimeout >> 16 ) & 0xFF );
    buf[5] = ( sx1262_uint8_t )( ( cadTimeout >> 8 ) 	& 0xFF );
    buf[6] = ( sx1262_uint8_t )( 	 cadTimeout 				& 0xFF );
																			 
    result = SX126xWriteCommand( RADIO_SET_CADPARAMS, buf, 7 );
    if(result != SX1262_EOK) return SX1262_ERR;
																			 
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
sx1262_err_t 					 SetBufferBaseAddress				( sx1262_uint8_t txBaseAddress			,
																								sx1262_uint8_t rxBaseAddress 			){
    sx1262_err_t result = SX1262_EOK;
																			 
	  sx1262_uint8_t buf[2];
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
sx1262_err_t 					 GetRxBufferStatus					( sx1262_uint8_t *payloadLength			,
																								sx1262_uint8_t *rxStartBufferPointer){
		sx1262_err_t result = SX1262_EOK;
																		
    sx1262_uint8_t status[2];

    result = SX126xReadCommand( RADIO_GET_RXBUFFERSTATUS, &status[0], 2 );
			if(result != SX1262_EOK) return SX1262_ERR;

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
sx1262_err_t 					 GetPacketStatus						( PacketStatus_t *pktStatus 		){
		sx1262_err_t result = SX1262_EOK;
	
    sx1262_uint8_t status[3];

    result = SX126xReadCommand( RADIO_GET_PACKETSTATUS, &status[0], 3 );
		if(result != SX1262_EOK) return SX1262_ERR;
	
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
            pktStatus->Params.LoRa.SnrPkt = ( ( ( sx1262_int8_t )status[1] ) + 2 ) >> 2;
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
sx1262_uint32_t				GetBoardTcxoWakeupTime		( void 													){
	return	BOARD_TCXO_WAKEUP_TIME;
}
/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_err_t 					SetRfFrequency						( sx1262_uint32_t frequency 						){
	
		sx1262_err_t result = SX1262_EOK;
	  sx1262_uint8_t buf[4];

    if( ImageCalibrated == SX1262_FALSE )
    {
        result = CalibrateImage( frequency );
				if( result != SX1262_EOK ) return SX1262_ERR;
			
        ImageCalibrated = SX1262_TRUE;
    }

    sx1262_uint32_t freqInPllSteps = ConvertFreqInHzToPllStep( frequency );

    buf[0] = ( sx1262_uint8_t )( ( freqInPllSteps >> 24 ) & 0xFF );
    buf[1] = ( sx1262_uint8_t )( ( freqInPllSteps >> 16 ) & 0xFF );
    buf[2] = ( sx1262_uint8_t )( ( freqInPllSteps >> 8 ) 	& 0xFF );
    buf[3] = ( sx1262_uint8_t )( 	 freqInPllSteps 				& 0xFF );
    	
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
sx1262_err_t  				SetRfTxPower							( sx1262_int8_t power 							){
		sx1262_err_t result = SX1262_EOK;
	
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
sx1262_err_t					SetLoRaSymbNumTimeout			( sx1262_uint8_t symbNum 						){
	
	sx1262_err_t result = SX1262_EOK;
	
  sx1262_uint8_t mant = ( ( ( symbNum > SX126X_MAX_LORA_SYMB_NUM_TIMEOUT ) ?
													SX126X_MAX_LORA_SYMB_NUM_TIMEOUT : 
													symbNum ) + 1 ) >> 1;
	
  sx1262_uint8_t exp  = 0;
  sx1262_uint8_t reg  = 0;

  while( mant > 31 )
  {
      mant = ( mant + 3 ) >> 2;
      exp++;
  }

  reg = mant << ( 2 * exp + 1 );
  result = SX126xWriteCommand( RADIO_SET_LORASYMBTIMEOUT, &reg, 1 );
  if(result != SX1262_EOK) return SX1262_ERR;
	
  if( symbNum != 0 )
  {
      reg = exp + ( mant << 3 );
      result = SX126xWriteRegister( REG_LR_SYNCH_TIMEOUT, reg );
			if(result != SX1262_EOK) return SX1262_ERR;
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
sx1262_err_t					CalibrateImage						( sx1262_uint32_t freq 							){
	
	  sx1262_err_t	result = SX1262_EOK;
	  sx1262_uint8_t calFreq[2];

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
sx1262_err_t					SetSyncWord								( sx1262_uint8_t * syncWord					){
	sx1262_err_t result = SX1262_EOK;
	
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
sx1262_err_t					SetCrcSeed								( sx1262_uint16_t seed 							){
		sx1262_err_t result = SX1262_EOK;
	
	  sx1262_uint8_t buf[2];

    buf[0] = ( sx1262_uint8_t )( ( seed >> 8 ) & 0xFF );
    buf[1] = ( sx1262_uint8_t )( 	 seed 			 & 0xFF );

    switch( GetPacketType() )
    {
		//@INFO: GFSK Paket tipi i�in CRC SEED
      case PACKET_TYPE_GFSK:
				
        result = SX126xWriteRegisters( REG_LR_CRCSEEDBASEADDR, buf, 2 );
			  if(result != SX1262_EOK) return SX1262_ERR;
			
      break;
		//@INFO: Hatali paket tipi 
      default:
				
					result = SX1262_ERR;
			
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
sx1262_err_t					SetCrcPolynomial					( sx1262_uint16_t polynomial 				){
		sx1262_err_t result = SX1262_EOK;
	  
		sx1262_uint8_t buf[2];

    buf[0] = ( sx1262_uint8_t )( ( polynomial >> 8 ) & 0xFF );
    buf[1] = ( sx1262_uint8_t )( polynomial & 0xFF );

    switch( GetPacketType() )
    {
		//@INFO: GFSK Paket tipi i�in CRC Poly
			case PACKET_TYPE_GFSK:
				
        result = SX126xWriteRegisters( REG_LR_CRCPOLYBASEADDR, buf, 2 );
				if(result != SX1262_EOK) return SX1262_ERR;
			
      break;
	  //@INFO: Hatali paket tipi CRC Poly
        default:
					
						result = SX1262_ERR;
				
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
sx1262_err_t					SetWhiteningSeed					( sx1262_uint16_t seed			 				){
		
		sx1262_err_t	result = SX1262_EOK;
	  sx1262_uint8_t regValue = 0;
    
    switch( GetPacketType() )
    {
        case PACKET_TYPE_GFSK:
            regValue = (sx1262_uint8_t)( SX126xReadRegister( REG_LR_WHITSEEDBASEADDR_MSB ) & 0xFE );
            regValue = (sx1262_uint8_t)(( ( seed >> 8 ) & 0x01 ) | regValue );
				
            result = SX126xWriteRegister( REG_LR_WHITSEEDBASEADDR_MSB, regValue ); // only 1 bit.
						if(result != SX1262_EOK) return SX1262_ERR;
				
            result = SX126xWriteRegister( REG_LR_WHITSEEDBASEADDR_LSB, ( sx1262_uint8_t )seed );
						if(result != SX1262_EOK) return SX1262_ERR;
				
        break;

        default:
						result = SX1262_ERR;
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
sx1262_uint32_t 	GetRandom			( void ){
	
	sx1262_uint32_t number = 0;
    sx1262_uint8_t regAnaLna = 0;
    sx1262_uint8_t regAnaMixer = 0;

    regAnaLna = SX126xReadRegister( REG_ANA_LNA );
    SX126xWriteRegister( REG_ANA_LNA, regAnaLna & ~( 1 << 0 ) );

    regAnaMixer = SX126xReadRegister( REG_ANA_MIXER );
    SX126xWriteRegister( REG_ANA_MIXER, regAnaMixer & ~( 1 << 7 ) );

    // Set radio in continuous reception
    SetRx( 0xFFFFFF ); // Rx Continuous

    SX126xReadRegisters( RANDOM_NUMBER_GENERATORBASEADDR, ( sx1262_uint8_t* )&number, 4 );

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
	
	sx1262_uint8_t err[] = { 0, 0 };
  RadioError_t error = { .Value = 0 };	//@BACK: Value degeri farklilik gosterebilir

	SX126xReadCommand( RADIO_GET_ERROR, ( sx1262_uint8_t* )err, 2 );
	
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
sx1262_err_t 					ClearDeviceErrors					( void													){
	
	    sx1262_err_t result = SX1262_EOK;
		sx1262_uint8_t buf[2] = { SX1262_NULL };
		
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
sx1262_uint32_t 			ConvertFreqInHzToPllStep	( sx1262_uint32_t freqInHz 					){
    sx1262_uint32_t stepsInt;
    sx1262_uint32_t stepsFrac;

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
sx1262_uint8_t				RadioGetFskBandwidthRegValue( sx1262_uint32_t bandwidth 			){
	
	
		sx1262_uint8_t i;

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
	
	  sx1262_uint8_t stat = 0;
	
    RadioStatus_t status ;			
		status.value = SX1262_NULL;
		
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
sx1262_int8_t 				GetRssiInst								( void 													){
	
    sx1262_uint8_t buf = 0;
    sx1262_int8_t 	rssi = 0;

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
void 							AddRegisterToRetentionList( sx1262_uint16_t registerAddress 			){
    sx1262_uint8_t buffer[9];

    // Read the address and registers already added to the list
    SX126xReadRegisters( REG_RETENTION_LIST_BASE_ADDRESS, buffer, 9 );

    const sx1262_uint8_t nbOfRegisters = buffer[0];
    sx1262_uint8_t* registerList   = &buffer[1];

    // Check if the register given as parameter is already added to the list
    for( sx1262_uint8_t i = 0; i < nbOfRegisters; i++ )
    {
        if( registerAddress == ( ( sx1262_uint16_t ) registerList[2 * i] << 8 ) + registerList[2 * i + 1] )
        {
            return;
        }
    }

    if( nbOfRegisters < MAX_NB_REG_IN_RETENTION )
    {
        buffer[0] += 1;
        registerList[2 * nbOfRegisters]     = ( sx1262_uint8_t )( registerAddress >> 8 );
        registerList[2 * nbOfRegisters + 1] = ( sx1262_uint8_t )( registerAddress >> 0 );

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
							� 0 if the LoRa BW = 500 kHz
							� 1 for any other LoRa BW
							� 1 for any (G)FSK configuration
							
********************************************************************************/
sx1262_err_t					WorkAround				( sx1262_uint8_t mode		,
														  sx1262_uint8_t bandwidth 	){
	
	sx1262_err_t 	result = 	SX1262_EOK;
	sx1262_uint8_t 	regVal = 	SX1262_NULL;
	

//	if( mode == RF_SETTINGS_LORA 	&&		/* @INFO: Lora modu seciliyse 				*/
//		  typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.Bandwidth == LORA_BW_500 		)		/* @INFO: Lora bant genisligi 500 ise */
//	{
//		regVal = SX126xReadRegister( (sx1262_uint16_t)REG_TX_MODULATION ); //@INFO:	REG_TX_MODULATION okunuyor.
//		regVal = (sx1262_uint8_t)RESET_WORKAROUND_BIT(regVal);						 //@INFO: WorkAround biti Reset yapiliyor.
//
//		result = SX126xWriteRegister( (sx1262_uint16_t)REG_TX_MODULATION ,
//																	 regVal											   );	//@INFO: WorkAround Reset yapilmis ayar tekrar yukleniyor.
//		if(result != SX1262_EOK) return SX1262_ERR;
//
//	}
//	else	//@INFO: 500kHz Lora-BW disindaki tum Lora ve tum GFSK modlarinda kullanilmaktadir.
//	{
		regVal = SX126xReadRegister( (sx1262_uint16_t)REG_TX_MODULATION ); //@INFO:	REG_TX_MODULATION okunuyor.
		regVal = (sx1262_uint8_t)SET_WORKAROUND_BIT(regVal);                       //@INFO: WorkAround biti Set yapiliyor.
		                                                                       
		result = SX126xWriteRegister( (sx1262_uint16_t)REG_TX_MODULATION ,
																	 regVal											  );	//@INFO: WorkAround Set yapilmis ayar tekrar yukleniyor.
		if(result != SX1262_EOK) return SX1262_ERR;
//	}
	
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
sx1262_err_t					SetFs											( void 													){
	
	sx1262_err_t result = SX1262_EOK;
	
	result = SX126xWriteCommand(RADIO_SET_FS , SX1262_NULL , SX1262_NULL );
	if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t					SetTx											( sx1262_uint32_t timeout 					){
	
	sx1262_err_t result = SX1262_EOK;

	sx1262_uint8_t buf[3];
	
	buf[0] = ( sx1262_uint8_t )( ( timeout >> 16 ) 	& 0xFF );
	buf[1] = ( sx1262_uint8_t )( ( timeout >> 8 ) 	& 0xFF );
	buf[2] = ( sx1262_uint8_t )( 		timeout 				& 0xFF );
	
	result = SX126xWriteCommand( RADIO_SET_TX, buf, 3 );
	if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t					SetRx											( sx1262_uint32_t timeout 					){
	
	sx1262_err_t result = SX1262_EOK;

	result = SX126xWriteRegister( REG_RX_GAIN, 0x94 ); // default gain
	if(result != SX1262_EOK) return SX1262_ERR;
	
	sx1262_uint8_t buf[3];
  buf[0] = ( sx1262_uint8_t )( ( timeout >> 16 ) & 0xFF );
  buf[1] = ( sx1262_uint8_t )( ( timeout >> 8 ) & 0xFF );
  buf[2] = ( sx1262_uint8_t )( timeout & 0xFF );
	
  result = SX126xWriteCommand( RADIO_SET_RX, buf, 3 );
	if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t					SetRxBoosted							( sx1262_uint32_t timeout			 			){
	
	sx1262_err_t result = SX1262_EOK;

  result = SX126xWriteRegister( REG_RX_GAIN, 0x96 ); // max LNA gain, increase current by ~2mA for around ~3dB in sensitivity
	if(result != SX1262_EOK) return SX1262_ERR;
	
	sx1262_uint8_t buf[3];
  buf[0] = ( sx1262_uint8_t )( ( timeout >> 16 ) & 0xFF );
  buf[1] = ( sx1262_uint8_t )( ( timeout >> 8 	) & 0xFF );
  buf[2] = ( sx1262_uint8_t )( 	timeout 				& 0xFF );
	
    result = SX126xWriteCommand( RADIO_SET_RX, buf, 3 );
	if(result != SX1262_EOK) return SX1262_ERR;
	
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

sx1262_err_t 					SetRxDutyCycle						( sx1262_uint32_t rxTime						,
																							sx1262_uint32_t sleepTime 				){
	 sx1262_err_t result = SX1262_EOK;
	
   sx1262_uint8_t buf[6];
	
   buf[0] = ( sx1262_uint8_t )( ( rxTime >> 16 ) & 0xFF );
   buf[1] = ( sx1262_uint8_t )( ( rxTime >> 8  ) & 0xFF );
   buf[2] = ( sx1262_uint8_t )( 	rxTime 				 & 0xFF );
	
   buf[3] = ( sx1262_uint8_t )( ( sleepTime >> 16 ) & 0xFF );
   buf[4] = ( sx1262_uint8_t )( ( sleepTime >> 8 	) & 0xFF );
   buf[5] = ( sx1262_uint8_t )( 	sleepTime 				& 0xFF );
	
   result = SX126xWriteCommand( RADIO_SET_RXDUTYCYCLE, buf, 6 );
	 if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t 					SetCad										( void 													){
	
	sx1262_err_t result = SX1262_EOK;
	
	result = SX126xWriteCommand( RADIO_SET_CAD, SX1262_NULL, SX1262_NULL );
	if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t 					SetTxContinuousWave				( void 													){
	
	sx1262_err_t result = SX1262_EOK;
	
	result = SX126xWriteCommand( RADIO_SET_TXCONTINUOUSWAVE, SX1262_NULL, SX1262_NULL );
	if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t 					SetTxInfinitePreamble			( void 													){
	
	sx1262_err_t result = SX1262_EOK;
	
	result = SX126xWriteCommand( RADIO_SET_TXCONTINUOUSPREAMBLE, SX1262_NULL, SX1262_NULL );
	if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t 					SetStopRxTimerOnPreambleDetect( sx1262_bool_t enable 					){
	sx1262_err_t result = SX1262_EOK;
	
  result = SX126xWriteCommand( RADIO_SET_STOPRXTIMERONPREAMBLE, ( sx1262_uint8_t* )&enable, 1 );
  if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t 					SetRegulatorMode					( RadioRegulatorMode_t mode 		){
	
	sx1262_err_t result = SX1262_EOK;
	
	result = SX126xWriteCommand( RADIO_SET_REGULATORMODE, ( sx1262_uint8_t* )&mode, 1 );

	return result;
}



/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_err_t 					SetPaConfig								(	RadioPaCommand_t param				){
	//@BACK @NOTICE @INFO: S1k1nt1 var, uretici ile gorusuluyor! @alkim.gokcen
	sx1262_err_t result = SX1262_EOK;
	
  sx1262_uint8_t buf[4];
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
sx1262_err_t 					SetRxTxFallbackMode				( sx1262_uint8_t fallbackMode 			){
	sx1262_err_t result = SX1262_EOK;
	
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
sx1262_err_t					SetStandby								( sx1262_uint8_t standbyTemp ){
	
	sx1262_err_t result = SX1262_EOK;
	
	RadioStandbyModes_t standbyConfig = (RadioStandbyModes_t)standbyTemp;
	
	result = SX126xWriteCommand( RADIO_SET_STANDBY , (sx1262_uint8_t*)&standbyConfig , 1);
	if(result != SX1262_EOK) return SX1262_ERR;
	
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
sx1262_err_t					SetSleep									( sx1262_uint8_t sleepTemp ){
	
	sx1262_err_t result = SX1262_EOK;
	typdef_unionSleepParams_t sleepConfig;
	
	sleepConfig.Value = sleepTemp;
	//@INFO: Sleep config op-param uygun olacak sekilde ayarlaniyor.
  sx1262_uint8_t value = ( ( ( sx1262_uint8_t )sleepConfig.Fields.WarmStart 	<< 2 ) |
											 ( ( sx1262_uint8_t )sleepConfig.Fields.Reset 			<< 1 ) |
											 ( ( sx1262_uint8_t )sleepConfig.Fields.WakeUpRTC 		 	 ) );

  if( sleepConfig.Fields.WarmStart == 0 )
  {
      // Force image calibration
      ImageCalibrated = SX1262_FALSE;
  }

	//@INFO: Uyku moduna girmesini saglayan opCode isleniyor.		
  result = SX126xWriteCommand( RADIO_SET_SLEEP, &value, 1 );
  if( result != SX1262_EOK ) return SX1262_ERR;
	
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
sx1262_err_t	 				SetDioIrqParams						( sx1262_uint16_t irqMask						,
																							sx1262_uint16_t dio1Mask					,
																							sx1262_uint16_t dio2Mask					,
																							sx1262_uint16_t dio3Mask 					){
	
	sx1262_err_t result = SX1262_EOK;
	
	sx1262_uint8_t buf[8];
  buf[0] = ( sx1262_uint8_t )( ( irqMask >> 8 ) & 0x00FF );
  buf[1] = ( sx1262_uint8_t )( irqMask & 0x00FF );
  buf[2] = ( sx1262_uint8_t )( ( dio1Mask >> 8 ) & 0x00FF );
  buf[3] = ( sx1262_uint8_t )( dio1Mask & 0x00FF );
  buf[4] = ( sx1262_uint8_t )( ( dio2Mask >> 8 ) & 0x00FF );
  buf[5] = ( sx1262_uint8_t )( dio2Mask & 0x00FF );
  buf[6] = ( sx1262_uint8_t )( ( dio3Mask >> 8 ) & 0x00FF );
  buf[7] = ( sx1262_uint8_t )( dio3Mask & 0x00FF );
	
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
sx1262_uint16_t 			GetIrqStatus							( void 													){
	
	sx1262_err_t result = SX1262_EOK;
	
	sx1262_uint8_t irqStatus[2];

    result = SX126xReadCommand( RADIO_GET_IRQSTATUS, irqStatus, 2 );
	if(result != SX1262_EOK) return (sx1262_err_t)SX1262_ERR;
	
  return ( irqStatus[0] << 8 ) | irqStatus[1];
	
}

/*******************************************************************************
	@func    : 
	@param   : 
  @return  : 
  @date	   : 
  @INFO		 : 
********************************************************************************/
sx1262_err_t					ClearIrqStatus						( sx1262_uint16_t irq 							){
	
	
		sx1262_err_t result = SX1262_EOK;
	  sx1262_uint8_t buf[2];

    buf[0] = ( sx1262_uint8_t )( ( 	( sx1262_uint16_t )irq >> 8 ) 	& 0x00FF );
    buf[1] = ( sx1262_uint8_t )( 		( sx1262_uint16_t )irq 				& 0x00FF );
	
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
sx1262_err_t					SetPayload								( sx1262_uint8_t* payload						,
																		  sx1262_size_t size							){
	
	sx1262_err_t result = SX1262_EOK;
	
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
sx1262_err_t 					GetPayload								( sx1262_uint8_t *buffer						,
																		  sx1262_uint8_t *size							,
																		  sx1262_uint8_t maxSize 						){
	
	sx1262_err_t 		result = SX1262_EOK;
	sx1262_uint8_t 	offset = 0;
	
	result = GetRxBufferStatus(size, &offset);
	if(result != SX1262_EOK) return SX1262_ERR;
	
	if( *size > maxSize ) return SX1262_ERR;
	
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
sx1262_err_t					SendPayload								( sx1262_uint8_t 	*payload					,
																		  sx1262_uint8_t 	size							,
																							sx1262_uint32_t timeout 					){
	
	sx1262_err_t result = SX1262_EOK;
	
	result = SetPayload(payload , size);
	if(result != SX1262_EOK) return SX1262_ERR;
	
	result = SetTx(timeout);
	
	return result;
	
}

/********************END OF RF ADAPTOR SPECIAL FUNCTIONS**********************/
#endif



/* END OF FILE */



