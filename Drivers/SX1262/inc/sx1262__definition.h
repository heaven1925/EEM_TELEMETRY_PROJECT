#ifndef __SX1262__DEFINITION_H__
#define	 __SX1262__DEFINITION_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define	SX1262_EN		//@ADD: aertekin 1262 kullanimina izin verir.

#ifdef SX1262_EN //@INFO : SX1262 Configurations
		#if 1 //@INFO: Freq Mode Macros
		#define SX126X_XTAL_FREQ                            32000000UL
		#define SX126X_PLL_STEP_SHIFT_AMOUNT                ( 14 )
		#define SX126X_PLL_STEP_SCALED                      ( SX126X_XTAL_FREQ >> ( 25 - SX126X_PLL_STEP_SHIFT_AMOUNT ) )
		#define SX126X_MAX_LORA_SYMB_NUM_TIMEOUT            248
		#endif
		#if 1 //@INFO: Main Register Definition
		
		#define RADIO_WAKEUP_TIME                           3					//@INFO: Radio complete Wake-up Time with margin for temperature compensation
		#define AUTO_RX_TX_OFFSET                           2					//@INFO: Compensation delay for SetAutoTx/Rx functions in 15.625 microseconds
		
		#define CRC_IBM_SEED                                0xFFFF		 //@INFO: LFSR initial value to compute IBM type CRC
		#define CRC_CCITT_SEED                              0x1D0F		 //@INFO: LFSR initial value to compute CCIT type CRC
		#define CRC_POLYNOMIAL_IBM                          0x8005    //@INFO: Polynomial used to compute IBM CRC
		#define CRC_POLYNOMIAL_CCITT                        0x1021    //@INFO: Polynomial used to compute CCIT CRC
																												
		#define REG_LR_CRCSEEDBASEADDR                      0x06BC    //@INFO: The address of the register holding the first byte defining the CRC seed
		#define REG_LR_CRCPOLYBASEADDR                      0x06BE    //@INFO: The address of the register holding the first byte defining the CRC polynomial
																												
		#define REG_LR_WHITSEEDBASEADDR_MSB                 0x06B8    //@INFO: The address of the register holding the first byte defining the whitening seed
		#define REG_LR_WHITSEEDBASEADDR_LSB                 0x06B9    //@INFO: The address of the register holding the first byte defining the whitening seed
																											
		#define REG_LR_PACKETPARAMS                         0x0704    //@INFO: The address of the register holding the packet configuration
		#define REG_LR_PAYLOADLENGTH                        0x0702    //@INFO: The address of the register holding the payload size
		#define REG_LR_SYNCH_TIMEOUT                        0x0706    //@INFO: The address of the register holding the re-calculated number of symbols
		#define REG_LR_SYNCWORDBASEADDRESS                  0x06C0    //@INFO: The addresses of the registers holding SyncWords values
		#define REG_LR_SYNCWORD                             0x0740    //@INFO: The addresses of the register holding LoRa Modem SyncWord valu
	
		#define	SX1276_REG_SYNCVALUE1												REG_LR_SYNCWORDBASEADDRESS
		#define	SX1276_REG_SYNCVALUE2												( SX1276_REG_SYNCVALUE1 + 0x01 )
		#define	SX1276_REG_SYNCVALUE3												( SX1276_REG_SYNCVALUE1 + 0x02 )
		#define	SX1276_REG_SYNCVALUE4												( SX1276_REG_SYNCVALUE1 + 0x03 )
		#define	SX1276_REG_SYNCVALUE5												( SX1276_REG_SYNCVALUE1 + 0x04 )	
		#define	SX1276_REG_SYNCVALUE6												( SX1276_REG_SYNCVALUE1 + 0x05 )
		#define	SX1276_REG_SYNCVALUE7												( SX1276_REG_SYNCVALUE1 + 0x06 )
		#define	SX1276_REG_SYNCVALUE8												( SX1276_REG_SYNCVALUE1 + 0x07 )

		#define LORA_MAC_PRIVATE_SYNCWORD                   0x1424    //@INFO: Syncword for Private LoRa networks
		#define LORA_MAC_PUBLIC_SYNCWORD                    0x3444    //@INFO: Syncword for Public LoRa networks
																												
		#define RANDOM_NUMBER_GENERATORBASEADDR             0x0819    //@INFO: The address of the register giving a 32-bit random number
					
		#define	REG_NODE_ADDRESS														0x06CD		//@INFO: Node Address used in FSK mode @NEW: a.ertekin
		#define	REG_BROADCAST_ADDRESS												0x06CE		//@INFO:  Broadcast Address used in FSK mode	@NEW: a.ertekin
		
		#define REG_ANA_LNA                                 0x08E2    //@INFO: The address of the register used to disable the LNA
		#define REG_ANA_MIXER                               0x08E5    //@INFO: The address of the register used to disable the mixer
		#define REG_RX_GAIN                                 0x08AC    //@INFO: The address of the register holding RX Gain value (0x94: power saving, 0x96: rx boosted)
		#define REG_XTA_TRIM                                0x0911    //@INFO: Change the value on the device internal trimming capacitor
		#define REG_OCP                                     0x08E7    //@INFO: Set the current max value in the over current protection
																											
		#define MAX_NB_REG_IN_RETENTION                     4         //@INFO: Maximum number of register that can be added to the retention list
																										
		#define REG_RETENTION_LIST_BASE_ADDRESS             0x029F    //@INFO: Base address of the register retention list
		#define REG_IQ_POLARITY                             0x0736    //@INFO: WORKAROUND - Optimizing the Inverted IQ Operation, see DS_SX1261-2_V1.2 datasheet chapter 15.4
		#define REG_TX_MODULATION                           0x0889    //@INFO: WORKAROUND - Modulation Quality with 500 kHz LoRa Bandwidth, see DS_SX1261-2_V1.2 datasheet chapter 15.1
		#define REG_TX_CLAMP_CFG                            0x08D8    //@INFO: WORKAROUND - Better resistance to antenna mismatch, see DS_SX1261-2_V1.2 datasheet chapter 15.2
		#define REG_RTC_CTRL                                0x0902    //@INFO: RTC control
		#define REG_EVT_CLR                                 0x0944    //@INFO: Event clear
		
		#endif
		
		#if 1	//@INFO: Register Default Reset Values
		
		#define	REG_LR_WHITSEEDBASEADDR_MSB_DEFAULT					0x01
		#define	REG_LR_WHITSEEDBASEADDR_LSB_DEFAULT					0x00
		#define	REG_LR_CRCSEEDBASEADDR_DEFAULT							0x1D0F
		#define	REG_NODE_ADDRESS_DEFAULT										0x00
		#define	REG_BROADCAST_ADDRESS_DEFAULT								0x00
		#define	REG_LR_SYNCWORD_DEFAULT											0x1424
		#define	REG_RX_GAIN_DEFAULT													0x94
		#define	REG_XTA_TRIM_DEFAULT												0x0505
		
		#endif
		
		#if 1 //@INFO: SyncValue Def
		
		#define RF_SYNCVALUE1_SYNCVALUE                     0x01  // Default
		#define RF_SYNCVALUE2_SYNCVALUE                     0x01  // Default
		#define RF_SYNCVALUE3_SYNCVALUE                     0x01  // Default
		#define RF_SYNCVALUE4_SYNCVALUE                     0x01  // Default
		#define RF_SYNCVALUE5_SYNCVALUE                     0x01  // Default
		#define RF_SYNCVALUE6_SYNCVALUE                     0x01  // Default
		#define RF_SYNCVALUE7_SYNCVALUE                     0x01  // Default
		#define RF_SYNCVALUE8_SYNCVALUE                     0x01  // Default
		
		#endif
		
		#if 1 //@INFO: WorkAround Register Macro
		//@NEW: aertekin //@INFO:REG_TX_MODULATION registerinin 2. biti icin set-reset makrolari
		
		#define	RESET_WORKAROUND_BIT(X)								( X	 & 	~( 1 << 2 ) )		
		#define	SET_WORKAROUND_BIT(X)									( X	 | 	 ( 1 << 2 )	)			
		
		#endif
		
		#if 1 //@INFO: SX1262 Register Configuration numarat�rleri 	//@NEW aertekin
		
		typedef enum	//@INFO: Her adim 2.5mA olmaktadir ! //@NOTICE: SetPaConfig() geldikten sonra otomatik 140mA olur !
		{
			REG_OCP_0    = 0x00	,	//@INFO : Over Current Protection is 0 mA 
			REG_OCP_2_5					,	//@INFO : Over Current Protection is 2.5 mA
			REG_OCP_5           , //@INFO : Over Current Protection is 5 mA
			REG_OCP_7_5         , //@INFO : Over Current Protection is 7.5   mA
			REG_OCP_10          , //@INFO : Over Current Protection is 10    mA
			REG_OCP_12_5        , //@INFO : Over Current Protection is 12.5  mA
			REG_OCP_15          , //@INFO : Over Current Protection is 15    mA
			REG_OCP_17_5        , //@INFO : Over Current Protection is 17_5  mA
			REG_OCP_20          , //@INFO : Over Current Protection is 20    mA
			REG_OCP_22_5        , //@INFO : Over Current Protection is 22.5  mA
			REG_OCP_25          , //@INFO : Over Current Protection is 25    mA
			REG_OCP_27_5        , //@INFO : Over Current Protection is 27.5  mA
			REG_OCP_30          , //@INFO : Over Current Protection is 30    mA
			REG_OCP_32_5        , //@INFO : Over Current Protection is 32.5  mA
			REG_OCP_35          , //@INFO : Over Current Protection is 35    mA
			REG_OCP_37_5        , //@INFO : Over Current Protection is 37.5  mA
			REG_OCP_40          , //@INFO : Over Current Protection is 40    mA
			REG_OCP_42_5        , //@INFO : Over Current Protection is 42.5  mA
			REG_OCP_45          , //@INFO : Over Current Protection is 45    mA
			REG_OCP_47_5        , //@INFO : Over Current Protection is 47.5  mA
			REG_OCP_50          , //@INFO : Over Current Protection is 50    mA
			REG_OCP_52_5        , //@INFO : Over Current Protection is 52.5  mA
			REG_OCP_55          , //@INFO : Over Current Protection is 55    mA
			REG_OCP_57_5        , //@INFO : Over Current Protection is 57.5  mA
			REG_OCP_60          , //@INFO : Over Current Protection is 60    mA
			REG_OCP_62_5        , //@INFO : Over Current Protection is 62_5  mA
			REG_OCP_65          , //@INFO : Over Current Protection is 65    mA
			REG_OCP_67_5        , //@INFO : Over Current Protection is 67_5  mA
			REG_OCP_70          , //@INFO : Over Current Protection is 70    mA
			REG_OCP_72_5        , //@INFO : Over Current Protection is 72_5  mA
			REG_OCP_75          , //@INFO : Over Current Protection is 75    mA
			REG_OCP_77_5        , //@INFO : Over Current Protection is 77_5  mA
			REG_OCP_80          , //@INFO : Over Current Protection is 80    mA
			REG_OCP_82_5        , //@INFO : Over Current Protection is 82_5  mA
			REG_OCP_85          , //@INFO : Over Current Protection is 85    mA
			REG_OCP_87_5        , //@INFO : Over Current Protection is 87_5  mA
			REG_OCP_90          , //@INFO : Over Current Protection is 90    mA
			REG_OCP_92_5        , //@INFO : Over Current Protection is 92_5  mA
			REG_OCP_95          , //@INFO : Over Current Protection is 95    mA
			REG_OCP_97_5        , //@INFO : Over Current Protection is 97_5  mA
			REG_OCP_100         , //@INFO : Over Current Protection is 100   mA
			REG_OCP_102_5       , //@INFO : Over Current Protection is 102_5 mA
			REG_OCP_105         , //@INFO : Over Current Protection is 105   mA
			REG_OCP_107_5       , //@INFO : Over Current Protection is 107_5 mA
			REG_OCP_110         , //@INFO : Over Current Protection is 110   mA
			REG_OCP_112_5       , //@INFO : Over Current Protection is 112_5 mA
			REG_OCP_115         , //@INFO : Over Current Protection is 115   mA
			REG_OCP_117_5       , //@INFO : Over Current Protection is 117_5 mA
			REG_OCP_120         , //@INFO : Over Current Protection is 120   mA
			REG_OCP_122_5       , //@INFO : Over Current Protection is 122_5 mA
			REG_OCP_125         , //@INFO : Over Current Protection is 125   mA
			REG_OCP_127_5       , //@INFO : Over Current Protection is 127_5 mA
			REG_OCP_130         , //@INFO : Over Current Protection is 130   mA
			REG_OCP_132_5       , //@INFO : Over Current Protection is 132_5 mA
			REG_OCP_135         , //@INFO : Over Current Protection is 135   mA
			REG_OCP_137_5       , //@INFO : Over Current Protection is 137_5 mA
			REG_OCP_140         , //@INFO : Over Current Protection is 140   mA
			REG_OCP_142_5       , //@INFO : Over Current Protection is 142_5 mA
			REG_OCP_145         , //@INFO : Over Current Protection is 145   mA
			REG_OCP_147_5       , //@INFO : Over Current Protection is 147_5 mA
			REG_OCP_150         , //@INFO : Over Current Protection is 150   mA
			REG_OCP_152_5       , //@INFO : Over Current Protection is 152_5 mA
			REG_OCP_155         , //@INFO : Over Current Protection is 155   mA
			REG_OCP_157_5       , //@INFO : Over Current Protection is 157_5 mA
			REG_OCP_160         , //@INFO : Over Current Protection is 160   mA

		}OverCurrent_t;
		
		#endif
		
		
		#if 1 //@INFO: Main Enumarator Definitiom
		
		//@INFO: Buffer temizleme numaratorleri
		enum
		{
			IDLE_CLR			= 0,
			OPCODE_CLR			 ,
			SEND_BUFFER_CLR	 ,
			RECV_BUFFER_CLR	 ,
			DATA_BUFFER_CLR	 ,
			SEND_RECV_BUFFER_CLR ,
			ALL_BUFFER_CLR	 
		};
		
		enum
		{
			ANT_SW_OFF = 0 ,
			ANT_SW_ON = !(ANT_SW_OFF)
		};
		
		
		//@INFO: Header Code Numaratorleri
		enum IrqPblSyncHeaderCode_t
		{
				IRQ_PBL_DETECT_CODE                     = 0x01,
				IRQ_SYNCWORD_VALID_CODE                 = 0x02,
				IRQ_HEADER_VALID_CODE                   = 0x04,
		};
		
		//@INFO: Callback fonksiyonlarinin donus tipi tanimlamalari
		typedef enum								
		{
				IRQ_HEADER_ERROR_CODE                   = 0x01,
				IRQ_SYNCWORD_ERROR_CODE                 = 0x02,
				IRQ_CRC_ERROR_CODE                      = 0x04,
		}IrqErrorCode_t;
		
		//@INFO: Kullanilan g�c reg�lat�r� numarat�r�
		typedef enum
		{
    USE_LDO                                 = 0x00, // default
    USE_DCDC                                = 0x01,
		}RadioRegulatorMode_t;
		
		//@INFO: Kullanulanbilecek paket-protokol tipleri numarat�r�
		typedef enum
		{
				PACKET_TYPE_GFSK                        = 0x00,
				PACKET_TYPE_LORA                        = 0x01,
				PACKET_TYPE_NONE                        = 0x0F,
		}RadioPacketTypes_t;

		//@INFO: G�� y�kseltecinin Ramping(Y�kselme) zamani numarat�r� 
		typedef enum																								
		{																											/* ramp time [us]	*/
				RADIO_RAMP_10_US                        = 0x00,		//!< 		10		us
				RADIO_RAMP_20_US                        = 0x01,		//!< 		20	  us
				RADIO_RAMP_40_US                        = 0x02,		//!< 		40	  us
				RADIO_RAMP_80_US                        = 0x03,		//!< 		80	  us
				RADIO_RAMP_200_US                       = 0x04,		//!< 		200	  us
				RADIO_RAMP_800_US                       = 0x05,		//!< 		800	  us
				RADIO_RAMP_1700_US                      = 0x06,		//!< 		1700	us
				RADIO_RAMP_3400_US                      = 0x07,		//!< 		3400	us
		}RadioRampTimes_t;
		

		#if 1 //@INFO: PA Operating Mode Optimal Settings @NEW: aertekin
		#ifndef RADIO_OUTPUTPOWER_22DBM		/* Value in SetTxParams -> 22dB */
		#define	RADIO_OUTPUTPOWER_22DBM		\
		{                                 \
			.paDutyCycle	 =	0x04  ,       \
			.hpMax				 =	0x07  ,       \
			.deviceSel     =	0x00  ,       \
			.paLut         =	0x01  ,       \
		}
		#endif
		
		#ifndef RADIO_OUTPUTPOWER_20DBM		/* Value in SetTxParams -> 22dB */
		#define	RADIO_OUTPUTPOWER_20DBM		\
		{                                 \
			.paDutyCycle	 =	0x03  ,       \
			.hpMax				 =	0x05  ,       \
			.deviceSel     =	0x00  ,       \
			.paLut         =	0x01  ,       \
		}
		#endif
		
		#ifndef RADIO_OUTPUTPOWER_17DBM		/* Value in SetTxParams -> 22dB */
		#define	RADIO_OUTPUTPOWER_17DBM		\
		{                                 \
			.paDutyCycle	 =	0x02  ,       \
			.hpMax				 =	0x03  ,       \
			.deviceSel     =	0x00  ,       \
			.paLut         =	0x01  ,       \
		}
		#endif
		
		#ifndef RADIO_OUTPUTPOWER_14DBM		/* Value in SetTxParams -> 22dB */
		#define	RADIO_OUTPUTPOWER_14DBM		\
		{                                 \
			.paDutyCycle	 =	0x02  ,       \
			.hpMax				 =	0x02  ,       \
			.deviceSel     =	0x00  ,       \
			.paLut         =	0x01  ,       \
		}
		#endif
		#endif
		
		
		
		//@INFO: LoRa kullanilan aktif kanal numarat�r�
		typedef enum
		{
				LORA_CAD_01_SYMBOL                      = 0x00,
				LORA_CAD_02_SYMBOL                      = 0x01,
				LORA_CAD_04_SYMBOL                      = 0x02,
				LORA_CAD_08_SYMBOL                      = 0x03,
				LORA_CAD_16_SYMBOL                      = 0x04,
		}RadioLoRaCadSymbols_t;
					
		//@INFO: LoRa CAD islemi tamamlandiktan sonra Kanal Etkinligi Algilama numarat�r�
		typedef enum
		{
				LORA_CAD_ONLY                           = 0x00,
				LORA_CAD_RX                             = 0x01,
				LORA_CAD_LBT                            = 0x10,
		}RadioCadExitModes_t;
					
		//@INFO: Mod�lasyon t�r� belirleme numarat�r�
		typedef enum
		{
				MOD_SHAPING_OFF                         = 0x00,	//!< No Filter applied
				MOD_SHAPING_G_BT_03                     = 0x08, //!< Gaussian BT 0.3
				MOD_SHAPING_G_BT_05                     = 0x09, //!< Gaussian BT 0.5
				MOD_SHAPING_G_BT_07                     = 0x0A, //!< Gaussian BT 0.7
				MOD_SHAPING_G_BT_1                      = 0x0B, //!< Gaussian BT 1
		}RadioModShapings_t;		
		
		
		#ifndef BITRATE_DEFAULT
			#define	WMBUS_
		#endif
		
		//@INFO: Mod�lasyon band genisligi numarat�r� 		
		typedef enum
		{
				RX_BW_4800                              = 0x1F,
				RX_BW_5800                              = 0x17,
				RX_BW_7300                              = 0x0F,
				RX_BW_9700                              = 0x1E,
				RX_BW_11700                             = 0x16,
				RX_BW_14600                             = 0x0E,
				RX_BW_19500                             = 0x1D,
				RX_BW_23400                             = 0x15,
				RX_BW_29300                             = 0x0D,
				RX_BW_39000                             = 0x1C,
				RX_BW_46900                             = 0x14,
				RX_BW_58600                             = 0x0C,
				RX_BW_78200                             = 0x1B,
				RX_BW_93800                             = 0x13,
				RX_BW_117300                            = 0x0B,
				RX_BW_156200                            = 0x1A,
				RX_BW_187200                            = 0x12,
				RX_BW_234300                            = 0x0A,
				RX_BW_312000                            = 0x19,
				RX_BW_373600                            = 0x11,
				RX_BW_467000                            = 0x09,
		}RadioRxBandwidth_t;		
				
		//@INFO:Lora Paket t�rleri i�in sa�ilma fakt�r� numarat�r�leri	
		typedef enum
		{
				LORA_SF5                                = 0x05,
				LORA_SF6                                = 0x06,
				LORA_SF7                                = 0x07,
				LORA_SF8                                = 0x08,
				LORA_SF9                                = 0x09,
				LORA_SF10                               = 0x0A,
				LORA_SF11                               = 0x0B,
				LORA_SF12                               = 0x0C,
		}RadioLoRaSpreadingFactors_t;		
				
		//@INFO: LoRa paket t�r� i�in bant genisligi numarat�r�
		typedef enum
		{
				LORA_BW_500                             = 6,
				LORA_BW_250                             = 5,
				LORA_BW_125                             = 4,
				LORA_BW_062                             = 3,
				LORA_BW_041                             = 10,
				LORA_BW_031                             = 2,
				LORA_BW_020                             = 9,
				LORA_BW_015                             = 1,
				LORA_BW_010                             = 8,
				LORA_BW_007                             = 0,
		}RadioLoRaBandwidths_t;
		
		//@INFO: LoRa paket t�r� i�in kodlama hizi degerleri numaratorleri
		typedef enum
		{
				LORA_CR_4_5                             = 0x01,
				LORA_CR_4_6                             = 0x02,
				LORA_CR_4_7                             = 0x03,
				LORA_CR_4_8                             = 0x04,
		}RadioLoRaCodingRates_t;
		
		//@INFO: RX tarafindan gelen bit uzunlugu tespit numarat�rler
		typedef enum
		{
				RADIO_PREAMBLE_DETECTOR_OFF             = 0x00,         //!< Preamble detection length off
				RADIO_PREAMBLE_DETECTOR_08_BITS         = 0x04,         //!< Preamble detection length 8 bits
				RADIO_PREAMBLE_DETECTOR_16_BITS         = 0x05,         //!< Preamble detection length 16 bits
				RADIO_PREAMBLE_DETECTOR_24_BITS         = 0x06,         //!< Preamble detection length 24 bits
				RADIO_PREAMBLE_DETECTOR_32_BITS         = 0x07,         //!< Preamble detection length 32 bit
		}RadioPreambleDetection_t;
		
	
		//@INFO: Represents the possible combinations of SyncWord correlators activated
		typedef enum
		{
				RADIO_ADDRESSCOMP_FILT_OFF              = 0x00,         //!< No correlator turned on, i.e. do not search for SyncWord
				RADIO_ADDRESSCOMP_FILT_NODE             = 0x01,
				RADIO_ADDRESSCOMP_FILT_NODE_BROAD       = 0x02,
		}RadioAddressComp_t;
		
		//@INFO: GFSK paket uzunlugu numaratoru
		typedef enum
		{
				RADIO_PACKET_FIXED_LENGTH               = 0x00,         //!< The packet is known on both sides, no header included in the packet
				RADIO_PACKET_VARIABLE_LENGTH            = 0x01,         //!< The packet is on variable size, header included
		}RadioPacketLengthModes_t;
		
		
		//@INFO: CRC Uzunlugu numarat�r�
		typedef enum
		{
				RADIO_CRC_OFF                           = 0x01,         //!< No CRC in use
				RADIO_CRC_1_BYTES                       = 0x00,
				RADIO_CRC_2_BYTES                       = 0x02,
				RADIO_CRC_1_BYTES_INV                   = 0x04,
				RADIO_CRC_2_BYTES_INV                   = 0x06,
				RADIO_CRC_2_BYTES_IBM                   = 0xF1,
				RADIO_CRC_2_BYTES_CCIT                  = 0xF2,
		}RadioCrcTypes_t;
		
		//@INFO: Radio whitening mode durum numarat�r�
		typedef enum
		{
				RADIO_DC_FREE_OFF                       = 0x00,
				RADIO_DC_FREEWHITENING                  = 0x01,
		}RadioDcFree_t;
		
		
		//@INFO: Lora paketi uzunluk enumaratorleri
		typedef enum
		{
				LORA_PACKET_VARIABLE_LENGTH             = 0x00,         //!< The packet is on variable size, header included
				LORA_PACKET_FIXED_LENGTH                = 0x01,         //!< The packet is known on both sides, no header included in the packet
				LORA_PACKET_EXPLICIT                    = LORA_PACKET_VARIABLE_LENGTH,
				LORA_PACKET_IMPLICIT                    = LORA_PACKET_FIXED_LENGTH,
		}RadioLoRaPacketLengthsMode_t;
		
		
		//@INFO: LoRA paketi i�in CRC durum numarat�r�
		typedef enum
		{
				LORA_CRC_ON                             = 0x01,         //!< CRC activated
				LORA_CRC_OFF                            = 0x00,         //!< CRC not used
		}RadioLoRaCrcModes_t;
		
		
		//@INFO: Lora paketi i�in IQ modu
		typedef enum
		{
				LORA_IQ_NORMAL                          = 0x00,
				LORA_IQ_INVERTED                        = 0x01,
		}RadioLoRaIQModes_t;
		

		/*******************************************************************************/
		
		//@INFO: Radio komutlari icin mevcut olan interrupt maskeleme numarat�rleri
		//@INFO: T�m paket t�rleri i�in bu interruptlar gecerlidir !
		typedef enum __attribute__((packed))
		{
				IRQ_RADIO_NONE                          = 0x0000,
				IRQ_TX_DONE                             = 0x0001,
				IRQ_RX_DONE                             = 0x0002,
				IRQ_PREAMBLE_DETECTED                   = 0x0004,
				IRQ_SYNCWORD_VALID                      = 0x0008,
				IRQ_HEADER_VALID                        = 0x0010,
				IRQ_HEADER_ERROR                        = 0x0020,
				IRQ_CRC_ERROR                           = 0x0040,
				IRQ_CAD_DONE                            = 0x0080,
				IRQ_CAD_ACTIVITY_DETECTED               = 0x0100,
				IRQ_RX_TX_TIMEOUT                       = 0x0200,
				IRQ_RADIO_ALL                           = 0xFFFF,
		}RadioIrqMasks_t;				
		
		//@INFO: SetDioIrqParams SPI Transaction ile 8 byte gonderilecektir.
		#define	SIZE_OF_IRQPARAMFRAME	8
		
		typedef struct __attribute__((packed))
		{
			uint16_t	irqMask  ;
			uint16_t	dio1Mask ;
			uint16_t	dio2Mask ;
		}IrqAndDioMasks;
		
		/*******************************************************************************/
#endif	
		#if 1 //@INFO: Radio Command Structures
		/***********************************************************************************************/
		typedef struct
		{		
			uint8_t sleepConfig_u8;
			union
			{
				uint8_t WakeUpRTC               : 1	;    //@INFO: RTC'den uyandirma sinyali geldiginde sleep mode'dan cikar !
				uint8_t Reset                   : 1	;
				uint8_t WarmStart               : 1	;
				uint8_t Reserved                : 5	;		
			}Bits;
		}SleepConfigType;

		#define		SETSLEEP_CMD_SIZE			2
		/***********************************************************************************************/
		
		/*******************************************************************************/
		//@INFO: Radio Status Durumlarinin belirtildigi structure 
		typedef union RadioStatus_u	
		{
			uint8_t value;
			struct
					{   //@INFO: Bit yerlesimi lsb -> msb seklindedir.
						uint8_t           : 1;  //!< Reserved
						uint8_t CmdStatus : 3;  //@INFO: Komut Durumu - Command status 
						uint8_t ChipMode  : 3;  //@INFO: �ip Modu - Chip mode
						uint8_t           : 1;  //!< Reserved
					}Fields;
			}RadioStatus_t;
		/*******************************************************************************/
		
		//@INFO: Power Amplifier ayarlarinin yapilacagi Opcommand Struct
		typedef struct	__attribute__((packed))
		{
			uint8_t paDutyCycle ;
			uint8_t hpMax				;
			uint8_t	deviceSel		;
			uint8_t	paLut				;
		}RadioPaCommand_t;
			
		/*******************************************************************************/
		//@INFO: Paket t�rleri icin mod�lasyon parametrelerinin belirtildigi yapi
		typedef struct	__attribute__((packed))
		{		
				RadioPacketTypes_t     PacketType;      //@INFO: Mod�lasyon yapilacak paket t�r� Lora/GFSK/None
				struct  __attribute__((packed)) 
				{		
						struct  __attribute__((packed)) 	//@INFO: GFSK Mod�lasyon Parametreleri
						{
								uint32_t                     										BitRate;
								uint32_t                     										Fdev;
								RadioModShapings_t           										ModulationShaping;
								uint8_t                      										Bandwidth;
						}Gfsk;
						
						struct  __attribute__((packed)) 	//@INFO: LoRa Mod�lasyon Parametreleri
						{
								RadioLoRaSpreadingFactors_t  SpreadingFactor;   		//!< Spreading Factor for the LoRa modulation
								RadioLoRaBandwidths_t        Bandwidth;         		//!< Bandwidth for the LoRa modulation
								RadioLoRaCodingRates_t       CodingRate;        		//!< Coding rate for the LoRa modulation
								uint8_t                   LowDatarateOptimize; 	//!< Indicates if the modem uses the low datarate optimization
						}LoRa;
						
				}Params;  //@INFO: Mod�lasyon Parametrelerini Tutan yapi
		}ModulationParams_t;
		/*******************************************************************************/
		
		
		
		/*******************************************************************************
		
								Sabit Genislikli - GFSK Paket Icerigi
		
		-------------------------------------------------------------
		| Preamble		| Sync Word	|	Adres	|			Payload		|		CRC		|
		| 8 - 65536		|	 0 - 8		|	0 - 1	|			1 - 255		|  0-1-2	|
		|		Byte			|		Byte		| Byte	|			 Byte			|	 Byte		|
		-------------------------------------------------------------
															<-----------------------> CRC, Checksum
																			 <------------------------> Whitening
		
						Ayarlanabilir Genislikli - GFSK Paket Icerigi
		
		-------------------------------------------------------------------------
		| Preamble		| Sync Word	|	 Genislik	|	Adres	|			Payload		|		CRC		|
		| 8 - 65536		|	 0 - 8		|			1			|		1		|			1 - 255		|  0-1-2	|
		|		Byte			|		Byte		| 	Byte		|	Byte	|			 Byte			|	 Byte		|
		-------------------------------------------------------------------------		
															<-----------------------------------> CRC, Checksum
															<---------------------------------------------> Whitening
															
		@NOTICE: Whitening, rastgele bir dizi olusturmak i�in kullanilan bir yapidir. 	
		
												LoRA Paket Icerigi
												
										<--------------------> nHeader Sembolleri		
		<-------------> nPreamble Sembolleri
		-----------------------------------------------------------------
		| 						| Header | 		CRC				|								|		CRC		|
		|  Preamble		|-----------------------|			Payload		| Payload	|
		|							| Sadece explicit mode	| 							|	 				|
		-----------------------------------------------------------------
									<-----------------------><------------------------> Coding Rate = 4/8
		<---------------------------------------------------------------> Spreading Factor																		
		
		*******************************************************************************/
		typedef struct	__attribute__((packed))
		{
				RadioPacketTypes_t       						 PacketType;        //@INFO: Paket icerigi belirtilecek paket t�r� Lora/GFSK/None
				struct  __attribute__((packed)) 
				{
						struct  __attribute__((packed)) 	//@INFO: GFSK Paket Parametreleri
						{
								uint16_t                  		PreambleLength;    //!< The preamble Tx length for GFSK packet type in bit
								RadioPreambleDetection_t     	PreambleMinDetect; //!< The preamble Rx length minimal for GFSK packet type
								uint8_t                   		SyncWordLength;    //!< The synchronization word length for GFSK packet type
								RadioAddressComp_t           	AddrComp;          //!< Activated SyncWord correlators
								RadioPacketLengthModes_t     	HeaderType;        //!< If the header is explicit, it will be transmitted in the GFSK packet. If the header is implicit, it will not be transmitted
								uint8_t                   		PayloadLength;     //!< Size of the payload in the GFSK packet
								RadioCrcTypes_t              	CrcLength;         //!< Size of the CRC block in the GFSK packet
								RadioDcFree_t               	 DcFree;
						}Gfsk;

						struct  __attribute__((packed))  //@INFO: LoRA Paket Parametreleri
						{
								uint16_t                  		PreambleLength;    //!< The preamble length is the number of LoRa symbols in the preamble
								RadioLoRaPacketLengthsMode_t 	HeaderType;        //!< If the header is explicit, it will be transmitted in the LoRa packet. If the header is implicit, it will not be transmitted
								uint8_t                   		PayloadLength;     //!< Size of the payload in the LoRa packet
								RadioLoRaCrcModes_t          	CrcMode;           //!< Size of CRC block in LoRa packet
								RadioLoRaIQModes_t           	InvertIQ;          //!< Allows to swap IQ for LoRa packet
						}LoRa;
				}Params;   //@INFO: Paket Parametrelerini Tutan yapi
				
		}PacketParams_t;
		/*******************************************************************************/
		
		
		/*******************************************************************************/
		//@INFO:  Her paket icin paketin durumunu belirten yapi
		typedef struct	__attribute__((packed))
		{
				RadioPacketTypes_t  									PacketType;   	//@INFO: Paket durumu g�zlemlenecek, paket t�r�
				struct  __attribute__((packed)) 
				{
						struct  __attribute__((packed)) 	//@INFO: GFSK Paket Durumlari
						{	
								uint8_t 																					RxStatus;
								int8_t 																					RssiAvg;       	//!< The averaged RSSI
								int8_t 																					RssiSync;      	//!< The RSSI measured on last packet
								uint32_t 																				FreqError;	
						}Gfsk;
						
						struct  __attribute__((packed)) 	//@INFO: LoRA Paket Durumlari
						{
								int8_t RssiPkt;                                //!< The RSSI of the last packet
								int8_t SnrPkt;                                 //!< The SNR of the last packet
								int8_t SignalRssiPkt;
								uint32_t FreqError;
						}LoRa;
						
				}Params;	//@INFO: Paket Durumlarini Tutan yapi
				
		}PacketStatus_t;
		/*******************************************************************************/
		#endif
		
		#if 1 //@INFO: Paket T�rlerine g�re �zel konfig�rasyon yapilari
		
		//@INFO:  GFSK or LoRa paket tipi kullanildigin alinan paket sayisinin hatali-paket , crc-hatasi ve alinan paketlerin tutuldugu yapi
		typedef struct	__attribute__((packed))
		{
				RadioPacketTypes_t                  packetType;       //!< Packet to which the packet status are referring to.
				uint16_t 														PacketReceived;
				uint16_t														CrcOk;
				uint16_t 														LengthError;
		}RxCounter_t;		
		
		//@INFO:  Kalibrasyon konfig�rasyonlarinin tutuldugu yapi
		typedef union
		{
				struct
				{
						uint8_t RC64KEnable    : 1;                             //!< Calibrate RC64K clock
						uint8_t RC13MEnable    : 1;                             //!< Calibrate RC13M clock
						uint8_t PLLEnable      : 1;                             //!< Calibrate PLL
						uint8_t ADCPulseEnable : 1;                             //!< Calibrate ADC Pulse
						uint8_t ADCBulkNEnable : 1;                             //!< Calibrate ADC bulkN
						uint8_t ADCBulkPEnable : 1;                             //!< Calibrate ADC bulkP
						uint8_t ImgEnable      : 1;
						uint8_t                : 1;
				}Fields;
				uint8_t Value;
		}CalibrationParams_t;
		
		
		//@INFO: Olusabilecek hata t�rlerinin tutuldugu yapi
		typedef union
		{
				struct
				{
						uint8_t Rc64kCalib              : 1;                    //!< RC 64kHz oscillator calibration failed
						uint8_t Rc13mCalib              : 1;                    //!< RC 13MHz oscillator calibration failed
						uint8_t PllCalib                : 1;                    //!< PLL calibration failed
						uint8_t AdcCalib                : 1;                    //!< ADC calibration failed
						uint8_t ImgCalib                : 1;                    //!< Image calibration failed
						uint8_t XoscStart               : 1;                    //!< XOSC oscillator failed to start
						uint8_t PllLock                 : 1;                    //!< PLL lock failed
						uint8_t                         : 1;                    //!< Buck converter failed to start
						uint8_t PaRamp                  : 1;                    //!< PA ramp failed
						uint8_t                         : 7;                    //!< Reserved
				}Fields;
				uint16_t Value;
		}RadioError_t;

		#endif
		
		//@INFO: Bandwidth Parametreleri
		#if 1	
		
		typedef struct __attribute__((packed)){
    uint32_t bandwidth;
    uint8_t  RegValue;
		}SX126xFskBandwidth_t;
		
		#endif
		
		#if 1	//@INFO: SX1262 Main Structures	
		//@INFO: SX1262 i�in pin yapisi
		//@INFO: ...//LORAWAN_LIB_VANGO/LoRaMac-node/src/radio/sx126x/sx126x.h'e gore yazilmistir.
			
		typedef struct
		{
				uint16_t      Addr;                             //!< The address of the register
				uint8_t       Value;                            //!< The value of the register
		}RadioRegisters_t;	
		
		typedef enum
		{
				MODE_SLEEP           = 0x00,          //! The radio is in sleep mode
				MODE_STDBY_RC,                      	//! The radio is in standby mode with RC oscillator
				MODE_STDBY_XOSC,                    	//! The radio is in standby mode with XOSC oscillator
				MODE_FS,                            	//! The radio is in frequency synthesis mode
				MODE_TX,                            	//! The radio is in transmit mode
				MODE_RX,                            	//! The radio is in receive mode
				MODE_RX_DC,                         	//! The radio is in receive duty cycle mode
				MODE_CAD,                           	//! The radio is in channel activity detection mode
				MODE_DEINIT                             //@DEL  @NOTICE : normal sartlarda sx de fiziksel deinit modu yok bu soyut katmana tasinacak 
		}RadioOperatingModes_t;
		
		//@INFO: DIO3 Pinine bagli TXCO konfigurasyonu numaratoru
		typedef enum {
				TCXO_CTRL_1_6V                          = 0x00,
				TCXO_CTRL_1_7V                          = 0x01,
				TCXO_CTRL_1_8V                          = 0x02,
				TCXO_CTRL_2_2V                          = 0x03,
				TCXO_CTRL_2_4V                          = 0x04,
				TCXO_CTRL_2_7V                          = 0x05,
				TCXO_CTRL_3_0V                          = 0x06,
				TCXO_CTRL_3_3V                          = 0x07,
		}RadioTcxoCtrlVoltage_t;
		
		#define BOARD_TCXO_WAKEUP_TIME						5
				
		//@INFO: StandBy modunda kullanilan OSC tipi numarat�rleri
		typedef enum{
			STDBY_RC                                = 0x00,
			STDBY_XOSC                              ,
		}RadioStandbyModes_t;	
		
		//@INFO:  Uyku modu konfig�rasyonlarinin tutuldugu yapi
		typedef union{
				struct
				{
						uint8_t WakeUpRTC               : 1;                    //!< Get out of sleep mode if wakeup signal received from RTC
						uint8_t Reset                   : 1;
						uint8_t WarmStart               : 1;
						uint8_t Reserved                : 5;
				}Fields;
				uint8_t Value;
		}typdef_unionSleepParams_t;

		//@INFO: Temel param Struct
		typedef struct __attribute__((packed))
		{
			PacketParams_t 								PacketParams;				//@INFO: Paket Parametrelerini Tutan yapi
			PacketStatus_t 								PacketStatus;				//@INFO: Her paket icin paketin durumunu belirten yapi
			ModulationParams_t 						ModulationParams;		//@INFO: Mod�lasyon Parametrelerini Tutan yapi			
		}SX126x_t;
		
		#endif




#endif

#define		SIZE_OF_OPS		50
		
//@INFO: 	FunctionPointer Decleration Struct Definition
typedef struct __attribute__((packed)) {
/*!	*/
	err_t 					 	(*SetPacketType								  )	 ( RadioPacketTypes_t packetType 				);
/*!	*/					                                      
	RadioPacketTypes_t 			(*GetPacketType								  )	 ( void 												 				);
/*!	*/					                                      
	err_t 						(*SetTxParams									  )	 ( int8_t power							 				, 
																											 		 RadioRampTimes_t rampTime 	 					);
/*!	*/        					                              
	err_t 						(*SetModulationParams					  )	 ( ModulationParams_t *modulationParams );
/*!	*/                                      				  
	err_t 						(*SetPacketParams							  )	 ( PacketParams_t *packetParams 				);
/*!	*/                                      				  	
	err_t 						(*SetCadParams								  )	 ( RadioLoRaCadSymbols_t cadSymbolNum		, 
																										  			uint8_t cadDetPeak						 		, 
																										  			uint8_t cadDetMin						 		, 
																										  			RadioCadExitModes_t cadExitMode	 		, 
																										  			uint32_t cadTimeout 							);
/*!	*/                                      				  	
	err_t 						(*SetBufferBaseAddress				  )		( uint8_t txBaseAddress						,
																										  			uint8_t rxBaseAddress 						);
/*!	*/					                            				  
	err_t 						(*GetRxBufferStatus						  )		( uint8_t *payloadLength						, 
																										  			uint8_t *rxStartBufferPointer		);
/*!	*/					                            				  
	err_t 						(*GetPacketStatus							  )		( PacketStatus_t *pktStatus 					);
/*!	*/					                            				  
	uint32_t						(*GetBoardTcxoWakeupTime			  )		( void 																);
/*!	*/					                            				  
	err_t 						(*SetRfFrequency							  )		( uint32_t frequency 									);
/*!	*/					                            				  
	err_t  						(*SetRfTxPower								  )		( rt_int8_t power 										);
/*!	*/					                            				  
	err_t						(*SetLoRaSymbNumTimeout				  )		( uint8_t symbNum 									);
/*!	*/					                            					 			
	err_t						(*CalibrateImage							  )		( uint32_t freq 										);
/*!	*/					                            				  				
	err_t						(*SetSyncWord									  )		( uint8_t * syncWord								);
/*!	*/					                            				  				
	err_t						(*SetCrcSeed									  )		( uint16_t seed 										);
/*!	*/					                            				  				
	err_t						(*SetCrcPolynomial						  )		( uint16_t polynomial 							);
/*!	*/					                            				  				
	err_t						(*SetWhiteningSeed						  )		( uint16_t seed			 							);
/*!	*/					                            				  				
	err_t 					(*GetRandom										  )		( void 																);
/*!	*/					                            				  				
	err_t					(*GetDeviceErrors							  )		( void 																);
/*!	*/					                           					  			
	err_t 						(*ClearDeviceErrors						  )		( void																);
/*!	*/					      	                              
	err_t				(*ConvertFreqInHzToPllStep		  )		( uint32_t freqInHz 								);
/*!	*/					                                      
	err_t						(*RadioGetFskBandwidthRegValue   )		( uint32_t bandwidth 							);
/*!	*/					      	                              
	RadioStatus_t					(*GetStatus						  )		( void																);
/*!	*/					                            				  					
	uin32_t 						(*GetRssiInst					  )		( void 																);
/*!	*/					                              				 	
	void 							(*AddRegisterToRetentionList	  )		( uint16_t registerAddress 						);
/*!	*/					                              	      
	err_t						(*WorkAround									  )		( uint8_t mode											, 
																														uint8_t bandwidth 								);
/*!	*/					      				                        
	err_t						(*SetFs												  )		( void 																);
/*!	*/					                            				  				
	err_t						(*SetTx												  )		( uint32_t timeout 								);
/*!	*/					                            				  				
	err_t						(*SetRx												  )		( uint32_t timeout 								);
/*!	*/					      					                      
	err_t						(*SetRxBoosted								  )		( uint32_t timeout			 						);
/*!	*/					    					                        
	err_t 						(*SetRxDutyCycle							  )		( uint32_t rxTime									, 
																														uint32_t sleepTime 							);
/*!	*/					     			                            
	err_t 						(*SetCad											  )		( void 																);
/*!	*/					      				                        
	err_t 						(*SetTxContinuousWave					  )		( void 																);
/*!	*/					     				                          
	err_t 						(*SetTxInfinitePreamble				  )		( void 																);
/*!	*/					      
	err_t 			 		  (*SetStopRxTimerOnPreambleDetect)		( err_t enable 										);
/*!	*/					      
	err_t 						(*SetRegulatorMode							)		( RadioRegulatorMode_t mode 					);
/*!	*/					      					
	err_t 						(*SetPaConfig										)		(	RadioPaCommand_t param							);
/*!	*/					     					
	err_t 						(*SetRxTxFallbackMode						)		( uint8_t fallbackMode 						);
/*!	*/					     					
	err_t						(*SetStandby										)		( uint8_t standbyTemp 							);
/*!	*/					      					
	err_t						(*SetSleep											)		( uint8_t sleepTemp 								);
/*!	*/					      					
	err_t	 					(*SetDioIrqParams								)		( uint16_t irqMask									, 
																														uint16_t dio1Mask								, 
																														uint16_t dio2Mask								, 
																														uint16_t dio3Mask 								);
/*!	*/					   					
	err_t 				        (*GetIrqStatus									    )		( void 													);
/*!	*/					      					
	err_t						(*ClearIrqStatus								    )		( uint16_t irq 										);
/*!	*/					     					
	err_t						(*SetPayload										)		( uint8_t* payload									, 
																														size_t size										);
/*!	*/					    					
	err_t 						(*GetPayload										)		( uint8_t *buffer									, 
																														uint8_t *size										,  
																														uint8_t maxSize 									);
/*!	*/					      					
	err_t						(*SendPayload										)		( uint8_t 	*payload								, 
																														uint8_t 	size										, 
																														uint32_t timeout 								);
}typedef_sx1262_ops_st;		
		
//@INFO: 	FunctionPointer Parameter Struct Definition
typedef struct{
	//@INFO: SetPacketType	
	RadioPacketTypes_t packetType ;	
	
	//@INFO: GetPacketType	
	
	//@INFO: void
	//@INFO: SetTxParams											
	int8_t power											; 
	RadioRampTimes_t rampTime 					;	
	
	//@INFO: SetModulationParams	 					
	ModulationParams_t *modulationParams;
	
	//@INFO: SetPacketParams								
	PacketParams_t *packetParams 				;
	
	//@INFO: SetCadParams											
	RadioLoRaCadSymbols_t cadSymbolNum	;	
	uint8_t cadDetPeak						 		;	
	uint8_t cadDetMin						 		;	
	RadioCadExitModes_t cadExitMode	 		;	
	uint32_t cadTimeout 							;
	
	//@INFO: SetBufferBaseAddress				
	uint8_t txBaseAddress						;
	uint8_t rxBaseAddress 					 	;
	
	//@INFO: GetRxBufferStatus								
	uint8_t *payloadLength						; 
	uint8_t *rxStartBufferPointer		;
	
	//@INFO: GetPacketStatus								
	PacketStatus_t *pktStatus 					;	
	
	//@INFO: GetBoardTcxoWakeupTime			
	//@INFO:void 			
	
	//@INFO: SetRfFrequency							
	uint32_t frequency 									;
	
	//@INFO: SetRfTxPower								
	int8_t rfTxPower 								;
	
	//@INFO: SetLoRaSymbNumTimeout				
	uint8_t symbNum 									;
	
	//@INFO: CalibrateImage							
	uint32_t freq 										;
	
	//@INFO: SetSyncWord									
	uint8_t * syncWord								;
	
	//@INFO: SetCrcSeed									
	uint16_t seed 										;
	
	//@INFO: SetCrcPolynomial						
	uint16_t polynomial 							;
	
	//@INFO: SetWhiteningSeed						
	uint16_t whiteningSeed			 			;
	
	//@INFO: GetRandom										
	//void 													
	
	//@INFO: GetDeviceErrors							
	//void 													
	
	//@INFO: ClearDeviceErrors						
	//void													
	
	//@INFO: ConvertFreqInHzToPllStep		
	uint32_t freqInHz 								;
	
	//@INFO: RadioGetFskBandwidthRegValue
	uint32_t bandwidth 							;
	
	//@INFO: GetStatus										
	//void													
	
	//@INFO: GetRssiInst							
	//void 												
	
	//@INFO: AddRegisterToRetentionList	
	uint16_t registerAddress 						;
	
	//@INFO: WorkAround										
	uint8_t mode											; 
	uint8_t workAroundBandwidth 			;
	
	//@INFO: SetFs											
	//void 	
	
	//@INFO: SetTx												
	uint32_t timeoutTx 							;
	
	//@INFO: SetRx												
	uint32_t timeoutRx 							;
	
	
	//@INFO: SetRxBoosted								
	uint32_t timeoutRxBoosted			 	;
	
	//@INFO: SetRxDutyCycle							
	uint32_t rxTime									;
	uint32_t sleepTime 							;
	
	//@INFO: SetCad											
	//void
	
	//@INFO: SetTxContinuousWave				
	//void 									
	
	//@INFO: SetTxInfinitePreamble				
	//void 													
	
	//@INFO: SetStopRxTimerOnPreambleDete
	rt_bool_t enable 										;
	
	//@INFO: SetRegulatorMode						
	RadioRegulatorMode_t regulatorMode 	;
	
	//@INFO: SetPaConfig								
	RadioPaCommand_t param							;	
	
	//@INFO: SetRxTxFallbackMode			
	uint8_t fallbackMode 						;		
	
	//@INFO: SetStandby									
	uint8_t standbyTemp 							;	
	
	//@INFO: SetSleep										
	uint8_t sleepTemp 								;
	
	//@INFO: SetDioIrqParams						
	uint16_t irqMask									; 
	uint16_t dio1Mask								; 
	uint16_t dio2Mask								; 
	uint16_t dio3Mask 								;	
	
	//@INFO: GetIrqStatus								
	//void 													
	
	//@INFO: ClearIrqStatus							
	uint16_t irq 										;
	
	//@INFO: SetPayload									
	uint8_t* payload									;   
	size_t size											;
	
	//@INFO: GetPayload																		
	uint8_t *buffer						  		;
	uint8_t *getSize									;  
	uint8_t maxSize 										;
	
	//@INFO: SendPayload 													
	uint8_t 	*sendPayload						;	  																			
	uint8_t 	sendSize								;	  																				
	uint32_t timeout 								;
	
}typedef_sx1262_configuration;




		
#ifdef __cplusplus
}
#endif

#endif // __SX1262__DEFINITION_H__
/* */
