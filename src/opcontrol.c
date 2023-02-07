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
int distance;
float sonar_speed;
float sonar_kp = 5;

void follow1D(int Distance){
//if (abs(Distance - target_dist) > 5) {
sonar_speed =  (Distance - target_dist) * sonar_kp;
motorSet(2, sonar_speed);
motorSet(3, sonar_speed);
motorSet(4, sonar_speed);
motorSet(5, sonar_speed);
}

void operatorControl() {
 Ultrasonic sonar;
 sonar = ultrasonicInit(2,1);
 while(true){
 distance = ultrasonicGet(sonar);
 follow1D(distance);
 //swerve();
 //turn();
 //zero();
 delay(30);
}}
