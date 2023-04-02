#ifndef	_SYS_RFADAPTOR__DEFINITION_H__
#define _SYS_RFADAPTOR__DEFINITION_H__

#include "sys_global__top.h"
#include "sx1262__definition.h"

#include <board.h>
#include <rtthread.h>



#define	  RFADAPTOR_ON
#define		SX1262_EN
//#define		WMBUS_EN
//#define		PCMODE_EN

#define		RFADAPTOR_VCC					SX1262_VCC_ENB
#define		RFADAPTOR_RESET				SX1262_NRST
#define		RFADAPTOR_BUSY				SX1262_BUSY

#define		RFADAPTOR_BUSY_PORT		'A'
#define		RFADAPTOR_BUSY_PIN		 8

#define		RFADAPTOR_MOSI				SX1262_MOSI
#define		RFADAPTOR_MISO				SX1262_MISO
#define		RFADAPTOR_SCLK				SX1262_CLK
#define		RFADAPTOR_NSS					SX1262_SSN

#define		RFADAPTOR_DIO					SX1262_IRQ

#define RFADAPTOR_VCC_ON				{ rt_pin_write( RFADAPTOR_VCC, PIN_LOW 	);  }
#define RFADAPTOR_VCC_OFF				{ rt_pin_write( RFADAPTOR_VCC, PIN_HIGH );  }

#define RFADAPTOR_RST_HIGH			{ rt_pin_write( RFADAPTOR_RESET, PIN_HIGH );  }	
#define RFADAPTOR_RST_LOW				{ rt_pin_write( RFADAPTOR_RESET, PIN_LOW );  }

#define RFADAPTOR_CS_ON					{ rt_pin_write( RFADAPTOR_NSS, PIN_LOW 	);  }
#define RFADAPTOR_CS_OFF				{ rt_pin_write( RFADAPTOR_NSS, PIN_HIGH );  }

#define		RFADAPTOR_CS					RFADAPTOR_NSS

#define 	RFADAPTOR_DEVNAME						"spiRFAdaptor"				
#define 	RFADAPTOR_CONFIG_DEFAULT           		\
{                                      				 	\
    RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB, \
		8,																					\
		0,                                   				\
		8e6																					\
}

//@INFO: Temel komutlarin byte genislikleri
#define		SIZE_OF_OPCODE																1
#define		SIZE_OF_READCMD																2
#define		SIZE_OF_WRITEREG_CMD													3
#define		SIZE_OF_READREG_CMD														4
#define		SIZE_OF_WRITEBUF_CMD													2
#define		SIZE_OF_READBUF_CMD														3
//@INFO: Temel komutlarin parametre indeksleri
#define		INDEX_OF_OPCODE																0
#define		INDEX_OF_16BITREG_MSB													1
#define		INDEX_OF_16BITREG_LSB													2
#define		INDEX_OF_BUFFEROFFSET													1
//@INFO: Temel Read komutlarinin NOP indeksleri
#define		INDEX_OF_READCMD_NOP													1
#define		INDEX_OF_READREG_NOP													3
#define		INDEX_OF_READBUF_NOP													2


//@INFO: RFADAPTOR GENERAL FLAGS :16bit 
#define		SYS_RFADAPTOR_DIO0_IRQ												0x0001		
#define		SYS_RFADAPTOR_HWTIM								 						0x0002    
#define		SYS_RFADAPTOR_BLOCKLORA				 								0x0004    
#define		SYS_RFADAPTOR_BLOCKWMBUS		  								0x0008    
#define		SYS_RFADAPTOR_DUMMY13													0x0010    
#define		SYS_RFADAPTOR_DUMMY14			 										0x0020		
#define		SYS_RFADAPTOR_DUMMY0	 												0x0040    
#define		SYS_RFADAPTOR_DUMMY1				 									0x0080    
#define		SYS_RFADAPTOR_DUMMY2				 									0x0100    
#define		SYS_RFADAPTOR_DUMMY3													0x0200    
#define		SYS_RFADAPTOR_DUMMY4													0x0400    
#define		SYS_RFADAPTOR_DUMMY5													0x0800    
#define		SYS_RFADAPTOR_DUMMY6		 											0x1000    
#define		SYS_RFADAPTOR_DUMMY7													0x2000    
#define		SYS_RFADAPTOR_DUMMY8				 									0x4000    
#define		SYS_RFADAPTOR_DUMMY9				 									0x8000    

#define 	SYS_RFADAPTOR_PARAM(value)			      (( sys_rfAdaptor_generalflags.main & 	 value ) == value )
#define 	SYS_RFADAPTOR_PARAM_SET(value)	       ( sys_rfAdaptor_generalflags.main |=  value )
#define 	SYS_RFADAPTOR_PARAM_RESET(value)       ( sys_rfAdaptor_generalflags.main &=~ value )

#define		NOP_MSG																				0x00
#define		RT_NONE																				0xFF

typedef union 
{	
	uint8_t main;
	struct
	{
		uint8_t 	pc 		: 1 ;
		uint8_t  lora	: 1 ;
		uint8_t	wmbus : 1 ;
		uint8_t  dummy : 5 ;
		
	}Bits;
}sys_rfAdaptor_RFSTATUS_st;

extern sys_rfAdaptor_RFSTATUS_st sys_rfAdaptor_RFSTATUS;


typedef union
{
	uint16_t main;
	struct
	{
		bool_t	dio0_IRQ  : 1 ;
		bool_t HW_TIM	  : 1 ;
		bool_t blockLora : 1 ;
		bool_t blockRF   : 1 ;
		//@INFO: RFU 
		uint16_t dummy:14;
	}Bits;	
}sys_rfAdaptor_generalflags_ut;

//@INFO  RX-TX Frequencies
#define		SYS_RFADAPTOR_BT2MODE_TX_FREQUENCY 										868950000
#define		SYS_RFADAPTOR_BT2MODE_RX_FREQUENCY 										868210000
#define		SYS_RFADAPTOR_BT2MODE_TEST_FREQ												868200000
//@NEW: develop //@INFO: PC Mode Frequencies
#define 	SYS_RFADAPTOR_RF_CHANNEL_FREQ      										868030000                                   
#define 	SYS_RFADAPTOR_RF_VANA_FREQ														868210000
#define 	SYS_RFADAPTOR_RF_BOOT_FREQ														866500000
#define 	SYS_RFADAPTOR_RF_LOG_FREQ															863200000

//@INFO: Modulation Params
#define 	SYS_RFADAPTOR_BT2MODE_FDEV                            50e3  			//25e3      // Hz 
#define 	SYS_RFADAPTOR_BT2MODE_DATARATE                        100e3 			//50e3      // bps
#define 	SYS_RFADAPTOR_BT2MODE_BANDWIDTH                       100e3       // Hz >> DSB in sx126x

//@INFO: Packet Params
#define 	SYS_RFADAPTOR_BT2MODE_PREAMBLE_LENGTH                 5         	// Same for Tx and Rx
//@INFO: RX-TX Syncword Length
#define		SYS_RFADAPTOR_BT2MODE_SYNCWORD_LENGTH_TX							2
#define		SYS_RFADAPTOR_BT2MODE_SYNCWORD_LENGTH_RX							2
//@INFO: RX-TX Payload Length
#define   SYS_RFADAPTOR_8BYTE_MODE_PAYLOAD_LENGTH_TX             8
#define 	SYS_RFADAPTOR_BT2MODE_PAYLOAD_LENGTH_TX               64
#define 	SYS_RFADAPTOR_BT2MODE_PAYLOAD_LENGTH_RX               16
#define		SYS_RFADAPTOR_BT2MODE_MAXPAYLOAD_LENGTH_RX						255

#define	 	SYS_RFADAPTOR_TX_OUTPUT_POWER                         17		       // dBm

//@NEW: develop
enum{
	RF_SETTINGS_PC = 0x00,
	RF_SETTINGS_LORA,
	RF_SETTINGS_WMBUS,
};

//@INFO: wmBUS RX-TX
enum{
	RF_WMBUS_NULL = 0x00,
	RF_WMBUS_MODE_TX	 			 ,
	RF_WMBUS_MODE_RX				 ,
};

enum{
	RF_WMBUS_MODE_NULL 	= 0x00,		//@INFO: RT_NULL ile ayni oldugundan tanimlanmistir.
	RF_WMBUS_MODE_PC					,
	RF_WMBUS_MODE_BT2MODE			,
	RF_WMBUS_MODE_BS2MODE			,
	RF_WMBUS_MODE_BT2LITEMODE	,
	RF_WMBUS_MODE_RECEIVE			,
};




//@INFO: Kullanilan Tüm Radio Komutlarina ait OPCODE'lari içermektedir.
typedef enum {
	
		RADIO_GET_STATUS                        = 0xC0,
		RADIO_WRITE_REGISTER                    = 0x0D,
		RADIO_READ_REGISTER                     = 0x1D,
		RADIO_WRITE_BUFFER                      = 0x0E,
		RADIO_READ_BUFFER                       = 0x1E,
		RADIO_SET_SLEEP                         = 0x84,
		RADIO_SET_STANDBY                       = 0x80,
		RADIO_SET_FS                            = 0xC1,
		RADIO_SET_TX                            = 0x83,
		RADIO_SET_RX                            = 0x82,
		RADIO_SET_RXDUTYCYCLE                   = 0x94,
		RADIO_SET_CAD                           = 0xC5,
		RADIO_SET_TXCONTINUOUSWAVE              = 0xD1,
		RADIO_SET_TXCONTINUOUSPREAMBLE          = 0xD2,
		RADIO_SET_PACKETTYPE                    = 0x8A,
		RADIO_GET_PACKETTYPE                    = 0x11,
		RADIO_SET_RFFREQUENCY                   = 0x86,
		RADIO_SET_TXPARAMS                      = 0x8E,
		RADIO_SET_PACONFIG                      = 0x95,
		RADIO_SET_CADPARAMS                     = 0x88,
		RADIO_SET_BUFFERBASEADDRESS             = 0x8F,
		RADIO_SET_MODULATIONPARAMS              = 0x8B,
		RADIO_SET_PACKETPARAMS                  = 0x8C,
		RADIO_GET_RXBUFFERSTATUS                = 0x13,
		RADIO_GET_PACKETSTATUS                  = 0x14,
		RADIO_GET_RSSIINST                      = 0x15,
		RADIO_GET_STATS                         = 0x10,
		RADIO_RESET_STATS                       = 0x00,
		RADIO_CFG_DIOIRQ                        = 0x08,
		RADIO_GET_IRQSTATUS                     = 0x12,
		RADIO_CLR_IRQSTATUS                     = 0x02,
		RADIO_CALIBRATE                         = 0x89,
		RADIO_CALIBRATEIMAGE                    = 0x98,
		RADIO_SET_REGULATORMODE                 = 0x96,
		RADIO_GET_ERROR                         = 0x17,
		RADIO_CLR_ERROR                         = 0x07,
		RADIO_SET_TCXOMODE                      = 0x97,
		RADIO_SET_TXFALLBACKMODE                = 0x93,
		RADIO_SET_RFSWITCHMODE                  = 0x9D,
		RADIO_SET_STOPRXTIMERONPREAMBLE         = 0x9F,
		RADIO_SET_LORASYMBTIMEOUT               = 0xA0,
}RadioCommands_t;



//@INFO :RF modulunun mevcut STATUS durumunu gostermek icin kullanilmistir
#define	sys_rfAdaptor_PC					0x01 //@INFO :BIT0
#define	sys_rfAdaptor_LORA				0x02 //@INFO :BIT1
#define	sys_rfAdaptor_WMBUS				0x04 //@INFO :BIT2
#define	sys_rfAdaptor_DUMMY1			0x08 //@INFO :BIT3
#define	sys_rfAdaptor_DUMMY2			0x10 //@INFO :BIT4
#define	sys_rfAdaptor_DUMMY3			0x20 //@INFO :BIT5
#define	sys_rfAdaptor_DUMMY4			0x40 //@INFO :BIT6
#define	sys_rfAdaptor_DUMMY5			0x80 //@INFO :BIT7

#define SYS_RF_STATUS_PARAM(value)				(( sys_rfAdaptor_RFSTATUS.main & value )== value )
#define SYS_RF_STATUS_PARAM_RUN(value)		( sys_rfAdaptor_RFSTATUS.main |= value )
#define SYS_RF_STATUS_PARAM_FINISH(value)	( sys_rfAdaptor_RFSTATUS.main &=~ value )
#define SYS_RF_STATUS_PARAM_STOPALL				( sys_rfAdaptor_RFSTATUS.main = 0 )


#ifdef SX1262_EN
//@NEW a.ertekin @INFO: GFSK packetparam, statusparam & modulation param structures
// @NOTICE: rfAdaptor katmaninda ayarlamalar yapilirken bu degiskenler uzerinden yapilacaktir !
// @NOTICE: Yapilan bu ayarlamalar global olarak SX1262 kütüphanesindeki SX1262_t 'tipine adres üzerinden 

typedef struct __attribute__((packed))	{
	err_t			(*wmBus_irqHandler)							(	uint16_t irqStatus	);
	err_t			(*txDone_irqHandler)						(	void									);
	err_t			(*rxDone_irqHandler)						(	void									);
	err_t			(*timeOut_irqHandler)						(	void									);
	err_t			(*preambleDetected_irqHandler)	(	void									);
	err_t			(*syncWordValid_irqHandler)			(	void									);
	err_t			(*crcError_irqHandler)					(	void									);
}typdef_rfAdaptor_irqHandlers;


//@INFO: 	Sx1262 Driver Struct Definition
typedef struct{
	SX126x_t								  drvObj	;	
	typedef_sx1262_ops_st 		ops			;
}typedef_rfAdaptor_device_st;



#endif

#endif //end _SYS_RFADAPTOR__DEFINITION_H__

