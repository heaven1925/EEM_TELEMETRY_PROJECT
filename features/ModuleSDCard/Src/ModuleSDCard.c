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

/************************** DEFINES ********************************************/
#define	MODULESDCARD_MAIN_THREAD

ModuleSDCard_MAIN_State_et ModuleSDCard_MAIN_State = ModuleSDCard_MAIN_State_IDLE;


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

//    fresult = f_mount(&fs, "", 0);
//
//	/* Check free space */
//	   f_getfree("", &fre_clust, &pfs);
//
//	   total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
//
//	   free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);
//
//	/* Open file to write/ create a file if it doesn't exist */
//    fresult = f_open(&file, "file1.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
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
	 @INFO		:
********************************************************************************/

void ModuleSDCard_MAIN_Routine(void)
{

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

