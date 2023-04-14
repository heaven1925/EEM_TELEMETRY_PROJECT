/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    TelemetryMAIN_definition.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __TELEMETRY_MAIN_DEFINITION_H__
#define	__TELEMETRY_MAIN_DEFINITION_H__

#include "stdbool.h"
#include "stdint.h"

typedef bool tlm_bool_t;
	
/*********************** INCLUDES **********************************************/




/*********************** DEFINES ***********************************************/

/*
 * Protocol Error type
 */
typedef enum
{
	TLM_EOK = 0,
	TLM_ERR = !TLM_EOK
}tlm_err_t;


/*
 * Rf Header Decleration
 */
typedef struct __attribute__((__packed__))
{
	uint16_t 	version;	/* 2 */
	uint8_t 	dataLenght; /* 1 */
	uint8_t 	data_ID;	/* 1 */

}header_st;

/*
 * Rf Application rx data payload decleration
 */
typedef struct __attribute__((__packed__))
{

	uint64_t speedVal;			/* 4 Byte */
	uint16_t battery_temp;		/* 2 Byte */
	uint16_t battery_voltage;	/* 2 Byte */
	uint16_t battery_current;	/* 2 Byte */

	uint16_t leftWheel_angle;   		/* 2 Byte */
	uint16_t rightWheel_angle;   		/* 2 Byte */

	union __attribute__((__packed__)) { /* 4 Byte */
		uint32_t main;
		struct
		{
		tlm_bool_t rf               :1;
		tlm_bool_t wifi             :1;
		tlm_bool_t left_signal      :1;
		tlm_bool_t right_signal     :1;
		tlm_bool_t head_light       :1;
		tlm_bool_t wipers           :1;
		tlm_bool_t wheel_angle_l    :1;
		tlm_bool_t wheel_angle_r    :1;
		tlm_bool_t up_hıll          :1;
		tlm_bool_t down_hıll        :1;
		tlm_bool_t straight         :1;
		tlm_bool_t spark            :1;
		tlm_bool_t hand_breaker     :1;
		tlm_bool_t flasher          :1;
		tlm_bool_t rain             :1;
		tlm_bool_t engine_heat      :1;
		uint16_t dummy :16;
		}flags;
	}icons;

	uint8_t seconds;	/* 1 */
	uint8_t minutes;	/* 1 */
	uint8_t hour;		/* 1 */
	uint8_t dayofweek;	/* 1 */
	uint8_t dayofmonth;	/* 1 */
	uint8_t month;		/* 1 */
	uint8_t year;		/* 1 */

}payloadRx_st;

/*
 * Rf Application tx data payload decleration
 */
typedef struct __attribute__((__packed__))
{
	uint8_t seconds;	/* 1 */
	uint8_t minutes;	/* 1 */
	uint8_t hour;		/* 1 */
	uint8_t dayofweek;	/* 1 */
	uint8_t dayofmonth;	/* 1 */
	uint8_t month;		/* 1 */
	uint8_t year;		/* 1 */

}payloadTx_st;

/*
 * Rf Application tx broadcast mode enumator
 */
typedef enum
{
	COMMON_BROADCAST = 0 	,
	CALIBRATION_BROADCAST 	,
	CONTROL_BROADCAST	  	,
	CLEARERROR_BROADCAST	,
	TEST_BROADCAST
}broadcastMode_Type;

/*
 * Rf Application CRC Process
 */
typedef union __attribute__((__packed__))
{
	uint32_t main;	/* 4 */
	struct{
		uint8_t	 lsb :8;
		uint8_t	 msb :8;
		uint16_t sum :16;
	}frame;
}crc_st;

/*
 * Rf Packed decleration
 */

typedef struct __attribute__((__packed__))
{
	header_st 		header;		/* 4  */
	payloadRx_st 	rxHandle;   /* 25 */
	payloadTx_st	txHandle;	/* 7 */
	crc_st 			crc;		/* 4 */
}EEM_RFProtocol_st; /* 40 Byte */


/*********************** STATE SELECTION ***************************************/
typedef enum
{
	TelemetryMain_MAIN_State_IDLE = 0,
	TelemetryMain_MAIN_State_ROUTINE ,
	TelemetryMain_MAIN_State_PROCESS ,
	TelemetryMain_MAIN_State_SUSPEND ,
	
}TelemetryMain_MAIN_State_et;





#endif /*__TELEMETRY_MAIN_DEFINITION_H__ */	

/*********************** END OF FILE ********************************************/
















































