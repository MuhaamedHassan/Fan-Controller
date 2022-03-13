/*
 * lcd.h
 *
 *  Created on: Feb 12, 2022
 *      Author: Mohamed
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_VREF     5
#define ADC_INTERNAL_VOLATAGE 2.56

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   ADC_INTERNAL_VOLATAGE


/*
 * IF U Will Use Adc With Interrupt  Please Make It TRUE ifnot make it FALSE
 */

#define ADC_INTERRUPT  FALSE

/* Extern Of Global Variable */
/* We Use adc_data In Case We Used ADC With Interrupt */
extern volatile  uint16 adc_data ;

/*
 * Select Which Refrence Of Vref
 * 0 - Vref = A ref
 * 1 - Vref = AVCC With External Capactor At AREF pin
 * 3 - Vref =  Internal 2.56 Voltage Reference
 */
typedef enum {
	AREF , AVCC , INTERNAL_VOLTAGE = 3
}ADC_volatageReference;

/*
 * Select Channel Number Of Conversion
 * Starting From 0 To 7
 */
typedef enum {
	CHANNEL0 , CHANNEL1 , CHANNEL2 , CHANNEL3 , CHANNEL4 , CHANNEL5 , CHANNEL6 , CHANNEL7

}ADC_channelNumber;

/*
 * Modes Of  Auto Triger Mode
 */
typedef enum {
	OFF_FREERUNNING , ANALOG_COMPARATOR , EX_INT0 , TIMER0_COMP , TIMER0_OVF , TIMER1_COMPB , TIMER1_OVF , TIMER1_ICU
}ADC_autoTrigger;

/*
 * Prescalling Of ADC
 * Adc  Frequancy From 50 To 200 KHZ
 */
typedef enum {
	FCPU_ , FCPU__2 , FCPU__4 , FCPU__8 , FCPU__16 , FCPU__32 , FCPU__64 , FCPU__128
}ADC_prescaler;

typedef struct
{
	ADC_autoTrigger auto_trigger_mode ;
	ADC_prescaler  prescaler ;
	ADC_volatageReference voltage_reference ;

}ADC_configType;


/*
 * Init Function For ADC
 */
void ADC_init( const ADC_configType *ConfigPtr);


/*
 * Read The Data From Coresponding Channel
 */
uint16 ADC_readChannel(ADC_channelNumber channel_number);
#endif /* ADC_H_ */
