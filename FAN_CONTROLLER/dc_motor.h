/*
 * dc_motor.h
 *
 *  Created on: Feb 22, 2022
 *      Author: Mohamed
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/******************************************************************************
 *                             Definition
 ******************************************************************************/

#define DC_MOTOR_PORT_ID PORTB_ID

#define DC_MOTOR_IN_1 PIN0_ID
#define DC_MOTOR_IN_2 PIN1_ID
#define DC_MOTOR_E    PIN3_ID


typedef enum {
	OFF ,CW ,CCW
}DCMOTOR_state;


/*******************************************************************************
 *                         Prototypes & Description
 ******************************************************************************/
/*
 * Configure Motor Pins As Output
 * And Make Dc Motor Stop At Begin
 */
void DCMOTOR_init(void);

/*
 *  Select The Direction Of Rotation
 *  Select Speed Of Rotation
 */
void DCMOTOR_rotate(uint8 speed ,DCMOTOR_state state);


#endif /* DC_MOTOR_H_ */
