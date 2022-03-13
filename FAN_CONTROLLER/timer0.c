/*
 * timer0.c
 *
 *  Created on: Feb 22, 2022
 *      Author: Mohamed
 */

#include "timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"

#if OVF_INTERRUPT_ENABLE == TRUE
ISR(TIMER0_OVF_vect)
{

}
#endif
#if CTC_INTERRUPT_ENABLE == TRUE
ISR(TIMER0_COMP_vect)
{

}
#endif


/*
 * Initialize Timer 0
 * 1- Select Mode Of Operation
 * 2- Clock Select
 */
void TIMER0_init (const TIMER0_configType *configptr)
{
	/* Clearing TCNT0  */
	TCNT0 = 0;
	TCCR0 = 0;
	/* Make PB3 As  output pin */
	if (configptr->mode == NORMAL)
	{
		SET_BIT(TCCR0,FOC0);
		/* Do Nothing  */
		/* We Already Made It By 0 */
	#if OVF_INTERRUPT_ENABLE  == TRUE
		SET_BIT(TIMSK,TOIE0);
	#endif
	}
	else if (configptr->mode == CTC)
	{
		SET_BIT(TCCR0,FOC0);
		SET_BIT(TCCR0,WGM01);
	#if CTC_INTERRUPT_ENABLE  == FALSE
		SET_BIT(DDRB,PB3);
	#else
		SET_BIT(TIMSK,OCIE);
	#endif

	}
	else if (configptr->mode == PWM_PHASE_CORRECT)
	{
		SET_BIT(TCCR0,WGM00);
		SET_BIT(DDRB,PB3);
	}
	else
	{
		SET_BIT(TCCR0,WGM01);
		SET_BIT(TCCR0,WGM00);
		SET_BIT(DDRB,PB3);
	}

	/* Configure Clock */
	TCCR0 = (TCCR0 & 0xF8) | (configptr->clock);

}

/*
 * Generate PWM Signale According to
 * 1 - duty cylcle
 * 2- Mode Of PWM
 */

void TIMER0_generatePWM(uint8 duty_cycle ,TIMER0_PWM_MODE pwm_mode)
{
	/* Select Mode Of Pwm Signals */
	TCCR0 = (TCCR0 & 0xCF) | (pwm_mode << COM00);

	OCR0 = duty_cycle ;
}

/*
 * Generate Square Wave Form With CTC Mode
 * if  u want to Make It Generate Squre Wave Choose Toggle Mode
 */
void TIMER0_generateCTC(uint8 duty_cycle ,TIMER0_CTC_MODE ctc_mode)
{
	/* Select Mode Of Pwm Signals */
	TCCR0 = (TCCR0 & 0xCF) | (ctc_mode << COM00);

	OCR0 = duty_cycle ;
}

/*
 * Use TIMER0 CTC Mode
 */
void TIMER0_CTC (uint8 top)
{
	OCR0 = top;
}

/*
 * De Init Timer 0
 */
void TIMER0_deinit(void)
{
	TCCR0 = 0 ;
	TCNT0 = 0 ;
}
