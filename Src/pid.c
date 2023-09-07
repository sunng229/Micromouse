/*
 * pid.c
 */

#include "main.h"
#include "motors.h"
#include "encoders.h"
int angleError = 0;
int oldAngleError = 0;
float distanceError = (0.4);
float oldDistanceError = 0;
float angleCorrection = 0;
float distanceCorrection = 0;
float kPw = (.02); //0.23
float kDw = (0.3); //0
float kPx = (.002); //0.0018
float kDx = (.005); //0
int goalAngle = 0;
int goalDistance = 0;
int done = 0;
int done2 = 0;
void resetPID() {
	/*
	 * For assignment 3.1: This function does not need to do anything
	 * For assignment 3.2: This function should reset all the variables you define in this file to help with PID to their default
	 *  values. You should also reset your motors and encoder counts (if you tell your rat to turn 90 degrees, there will be a big
	 * difference in encoder counts after it turns. If you follow that by telling your rat to drive straight without first
	 * resetting the encoder counts, your rat is going to see a huge angle error and be very unhappy).
	 *
	 * You should additionally set your distance and error goal values (and your oldDistanceError and oldAngleError) to zero.
	 */
	 angleError = 0;
	 oldAngleError = 0;
	 distanceError = 0;
	 oldDistanceError = 0;
	 //kPw = (0.03);
	 //kDw = (0);
	 //kPx = 1;
	 //kDx = (0.5);
	 goalAngle = 0;
	 goalDistance = 0;
	 done = 0;
	 resetEncoders();
	 done2 = 0;
	 resetMotors();
}

void updatePID() {
	/*
	 * This function will do the heavy lifting PID logic. It should do the following: read the encoder counts to determine an error,
	 * use that error along with some PD constants you determine in order to determine how to set the motor speeds, and then actually
	 * set the motor speeds.
	 *
	 * For assignment 3.1: implement this function to get your rat to drive forwards indefinitely in a straight line. Refer to pseudocode
	 * example document on the google drive for some pointers
	 *
	 * TIPS (assignment 3.1): Create kPw and kDw variables, use a variable to store the previous error for use in computing your
	 * derivative term. You may get better performance by having your kDw term average the previous handful of error values instead of the
	 * immediately previous one, or using a stored error from 10-15 cycles ago (stored in an array?). This is because systick calls so frequently
	 * that the error change may be very small and hard to operate on.
	 *
	 * For assignment 3.2: implement this function so it calculates distanceError as the difference between your goal distance and the average of
	 * your left and right encoder counts. Calculate angleError as the difference between your goal angle and the difference between your left and
	 * right encoder counts. Refer to pseudocode example document on the google drive for some pointers.
	 */
	int left_receiverr = get_left_receiver();
	int right_receiverr = get_right_receiver();
	int adjust = 0;
if(!get_turn_status()){
	if(left_receiverr > 1000 && right_receiverr > 1000) {
							adjust = left_receiverr - right_receiverr;
							adjust = adjust/95;
							if(adjust < 15)
								adjust = 0;
							setPIDGoalA(adjust);
						}
			else if(left_receiverr > 2900){ //3000
				adjust = (left_receiverr/100); //110
				if(adjust < 15)
					adjust = 0;
				setPIDGoalA(adjust);
			}
			else if(right_receiverr > 2900)//3000
			{
				adjust=-(right_receiverr/100); //110
				if(adjust < 15)
					adjust = 0;
				setPIDGoalA(adjust);
			}
}
		angleError = goalAngle + (-(getRightEncoderCounts()*0.9995) + getLeftEncoderCounts());
	angleCorrection = kPw * angleError + kDw * (angleError - oldAngleError);
		oldAngleError = angleError;


		distanceError = goalDistance + ((-getLeftEncoderCounts() - getRightEncoderCounts())/2);
	distanceCorrection = kPx * distanceError + kDx * (distanceError - oldDistanceError);
		oldDistanceError = distanceError;

		if(distanceCorrection > 0.25 ) {
			distanceCorrection = 0.25;
		}
		if(angleCorrection > 0.25) {
			angleCorrection = 0.25;
		}
		else if(angleCorrection < -0.25) {
			angleCorrection = -0.25;
		}

	setMotorLPWM((distanceCorrection - angleCorrection));
	setMotorRPWM((distanceCorrection + angleCorrection));

	if(angleError < 8 && angleError > -8){	done++;}
	if(distanceError < 75 && distanceError > -75){	done2++;}

		/*
		Since the goal of this assignment is to go forwards indefinitely, we just set the distanceError to
		some arbitrary value. Since the error is fixed, distanceCorrection will always equal kPx times
		whatever value you set distanceError to be. If you follow the suggested values and set kPx equal
		to 1 and distance error to 0.4, your motors will have an effecitve base speed of 0.4. The derivative
		term will always be zero since the distanceError doesn't change.

		PD control is implemented in the angleCorrection line, and this adjustment is added (or subtracted)
		from each motor, depending on what you treat as your positive angle direction. In the next assignment,
		you will dynamically set distanceError based on encoder counts in order to move fixed distances.
		*/
}

void setPIDGoalD(int16_t distance) {
	/*
	 * For assignment 3.1: this function does not need to do anything.
	 * For assignment 3.2: this function should set a variable that stores the goal distance.
	 */
	goalDistance = distance;
	done = 0;
	done2 = 0;

}

void setPIDGoalA(int16_t angle) {
	/*
	 * For assignment 3.1: this function does not need to do anything
	 * For assignment 3.2: This function should set a variable that stores the goal angle.
	 */
	goalAngle = angle;
	done = 0;
	done2 = 0;
}

int8_t PIDdone(void) { // There is no bool type in C. True/False values are represented as 1 or 0.
	/*
	 * For assignment 3.1: this function does not need to do anything (your rat should just drive straight indefinitely)
	 * For assignment 3.2:This function should return true if the rat has achieved the set goal. One way to do this by having updatePID() set some variable when
	 * the error is zero (realistically, have it set the variable when the error is close to zero, not just exactly zero). You will have better results if you make
	 * PIDdone() return true only if the error has been sufficiently close to zero for a certain number, say, 50, of SysTick calls in a row.
	 */

    return (done) && (done2);
}
