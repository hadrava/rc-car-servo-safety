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

	uint16_t servoA = 1;
	uint16_t servoB = 1;

	uint16_t xy;
	while (1) {
		PORTB &= ~ _BV(PB5);
		//set_std_servo(servoA, servoB);
		set_servo_us(servoA, servoB);
		_delay_ms(20);
		input_capture_0_single_shot();
		input_capture_1_single_shot();
		while(input_capture_0_running())
			;
		while(input_capture_1_running())
			;

		UDR0 = (OCR1A >> 8) | 0x80;
		_delay_ms(1);
		UDR0 = OCR1A;
		_delay_ms(1);
		UDR0 = OCR1B >> 8;
		_delay_ms(1);
		UDR0 = OCR1B;
		_delay_ms(1);

		xy = convert_raw_counter_to_us(counter_0);
		UDR0 = (xy >> 8);
		_delay_ms(1);
		UDR0 = xy;
		_delay_ms(1);

		xy = convert_raw_counter_to_us(counter_1);
		UDR0 = (xy >> 8);
		_delay_ms(1);
		UDR0 = xy;
		_delay_ms(1);

		PORTB |= _BV(PB5);
		_delay_ms(20);

		input_capture_0_single_shot();
		input_capture_1_single_shot();
		while(input_capture_0_running())
			;
		while(input_capture_1_running())
			;

		UDR0 = OCR1A >> 8;
		_delay_ms(1);
		UDR0 = OCR1A;
		_delay_ms(1);
		UDR0 = OCR1B >> 8;
		_delay_ms(1);
		UDR0 = OCR1B;
		_delay_ms(1);

		xy = convert_raw_counter_to_us(counter_0);
		UDR0 = (xy >> 8);
		_delay_ms(1);
		UDR0 = xy;
		_delay_ms(1);

		xy = convert_raw_counter_to_us(counter_1);
		UDR0 = (xy >> 8);
		_delay_ms(1);
		UDR0 = xy;
		_delay_ms(1);


		servoA++;
		servoB++;
	}
}
