/*
 * main.c
 *
 *  Created on: Feb 23, 2022
 *      Author: Mohamed
 */

#include "lcd.h"
#include "lm35.h"
#include "dc_motor.h"
#include "adc.h"
#include "timer0.h"


int main(void)
{
	uint8 temp = 0;
	/*
	 * Configure ADC
	 */
	ADC_configType adc_init = {OFF_FREERUNNING, FCPU__8 ,INTERNAL_VOLTAGE};

	/*
	 * Configure Timer Modes
	 */
	TIMER0_configType timer0_init = {FAST_PWM,FCPU_8};

	ADC_init(&adc_init);
	TIMER0_init(&timer0_init);
	LCD_init();
	DCMOTOR_init();
	LCD_moveCursor(0,3);
	LCD_displayString("Fan Is ");
	LCD_moveCursor(1,3);
	LCD_displayString("TEMP=     C");

	while(1)
	{
		temp = LM35_getTemperature();

		if ( temp < 30)
		{
			LCD_moveCursor(0,10);
			LCD_displayString("OFF");
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp);
			DCMOTOR_rotate(0, OFF);
		}
		else if ((temp >= 30 ) && ( temp < 60) )
		{
			LCD_moveCursor(0, 10);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 9);
			LCD_intgerToString(temp);
			DCMOTOR_rotate(25,CW);
		}
		else if ((temp >= 60) && (temp <90))
		{
			LCD_moveCursor(0,10);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 9);
			LCD_intgerToString(temp);
			DCMOTOR_rotate(50, CW);
		}
		else if ((temp >= 90 ) && (temp <120))
		{
			 if ( temp < 100 )
			 {
				 LCD_moveCursor(1,11);
				 LCD_displayString(" ");
			 }
			LCD_moveCursor(0, 10);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 9);
			LCD_intgerToString(temp);
			DCMOTOR_rotate(75, CW);
		}
		else
		{
			LCD_moveCursor(0, 10);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 9);
			LCD_intgerToString(temp);
			DCMOTOR_rotate(100, CW);
		}


	}
}

