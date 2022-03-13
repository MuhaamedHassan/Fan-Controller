
/*
 * lcd.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Mohamed
 */


#include "adc.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* Global Variable Which Use To Read Data From ISR */
volatile uint16 adc_data;
/*
 * Intialize The Adc
 * 1 - Select Prescalling
 * 2- Closed ADLAR
 * 3- Select Vref
 * 4- Enable Adc
 */

void ADC_init( const ADC_configType *ConfigPtr)
{
	/*
	 * Disable ADLAR
	 * Select ADC Channels From 0 To 7
	 * Assumed Vref = AREF
	 */
	ADMUX = 0;

	/*
	 * Select Vref
	 */
	if (ConfigPtr -> voltage_reference == AREF)
	{
		/* Do Nothing */
	}
	else if (ConfigPtr -> voltage_reference == AVCC)
	{
		SET_BIT(ADMUX,REFS0);
	}
	else if (ConfigPtr->voltage_reference == INTERNAL_VOLTAGE)
	{
		ADMUX |= 0xC0 ;
	}

	/*
	 * Enable Adc
	 */
	SET_BIT(ADCSRA,ADEN);

	/*
	 * Select To Enable Or Disable Auto Trigger Mode
	 */
	if (ConfigPtr -> auto_trigger_mode == OFF_FREERUNNING)
	{
		CLEAR_BIT(ADCSRA,ADATE);
	}
	else
	{
		SET_BIT(ADCSRA,ADATE);
	}
	/* Enable Or Disable Interrupt Mode */
	#if ADC_INTERRUPT == TRUE
	SET_BIT(ADCSRA,ADIE);
	#else
	CLEAR_BIT(ADCSRA,ADIE);
	#endif
	/* Adc Prescaling */

	ADCSRA = (ADCSRA & 0xF8) | (ConfigPtr ->prescaler);

	/*
	 * Special Register Function
	 * Auto Trigger Modes
	 */
	SFIOR = (SFIOR & 0x1F) | ((ConfigPtr -> auto_trigger_mode) << 5);

}


/*
 * Read The Data From Coresponding Channel
 * if Interrupt Mode Is True This Function Return 0
 */
uint16 ADC_readChannel(ADC_channelNumber channel_number)
{
	/*Insertion Of Channel Num At Mux Bits MUX 0 .... 4 */
	ADMUX = (ADMUX & 0xE0) | (channel_number & 0x07);
	/* Start Conversion */
	SET_BIT(ADCSRA,ADSC);
	#if ADC_INTERRUPT == TRUE
	return adc_data ;
	#else
	/* Polling Until Flag = 1 */
	/* Check For 0 */
	while (BIT_IS_CLEAR(ADCSRA,ADIF));
	/* Clear Flag By Put 1 At Its Bit */
	SET_BIT(ADCSRA,ADIF);
	/* Return Data At Register Data */
	return ADC ;
	#endif
}

#if ADC_INTERRUPT == TRUE
ISR(ADC_vect)
{
	/* Read Data From ADC Register */
	adc_data = ADC ;
}
#endif
