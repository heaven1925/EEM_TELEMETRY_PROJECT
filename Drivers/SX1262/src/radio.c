/*!
 * \file      radio.c
 *
 * \brief     Radio driver API definition
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 */
#include <math.h>
#include <string.h>


#include "radio.h"


#define LORAWAN_TIMESERVER_INCLUDE
#undef	LORAWAN_TIMESERVER_INCLUDE	//@NEW: @a.ertekin //@INFO: Lorawan time server projeye ekli değildir.

#define WDT_INCLUDE
#undef	WDT_INCLUDE	//@NEW: @a.ertekin //@INFO: Lorawan time server projeye ekli değildir.

/*!
 * \brief Initializes the radio
 *
 * \param [IN] events Structure containing the driver callback functions
 */
radio_err_t RadioInit( RadioEvents_t *events );

/*!
 * Return current radio status
 *
 * \param status Radio status.[RF_IDLE, RF_RX_RUNNING, RF_TX_RUNNING]
 */
RadioState_t RadioGetStatus( void );

/*!
 * \brief Configures the radio with the given modem
 *
 * \param [IN] modem Modem to be used [0: FSK, 1: LoRa]
 */
void RadioSetModem( RadioModems_t modem );

/*!
 * \brief Sets the channel frequency
 *
 * \param [IN] freq         Channel RF frequency
 */
radio_err_t RadioSetChannel( uint32_t freq );

/*!
 * \brief Checks if the channel is free for the given time
 *
 * \remark The FSK modem is always used for this task as we can select the Rx bandwidth at will.
 *
 * \param [IN] freq                Channel RF frequency in Hertz
 * \param [IN] rxBandwidth         Rx bandwidth in Hertz
 * \param [IN] rssiThresh          RSSI threshold in dBm
 * \param [IN] maxCarrierSenseTime Max time in milliseconds while the RSSI is measured
 *
 * \retval isFree         [true: Channel is free, false: Channel is not free]
 */
bool RadioIsChannelFree( uint32_t freq, uint32_t rxBandwidth, int16_t rssiThresh, uint32_t maxCarrierSenseTime );

/*!
 * \brief Generates a 32 bits random value based on the RSSI readings
 *
 * \remark This function sets the radio in LoRa modem mode and disables
 *         all interrupts.
 *         After calling this function either Radio.SetRxConfig or
 *         Radio.SetTxConfig functions must be called.
 *
 * \retval randomValue    32 bits random value
 */
uint32_t RadioRandom( void );

/*!
 * \brief Sets the reception parameters
 *
 * \param [IN] modem        Radio modem to be used [0: FSK, 1: LoRa]
 * \param [IN] bandwidth    Sets the bandwidth
 *                          FSK : >= 2600 and <= 250000 Hz
 *                          LoRa: [0: 125 kHz, 1: 250 kHz,
 *                                 2: 500 kHz, 3: Reserved]
 * \param [IN] datarate     Sets the Datarate
 *                          FSK : 600..300000 bits/s
 *                          LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
 *                                10: 1024, 11: 2048, 12: 4096  chips]
 * \param [IN] coderate     Sets the coding rate (LoRa only)
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
 * \param [IN] bandwidthAfc Sets the AFC Bandwidth (FSK only)
 *                          FSK : >= 2600 and <= 250000 Hz
 *                          LoRa: N/A ( set to 0 )
 * \param [IN] preambleLen  Sets the Preamble length
 *                          FSK : Number of bytes
 *                          LoRa: Length in symbols (the hardware adds 4 more symbols)
 * \param [IN] symbTimeout  Sets the RxSingle timeout value
 *                          FSK : timeout in number of bytes
 *                          LoRa: timeout in symbols
 * \param [IN] fixLen       Fixed length packets [0: variable, 1: fixed]
 * \param [IN] payloadLen   Sets payload length when fixed length is used
 * \param [IN] crcOn        Enables/Disables the CRC [0: OFF, 1: ON]
 * \param [IN] FreqHopOn    Enables disables the intra-packet frequency hopping
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [0: OFF, 1: ON]
 * \param [IN] HopPeriod    Number of symbols between each hop
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: Number of symbols
 * \param [IN] iqInverted   Inverts IQ signals (LoRa only)
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [0: not inverted, 1: inverted]
 * \param [IN] rxContinuous Sets the reception in continuous mode
 *                          [false: single mode, true: continuous mode]
 */
void RadioSetRxConfig( RadioModems_t modem, uint32_t bandwidth,
                          uint32_t datarate, uint8_t coderate,
                          uint32_t bandwidthAfc, uint16_t preambleLen,
                          uint16_t symbTimeout, bool fixLen,
                          uint8_t payloadLen,
                          bool crcOn, bool FreqHopOn, uint8_t HopPeriod,
                          bool iqInverted, bool rxContinuous );

/*!
 * \brief Sets the transmission parameters
 *
 * \param [IN] modem        Radio modem to be used [0: FSK, 1: LoRa]
 * \param [IN] power        Sets the output power [dBm]
 * \param [IN] fdev         Sets the frequency deviation (FSK only)
 *                          FSK : [Hz]
 *                          LoRa: 0
 * \param [IN] bandwidth    Sets the bandwidth (LoRa only)
 *                          FSK : 0
 *                          LoRa: [0: 125 kHz, 1: 250 kHz,
 *                                 2: 500 kHz, 3: Reserved]
 * \param [IN] datarate     Sets the Datarate
 *                          FSK : 600..300000 bits/s
 *                          LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
 *                                10: 1024, 11: 2048, 12: 4096  chips]
 * \param [IN] coderate     Sets the coding rate (LoRa only)
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
 * \param [IN] preambleLen  Sets the preamble length
 *                          FSK : Number of bytes
 *                          LoRa: Length in symbols (the hardware adds 4 more symbols)
 * \param [IN] fixLen       Fixed length packets [0: variable, 1: fixed]
 * \param [IN] crcOn        Enables disables the CRC [0: OFF, 1: ON]
 * \param [IN] FreqHopOn    Enables disables the intra-packet frequency hopping
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [0: OFF, 1: ON]
 * \param [IN] HopPeriod    Number of symbols between each hop
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: Number of symbols
 * \param [IN] iqInverted   Inverts IQ signals (LoRa only)
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [0: not inverted, 1: inverted]
 * \param [IN] timeout      Transmission timeout [ms]
 */
void RadioSetTxConfig( RadioModems_t modem, int8_t power, uint32_t fdev,
                          uint32_t bandwidth, uint32_t datarate,
                          uint8_t coderate, uint16_t preambleLen,
                          bool fixLen, bool crcOn, bool FreqHopOn,
                          uint8_t HopPeriod, bool iqInverted, uint32_t timeout );

/*!
 * \brief Checks if the given RF frequency is supported by the hardware
 *
 * \param [IN] frequency RF frequency to be checked
 * \retval isSupported [true: supported, false: unsupported]
 */
bool RadioCheckRfFrequency( uint32_t frequency );

/*!
 * \brief Computes the packet time on air in ms for the given payload
 *
 * \Remark Can only be called once SetRxConfig or SetTxConfig have been called
 *
 * \param [IN] modem      Radio modem to be used [0: FSK, 1: LoRa]
 * \param [IN] bandwidth    Sets the bandwidth
 *                          FSK : >= 2600 and <= 250000 Hz
 *                          LoRa: [0: 125 kHz, 1: 250 kHz,
 *                                 2: 500 kHz, 3: Reserved]
 * \param [IN] datarate     Sets the Datarate
 *                          FSK : 600..300000 bits/s
 *                          LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
 *                                10: 1024, 11: 2048, 12: 4096  chips]
 * \param [IN] coderate     Sets the coding rate (LoRa only)
 *                          FSK : N/A ( set to 0 )
 *                          LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
 * \param [IN] preambleLen  Sets the Preamble length
 *                          FSK : Number of bytes
 *                          LoRa: Length in symbols (the hardware adds 4 more symbols)
 * \param [IN] fixLen       Fixed length packets [0: variable, 1: fixed]
 * \param [IN] payloadLen   Sets payload length when fixed length is used
 * \param [IN] crcOn        Enables/Disables the CRC [0: OFF, 1: ON]
 *
 * \retval airTime        Computed airTime (ms) for the given packet payload length
 */
uint32_t RadioTimeOnAir( RadioModems_t modem, uint32_t bandwidth,
                              uint32_t datarate, uint8_t coderate,
                              uint16_t preambleLen, bool fixLen, uint8_t payloadLen,
                              bool crcOn );

/*!
 * \brief Sends the buffer of size. Prepares the packet to be sent and sets
 *        the radio in transmission
 *
 * \param [IN]: buffer     Buffer pointer
 * \param [IN]: size       Buffer size
 */
void RadioSend( uint8_t *buffer, uint8_t size );

/*!
 * \brief Sets the radio in sleep mode
 */
void RadioSleep( void );

/*!
 * \brief Sets the radio in standby mode
 */
void RadioStandby( void );

/*!
 * \brief Sets the radio in reception mode for the given time
 * \param [IN] timeout Reception timeout [ms]
 *                     [0: continuous, others timeout]
 */
void RadioRx( uint32_t timeout );

/*!
 * \brief Start a Channel Activity Detection
 */
void RadioStartCad( void );

/*!
 * \brief Sets the radio in continuous wave transmission mode
 *
 * \param [IN]: freq       Channel RF frequency
 * \param [IN]: power      Sets the output power [dBm]
 * \param [IN]: time       Transmission mode timeout [s]
 */
void RadioSetTxContinuousWave( uint32_t freq, int8_t power, uint16_t time );

/*!
 * \brief Reads the current RSSI value
 *
 * \retval rssiValue Current RSSI value in [dBm]
 */
int16_t RadioRssi( RadioModems_t modem );

/*!
 * \brief Writes the radio register at the specified address
 *
 * \param [IN]: addr Register address
 * \param [IN]: data New register value
 */
void RadioWrite( uint32_t addr, uint8_t data );

/*!
 * \brief Reads the radio register at the specified address
 *
 * \param [IN]: addr Register address
 * \retval data Register value
 */
uint8_t RadioRead( uint32_t addr );

/*!
 * \brief Writes multiple radio registers starting at address
 *
 * \param [IN] addr   First Radio register address
 * \param [IN] buffer Buffer containing the new register's values
 * \param [IN] size   Number of registers to be written
 */
void RadioWriteBuffer( uint32_t addr, uint8_t *buffer, uint8_t size );

/*!
 * \brief Reads multiple radio registers starting at address
 *
 * \param [IN] addr First Radio register address
 * \param [OUT] buffer Buffer where to copy the registers data
 * \param [IN] size Number of registers to be read
 */
void RadioReadBuffer( uint32_t addr, uint8_t *buffer, uint8_t size );

/*!
 * \brief Sets the maximum payload length.
 *
 * \param [IN] modem      Radio modem to be used [0: FSK, 1: LoRa]
 * \param [IN] max        Maximum payload length in bytes
 */
void RadioSetMaxPayloadLength( RadioModems_t modem, uint8_t max );

/*!
 * \brief Sets the network to public or private. Updates the sync byte.
 *
 * \remark Applies to LoRa modem only
 *
 * \param [IN] enable if true, it enables a public network
 */
void RadioSetPublicNetwork( bool enable );

/*!
 * \brief Gets the time required for the board plus radio to get out of sleep.[ms]
 *
 * \retval time Radio plus board wakeup time in ms.
 */
uint32_t RadioGetWakeupTime( void );

/*!
 * \brief Process radio irq
 */
void RadioIrqProcess( void );

/*!
 * \brief Sets the radio in reception mode with Max LNA gain for the given time
 * \param [IN] timeout Reception timeout [ms]
 *                     [0: continuous, others timeout]
 */
void RadioRxBoosted( uint32_t timeout );

/*!
 * \brief Sets the Rx duty cycle management parameters
 *
 * \param [in]  rxTime        Structure describing reception timeout value
 * \param [in]  sleepTime     Structure describing sleep timeout value
 */
void RadioSetRxDutyCycle( uint32_t rxTime, uint32_t sleepTime );

/*!
 * \brief Add a register to the retention list
 *
 * \param [in] registerAddress The address of the register to be kept in retention
 */
void RadioAddRegisterToRetentionList( uint16_t registerAddress );

/*!
 * Radio driver structure initialization
 */
const struct Radio_s Radio =
{
    RadioInit,
    RadioGetStatus,
    RadioSetModem,
    RadioSetChannel,
    RadioIsChannelFree,
    RadioRandom,
    RadioSetRxConfig,
    RadioSetTxConfig,
    RadioCheckRfFrequency,
    RadioTimeOnAir,
    RadioSend,
    RadioSleep,
    RadioStandby,
    RadioRx,
    RadioStartCad,
    RadioSetTxContinuousWave,
    RadioRssi,
    RadioWrite,
    RadioRead,
    RadioWriteBuffer,
    RadioReadBuffer,
    RadioSetMaxPayloadLength,
    RadioSetPublicNetwork,
    RadioGetWakeupTime,
    RadioIrqProcess,
    // Available on SX126x only
    RadioRxBoosted,
    RadioSetRxDutyCycle
};

/*
 * Local types definition
 */


 /*!
 * FSK bandwidth definition
 */
typedef struct
{
    uint32_t bandwidth;
    uint8_t  RegValue;
}FskBandwidth_t;

/*!
 * Precomputed FSK bandwidth registers values
 */
const FskBandwidth_t FskBandwidths[] =
{
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

const RadioLoRaBandwidths_t Bandwidths[] = { LORA_BW_125, LORA_BW_250, LORA_BW_500 };

uint8_t MaxPayloadLength = 0xFF;

uint32_t TxTimeout = 0;
uint32_t RxTimeout = 0;

bool RxContinuous = false;

uint16_t irqRegs = 0;

PacketStatus_t RadioPktStatus;
uint8_t RadioRxPayload[255];

bool IrqFired = false;

/*
 * SX126x DIO IRQ callback functions prototype
 */

/*!
 * \brief DIO 0 IRQ callback
 */
void RadioOnDioIrq( void* context );

/*!
 * \brief Tx timeout timer callback
 */
void RadioOnTxTimeoutIrq( void* context );

/*!
 * \brief Rx timeout timer callback
 */
void RadioOnRxTimeoutIrq( void* context );

/*
 * Private global variables
 */


/*!
 * Holds the current network type for the radio
 */
typedef struct
{
    bool Previous;
    bool Current;
}RadioPublicNetwork_t;

static RadioPublicNetwork_t RadioPublicNetwork = { false };

/*!
 * Radio callbacks variable
 */
static RadioEvents_t* RadioEvents;

/*
 * Public global variables
 */

/*!
 * Radio hardware and global parameters
 */

#if defined(LORAWAN_TIMESERVER_INCLUDE)
/*!
 * Tx and Rx timers
 */
TimerEvent_t TxTimeoutTimer;
TimerEvent_t RxTimeoutTimer;
#endif

/*!
 * Returns the known FSK bandwidth registers value
 *
 * \param [IN] bandwidth Bandwidth value in Hz
 * \retval regValue Bandwidth register value.
 */
static uint8_t RadioGetFskBandwidthRegValue( uint32_t bandwidth )
{
    uint8_t i;

    if( bandwidth == 0 )
    {
        return( 0x1F );
    }

    for( i = 0; i < ( sizeof( FskBandwidths ) / sizeof( FskBandwidth_t ) ) - 1; i++ )
    {
        if( ( bandwidth >= FskBandwidths[i].bandwidth ) && ( bandwidth < FskBandwidths[i + 1].bandwidth ) )
        {
            return FskBandwidths[i+1].RegValue;
        }
    }
    // ERROR: Value not found
    while( 1 );
}

radio_err_t RadioInit( RadioEvents_t *events )
{
    RadioEvents = events;
		radio_err_t result = RADIO_EOK;
	
    //typdef_rfAdaptor_dev.ops.Init( RadioOnDioIrq );
#if defined(LORAWAN_TIMESERVER_INCLUDE)
		result 	= sys_rfAdaptor_init( RF_SETTINGS_LORA ); // @BACK @INFO: Birlikte bakilacak
		if( result != RADIO_EOK ) return RADIO_ERR;
#endif

    result = typdef_rfAdaptor_dev.ops.SetStandby( STDBY_RC );
		if( result != RADIO_EOK ) return RADIO_ERR;
	
    typdef_rfAdaptor_dev.ops.SetRegulatorMode( USE_DCDC );

    typdef_rfAdaptor_dev.ops.SetBufferBaseAddress( 0x00, 0x00 );
    typdef_rfAdaptor_dev.ops.SetTxParams( 0, RADIO_RAMP_200_US );
	
	typdef_rfAdaptor_dev.ops.SetDioIrqParams( IRQ_RADIO_ALL, IRQ_RADIO_ALL, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
	
    // Add registers to the retention list (4 is the maximum possible number)
    RadioAddRegisterToRetentionList( REG_RX_GAIN );
    RadioAddRegisterToRetentionList( REG_TX_MODULATION );

#if defined(LORAWAN_TIMESERVER_INCLUDE)
    // Initialize driver timeout timers
    TimerInit( &TxTimeoutTimer, RadioOnTxTimeoutIrq , TIMEREVENT_WINDOW);	
    TimerInit( &RxTimeoutTimer, RadioOnRxTimeoutIrq , TIMEREVENT_WINDOW);
#endif

    IrqFired = false;
		
	return RADIO_EOK;
}

RadioState_t RadioGetStatus( void )
{
    switch( sys_rfAdaptor_getOperatingMode( ) )
    {
        case MODE_TX:
            return RF_TX_RUNNING;
        case MODE_RX:
            return RF_RX_RUNNING;
        case MODE_CAD:
            return RF_CAD;
        default:
            return RF_IDLE;
    }
}

void RadioSetModem( RadioModems_t modem )
{
    switch( modem )
    {
    default:
    case MODEM_FSK:
        typdef_rfAdaptor_dev.ops.SetPacketType( PACKET_TYPE_GFSK );
        // When switching to GFSK mode the LoRa SyncWord register value is reset
        // Thus, we also reset the RadioPublicNetwork variable
        RadioPublicNetwork.Current = false;
        break;
    case MODEM_LORA:
        typdef_rfAdaptor_dev.ops.SetPacketType( PACKET_TYPE_LORA );
        // Public/Private network register is reset when switching modems
        if( RadioPublicNetwork.Current != RadioPublicNetwork.Previous )
        {
            RadioPublicNetwork.Current = RadioPublicNetwork.Previous;
            RadioSetPublicNetwork( RadioPublicNetwork.Current );
        }
        break;
    }
}

radio_err_t RadioSetChannel( uint32_t freq )
{
    return typdef_rfAdaptor_dev.ops.SetRfFrequency( freq );
}

bool RadioIsChannelFree( uint32_t freq, uint32_t rxBandwidth, int16_t rssiThresh, uint32_t maxCarrierSenseTime )
{
    bool     status           = true;

    RadioSetModem( MODEM_FSK );

    RadioSetChannel( freq );

    // Set Rx bandwidth. Other parameters are not used.
    RadioSetRxConfig( MODEM_FSK, rxBandwidth, 600, 0, rxBandwidth, 3, 0, false,
                      0, false, 0, 0, false, true );
    RadioRx( 0 );

    DelayMs( 1 );

#if defined(LORAWAN_TIMESERVER_INCLUDE)

    int16_t  rssi             = 0;
    uint32_t carrierSenseTime = 0;

    carrierSenseTime = TimerGetCurrentTime( );

    // Perform carrier sense for maxCarrierSenseTime
    while( TimerGetElapsedTime( carrierSenseTime ) < maxCarrierSenseTime )
    {
        rssi = RadioRssi( MODEM_FSK );

        if( rssi > rssiThresh )
        {
            status = false;
            break;
        }
    }
#endif

    RadioSleep( );

    return status;
}

uint32_t RadioRandom( void )
{
    uint32_t rnd = 0;

    /*
     * Radio setup for random number generation
     */
    // Set LoRa modem ON
    RadioSetModem( MODEM_LORA );

    // Disable LoRa modem interrupts
    typdef_rfAdaptor_dev.ops.SetDioIrqParams( IRQ_RADIO_NONE, IRQ_RADIO_NONE, IRQ_RADIO_NONE, IRQ_RADIO_NONE );

    rnd = typdef_rfAdaptor_dev.ops.GetRandom( );

    return rnd;
}

void RadioSetRxConfig( RadioModems_t modem, uint32_t bandwidth,
                         uint32_t datarate, uint8_t coderate,
                         uint32_t bandwidthAfc, uint16_t preambleLen,
                         uint16_t symbTimeout, bool fixLen,
                         uint8_t payloadLen,
                         bool crcOn, bool freqHopOn, uint8_t hopPeriod,
                         bool iqInverted, bool rxContinuous )
{

    RxContinuous = rxContinuous;
    if( rxContinuous == true )
    {
        symbTimeout = 0;
    }
    if( fixLen == true )
    {
        MaxPayloadLength = payloadLen;
    }
    else
    {
        MaxPayloadLength = 0xFF;
    }

    switch( modem )
    {
        case MODEM_FSK:
            typdef_rfAdaptor_dev.ops.SetStopRxTimerOnPreambleDetect( false );
				
            typdef_rfAdaptor_dev.drvObj.ModulationParams.PacketType = PACKET_TYPE_GFSK;

            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.Gfsk.BitRate = datarate;
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.Gfsk.ModulationShaping = MOD_SHAPING_G_BT_1;
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.Gfsk.Bandwidth = RadioGetFskBandwidthRegValue( bandwidth << 1 ); // SX126x badwidth is double sided

            typdef_rfAdaptor_dev.drvObj.PacketParams.PacketType = PACKET_TYPE_GFSK;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.PreambleLength = ( preambleLen << 3 ); // convert byte into bit
					  typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.PreambleMinDetect = RADIO_PREAMBLE_DETECTOR_08_BITS;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.SyncWordLength = 3 << 3; // convert byte into bit
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.AddrComp = RADIO_ADDRESSCOMP_FILT_OFF;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.HeaderType = ( fixLen == true ) ? RADIO_PACKET_FIXED_LENGTH : RADIO_PACKET_VARIABLE_LENGTH;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.PayloadLength = MaxPayloadLength;
				
            if( crcOn == true )
            {
                typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.CrcLength = RADIO_CRC_2_BYTES_CCIT;
            }
            else
            {
                typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.CrcLength = RADIO_CRC_OFF;
            }
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.DcFree = RADIO_DC_FREEWHITENING;

            RadioStandby( );
            RadioSetModem( ( typdef_rfAdaptor_dev.drvObj.ModulationParams.PacketType == PACKET_TYPE_GFSK ) ? MODEM_FSK : MODEM_LORA );
						
            typdef_rfAdaptor_dev.ops.SetModulationParams( &typdef_rfAdaptor_dev.drvObj.ModulationParams );
            typdef_rfAdaptor_dev.ops.SetPacketParams( &typdef_rfAdaptor_dev.drvObj.PacketParams );
            typdef_rfAdaptor_dev.ops.SetSyncWord( ( uint8_t[] ){ 0xC1, 0x94, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00 } );
            typdef_rfAdaptor_dev.ops.SetWhiteningSeed( 0x01FF );

            RxTimeout = ( uint32_t )symbTimeout * 8000UL / datarate;
            break;

        case MODEM_LORA:
            typdef_rfAdaptor_dev.ops.SetStopRxTimerOnPreambleDetect( false );
            typdef_rfAdaptor_dev.drvObj.ModulationParams.PacketType = PACKET_TYPE_LORA;
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.SpreadingFactor = ( RadioLoRaSpreadingFactors_t )datarate;
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.Bandwidth = Bandwidths[bandwidth];
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.CodingRate = ( RadioLoRaCodingRates_t )coderate;

            if( ( ( bandwidth == 0 ) && ( ( datarate == 11 ) || ( datarate == 12 ) ) ) ||
            ( ( bandwidth == 1 ) && ( datarate == 12 ) ) )
            {
                typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.LowDatarateOptimize = 0x01;
            }
            else
            {
                typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.LowDatarateOptimize = 0x00;
            }

            typdef_rfAdaptor_dev.drvObj.PacketParams.PacketType = PACKET_TYPE_LORA;

            if( ( typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.SpreadingFactor == LORA_SF5 ) ||
                ( typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.SpreadingFactor == LORA_SF6 ) )
            {
                if( preambleLen < 12 )
                {
                    typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PreambleLength = 12;
                }
                else
                {
                    typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PreambleLength = preambleLen;
                }
            }
            else
            {
                typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PreambleLength = preambleLen;
            }

            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.HeaderType = ( RadioLoRaPacketLengthsMode_t )fixLen;

            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PayloadLength = MaxPayloadLength;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.CrcMode = ( RadioLoRaCrcModes_t )crcOn;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.InvertIQ = ( RadioLoRaIQModes_t )iqInverted;

            RadioStandby( );
            RadioSetModem( ( typdef_rfAdaptor_dev.drvObj.ModulationParams.PacketType == PACKET_TYPE_GFSK ) ? MODEM_FSK : MODEM_LORA );
            typdef_rfAdaptor_dev.ops.SetModulationParams( &typdef_rfAdaptor_dev.drvObj.ModulationParams );
            typdef_rfAdaptor_dev.ops.SetPacketParams( &typdef_rfAdaptor_dev.drvObj.PacketParams );
            typdef_rfAdaptor_dev.ops.SetLoRaSymbNumTimeout( symbTimeout );

            // WORKAROUND - Optimizing the Inverted IQ Operation, see DS_SX1261-2_V1.2 datasheet chapter 15.4
            if( typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.InvertIQ == LORA_IQ_INVERTED )
            {
                sys_rfAdaptor_writeRegister( (radio_uint16_t)REG_IQ_POLARITY, sys_rfAdaptor_readRegister( REG_IQ_POLARITY ) & ~( 1 << 2 ) );
            }
            else
            {
                sys_rfAdaptor_writeRegister( REG_IQ_POLARITY, sys_rfAdaptor_readRegister( REG_IQ_POLARITY ) | ( 1 << 2 ) );
            }
            // WORKAROUND END

            // Timeout Max, Timeout handled directly in SetRx function
            RxTimeout = 0xFFFF; 

            break;
    }
}

void RadioSetTxConfig( RadioModems_t modem, int8_t power, uint32_t fdev,
                        uint32_t bandwidth, uint32_t datarate,
                        uint8_t coderate, uint16_t preambleLen,
                        bool fixLen, bool crcOn, bool freqHopOn,
                        uint8_t hopPeriod, bool iqInverted, uint32_t timeout )
{

    switch( modem )
    {
        case MODEM_FSK:
            typdef_rfAdaptor_dev.drvObj.ModulationParams.PacketType = PACKET_TYPE_GFSK;
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.Gfsk.BitRate = datarate;

//            SX126x.ModulationParams.Params.Gfsk.ModulationShaping = MOD_SHAPING_G_BT_1;
						typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.Gfsk.ModulationShaping = MOD_SHAPING_OFF;
						typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.Gfsk.Bandwidth = RadioGetFskBandwidthRegValue( bandwidth << 1 ); // SX126x badwidth is double sided
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.Gfsk.Fdev = fdev;

            typdef_rfAdaptor_dev.drvObj.PacketParams.PacketType = PACKET_TYPE_GFSK;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.PreambleLength = ( preambleLen << 3 ); // convert byte into bit
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.PreambleMinDetect = RADIO_PREAMBLE_DETECTOR_08_BITS;
//            SX126x.PacketParams.Params.Gfsk.SyncWordLength = 3 << 3 ; // convert byte into bit
						typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.SyncWordLength = 2 << 3 ; // convert byte into bit
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.AddrComp = RADIO_ADDRESSCOMP_FILT_OFF;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.HeaderType = ( fixLen == true ) ? RADIO_PACKET_FIXED_LENGTH : RADIO_PACKET_VARIABLE_LENGTH;

            if( crcOn == true )
            {
                typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.CrcLength = RADIO_CRC_2_BYTES_CCIT;
            }
            else
            {
                typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.CrcLength = RADIO_CRC_OFF;
            }
//            SX126x.PacketParams.Params.Gfsk.DcFree = RADIO_DC_FREEWHITENING;
						typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.DcFree = RADIO_DC_FREE_OFF;

            RadioStandby( );
            RadioSetModem( ( typdef_rfAdaptor_dev.drvObj.ModulationParams.PacketType == PACKET_TYPE_GFSK ) ? MODEM_FSK : MODEM_LORA );
            typdef_rfAdaptor_dev.ops.SetModulationParams( &typdef_rfAdaptor_dev.drvObj.ModulationParams );
            typdef_rfAdaptor_dev.ops.SetPacketParams( &typdef_rfAdaptor_dev.drvObj.PacketParams );
//            SX126xSetSyncWord( ( uint8_t[] ){ 0xC1, 0x94, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00 } );
						typdef_rfAdaptor_dev.ops.SetSyncWord( ( uint8_t[] ){ 0x54, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } );
//            SX126xSetWhiteningSeed( 0x01FF );
            break;

        case MODEM_LORA:
            typdef_rfAdaptor_dev.drvObj.ModulationParams.PacketType = PACKET_TYPE_LORA;
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.SpreadingFactor = ( RadioLoRaSpreadingFactors_t ) datarate;
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.Bandwidth =  Bandwidths[bandwidth];
            typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.CodingRate= ( RadioLoRaCodingRates_t )coderate;

            if( ( ( bandwidth == 0 ) && ( ( datarate == 11 ) || ( datarate == 12 ) ) ) ||
            ( ( bandwidth == 1 ) && ( datarate == 12 ) ) )
            {
                typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.LowDatarateOptimize = 0x01;
            }
            else
            {
                typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.LowDatarateOptimize = 0x00;
            }

            typdef_rfAdaptor_dev.drvObj.PacketParams.PacketType = PACKET_TYPE_LORA;

            if( ( typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.SpreadingFactor == LORA_SF5 ) ||
                ( typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.SpreadingFactor == LORA_SF6 ) )
            {
                if( preambleLen < 12 )
                {
                    typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PreambleLength = 12;
                }
                else
                {
                    typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PreambleLength = preambleLen;
                }
            }
            else
            {
                typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PreambleLength = preambleLen;
            }

            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.HeaderType = ( RadioLoRaPacketLengthsMode_t )fixLen;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PayloadLength = MaxPayloadLength;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.CrcMode = ( RadioLoRaCrcModes_t )crcOn;
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.InvertIQ = ( RadioLoRaIQModes_t )iqInverted;

            RadioStandby( );
            RadioSetModem( ( typdef_rfAdaptor_dev.drvObj.ModulationParams.PacketType == PACKET_TYPE_GFSK ) ? MODEM_FSK : MODEM_LORA );
            typdef_rfAdaptor_dev.ops.SetModulationParams( &typdef_rfAdaptor_dev.drvObj.ModulationParams );
            typdef_rfAdaptor_dev.ops.SetPacketParams( &typdef_rfAdaptor_dev.drvObj.PacketParams );
            break;
    }

    // WORKAROUND - Modulation Quality with 500 kHz LoRa Bandwidth, see DS_SX1261-2_V1.2 datasheet chapter 15.1
    if( ( modem == MODEM_LORA ) && ( typdef_rfAdaptor_dev.drvObj.ModulationParams.Params.LoRa.Bandwidth == LORA_BW_500 ) )
    {
        sys_rfAdaptor_writeRegister( REG_TX_MODULATION, sys_rfAdaptor_readRegister( REG_TX_MODULATION ) & ~( 1 << 2 ) );
    }
    else
    {
        sys_rfAdaptor_writeRegister( REG_TX_MODULATION, sys_rfAdaptor_readRegister( REG_TX_MODULATION ) | ( 1 << 2 ) );
    }
    // WORKAROUND END

    typdef_rfAdaptor_dev.ops.SetRfTxPower( power );
    TxTimeout = timeout;
}

bool RadioCheckRfFrequency( uint32_t frequency )
{
    return true;
}

static uint32_t RadioGetLoRaBandwidthInHz( RadioLoRaBandwidths_t bw )
{
    uint32_t bandwidthInHz = 0;

    switch( bw )
    {
    case LORA_BW_007:
        bandwidthInHz = 7812UL;
        break;
    case LORA_BW_010:
        bandwidthInHz = 10417UL;
        break;
    case LORA_BW_015:
        bandwidthInHz = 15625UL;
        break;
    case LORA_BW_020:
        bandwidthInHz = 20833UL;
        break;
    case LORA_BW_031:
        bandwidthInHz = 31250UL;
        break;
    case LORA_BW_041:
        bandwidthInHz = 41667UL;
        break;
    case LORA_BW_062:
        bandwidthInHz = 62500UL;
        break;
    case LORA_BW_125:
        bandwidthInHz = 125000UL;
        break;
    case LORA_BW_250:
        bandwidthInHz = 250000UL;
        break;
    case LORA_BW_500:
        bandwidthInHz = 500000UL;
        break;
    }

    return bandwidthInHz;
}

static uint32_t RadioGetGfskTimeOnAirNumerator( uint32_t datarate, uint8_t coderate,
                              uint16_t preambleLen, bool fixLen, uint8_t payloadLen,
                              bool crcOn )
{
    const RadioAddressComp_t addrComp = RADIO_ADDRESSCOMP_FILT_OFF;
    const uint8_t syncWordLength = 3;

    return ( preambleLen << 3 ) +
           ( ( fixLen == false ) ? 8 : 0 ) +
             ( syncWordLength << 3 ) +
             ( ( payloadLen +
               ( addrComp == RADIO_ADDRESSCOMP_FILT_OFF ? 0 : 1 ) +
               ( ( crcOn == true ) ? 2 : 0 ) 
               ) << 3 
             );
}

static uint32_t RadioGetLoRaTimeOnAirNumerator( uint32_t bandwidth,
                              uint32_t datarate, uint8_t coderate,
                              uint16_t preambleLen, bool fixLen, uint8_t payloadLen,
                              bool crcOn )
{
    int32_t crDenom           = coderate + 4;
    bool    lowDatareOptimize = false;

    // Ensure that the preamble length is at least 12 symbols when using SF5 or
    // SF6
    if( ( datarate == 5 ) || ( datarate == 6 ) )
    {
        if( preambleLen < 12 )
        {
            preambleLen = 12;
        }
    }

    if( ( ( bandwidth == 0 ) && ( ( datarate == 11 ) || ( datarate == 12 ) ) ) ||
        ( ( bandwidth == 1 ) && ( datarate == 12 ) ) )
    {
        lowDatareOptimize = true;
    }

    int32_t ceilDenominator;
    int32_t ceilNumerator = ( payloadLen << 3 ) +
                            ( crcOn ? 16 : 0 ) -
                            ( 4 * datarate ) +
                            ( fixLen ? 0 : 20 );

    if( datarate <= 6 )
    {
        ceilDenominator = 4 * datarate;
    }
    else
    {
        ceilNumerator += 8;

        if( lowDatareOptimize == true )
        {
            ceilDenominator = 4 * ( datarate - 2 );
        }
        else
        {
            ceilDenominator = 4 * datarate;
        }
    }

    if( ceilNumerator < 0 )
    {
        ceilNumerator = 0;
    }

    // Perform integral ceil()
    int32_t intermediate =
        ( ( ceilNumerator + ceilDenominator - 1 ) / ceilDenominator ) * crDenom + preambleLen + 12;

    if( datarate <= 6 )
    {
        intermediate += 2;
    }

    return ( uint32_t )( ( 4 * intermediate + 1 ) * ( 1 << ( datarate - 2 ) ) );
}

uint32_t RadioTimeOnAir( RadioModems_t modem, uint32_t bandwidth,
                              uint32_t datarate, uint8_t coderate,
                              uint16_t preambleLen, bool fixLen, uint8_t payloadLen,
                              bool crcOn )
{
    uint32_t numerator = 0;
    uint32_t denominator = 1;

    switch( modem )
    {
    case MODEM_FSK:
        {
            numerator   = 1000U * RadioGetGfskTimeOnAirNumerator( datarate, coderate,
                                                                  preambleLen, fixLen,
                                                                  payloadLen, crcOn );
            denominator = datarate;
        }
        break;
    case MODEM_LORA:
        {
            numerator   = 1000U * RadioGetLoRaTimeOnAirNumerator( bandwidth, datarate,
                                                                  coderate, preambleLen,
                                                                  fixLen, payloadLen, crcOn );
            denominator = RadioGetLoRaBandwidthInHz( Bandwidths[bandwidth] );
        }
        break;
    }
    // Perform integral ceil()
    return ( numerator + denominator - 1 ) / denominator;
}

void RadioSend( uint8_t *buffer, uint8_t size )
{
    typdef_rfAdaptor_dev.ops.SetDioIrqParams( IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT,
																							IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT,
																							IRQ_RADIO_NONE,
																							IRQ_RADIO_NONE );
    
    if( typdef_rfAdaptor_dev.ops.GetPacketType( ) == PACKET_TYPE_LORA )
    {
        typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PayloadLength = size;
    }
    else
    {
        typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.PayloadLength = size;
    }

#if defined(WDT_INCLUDE)
		WDT_CLR();
#endif
		typdef_rfAdaptor_dev.ops.SetPacketParams( &typdef_rfAdaptor_dev.drvObj.PacketParams );
#if defined(WDT_INCLUDE)
		WDT_CLR();
#endif
		typdef_rfAdaptor_dev.ops.SendPayload( buffer, size, 0 );
#if defined(WDT_INCLUDE)
		WDT_CLR();
#endif

#if defined(LORAWAN_TIMESERVER_INCLUDE)
    TimerSetValue( &TxTimeoutTimer, TxTimeout );
    TimerStart( &TxTimeoutTimer );
#endif
		
}

void RadioSleep( void )
{
    typdef_unionSleepParams_t params = { 0 };

    params.Fields.WarmStart = 1;
		
	typdef_rfAdaptor_dev.ops.SetSleep( params.Value );   //@BACK @INFO: Lora sleep sorun cikarsa buraya bakilacak

    DelayMs( 2 );
}

void RadioStandby( void )
{
    typdef_rfAdaptor_dev.ops.SetStandby( STDBY_RC );
}

void RadioRx( uint32_t timeout )
{
    typdef_rfAdaptor_dev.ops.SetDioIrqParams( IRQ_RADIO_ALL, //IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT,
																							IRQ_RADIO_ALL, //IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT, 
																							IRQ_RADIO_NONE,
																							IRQ_RADIO_NONE );
#if defined(LORAWAN_TIMESERVER_INCLUDE)
    if( timeout != 0 )
    {
        TimerSetValue( &RxTimeoutTimer, timeout );
        TimerStart( &RxTimeoutTimer );
    }
#endif

    if( RxContinuous == true )
    {
        typdef_rfAdaptor_dev.ops.SetRx( 0xFFFFFF ); // Rx Continuous
    }
    else
    {
        typdef_rfAdaptor_dev.ops.SetRx( RxTimeout << 6 );
    }
}

void RadioRxBoosted( uint32_t timeout )
{
    typdef_rfAdaptor_dev.ops.SetDioIrqParams( IRQ_RADIO_ALL, //IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT,
																							IRQ_RADIO_ALL, //IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT,
																							IRQ_RADIO_NONE,
																							IRQ_RADIO_NONE );
#if defined(LORAWAN_TIMESERVER_INCLUDE)
    if( timeout != 0 )
    {
        TimerSetValue( &RxTimeoutTimer, timeout );
        TimerStart( &RxTimeoutTimer );
    }
#endif

    if( RxContinuous == true )
    {
        typdef_rfAdaptor_dev.ops.SetRxBoosted( 0xFFFFFF ); // Rx Continuous
    }
    else
    {
        typdef_rfAdaptor_dev.ops.SetRxBoosted( RxTimeout << 6 );
    }
}

void RadioSetRxDutyCycle( uint32_t rxTime, uint32_t sleepTime )
{
    typdef_rfAdaptor_dev.ops.SetRxDutyCycle( rxTime, sleepTime );
}

void RadioAddRegisterToRetentionList( uint16_t registerAddress )
{
    uint8_t buffer[9];

    // Read the address and registers already added to the list
    sys_rfAdaptor_readRegisters( REG_RETENTION_LIST_BASE_ADDRESS, buffer, 9 );

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
        sys_rfAdaptor_writeRegisters( REG_RETENTION_LIST_BASE_ADDRESS, buffer, 9 );
    }
}

void RadioStartCad( void )
{
    typdef_rfAdaptor_dev.ops.SetDioIrqParams( IRQ_CAD_DONE | IRQ_CAD_ACTIVITY_DETECTED, IRQ_CAD_DONE | IRQ_CAD_ACTIVITY_DETECTED, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
    typdef_rfAdaptor_dev.ops.SetCad( );
}

void RadioSetTxContinuousWave( uint32_t freq, int8_t power, uint16_t time )
{
    typdef_rfAdaptor_dev.ops.SetRfFrequency( freq );
    typdef_rfAdaptor_dev.ops.SetRfTxPower( power );
    typdef_rfAdaptor_dev.ops.SetTxContinuousWave( );

#if defined(LORAWAN_TIMESERVER_INCLUDE)

    uint32_t timeout = ( uint32_t )time * 1000;

    TimerSetValue( &TxTimeoutTimer, timeout );
    TimerStart( &TxTimeoutTimer );
#endif
}

int16_t RadioRssi( RadioModems_t modem )
{
    return typdef_rfAdaptor_dev.ops.GetRssiInst( );
}

void RadioWrite( uint32_t addr, uint8_t data )
{
    sys_rfAdaptor_writeRegister( addr, data );
}

uint8_t RadioRead( uint32_t addr )
{
    return sys_rfAdaptor_readRegister( addr );
}

void RadioWriteBuffer( uint32_t addr, uint8_t *buffer, uint8_t size )
{
    sys_rfAdaptor_writeRegisters( addr, buffer, size );
}

void RadioReadBuffer( uint32_t addr, uint8_t *buffer, uint8_t size )
{
    sys_rfAdaptor_readRegisters( addr, buffer, size );
}

void RadioSetMaxPayloadLength( RadioModems_t modem, uint8_t max )
{
    if( modem == MODEM_LORA )
    {
        typdef_rfAdaptor_dev.drvObj.PacketParams.Params.LoRa.PayloadLength = MaxPayloadLength = max;
        typdef_rfAdaptor_dev.ops.SetPacketParams( &typdef_rfAdaptor_dev.drvObj.PacketParams );
    }
    else
    {
        if( typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.HeaderType == RADIO_PACKET_VARIABLE_LENGTH )
        {
            typdef_rfAdaptor_dev.drvObj.PacketParams.Params.Gfsk.PayloadLength = MaxPayloadLength = max;
            typdef_rfAdaptor_dev.ops.SetPacketParams( &typdef_rfAdaptor_dev.drvObj.PacketParams );
        }
    }
}

void RadioSetPublicNetwork( bool enable )
{
    RadioPublicNetwork.Current = RadioPublicNetwork.Previous = enable;

    RadioSetModem( MODEM_LORA );
    if( enable == true )
    {
        // Change LoRa modem SyncWord
        sys_rfAdaptor_writeRegister( REG_LR_SYNCWORD, ( LORA_MAC_PUBLIC_SYNCWORD >> 8 ) & 0xFF );
        sys_rfAdaptor_writeRegister( REG_LR_SYNCWORD + 1, LORA_MAC_PUBLIC_SYNCWORD & 0xFF );
    }
    else
    {
        // Change LoRa modem SyncWord
        sys_rfAdaptor_writeRegister( REG_LR_SYNCWORD, ( LORA_MAC_PRIVATE_SYNCWORD >> 8 ) & 0xFF );
        sys_rfAdaptor_writeRegister( REG_LR_SYNCWORD + 1, LORA_MAC_PRIVATE_SYNCWORD & 0xFF );
    }
}

uint32_t RadioGetWakeupTime( void )
{
    return typdef_rfAdaptor_dev.ops.GetBoardTcxoWakeupTime( ) + RADIO_WAKEUP_TIME;
}

void RadioOnTxTimeoutIrq( void* context )
{
    if( ( RadioEvents != NULL ) && ( RadioEvents->TxTimeout != NULL ) )
    {
        RadioEvents->TxTimeout( );
    }
}

void RadioOnRxTimeoutIrq( void* context )
{
    if( ( RadioEvents != NULL ) && ( RadioEvents->RxTimeout != NULL ) )
    {
        RadioEvents->RxTimeout( );
    }
}

void RadioOnDioIrq( void* context )
{
    IrqFired = true;
	irqRegs = typdef_rfAdaptor_dev.ops.GetIrqStatus();
    typdef_rfAdaptor_dev.ops.ClearIrqStatus( irqRegs );
	
}

void RadioIrqProcess( void )
{
    //__disable_irq(); //CRITICAL_SECTION_BEGIN( );
    // Clear IRQ flag
    volatile const bool isIrqFired = IrqFired;
    IrqFired = false;
    //__enable_irq(); //CRITICAL_SECTION_END( );
	
    if( isIrqFired == true )
    {
        // Check if DIO1 pin is High. If it is the case revert IrqFired to true
    	 //__disable_irq(); //CRITICAL_SECTION_BEGIN( );
        if( sys_rfAdaptor_readPin() == 1 )
        {
            IrqFired = true;
        }
        //__enable_irq(); //CRITICAL_SECTION_END( );

        if( ( irqRegs & IRQ_TX_DONE ) == IRQ_TX_DONE )
        {
#if defined(LORAWAN_TIMESERVER_INCLUDE)
            TimerStop( &TxTimeoutTimer );
#endif
            //!< Update operating mode state to a value lower than \ref MODE_STDBY_XOSC
            sys_rfAdaptor_setOperatingMode( MODE_STDBY_RC );
            if( ( RadioEvents != NULL ) && ( RadioEvents->TxDone != NULL ) )
            {
                RadioEvents->TxDone( );
            }
        }

        if( ( irqRegs & IRQ_RX_DONE ) == IRQ_RX_DONE )
        {
#if defined(LORAWAN_TIMESERVER_INCLUDE)
            TimerStop( &RxTimeoutTimer );
#endif
            if( ( irqRegs & IRQ_CRC_ERROR ) == IRQ_CRC_ERROR )
            {
                if( RxContinuous == false )
                {
                    //!< Update operating mode state to a value lower than \ref MODE_STDBY_XOSC
                    sys_rfAdaptor_setOperatingMode( MODE_STDBY_RC );
                }
                if( ( RadioEvents != NULL ) && ( RadioEvents->RxError ) )
                {
                    RadioEvents->RxError( );
                }
            }
            else
            {
                uint8_t size;

                if( RxContinuous == false )
                {
                    //!< Update operating mode state to a value lower than \ref MODE_STDBY_XOSC
                    sys_rfAdaptor_setOperatingMode( MODE_STDBY_RC );

                    // WORKAROUND - Implicit Header Mode Timeout Behavior, see DS_SX1261-2_V1.2 datasheet chapter 15.3
                    sys_rfAdaptor_writeRegister( REG_RTC_CTRL, 0x00 );
                    sys_rfAdaptor_writeRegister( REG_EVT_CLR, sys_rfAdaptor_readRegister( REG_EVT_CLR ) | ( 1 << 1 ) );
                    // WORKAROUND END
                }
                typdef_rfAdaptor_dev.ops.GetPayload( RadioRxPayload, &size , 255 );
                typdef_rfAdaptor_dev.ops.GetPacketStatus( &RadioPktStatus );
                if( ( RadioEvents != NULL ) && ( RadioEvents->RxDone != NULL ) )
                {
                    RadioEvents->RxDone( RadioRxPayload, size, RadioPktStatus.Params.LoRa.RssiPkt, RadioPktStatus.Params.LoRa.SnrPkt );
                }
            }
        }

        if( ( irqRegs & IRQ_CAD_DONE ) == IRQ_CAD_DONE )
        {
            //!< Update operating mode state to a value lower than \ref MODE_STDBY_XOSC
            sys_rfAdaptor_setOperatingMode( MODE_STDBY_RC );
            if( ( RadioEvents != NULL ) && ( RadioEvents->CadDone != NULL ) )
            {
                RadioEvents->CadDone( ( ( irqRegs & IRQ_CAD_ACTIVITY_DETECTED ) == IRQ_CAD_ACTIVITY_DETECTED ) );
            }
        }

        if( ( irqRegs & IRQ_RX_TX_TIMEOUT ) == IRQ_RX_TX_TIMEOUT )
        {
            if( sys_rfAdaptor_getOperatingMode( ) == MODE_TX )
            {
#if defined(LORAWAN_TIMESERVER_INCLUDE)
                TimerStop( &TxTimeoutTimer );
#endif
                //!< Update operating mode state to a value lower than \ref MODE_STDBY_XOSC
                sys_rfAdaptor_setOperatingMode( MODE_STDBY_RC );
                if( ( RadioEvents != NULL ) && ( RadioEvents->TxTimeout != NULL ) )
                {
                    RadioEvents->TxTimeout( );
                }
            }
            else if( sys_rfAdaptor_getOperatingMode( ) == MODE_RX )
            {
#if defined(LORAWAN_TIMESERVER_INCLUDE)
                TimerStop( &RxTimeoutTimer );     //@BACK
#endif
                //!< Update operating mode state to a value lower than \ref MODE_STDBY_XOSC
                sys_rfAdaptor_setOperatingMode( MODE_STDBY_RC );
                if( ( RadioEvents != NULL ) && ( RadioEvents->RxTimeout != NULL ) )
                {
                    RadioEvents->RxTimeout( );
                }
            }
        }

        if( ( irqRegs & IRQ_PREAMBLE_DETECTED ) == IRQ_PREAMBLE_DETECTED )
        {
            //__NOP( );
        }

        if( ( irqRegs & IRQ_SYNCWORD_VALID ) == IRQ_SYNCWORD_VALID )
        {
            //__NOP( );
        }

        if( ( irqRegs & IRQ_HEADER_VALID ) == IRQ_HEADER_VALID )
        {
            //__NOP( );
        }

        if( ( irqRegs & IRQ_HEADER_ERROR ) == IRQ_HEADER_ERROR )
        {
#if defined(LORAWAN_TIMESERVER_INCLUDE)
            TimerStop( &RxTimeoutTimer );
#endif
            if( RxContinuous == false )
            {
                //!< Update operating mode state to a value lower than \ref MODE_STDBY_XOSC
                sys_rfAdaptor_setOperatingMode( MODE_STDBY_RC );
            }
            if( ( RadioEvents != NULL ) && ( RadioEvents->RxTimeout != NULL ) )
            {
                RadioEvents->RxTimeout( );
            }
        }
    }
}

////////////////// For Baylan RF //////////////////////

uint8_t *GetRfRxBuffer(void)
{
	return RadioRxPayload;
}

////////////////// For Baylan RF //////////////////////
