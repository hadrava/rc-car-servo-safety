#ifndef _SERVO_H_
#define _SERVO_H_

#include <stdint.h>

void set_std_servo(uint8_t servoA, uint8_t servoB);
void set_ext_servo(uint8_t servoA, uint8_t servoB);
void set_servo_us(uint16_t servoA, uint16_t servoB);
void servo_init(void);
void servo_deinit(void);

#endif
