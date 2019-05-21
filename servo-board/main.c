#include "global.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "servo.h"
#include "uart.h"
#include "input_capture.h"


int main(void) {
	DDRB |= _BV(PB5); // LED output enable

	servo_init();
	uart_init();
	input_capture_init();
	sei();

	uint16_t servoA = 0;
	uint16_t servoB = 0;

	int8_t drunk = 0x7F;
	while (1) {
		PORTB &= ~ _BV(PB5);

		input_capture_0_single_shot();
		input_capture_1_single_shot();

		while(input_capture_0_running())
			;
		while(input_capture_1_running())
			;
		PORTB |= _BV(PB5);

		servoA = convert_raw_counter_to_us(counter_0);
		servoB = convert_raw_counter_to_us(counter_1);
		//servoA = servoA + drunk - 0x80;
		set_servo_us(servoA, servoB);

		drunk++;
		UDR0 = (servoA >> 8) | 0x80;
		_delay_ms(1);
		UDR0 = servoA;
		_delay_ms(1);
		UDR0 = (servoB >> 8);
		_delay_ms(1);
		UDR0 = servoB;
		_delay_ms(1);
	}
}
