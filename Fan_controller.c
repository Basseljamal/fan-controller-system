/*
 * Fan_controller.c
 *
 *  Created on: Oct 8, 2023
 *      Author: Bassel Jamal
 */
#include<avr/interrupt.h>
#include"Motor_driver.h"
#include"lcd.h"
#include"adc.h"
#include"gpio.h"
#include"std_types.h"
#include"lm35_sensor.h"
#include"PWM.h"
#include<util/delay.h>

#define I_BIT 7
#define INT1_PORT_ID PORTD_ID
#define INT1_PIN_ID PIN3_ID

void INT1_init(void);

DcMotor_State motor_state;

int main(void){
	/*
	 * define the struct needed by the ADC module to initialize it
	 * set the reference voltage and the prescalar of the ADC
	 * define the struct needed by the PWM module to initialize it
	 * set the clock of timer0
	 */
	ADC_ConfigType ADC_Configrations = {INTERNAL_REF,ADC_PRESCALAR_8};
	PWM_CLOCK_conf PWM_config = {PWM_CLOCK_8};

	uint8 motor_speed;
	uint8 tempreture_value;

	SET_BIT(SREG,I_BIT); /* Enable the global interrupt */
	/* initialize all the needed modules in the project*/
	INT1_init();
	LCD_init();
	PWM_init(PWM_config);
	ADC_init(&ADC_Configrations);
	DcMotor_init();
	/*A starting message display on the screen of the LCD for 1 second before the main program */
	LCD_displayStringRowColumn(0,0,"Fan Controller");
	LCD_displayStringRowColumn(1,4,"system");
	_delay_ms(1000);
	LCD_clearScreen();

	while(1){
		//Get the value of LM35"Temperature sensor" and store it in a local variable
		tempreture_value = LM35_getTemperature();
		/*
		 * check the range of the temperature to control the DC motor
		 * if the temperature is lower than 30 degree the DC should stop
		 * and display this message on LCD "Fan is off"
		 * if the temperature ranges from 30 degree to 60 degree
		 * the fan should rotate with 25% of it's max speed
		 * and display "Fan is on" on the LCD
		 * if the temperature ranges from 60 degree to 90 degree
		 * the fan should rotate with 50% of it's max speed
		 * and display "Fan is on" on the LCD
		 * if the temperature ranges from 90 degree to 120 degree
		 * the fan should rotate with 75% of it's max speed
		 * and display "Fan is on" on the LCD
		 * if the temperature is higher than 120
		 * the fan should rotate with 100% of it's max speed
		 * and display "Fan is on" on the LCD
		 * Always , the temperature should be displayed on the LCD*/
		if(tempreture_value < 30){
			LCD_displayStringRowColumn(0,0,"Fan is OFF");
			motor_state = STOP;
			motor_speed = 0;
		}
		else if(tempreture_value >= 30 && tempreture_value < 60){
			LCD_displayStringRowColumn(0,0,"Fan is ON  ");
			motor_speed = 25;
			if(motor_state == STOP){
				motor_state = CW;
			}
		}
		else if(tempreture_value >= 60 && tempreture_value < 90){
			LCD_displayStringRowColumn(0,0,"Fan is ON  ");
			motor_speed = 50;
			if(motor_state == STOP){
				motor_state = CW;
			}
		}
		else if(tempreture_value >= 90 && tempreture_value < 120){
			LCD_displayStringRowColumn(0,0,"Fan is ON  ");
			motor_speed = 75;
			if(motor_state == STOP){
				motor_state = CW;
			}
		}
		else if(tempreture_value >= 120 && tempreture_value < SENSOR_MAX_TEMPERATURE){
			LCD_displayStringRowColumn(0,0,"Fan is ON  ");
			motor_speed = 100;
			if(motor_state == STOP){
				motor_state = CW;
			}
		}
		else{
			LCD_displayStringRowColumn(0,0,"Fan is OFF  ");
			motor_state = STOP;
			motor_speed = 0;
		}
		DcMotor_Rotate(motor_state,motor_speed);
		LCD_moveCursor(1,0);
		LCD_displayString("Temperature=");
		LCD_intgerToString(tempreture_value);
		LCD_displayCharacter(' ');
	}

}

void INT1_init(void){
	GPIO_setupPinDirection(INT1_PORT_ID,INT1_PIN_ID,PIN_INPUT); //activate pin 3 in port D as input pin
	PORTD |= (1<<3); //activate the internal pull up in pin 3 in port D
	GICR |= (1<<INT1); //activate external interrupt 0
	MCUCR |= (1<<ISC11); //activate interrupt 0 to detect falling edge
}
ISR(INT1_vect){
	if(motor_state == CW){
		motor_state = CCW;
	}
	else{
		motor_state = CW;
	}

}
