 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Bassel Jamal
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56


typedef enum{
	OFF,AREF,NOTHING,INTERNAL_REF

}ADC_RefrenceVoltage;
typedef enum{
	NO_PRESCALAR,ADC_PRESCALAR,ADC_PRESCALAR_4,ADC_PRESCALAR_8,ADC_PRESCALAR_16,ADC_PRESCALAR_32,ADC_PRESCALAR_64,ADC_PRESCALAR_128


}ADC_Prescaler;
typedef struct{
	ADC_RefrenceVoltage ref_volt;
	ADC_Prescaler prescaler;

}ADC_ConfigType;

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
