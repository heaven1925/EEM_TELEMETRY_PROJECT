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



/************************** DEFINES ********************************************/
#define	MODULESDCARD_MAIN_THREAD

ModuleSDCard_MAIN_State_et ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_IDLE;

ModuleSDCard_ROUTINE_State_et SDCard_ROUTINE_STATE;

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

//	/* Open file to write/ create a file if it doesn't exist */
//
//
//	/* Writing text */
//	f_puts("This data is from the FILE1.txt. And it was written using ...f_puts... ", &file);
//
//	/* Close file */
//	fresult = f_close(&file);


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


      f_printf(&file, "%s\n",bufferSDcard,50);
     /* Close file */

       fresult = f_close(&file);

       if(fresult!=FR_OK)
       {

           	 ModuleSDCard_MAIN_State=ModuleSDCard_MAIN_State_SUSPEND;

       }

	    	/* Writing text string */
	   f_puts("This data is from the FILE1.txt. And it was written using ...f_puts... ", &file);



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

