/*
 * PWM.c
 *
 *  Created on: Oct 9, 2023
 *      Author: Bassel Jamal
 */


#include"PWM.h"

/*
 * Description :
 * Function responsible for setup the registers of timer0 to work as PWM mode.
 */
void PWM_init(PWM_CLOCK_conf clk){
	GPIO_setupPinDirection(PWM_PORT_ID,PWM_CHANNEL,PIN_OUTPUT);

	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01); // Set timer registers on PWM mode

	TCCR0 = (TCCR0 & 0xF8) | (clk & 0x07); //Set the clock of the timer

}
/*
 * Description :
 * Function responsible for calculate the duty cycle needed by the motor.
 */
void PWM_Timer0_Start(uint8 duty_cycle){
	TCNT0 = 0; // Set Timer Initial Value to 0

	OCR0  = (uint8)(((float32)(duty_cycle)/100)*(float32)255); //Set Compare value
}
