/*
 * Motor_driver.h
 *
 *  Created on: Oct 8, 2023
 *      Author: Bassel Jamal
 */

#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include"gpio.h"
#include"std_types.h"
#include"common_macros.h"
#include"PWM.h"

#define MOTOR_PORT_ID          PORTB_ID
#define MOTOR_PIN1_ID          PIN0_ID
#define MOTOR_PIN2_ID          PIN1_ID

typedef enum{
	STOP,CW,CCW
}DcMotor_State;


void DcMotor_init(void);

void DcMotor_Rotate(DcMotor_State state,uint8 speed);
static void MOTOR_STOP(void);
static void MOTOR_CW(void);
static void MOTOR_CCW(void);
#endif /* MOTOR_DRIVER_H_ */
