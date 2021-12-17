# Analog Digital Converted - Interrupt service routine 

- ADC ISR USART Atmega328p Arduino UNO 

- Here we are reading the A0 analog input pin of arduino UNO and transmitting it to the serial monitor using USART inside ADC_vect interrupt service routine.

- We have dissabled ADATE (auto trigger enable) pin of ADCSRA register so that ADSC pin doesnt set again on itself, this is because we need time to write to the serial monitor using USART registers.

- Here we are running ADC in free running mode with clock divider at 128.

- Baud rate of transmission is 9600bps which corresponds to UBRR value 103. If you want to change the baud rate refer the Atmega328p datasheet for UBRR values.

- We are using the internal Vref AVcc 5v.