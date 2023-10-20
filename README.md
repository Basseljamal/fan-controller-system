# fan-controller-system
Project summary:

In this project, I've used the ATmega32 microcontroller operating at a frequency of 1MHz to create a fan control system that responds to temperature variations. The heart of this system is the LM35 temperature sensor, which provides analog temperature readings. Here's a quick breakdown of the project's core features:
-LM35 Sensor :
The LM35 sensor continuously measures the temperature and provides analog output.
-ADC :
The ATmega32's ADC converts analog readings into digital values.
-Temperature Calculation:
We perform temperature calculations within the microcontroller to determine the precise temperature based on the ADC data.
-LCD Display:
The temperature is displayed on an LCD screen, allowing for easy monitoring.
-Fan Control:
The microcontroller actively manages the fan's speed based on temperature readings.
The fan operates under different conditions:
<30°C: Fan is turned off.
≥30°C: Fan operates at 25% speed.
≥60°C: Fan operates at 50% speed.
≥90°C: Fan operates at 75% speed.
≥120°C: Fan operates at 100% speed.
-PWM Speed Control:
The fan's speed is controlled using Pulse Width Modulation (PWM) generated from Timer0.
-Push button:
The push button is an external interrupt connected to interrupt 1 that is used to inverse the direction of the fan.
The project is designed using a layered architecture model, with distinct components:

Application Layer.

HAL: (LCD, LM35 Sensor, DC-Motor), 

MCAL: (GPIO, ADC, PWM), 
