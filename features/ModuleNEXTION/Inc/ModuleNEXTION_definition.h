/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    ModuleRF_definition.h
  * @author	 Atakan ERTEKiN,Ömer Faruk USLU
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __NEXTION_MODULE_DEFINITION_H__
#define	__NEXTION_MODULE_DEFINITION_H__

	
	
/*********************** INCLUDES **********************************************/

#include <stdint.h>
#include <stdbool.h>




/*********************** DEFINES ***********************************************/

#define  RF_SIGNAL      "RF_Signals"
#define  WI_FI          "Wi_Fi"
#define  LEFT_SIGNAL    "Left_Signal"
#define  RIGT_SIGNAL    "Right_Signal"
#define  HEAD_LIGHT     "Head_Light"
#define  WIPERS         "Wipers"
#define  WHEEL_ANGLE_L  "Wheel_Angle_L"
#define  WHEEL_ANGLE_R  "Wheel_Angle_R"
#define  UP_HILL        "Up_Hill"
#define  DOWN_HILL      "Down_Hill"
#define  STRAIGHT       "Straight"
#define  SPARK          "Spark"
#define  BATTERY_LEVEL  "Battery_Level"
#define  HAND_BREAK     "Hand_Break"
#define  FLASHER        "Flasher"
#define  SPEED          "SPEED"
#define  SPEED_POINTER  "Speed_Pointer"
#define  RAIN           "Rain"
#define  ENGINE_HEAT    "Engine_Heat"


typedef union __attribute__((__packed__)){

	uint32_t nextionIkons;
	struct
	{
	 bool rf              :1;
	 bool wifi            :1;
	 bool left_signal     :1;
	 bool right_signal    :1;
	 bool head_light      :1;
	 bool wipers          :1;
	 bool wheel_angle_l   :1;
	 bool wheel_angle_r   :1;
	 bool up_hıll         :1;
	 bool down_hıll       :1;
	 bool straight        :1;
	 bool spark           :1;
	 bool hand_breaker    :1;
	 bool flasher         :1;
	 bool rain            :1;
	 bool engine_heat     :1;
	 uint16_t dummy :16;
	} flags;

} nextionIkon_ut;


typedef enum
{
	ModuleNEXTION_PROCESS_State_RF_SIGNAL  = 0,
	ModuleNEXTION_PROCESS_State_WI_FI         ,
	ModuleNEXTION_PROCESS_State_LEFT_SIGNAL   ,
	ModuleNEXTION_PROCESS_State_RIGT_SIGNAL   ,
	ModuleNEXTION_PROCESS_State_HEAD_LIGHT    ,
	ModuleNEXTION_PROCESS_State_WIPERS        ,
	ModuleNEXTION_PROCESS_State_WHEEL_ANGLE   ,
   	ModuleNEXTION_PROCESS_State_UP_HILL       ,
    ModuleNEXTION_PROCESS_State_DOWN_HILL     ,
    ModuleNEXTION_PROCESS_State_STRAIGHT      ,
    ModuleNEXTION_PROCESS_State_SPARK         ,
    ModuleNEXTION_PROCESS_State_BATTERY_LEVEL ,
    ModuleNEXTION_PROCESS_State_HAND_BREAK    ,
    ModuleNEXTION_PROCESS_State_FLASHER       ,
    ModuleNEXTION_PROCESS_State_SPEED         ,
    ModuleNEXTION_PROCESS_State_RAIN          ,
    ModuleNEXTION_PROCESS_State_ENGINE_HEAT   ,

}ModuleNEXTION_PROCESS_State_et;



typedef enum
{
	ModuleNEXTION_MAIN_State_IDLE = 0,
	ModuleNEXTION_MAIN_State_ROUTINE ,
	ModuleNEXTION_MAIN_State_PROCESS ,
	ModuleNEXTION_MAIN_State_SUSPEND ,

}ModuleNEXTION_MAIN_State_et;


	
	
/********************** FUNCTION PROTOTYPE **************************************/	
	

	
	
	
	
#endif /*__NEXTION_MODULE_DEFINITION_H__ */	

/*********************** END OF FILE ********************************************/

