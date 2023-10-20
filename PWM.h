/*
 * PWM.h
 *
 *  Created on: Oct 9, 2023
 *      Author: Bassel Jamal
 */

#ifndef PWM_H_
#define PWM_H_

#include"std_types.h"
#include"gpio.h"
#include"avr/io.h"


#define PWM_PORT_ID PORTB_ID // define the port to which timer0 is connected
#define PWM_CHANNEL 3 // define the pin to which timer0 is connected

typedef enum{
	NO_CLOCK,PWM_CLOCK,PWM_CLOCK_8,PWM_CLOCK_64,PWM_CLOCK_256,PWM_CLOCK_1024

}PWM_CLOCK_conf;

/*
 * Description :
 * Function responsible for setup the registers of timer0 to work as PWM mode.
 */
void PWM_init(PWM_CLOCK_conf clk);

/*
 * Description :
 * Function responsible for calculate the duty cycle needed by the motor.
 */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
