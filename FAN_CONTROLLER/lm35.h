/*
 * lm35.h
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohamed
 */

#ifndef LM35_H_
#define LM35_H_

#include "std_types.h"
/* Definations */

#define SENSOR_CHANNEL_ID CHANNEL2
#define SENSOR_MAX_VOLT  1.5
#define SENSOR_MAX_TEMP 150


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
uint8 LM35_getTemperature(void);


#endif /* LM35_H_ */
