# ADC USART Atmega328p Arduino UNO

- Here we read the sensor value from the A0 pin of arduino UNO.

- We set the ADSC bit of ADCSRA register to 1 to start the conversion once in free running mode. 

- We read from the ADC register (ADCL and ADCH), after the ADSC bit is set to 0 (processing is done).

- Then we transmit the value through USART UDR register to serial monitor.