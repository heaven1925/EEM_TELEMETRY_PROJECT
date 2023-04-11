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

	
	
/*********************** INCLUDES **********************************************/




/*********************** DEFINES ***********************************************/


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
















































