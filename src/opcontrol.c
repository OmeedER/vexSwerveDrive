/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
*/

#include "main.h"


/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
*/
 
float target_dist = 30;
int tempDistance;
int DistanceLeft;
int DistanceRight;
float sonar_speed;
float sonar_kp = 10;

void follow1D(int Distance){
sonar_speed =  (Distance - target_dist) * sonar_kp;
motorSet(2, sonar_speed);
motorSet(3, sonar_speed);
motorSet(4, sonar_speed);
motorSet(5, sonar_speed);
}

void follow2D(int distanceLeft, int distanceRight){
	int avg_Dist = (distanceLeft + distanceRight)/2;
	sonar_speed =  (avg_Dist - target_dist) * sonar_kp;
	if (distanceLeft < distanceRight) {
		int speedChange = (distanceRight-distanceLeft) * sonar_kp;
        motorSet(2, sonar_speed);
		motorSet(3, sonar_speed);
		motorSet(4, sonar_speed+speedChange);
		motorSet(5, sonar_speed+speedChange);
	}
	/*if (distanceLeft > distanceRight) {
		int speedChange = (distanceLeft-distanceRight) * sonar_kp;
		motorSet(2, sonar_speed+speedChange);
		motorSet(3, sonar_speed+speedChange);
        motorSet(4, sonar_speed);
		motorSet(5, sonar_speed);
	}
     else{
        motorSet(2, sonar_speed);
		motorSet(3, sonar_speed);
		motorSet(4, sonar_speed);
		motorSet(5, sonar_speed);
    }*/
    
}

void holdTurn(){
motorSet(6, 3);
motorSet(7, 3);
motorSet(8, 3);
motorSet(9, 3);   
}

void operatorControl() {
 Ultrasonic sonarLeft;
 Ultrasonic sonarRight;
 sonarRight = ultrasonicInit(2,1);
 sonarLeft = ultrasonicInit(4,3);
 while(true){
 DistanceLeft = ultrasonicGet(sonarLeft);
 DistanceRight = ultrasonicGet(sonarRight);
 printf("SonarLeft:%d   SonarRight:%d \n", DistanceLeft, DistanceRight);
 holdTurn();
 follow2D(DistanceLeft, DistanceRight);
 delay(50);
}}
