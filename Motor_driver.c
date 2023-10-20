/*
 * Motor_driver.c
 *
 *  Created on: Oct 8, 2023
 *      Author: Bassel Jamal
 */

#include"Motor_driver.h"

void DcMotor_init(void){
	GPIO_setupPinDirection(MOTOR_PORT_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_writePin(MOTOR_PORT_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID,PIN1_ID,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	PWM_Timer0_Start(speed);
	switch(state){
	case 0: MOTOR_STOP();break;
	case 1: MOTOR_CW();break;
	case 2: MOTOR_CCW();break;
	}

}
static void MOTOR_STOP(void){
	GPIO_writePin(MOTOR_PORT_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID,PIN1_ID,LOGIC_LOW);
}
static void MOTOR_CW(void){
	GPIO_writePin(MOTOR_PORT_ID,PIN0_ID,LOGIC_HIGH);
	GPIO_writePin(MOTOR_PORT_ID,PIN1_ID,LOGIC_LOW);
}
static void MOTOR_CCW(void){
	GPIO_writePin(MOTOR_PORT_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID,PIN1_ID,LOGIC_HIGH);
}
