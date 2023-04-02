/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

/************************** INCLUDES *******************************************/

#include "ModuleNEXTION_private.h"
#include "nextion.h"

/************************** DEFINES ********************************************/
#define	MODULENEXTION_MAIN_THREAD

ModuleNEXTION_MAIN_State_et ModuleNEXTION_MAIN_State = ModuleNEXTION_MAIN_State_IDLE;

ModuleNEXTION_FLAG_State_et ModuleNEXTION_FLAG_State;

nextion_St nextion;

nextionIkon_ut ikon;



#if 1	/* Init Functions */

/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void ModuleNEXTION_HWInit(void)
{
	 CTOR_nextion(&nextion,huart1,nexOps);


	//@INFO: NEXTION thread'ine ait donanımsal init fonksiyonları
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleNEXTION_SWInit(void)
{
	//@INFO: NEXTION thread'ine ait yazilimsal init fonksiyonları
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleNEXTION_StartUP(void)
{
	ModuleNEXTION_HWInit();
	ModuleNEXTION_SWInit();
}


#endif


#if 1	/* Application Functions */


#endif


#ifdef MODULENEXTION_MAIN_THREAD

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO	  :
********************************************************************************/

void ModuleNEXTION_MAIN_Routine(void)
{
	switch(ModuleNEXTION_FLAG_State)
		{
		    case ModuleNEXTION_FLAG_State_RF_SIGNAL:

                nextion.ops.sendCmd(&nextion.obj,RF_SIGNAL,ikon.flags.rf);


		    break;

		    case ModuleNEXTION_FLAG_State_WI_FI:

		    	nextion.ops.sendCmd(&nextion.obj,WI_FI,ikon.flags.wi_fi);

		    break;

		    case ModuleNEXTION_FLAG_State_LEFT_SIGNAL:

		    	nextion.ops.sendCmd(&nextion.obj,LEFT_SIGNAL,ikon.flags.left_signal);

		    break;

		    case ModuleNEXTION_FLAG_State_RIGT_SIGNAL:

		    	nextion.ops.sendCmd(&nextion.obj,RIGT_SIGNAL,ikon.flags.right_signal);

		    break;

		    case ModuleNEXTION_FLAG_State_HEAD_LIGHT:

		    	nextion.ops.sendCmd(&nextion.obj,HEAD_LIGHT,ikon.flags.head_light);

		    break;

		    case ModuleNEXTION_FLAG_State_WIPERS:

		    	nextion.ops.sendCmd(&nextion.obj,WIPERS,ikon.flags.wipers);

		    break;

		    case ModuleNEXTION_FLAG_State_WHEEL_ANGLE:

		    	nextion.ops.sendNum(&nextion.obj,WHEEL_ANGLE_R,25);
		    	nextion.ops.sendNum(&nextion.obj,WHEEL_ANGLE_L,20);

		    break;


		    case ModuleNEXTION_FLAG_State_UP_HILL:

		    nextion.ops.sendCmd(&nextion.obj,UP_HILL,ikon.flags.up_hıll);


		    break;

		    case ModuleNEXTION_FLAG_State_DOWN_HILL:

		    	nextion.ops.sendCmd(&nextion.obj,DOWN_HILL,ikon.flags.down_hıll);


		    break;

		    case ModuleNEXTION_FLAG_State_STRAIGHT:

		    	nextion.ops.sendCmd(&nextion.obj,STRAIGHT,ikon.flags.straight);

		    break;

		    case ModuleNEXTION_FLAG_State_HAND_BREAK:

		    	nextion.ops.sendCmd(&nextion.obj,HAND_BREAK,ikon.flags.hand_breaker);

		    break;

		    case ModuleNEXTION_FLAG_State_FLASHER:

		    	nextion.ops.sendCmd(&nextion.obj,FLASHER,ikon.flags.flasher);

		    break;

		    case ModuleNEXTION_FLAG_State_SPEED:

		    	nextion.ops.sendNum(&nextion.obj,SPEED,50);
		    	nextion.ops.sendNum(&nextion.obj,SPEED_POINTER,50);

		    break;

		    case ModuleNEXTION_FLAG_State_RAIN:

		    	nextion.ops.sendNum(&nextion.obj,RAIN,ikon.flags.rain);

		    break;

		    case ModuleNEXTION_FLAG_State_ENGINE_HEAT:

		   	nextion.ops.sendNum(&nextion.obj,ENGINE_HEAT,ikon.flags.engine_heat);

		   	break;

		    default:

		    break;

		}
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
void ModuleNEXTION_MAIN_Process(void)
{

}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/

void ModuleNEXTION_MAIN(void)
{
	switch(ModuleNEXTION_MAIN_State)
	{
	    case ModuleNEXTION_MAIN_State_IDLE:
	    	//@INFO: IDLE Operations ..
	    	ModuleNEXTION_MAIN_State = ModuleNEXTION_MAIN_State_ROUTINE;
	    break;

	    case ModuleNEXTION_MAIN_State_ROUTINE:

	    	ModuleNEXTION_MAIN_Routine();
	    break;

	    case ModuleNEXTION_MAIN_State_PROCESS:

	    	ModuleNEXTION_MAIN_Process();

	    break;

	    case ModuleNEXTION_MAIN_State_SUSPEND:
	    	ModuleNEXTION_MAIN_State = ModuleNEXTION_MAIN_State_IDLE;
	    break;

	    default:
	    	ModuleNEXTION_MAIN_State = ModuleNEXTION_MAIN_State_SUSPEND;
	    break;

	}

}


#endif

