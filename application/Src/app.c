
/*******************************************************************************
  * @file    app.c
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil SCB Telemetry MAIN Code
********************************************************************************/

/* Main application header definition*/
#include "app.h"

GL_st __attribute__((section(".ARM.__at_0x20000000"))) __GL   = {0}; //@INFO: 4 Kbyte


#include "TelemetryMAIN_public.h"

#include "ModuleFlash_public.h"
#include "ModuleCAN_public.h"
#include "ModuleRTC_public.h"
#include "ModuleSDCard_public.h"
#include "ModuleWIFI_public.h"
#include "ModuleNEXTION_public.h"

APP_StaticTask_TYPE 			xTaskBuffer		;
APP_StackType_TYPE 				xStack			;
APP_TaskHandle_TYPE 			xHandle			;
APP_StaticSemaphore_TYPE 		xSemaphore		;
APP_SemaphoreHandle_TYPE 		xSemHandle		;
APP_SemaphoreResult_TYPE 		xSemResult		;
APP_StaticTimer_TYPE 			xStaticTimer	;
APP_TimerID_TYPE				xTimerID		;
APP_StaticTimerDef_TYPE			xStaticTimerDef	;

const osTimerAttr_t APP_periodic_attributes =
{
  .name = PROCESS_PERIODIC_SWTIMERNAME					,
  .cb_mem = &xStaticTimerDef.periodic					,
  .cb_size = sizeof(xStaticTimerDef.periodic)			,
};

const osTimerAttr_t APP_timeout_attributes =
{
  .name = PROCESS_TIMEOUT_SWTIMERNAME					,
  .cb_mem = &xStaticTimerDef.timeout					,
  .cb_size = sizeof(xStaticTimerDef.timeout)			,
};

/********************************************************************************/

#if 1 /* Software Timer IRQ Handlers */

void APP_timeoutTimerIRQHandler(void* param)
{

}

void APP_periodicTimerIRQHandler(void* param)
{

}

#endif


void Initilialise_App(void)
{
	/***************** Create Static Threads ******************************/

	/* Create Static TelemetryMAIN Thread */
#ifdef BSP_PROCESS_TELEMETRYMAIN

	xHandle.Process_TelemetryMAIN = xTaskCreateStatic
									(
									Process_TelemetryMAIN_TaskHandler,
									PROCESS_TELEMETRYMAIN_THREADNAME,
									PROCESS_TELEMETRYMAIN_STACKSIZE,
									(void *)1,
									PROCESS_TELEMETRYMAIN_PRIORITY,
									xStack.Process_TelemetryMAIN,
									&xTaskBuffer.Process_TelemetryMAIN
									);
#endif


#ifdef BSP_PROCESS_FLASH
	/* Create Static Flash Task	*/
    xHandle.Process_Flash = xTaskCreateStatic(
            Process_Flash_TaskHandler,
            PROCESS_FLASH_THREADNAME,
            PROCESS_FLASH_STACKSIZE,
            (void *)1,
            PROCESS_FLASH_PRIORITY,
            xStack.Process_Flash,
            &xTaskBuffer.Process_Flash);
#endif


#ifdef BSP_PROCESS_CAN
    /* Create Static can Task	*/
    xHandle.Process_CAN = xTaskCreateStatic(
            Process_CAN_TaskHandler,
            PROCESS_CAN_THREADNAME,
            PROCESS_CAN_STACKSIZE,
            (void *)1,
            PROCESS_CAN_PRIORITY,
            xStack.Process_CAN,
            &xTaskBuffer.Process_CAN);

#endif


#ifdef BSP_PROCESS_RTC
    /* Create Static RTC Task	*/
    xHandle.Process_RTC = xTaskCreateStatic(
    		Process_RTC_TaskHandler,
			PROCESS_RTC_THREADNAME,
			PROCESS_RTC_STACKSIZE,
            (void *)1,
            PROCESS_RTC_PRIORITY,
            xStack.Process_RTC,
            &xTaskBuffer.Process_RTC);

#endif

#ifdef BSP_PROCESS_SDCARD
    /* Create Static sdcard Task	*/
    xHandle.Process_SDCARD = xTaskCreateStatic(
    		Process_SDCARD_TaskHandler,
			PROCESS_SDCARD_THREADNAME,
			PROCESS_SDCARD_STACKSIZE,
            (void *)1,
            PROCESS_SDCARD_PRIORITY,
            xStack.Process_SDCARD,
            &xTaskBuffer.Process_SDCARD);

#endif

#ifdef BSP_PROCESS_WIFI
    /* Create Static wifi Task	*/
    xHandle.Process_WIFI = xTaskCreateStatic(
    		Process_WIFI_TaskHandler,
			PROCESS_WIFI_THREADNAME,
			PROCESS_WIFI_STACKSIZE,
            (void *)1,
            PROCESS_WIFI_PRIORITY,
            xStack.Process_WIFI,
            &xTaskBuffer.Process_WIFI);

#endif

#ifdef BSP_PROCESS_NEXTION
    /* Create Static nextion Task	*/
    xHandle.Process_NEXTION = xTaskCreateStatic(
    		Process_NEXTION_TaskHandler,
			PROCESS_NEXTION_THREADNAME,
			PROCESS_NEXTION_STACKSIZE,
            (void *)1,
            PROCESS_NEXTION_PRIORITY,
            xStack.Process_NEXTION,
            &xTaskBuffer.Process_NEXTION);

#endif

/********************* Binary Semaphore Create **********************/

#ifdef BSP_PROCESS_FLASH
	/* Create Static Flash Semaphore	*/
	xSemHandle.Process_Flash 	 = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_Flash		);
#endif


#ifdef BSP_PROCESS_CAN
    /* Create Static can Semaphore	*/
	xSemHandle.Process_CAN 		  = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_CAN		);
#endif


#ifdef BSP_PROCESS_RTC
    /* Create Static RTC Semaphore	*/
	xSemHandle.Process_RTC 		  = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_RTC		);
#endif

#ifdef BSP_PROCESS_SDCARD
    /* Create Static sdcard Semaphore	*/
	xSemHandle.Process_SDCARD 	  = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_SDCARD		);
#endif

#ifdef BSP_PROCESS_WIFI
    /* Create Static wifi Semaphore	*/
	xSemHandle.Process_WIFI 	  = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_WIFI		);
#endif

#ifdef BSP_PROCESS_NEXTION
    /* Create Static nextion Semaphore	*/
	xSemHandle.Process_NEXTION 	  = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_NEXTION	);
#endif

	/************************ Create  Software Timers ***********************************/

    xTimerID.periodic = 	osTimerNew( APP_periodicTimerIRQHandler			,
    									osTimerPeriodic						,
										NULL								,
										&APP_periodic_attributes			);

    xTimerID.timeout  = 	osTimerNew( APP_timeoutTimerIRQHandler			,
    									osTimerOnce							,
										NULL								,
										&APP_timeout_attributes				);

#ifdef DEBUG_MODE
    HAL_UART_Receive_DMA(&huart1, (U8 *)&__GL.DEBUG_Buffer[0], (U8)DEBUG_MSG_SIZE);
#endif

}




/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void MAIN_App(void)
{
	/* Create Threads, Semph, SW Timers */
    Initilialise_App();
    /* Start Scheduler */
    vTaskStartScheduler();

}








#if 1 /* Thread Definitions */
/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void Process_TelemetryMAIN_TaskHandler(void* param)
{

	TelemetryMain_StartUP();

	while(1)
	{

		//HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_TELEMETRYMAIN_THREADNAME, "STARTED");
#endif
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

        TelemetyMain_MAIN(); /* Main Application */

		vTaskDelay(10);  /* Main Thread Checkout every 10ms tick */

        // ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_TELEMETRYMAIN_THREADNAME, "ENDED");
#endif
        //HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
	}

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void Process_Flash_TaskHandler(void* param)
{

	ModuleFlash_StartUP();

	/* Semaphore Wait */
	xSemResult.Process_Flash = xQueueSemaphoreTake(xSemHandle.Process_Flash, osWaitForever);
	if (pdTRUE == xSemResult.Process_Flash)
	{

		while(1)
		{

		//HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_FLASH_THREADNAME, "STARTED");
#endif
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

        ModuleFlash_MAIN(); /* Main Application */

        // ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_FLASH_THREADNAME, "ENDED");
#endif
        //HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
		}

	}
	else
	{
		/* Semaphore fail / Create Again                                                             */
		xSemHandle.Process_Flash = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_Flash);
	}


}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void Process_CAN_TaskHandler(void* param)
{
	ModuleCAN_StartUP();

	/* Semaphore Wait */
	xSemResult.Process_CAN = xQueueSemaphoreTake(xSemHandle.Process_CAN, osWaitForever);
	if (pdTRUE == xSemResult.Process_CAN)
	{

		while(1)
		{

		//HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_CAN_THREADNAME, "STARTED");
#endif
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

        ModuleCAN_MAIN(); /* Main Application */

        // ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_CAN_THREADNAME, "ENDED");
#endif
        //HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
		}

	}
	else
	{
		/* Semaphore fail / Create Again                                                             */
		xSemHandle.Process_CAN = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_CAN);
	}
}


/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void Process_RTC_TaskHandler(void* param)
{
	ModuleRTC_StartUP();

	/* Semaphore Wait */
	xSemResult.Process_RTC = xQueueSemaphoreTake(xSemHandle.Process_RTC, osWaitForever);
	if (pdTRUE == xSemResult.Process_RTC)
	{

		while(1)
		{

		//HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_RTC_THREADNAME, "STARTED");
#endif
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

        ModuleRTC_MAIN(); /* Main Application */

        // ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_RTC_THREADNAME, "ENDED");
#endif
        //HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
		}

	}
	else
	{
		/* Semaphore fail / Create Again  */
		xSemHandle.Process_RTC = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_RTC);
	}

}


/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void Process_SDCARD_TaskHandler(void* param)
{
	ModuleSDCard_StartUP();

	/* Semaphore Wait */
	xSemResult.Process_SDCARD = xQueueSemaphoreTake(xSemHandle.Process_SDCARD, osWaitForever);
	if (pdTRUE == xSemResult.Process_SDCARD)
	{
		while(1)
		{

		//HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_SDCARD_THREADNAME, "STARTED");
#endif
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

        ModuleSDCard_MAIN(); /* Main Application */

        // ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_SDCARD_THREADNAME, "ENDED");
#endif
        //HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
		}

	}
	else
	{
		/* Semaphore fail / Create Again  */
		xSemHandle.Process_SDCARD = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_SDCARD);
	}
}


/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void Process_WIFI_TaskHandler(void* param)
{
	ModuleWIFI_StartUP();

	/* Semaphore Wait */
	xSemResult.Process_WIFI = xQueueSemaphoreTake(xSemHandle.Process_WIFI, osWaitForever);
	if (pdTRUE == xSemResult.Process_WIFI)
	{

		while(1)
		{

		//HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_WIFI_THREADNAME, "STARTED");
#endif
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

        ModuleWIFI_MAIN(); /* Main Application */

        // ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_WIFI_THREADNAME, "ENDED");
#endif
        //HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
		}

	}
	else
	{
		/* Semaphore fail / Create Again  */
		xSemHandle.Process_WIFI = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_WIFI);
	}

}


/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void Process_NEXTION_TaskHandler(void* param)
{
	ModuleNEXTION_StartUP();

	/* Semaphore Wait */
	xSemResult.Process_NEXTION = xQueueSemaphoreTake(xSemHandle.Process_NEXTION, osWaitForever);
	if (pdTRUE == xSemResult.Process_NEXTION)
	{

		while(1)
		{

		//HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_NEXTION_THREADNAME, "STARTED");
#endif
        // [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[

        ModuleNEXTION_MAIN(); /* Main Application */

        // ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifdef DEBUG_THREAD
        DEBUG_printThread((char *)PROCESS_NEXTION_THREADNAME, "ENDED");
#endif
        //HAL_IWDG_Refresh(&hiwdg);   /*	Watchdog-Clear	 */
		}
	}
	else
	{
		/* Semaphore fail / Create Again  */
		xSemHandle.Process_NEXTION = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_NEXTION);
	}


}

#endif /* Thread Definitions */

#if 1 /* Semaphore Run Definitions */

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void     Process_Flash_Run(void)
{
#ifdef BSP_PROCESS_FLASH
	/* Message first, release later :) */

#ifdef DEBUG_THREAD
    DEBUG_printThread((char *)PROCESS_FLASH_SEMAPHORENAME, "RELEASED");
#endif

    xSemResult.Process_Flash = xSemaphoreGive(xSemHandle.Process_Flash);

    if (pdPASS == xSemResult.Process_Flash)
    {
        /* Bootloader Semaphore is Passed */
    	__GL.itc.flag.flash = TRUE;
    }
    else
    {
        /* Bootloader Semaphore is Fail	& Create Again */
    	__GL.itc.flag.flash = FALSE;

#ifdef DEBUG_THREAD
   DEBUG_printThread((char *)PROCESS_FLASH_SEMAPHORENAME, "ALREADY RUNNING");
#endif

        xSemHandle.Process_Flash = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_Flash);
    }
#endif
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void     Process_Can_Run(void)
{
#ifdef BSP_PROCESS_CAN
	/* Message first, release later :) */

#ifdef DEBUG_THREAD
    DEBUG_printThread((char *)PROCESS_CAN_SEMAPHORENAME, "RELEASED");
#endif

    xSemResult.Process_CAN = xSemaphoreGive(xSemHandle.Process_CAN);

    if (pdPASS == xSemResult.Process_CAN)
    {
        /* Bootloader Semaphore is Passed */
    	__GL.itc.flag.can = TRUE;
    }
    else
    {
        /* Bootloader Semaphore is Fail	& Create Again */
    	__GL.itc.flag.can = FALSE;

#ifdef DEBUG_THREAD
   DEBUG_printThread((char *)PROCESS_CAN_SEMAPHORENAME, "ALREADY RUNNING");
#endif

        xSemHandle.Process_CAN = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_CAN);
    }
#endif
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void     Process_RTC_Run(void)
{
#ifdef BSP_PROCESS_RTC
	/* Message first, release later :) */

#ifdef DEBUG_THREAD
    DEBUG_printThread((char *)PROCESS_RTC_SEMAPHORENAME, "RELEASED");
#endif

    xSemResult.Process_RTC = xSemaphoreGive(xSemHandle.Process_RTC);

    if (pdPASS == xSemResult.Process_RTC)
    {
        /* Bootloader Semaphore is Passed */
    	__GL.itc.flag.rtc = TRUE;
    }
    else
    {
        /* Bootloader Semaphore is Fail	& Create Again */
    	__GL.itc.flag.rtc = FALSE;

#ifdef DEBUG_THREAD
   DEBUG_printThread((char *)PROCESS_RTC_SEMAPHORENAME, "ALREADY RUNNING");
#endif

        xSemHandle.Process_RTC = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_RTC);
    }
#endif
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void     Process_SDCARD_Run(void)
{
#ifdef BSP_PROCESS_SDCARD
	/* Message first, release later :) */

#ifdef DEBUG_THREAD
    DEBUG_printThread((char *)PROCESS_SDCARD_SEMAPHORENAME, "RELEASED");
#endif

    xSemResult.Process_SDCARD = xSemaphoreGive(xSemHandle.Process_SDCARD);

    if (pdPASS == xSemResult.Process_SDCARD)
    {
        /* Bootloader Semaphore is Passed */
    	__GL.itc.flag.sdcard = TRUE;
    }
    else
    {
        /* Bootloader Semaphore is Fail	& Create Again */
    	__GL.itc.flag.sdcard = FALSE;

#ifdef DEBUG_THREAD
   DEBUG_printThread((char *)PROCESS_SDCARD_SEMAPHORENAME, "ALREADY RUNNING");
#endif

        xSemHandle.Process_SDCARD = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_SDCARD);
    }
#endif
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void     Process_WIFI_Run(void)
{
#ifdef BSP_PROCESS_WIFI
	/* Message first, release later :) */

#ifdef DEBUG_THREAD
    DEBUG_printThread((char *)PROCESS_WIFI_SEMAPHORENAME, "RELEASED");
#endif

    xSemResult.Process_WIFI = xSemaphoreGive(xSemHandle.Process_WIFI);

    if (pdPASS == xSemResult.Process_WIFI)
    {
        /* Bootloader Semaphore is Passed */
    	__GL.itc.flag.wifi = TRUE;
    }
    else
    {
        /* Bootloader Semaphore is Fail	& Create Again */
    	__GL.itc.flag.wifi = FALSE;

#ifdef DEBUG_THREAD
   DEBUG_printThread((char *)PROCESS_WIFI_SEMAPHORENAME, "ALREADY RUNNING");
#endif

        xSemHandle.Process_WIFI = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_WIFI);
    }
#endif
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void     Process_NEXTION_Run(void)
{
#ifdef BSP_PROCESS_NEXTION
	/* Message first, release later :) */

#ifdef DEBUG_THREAD
    DEBUG_printThread((char *)PROCESS_NEXTION_SEMAPHORENAME, "RELEASED");
#endif

    xSemResult.Process_NEXTION = xSemaphoreGive(xSemHandle.Process_NEXTION);

    if (pdPASS == xSemResult.Process_NEXTION)
    {
        /* Bootloader Semaphore is Passed */
    	__GL.itc.flag.wifi = TRUE;
    }
    else
    {
        /* Bootloader Semaphore is Fail	& Create Again */
    	__GL.itc.flag.wifi = FALSE;

#ifdef DEBUG_THREAD
   DEBUG_printThread((char *)PROCESS_NEXTION_SEMAPHORENAME, "ALREADY RUNNING");
#endif

        xSemHandle.Process_NEXTION = xSemaphoreCreateBinaryStatic(&xSemaphore.Process_NEXTION);
    }
#endif
}








#endif
