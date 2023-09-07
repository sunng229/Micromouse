/*
 * controller.c
 */

#include "main.h"
#include "controller.h"
#include "pid.h"
#include "irs.h"

/*
 * We recommend you implement this function so that move(1) will move your rat 1 cell forward.
 */
int left_receiver1 = 0;
int right_receiver1 = 0;
int front_left_receiver1 = 0;
int front_right_receiver1 = 0;
int turn_status = 0;
void move(int8_t n) {
	/*
	 * For assignment 3.1: Don't worry about implementing this yet
	 * For assignment 3.2: This function should set the distance and angle goals appropriately for PID (hint: using the setGoal functions in pid.c)
	 * and wait until the error becomes sufficiently small and persistent before exiting. This function should NOT exit before then.
	 *
	 * HINT: Use a while loop to wait until the rat has moved the desired distance
	 *
	 * You should also call resetPID before exiting this function so your rat is ready for the next instruction.
	 */


		setPIDGoalD(720*n); //maybe too short
		updatePID();
		//adjust = 0;
		while(PIDdone() == 0) {
			left_receiver1 = readRightIR();
			right_receiver1 = readLeftIR();
			front_right_receiver1 = readFrontRightIR();
			front_left_receiver1 = readFrontLeftIR();
			if(front_right_receiver1 > 3000 && front_left_receiver1 > 3000)
				break;
		};
		resetPID();
}

/*
 * We recommend you implement this function so that turn(1) turns your rat 90 degrees in your positive rotation
 * direction and turn(-1) turns the other way.
 */
void turn(int8_t n) {
	/*
	 * For assignment 3.1: Don't worry about implementing this yet
	 * For assignment 3.2: This function should set the distance and angle goals appropriately for PID (hint: using the setGoal functions in pid.c)
	 * and wait until the error becomes sufficiently small and persistent before exiting. This function should NOT exit before then.
	 *
	 * HINT: Use a while loop to wait until the turn is complete
	 *
	 * You should also call resetPID before exiting this function so your rat is ready for the next instruction.
	 */
		setPIDGoalA(540*n); //maybe too small
		setPIDGoalD(0);
		turn_status =1;
		updatePID();
		while(PIDdone() == 0) {};
		resetPID();
		turn_status = 0;
}

int get_turn_status() {
	return turn_status;
}
int get_left_receiver() {
	return left_receiver1;
}
int get_right_receiver() {
	return right_receiver1;
}
int get_front_left_receiver()
{
	return front_left_receiver1;
}
int get_front_right_receiver()
{
	return front_right_receiver1;
}
