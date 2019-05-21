#include "global.h"
#include <avr/io.h>
#include <stdint.h>
#include "servo.h"

#define STD_SERVO_OFFSET 990
#define EXT_SERVO_OFFSET 480

// Counter top, (one phase is upcounting + downcounting = 2x ICR1 timer clock cycles)
// We are using 16MHz / 8 prescaler --> 2MHz timer clock
#define SERVO_100HZ8_ICR1 9921 // 9.921 ms = apx. 100.8 Hz (Measured signal period of the receiver)
#define SERVO_50HZ_ICR1 20000 // 20 ms = 50 Hz

// Use 100.8 Hz
#define SERVO_ICR1 SERVO_100HZ8_ICR1


void set_std_servo(uint8_t servoA, uint8_t servoB) {
	// Generates signal in range 1 - 2 ms
	// Registers are double buffered in PWM modes, so any change is glitch-free
	OCR1A = STD_SERVO_OFFSET + ((uint16_t) servoA << 2);
	OCR1B = STD_SERVO_OFFSET + ((uint16_t) servoB << 2);
}

void set_ext_servo(uint8_t servoA, uint8_t servoB) {
	// Generates signal in range 0.5 - 2.5 ms
	// Registers are double buffered in PWM modes, so any change is glitch-free
	OCR1A = EXT_SERVO_OFFSET + ((uint16_t) servoA << 3);
	OCR1B = EXT_SERVO_OFFSET + ((uint16_t) servoB << 3);
}

void set_servo_us(uint16_t servoA, uint16_t servoB) {
	// Set length of servo signal in us. You can send signal that will make the servo colide.
	OCR1A = servoA;
	OCR1B = servoB;
}

void servo_init(void) {
	set_std_servo(0x80, 0x80);           // default servo position in the middle
	ICR1 = SERVO_ICR1;                   // Selected signal period
	TCCR1B = (1<<WGM13) | (1<<CS11);     // WGM13: PWM, Phase and Frequency Correct, CS11: clk / 8 (--> 16 MHz / 8 = 2 MHz clock)
	TCCR1A = (1<<COM1A1) | (1<<COM1B1);  // Clear OC1A/B when upcounting, set when downcounting, assign output pins
	DDRB |= _BV(PB1) | _BV(PB2);         // Servo outputs enable
}

void servo_deinit(void) {
	DDRB &= ~(_BV(PB1) | _BV(PB2));      // Servo outputs disable
	TCCR1A = 0;                          // Initial value, Normal port operation, pins disconnected
	TCCR1B = 0;                          // Initial value
	ICR1 = 0;                            // Initial value
	OCR1A = 0;                           // Initial value
	OCR1B = 0;                           // Initial value
}
