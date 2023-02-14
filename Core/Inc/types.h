/*******************************************************************************
  * @file    types.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil Main variables & types
********************************************************************************/

#ifndef INC_TYPES_H_
#define INC_TYPES_H_

#include <stdbool.h>
#include <ctype.h>
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

#include "main.h"

#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

#define BIT_SET(addr, shift) 	(addr | (1 << shift))
#define BIT_RESET(addr, shift) 	(addr & ~(1 << shift))
#define BIT_GET(addr, shift) 	(addr & (1 << shift))

//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

#define DEBUG_MSG_SIZE  6

#define is_not                          !=
#define is                              ==
#define and                             &&
#define or                              ||

typedef     uint8_t        U8;
typedef     int8_t         S8;
typedef     uint16_t       U16;
typedef     int16_t        S16;
typedef     uint32_t       U32;
typedef     int32_t        S32;

typedef		U32			  DUMMY;  /* Used only dummy union-struct */

typedef enum {
	FALSE  = 0x0,
	TRUE   = !FALSE
}BOOL;

typedef union
{
	U32 U32;
    struct
    {
		U8 byte0;
		U8 byte1 ;
		U8 byte2 ;
		U8 byte3 ;
    } Byte;
}U32Union;

//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define	ITC_UT_BYTE_SIZE			1
typedef union{
	U8	itcFlags;
	struct{
		BOOL flash 		: 1 ;
		BOOL can 		: 1 ;
		BOOL rtc 		: 1 ;
		BOOL sdcard 	: 1 ;
		BOOL wifi 		: 1 ;
		BOOL nextion 	: 1 ;
		U8:2; /* dummy RFU */
	}__packed flag;
}__packed itc_ut;

// [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

#define		MAIN_PACKEDSIZE			0x200
typedef struct{
	U8 dummy[MAIN_PACKEDSIZE];		//@INFO: 512 Byte
}main_st;

#define		FLASH_PACKEDSIZE		0x100
typedef struct{
	U8 dummy[FLASH_PACKEDSIZE];		//@INFO: 256 Byte
}flash_st;

#define		CAN_PACKEDSIZE			0x100
typedef struct{
	U8 dummy[CAN_PACKEDSIZE];		//@INFO: 256 Byte
}can_st;

#define		RTC_PACKEDSIZE			0x100
typedef struct{
	U8 dummy[RTC_PACKEDSIZE];		//@INFO: 256 Byte
}rtc_st;

#define		SDCARD_PACKEDSIZE		0x200
typedef struct{
	U8 dummy[SDCARD_PACKEDSIZE];	//@INFO: 512 Byte
}sdcard_st;

#define		WIFI_PACKEDSIZE			0x200
typedef struct{
	U8 dummy[WIFI_PACKEDSIZE];		//@INFO: 512 Byte
}wifi_st;

#define		NEXTION_PACKEDSIZE		0x200
typedef struct{
	U8 dummy[NEXTION_PACKEDSIZE];	//@INFO: 512 Byte
}nextion_st;


#define		GLSTRUCT_PACKEDSIZE		0x1000				- \
/* 512 Byte */						MAIN_PACKEDSIZE     - \
/* 256 Byte */						FLASH_PACKEDSIZE    - \
/* 256 Byte */						CAN_PACKEDSIZE      - \
/* 256 Byte */						RTC_PACKEDSIZE      - \
/* 512 Byte */						SDCARD_PACKEDSIZE   - \
/* 512 Byte */						WIFI_PACKEDSIZE     - \
/* 512 Byte */						NEXTION_PACKEDSIZE  /* ---> 2816 Byte until here */	 - \
/* itc_ut itc  : 1 Byte */			ITC_UT_BYTE_SIZE

typedef struct
{
	main_st 	main;
	flash_st 	flash;
	can_st		can;
	rtc_st		rtc;
	sdcard_st	sdcard;
	wifi_st		wifi;
	nextion_st	nextion;
	/* Global Variable Definitions */
	itc_ut itc;

	U8 dummy[ GLSTRUCT_PACKEDSIZE ]; //@INFO: Total 4Kbyte - Others
}GL_st;
// ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

extern GL_st __GL;	//@INFO: attribute assigned at application.c


#endif /* INC_TYPES_H_ */
