/*
 * timer0.h
 *
 *  Created on: Feb 22, 2022
 *      Author: Mohamed
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_types.h"

/******************************************************************************
 *                         Definations
 ******************************************************************************/
/* If U Want to Enable TOV INTERRUPT MAKE IT TRUE ifnot make it FALSE */
#define OVF_INTERRUPT_ENABLE  FLASE
/* If U Want to Enable CTC INTERRUPT MAKE IT TRUE ifnot make it FALSE */
#define CTC_INTERRUPT_ENABLE  FALSE

#define TIMER0_MAX_VALUE 255

/******************************************************************************
 *                         types
 ******************************************************************************/

typedef enum {
	NORMAL , PWM_PHASE_CORRECT , CTC , FAST_PWM
}TIMER0_mode;

typedef enum {
	OFF_CLK , FCPU , FCPU_8 , FCPU_64 , FCPU_256 , FCPU_1024 ,EXT_FALLING_EDGE , EXT_RISING_EDGE
}TIMER0_prescaler;

typedef enum {
	OC0_OFF , TOGGLE_OC0 , CLEAR_OC0 , SET_OC0
}TIMER0_CTC_MODE;

typedef enum {
	NORMAL_OC0_OFF , NON_INVERTING = 2 , INVERTING
}TIMER0_PWM_MODE;

typedef struct {
	TIMER0_mode mode ;
	TIMER0_prescaler clock ;
}TIMER0_configType;

/******************************************************************************
 *                         Prototype & Description
 ******************************************************************************/
/*
 * Initialize Timer 0
 * 1- Select Mode Of Operation
 * 2- Clock Select
 */
void TIMER0_init (const TIMER0_configType *configptr);

/*
 * Generate PWM Signale According to
 * 1 - duty cylcle
 * 2- Mode Of PWM
 */

void TIMER0_generatePWM(uint8 duty_cycle ,TIMER0_PWM_MODE pwm_mode);

/*
 * Generate Square Wave Form With CTC Mode
 * if  u want to Make It Generate Squre Wave Choose Toggle Mode
 */
void TIMER0_generateCTC(uint8 duty_cycle ,TIMER0_CTC_MODE ctc_mode);

/*
 * Use TIMER0 CTC Mode
 */
void TIMER0_CTC (uint8 top);

/*
 * De Init Timer 0
 */
void TIMER0_deinit(void);

#endif /* TIMER0_H_ */
