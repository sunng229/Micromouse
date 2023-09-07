/*
 * controller.h
 */

#ifndef INC_CONTROLLER_H_
#define INC_CONTROLLER_H_

#include "main.h"

void move(int8_t n);
void turn(int8_t n);
int get_left_receiver();
int get_right_receiver();
int get_front_left_receiver();
int get_front_right_receiver();
int get_turn_status();

#endif /* INC_CONTROLLER_H_ */
