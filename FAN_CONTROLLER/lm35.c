/*
 * lm35.c
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohamed
 */

#include "adc.h"
#include "lm35.h"

uint8 LM35_getTemperature(void)
{
	uint16 adc_value = 0 ;
	uint8 temp_value = 0 ;
	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMP*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT));

 return temp_value ;

}
