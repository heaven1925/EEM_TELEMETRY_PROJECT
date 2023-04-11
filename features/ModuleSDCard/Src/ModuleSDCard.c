/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleSDCard.c
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

/************************** INCLUDES *******************************************/

#include "ModuleSDCard_private.h"
#include "fatfs_sd.h"
#include "fatfs.h"
#include "types.h"



/************************** DEFINES ********************************************/
#define	MODULESDCARD_MAIN_THREAD

ModuleSDCard_MAIN_State_et ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_IDLE;



FATFS *fs;
FIL file;
uint8_t byteread;
char bufferSDcard[20]="HELLO WORLD";


#if 1	/* Init Functions */

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void ModuleSDCard_HWInit(void)
{
	FRESULT fresult;

    fresult = f_mount(fs, "", 0);

    if(fresult!=FR_OK){

    	ModuleSDCard_MAIN_State=ModuleSDCard_MAIN_State_SUSPEND;
    }

	//@INFO: SDCard thread'ine ait donanımsal init fonksiyonları
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleSDCard_SWInit(void)
{



	 //@INFO: WIFI thread'ine ait yazilimsal init fonksiyonları
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleSDCard_StartUP(void)
{
	ModuleSDCard_HWInit();
	ModuleSDCard_SWInit();
}


#endif


#if 1	/* Application Functions */


#endif


#ifdef MODULESDCARD_MAIN_THREAD

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO	  :
********************************************************************************/

void ModuleSDCard_MAIN_Routine(void)
{

	 FRESULT fresult;


      fresult = f_open(&file, "SDCard_Logger.txt", FA_OPEN_ALWAYS | FA_OPEN_APPEND| FA_WRITE);
      if(fresult!=FR_OK)
      {

    	    ModuleSDCard_MAIN_State=ModuleSDCard_MAIN_State_SUSPEND;
      }

      sprintf((char*)__GL.sdcard.main.buffadrr , "VOLTAGE:%d \n BATTERY POWER:%d \n TEMPERATURE:%d \n SPEED:%d  \n",50,50,50,50);
      f_printf(&file, "%s\n",bufferSDcard,__GL.sdcard.main.buffadrr);
     /* Close file */

       fresult = f_close(&file);

       if(fresult!=FR_OK)
       {

           	 ModuleSDCard_MAIN_State=ModuleSDCard_MAIN_State_SUSPEND;

       }




	       /* Close file */
	    fresult = f_close(&file);

		if(fresult!=FR_OK){

		    	ModuleSDCard_MAIN_State=ModuleSDCard_MAIN_State_SUSPEND;
		  }

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleSDCard_MAIN_Process(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleSDCard_MAIN(void)
{
	switch(ModuleSDCard_MAIN_State)
	{
	    case ModuleSDCard_MAIN_State_IDLE:
	    	//@INFO: IDLE Operations ..
	    	ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_ROUTINE;
	    break;

	    case ModuleSDCard_MAIN_State_ROUTINE:

	    	ModuleSDCard_MAIN_Routine();
	    break;

	    case ModuleSDCard_MAIN_State_PROCESS:

	    	ModuleSDCard_MAIN_Process();

	    break;

	    case ModuleSDCard_MAIN_State_SUSPEND:
	    	ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_IDLE;
	    break;

	    default:
	    	ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_SUSPEND;
	    break;

	}

}


#endif

