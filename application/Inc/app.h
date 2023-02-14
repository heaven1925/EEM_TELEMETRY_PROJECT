#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "main.h"
#include "types.h"

/*----------------------------------------------------------------------------*/
/* Miscellaneous definitions                                                  */
/*----------------------------------------------------------------------------*/


/* Process Task Name definitions */
#define	PROCESS_TELEMETRYMAIN_THREADNAME		"ProcessTelemetryMAINThread"
#define PROCESS_FLASH_THREADNAME                "ProcessFlashThread"
#define PROCESS_CAN_THREADNAME                  "ProcessCANThread"
#define PROCESS_RTC_THREADNAME                  "ProcessRTCThread"
#define PROCESS_SDCARD_THREADNAME               "ProcessSDCardThread"
#define PROCESS_WIFI_THREADNAME               	"ProcessWIFIThread"
#define PROCESS_NEXTION_THREADNAME              "ProcessNextionThread"

/* Process Semphore Name definitions */
#define PROCESS_FLASH_SEMAPHORENAME              "ProcessFlashSemaphore"
#define PROCESS_CAN_SEMAPHORENAME                "ProcessCANSemaphore"
#define PROCESS_RTC_SEMAPHORENAME                "ProcessRTCSemaphore"
#define PROCESS_SDCARD_SEMAPHORENAME             "ProcessSDCardSemaphore"
#define PROCESS_WIFI_SEMAPHORENAME               "ProcessWIFISemaphore"
#define PROCESS_NEXTION_SEMAPHORENAME            "ProcessNextionSemaphore"

/* Process SW Timer Name definitions */
#define	PROCESS_PERIODIC_SWTIMERNAME			 	"ProcessPeriodicTimer"
#define	PROCESS_TIMEOUT_SWTIMERNAME					"ProcessTimeoutTimer"

/* Software Default Timer Periods */

/* Process Task Stack Size definitions */

#define PROCESS_TELEMETRYMAIN_STACKSIZE     1024
#define PROCESS_FLASH_STACKSIZE             512
#define PROCESS_CAN_STACKSIZE               512
#define PROCESS_RTC_STACKSIZE        		256
#define PROCESS_SDCARD_STACKSIZE        	512
#define PROCESS_WIFI_STACKSIZE        		1024
#define PROCESS_NEXTION_STACKSIZE        	512

/* Process Task Stack Size Priority definitions  */

#define PROCESS_TELEMETRYMAIN_PRIORITY      0x01

#define PROCESS_CAN_PRIORITY               	0x02
#define PROCESS_FLASH_PRIORITY            	0x03
#define PROCESS_RTC_PRIORITY        	   	0x04
#define PROCESS_NEXTION_PRIORITY        	0x05
#define PROCESS_WIFI_PRIORITY        		0x06
#define PROCESS_SDCARD_PRIORITY        		0x07

/*----------------------------------------------------------------------------*/
/* Functions used outside this module                                         */
/*----------------------------------------------------------------------------*/
void            MAIN_App(void);

void            DEBUG_printThread(char *threadName,
                                  char *threadStatus);

/*----------------------------------------------------------------------------*/
/* Functions used only by this module                                         */
/*----------------------------------------------------------------------------*/
void     		Initilialise_App(void);

/* Main Thread */
#ifdef BSP_PROCESS_TELEMETRYMAIN
void     		Process_TelemetryMAIN_TaskHandler(void *params);
#endif

/* Depends Semph Release */
#ifdef BSP_PROCESS_FLASH
void     		Process_Flash_TaskHandler(void *params);
extern void     Process_Flash_Run(void);
#endif

#ifdef BSP_PROCESS_CAN
void     		Process_CAN_TaskHandler(void *params);
extern void     Process_Can_Run(void);
#endif

#ifdef BSP_PROCESS_RTC
void     		Process_RTC_TaskHandler(void *params);
extern void     Process_RTC_Run(void);
#endif

#ifdef BSP_PROCESS_SDCARD
void     		Process_SDCARD_TaskHandler(void *params);
extern void     Process_SDCARD_Run(void);
#endif

#ifdef BSP_PROCESS_WIFI
void     		Process_WIFI_TaskHandler(void *params);
extern void     Process_WIFI_Run(void);
#endif

#ifdef BSP_PROCESS_NEXTION
void     		Process_NEXTION_TaskHandler(void *params);
extern void     Process_NEXTION_Run(void);
#endif

/*----------------------------------------------------------------------------*/
/* Variables used only by this module                                         */
/*----------------------------------------------------------------------------*/

/* Structure that will hold the TCB of the task being created.                */
typedef struct {

#ifdef BSP_PROCESS_TELEMETRYMAIN
	StaticTask_t Process_TelemetryMAIN;
#endif

#ifdef BSP_PROCESS_FLASH
    StaticTask_t Process_Flash;
#endif

#ifdef BSP_PROCESS_CAN
    StaticTask_t Process_CAN;
#endif

#ifdef BSP_PROCESS_RTC
    StaticTask_t Process_RTC;
#endif

#ifdef BSP_PROCESS_SDCARD
    StaticTask_t Process_SDCARD;
#endif

#ifdef BSP_PROCESS_WIFI
    StaticTask_t Process_WIFI;
#endif

#ifdef BSP_PROCESS_NEXTION
    StaticTask_t Process_NEXTION;
#endif


}APP_StaticTask_TYPE;

typedef struct {
#ifdef BSP_PROCESS_TELEMETRYMAIN
	StackType_t Process_TelemetryMAIN	[ PROCESS_TELEMETRYMAIN_STACKSIZE ];
#endif

#ifdef BSP_PROCESS_FLASH
    StackType_t Process_Flash			[ PROCESS_FLASH_STACKSIZE];
#endif

#ifdef BSP_PROCESS_CAN
    StackType_t Process_CAN				[ PROCESS_CAN_STACKSIZE];
#endif

#ifdef BSP_PROCESS_RTC
    StackType_t Process_RTC				[ PROCESS_RTC_STACKSIZE];
#endif

#ifdef BSP_PROCESS_SDCARD
    StackType_t Process_SDCARD			[ PROCESS_SDCARD_STACKSIZE];
#endif

#ifdef BSP_PROCESS_WIFI
    StackType_t Process_WIFI			[ PROCESS_WIFI_STACKSIZE];
#endif

#ifdef BSP_PROCESS_NEXTION
    StackType_t Process_NEXTION			[ PROCESS_NEXTION_STACKSIZE];
#endif


}APP_StackType_TYPE;


typedef struct {
#ifdef BSP_PROCESS_TELEMETRYMAIN
	TaskHandle_t Process_TelemetryMAIN;
#endif

#ifdef BSP_PROCESS_FLASH
    TaskHandle_t Process_Flash;
#endif

#ifdef BSP_PROCESS_CAN
    TaskHandle_t Process_CAN;
#endif

#ifdef BSP_PROCESS_RTC
    TaskHandle_t Process_RTC;
#endif

#ifdef BSP_PROCESS_SDCARD
    TaskHandle_t Process_SDCARD;
#endif

#ifdef BSP_PROCESS_WIFI
    TaskHandle_t Process_WIFI;
#endif

#ifdef BSP_PROCESS_NEXTION
    TaskHandle_t Process_NEXTION;
#endif

}APP_TaskHandle_TYPE;


/* Semaphore definitions							 */
typedef struct {
#ifdef BSP_PROCESS_FLASH
	StaticSemaphore_t Process_Flash;
#endif

#ifdef BSP_PROCESS_CAN
	StaticSemaphore_t Process_CAN;
#endif

#ifdef BSP_PROCESS_RTC
    StaticSemaphore_t Process_RTC;
#endif

#ifdef BSP_PROCESS_SDCARD
    StaticSemaphore_t Process_SDCARD;
#endif

#ifdef BSP_PROCESS_WIFI
    StaticSemaphore_t Process_WIFI;
#endif

#ifdef BSP_PROCESS_NEXTION
    StaticSemaphore_t Process_NEXTION;
#endif
}APP_StaticSemaphore_TYPE;

typedef struct { /* Same as QueueHandle_t */
#ifdef BSP_PROCESS_FLASH
	QueueHandle_t Process_Flash;
#endif

#ifdef BSP_PROCESS_CAN
	QueueHandle_t Process_CAN;
#endif

#ifdef BSP_PROCESS_RTC
	QueueHandle_t Process_RTC;
#endif

#ifdef BSP_PROCESS_SDCARD
	QueueHandle_t Process_SDCARD;
#endif

#ifdef BSP_PROCESS_WIFI
	QueueHandle_t Process_WIFI;
#endif

#ifdef BSP_PROCESS_NEXTION
	QueueHandle_t Process_NEXTION;
#endif

}APP_SemaphoreHandle_TYPE;

typedef struct {
#ifdef BSP_PROCESS_FLASH
    BaseType_t Process_Flash;
#endif

#ifdef BSP_PROCESS_CAN
	BaseType_t Process_CAN;
#endif

#ifdef BSP_PROCESS_RTC
	BaseType_t Process_RTC;
#endif

#ifdef BSP_PROCESS_SDCARD
	BaseType_t Process_SDCARD;
#endif

#ifdef BSP_PROCESS_WIFI
	BaseType_t Process_WIFI;
#endif

#ifdef BSP_PROCESS_NEXTION
	BaseType_t Process_NEXTION;
#endif
}APP_SemaphoreResult_TYPE;

/* Timer Structures */

typedef struct
{
	StaticTimer_t	periodic;
	/**************************/
	StaticTimer_t 	timeout;

}APP_StaticTimer_TYPE;

/* Timer Handle */

typedef struct
{
	osTimerId_t	periodic;
	/**************************/
	osTimerId_t timeout;

}APP_TimerID_TYPE;

/* Timer Default */

typedef struct
{
	osStaticTimerDef_t	periodic;
	/**************************/
	osStaticTimerDef_t	timeout;
}APP_StaticTimerDef_TYPE;


#endif /* APPLICATION_H_ */




