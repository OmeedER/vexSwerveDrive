#include "main.h"
#include "swerve.h"


float target;
float speed;
int counts1;
int counts2;
int counts3;
int counts4;
float kp = 1.4;
float pi = 3.1415926535;

void swerve(){
 if((abs(joystickGetAnalog(1,1)) > 30) || (abs(joystickGetAnalog(1,2)) > 30)){
 if(joystickGetAnalog(1,2) == 0 && joystickGetAnalog(1,1) != 0){
 target = 158;
 speed = joystickGetAnalog(1,1);
 }
 else{
 target = (180/pi)*atan2(joystickGetAnalog(1,1), joystickGetAnalog(1,2));
 speed = sqrt(pow(joystickGetAnalog(1,1),2) + pow(joystickGetAnalog(1,2),2));
 }
 motorSet(6, kp*(target - (counts1 * 27/79)));
 motorSet(7, kp*(target - (counts2 * 27/79)));
 motorSet(8, kp*(target - (counts3 * 27/79)));
 motorSet(9, kp*(target - (counts4 * 27/79)));

 motorSet(2, speed);
 motorSet(3, speed);
 motorSet(4, speed);
 motorSet(5, speed);
 }
 else{
 motorStopAll();
 }
 printf("\nD1: %d", counts1);
 printf("\nD2: %d", counts2);
}

void turn(){
 if(joystickGetDigital(1, 8, JOY_DOWN) == 1){
 delay(100);
 while(joystickGetDigital(1, 8, JOY_DOWN) == 0){
  motorSet(6, kp*(45-(counts1 * 27/79)));
  motorSet(7, -kp*(45+(counts2 * 27/79)));
  motorSet(8, -kp*(45+(counts3 * 27/79)));
  motorSet(9, kp*(45-(counts4 * 27/79)));

  motorSet(2, joystickGetAnalog(1,4));
  motorSet(3, joystickGetAnalog(1,4));
  motorSet(4, joystickGetAnalog(1,4));
  motorSet(5, joystickGetAnalog(1,4));
  delay(20);
 }
 delay(100);
}}

void IMESet(){
  imeGet(IME_MOTOR_1, &counts1);
  imeGet(IME_MOTOR_2, &counts2);
  imeGet(IME_MOTOR_3, &counts3);
  imeGet(IME_MOTOR_4, &counts4);
}

void zero(){
 if(joystickGetDigital(1, 8, JOY_UP) == 1){
 imeReset(IME_MOTOR_1);
 imeReset(IME_MOTOR_2);
 imeReset(IME_MOTOR_3);
 imeReset(IME_MOTOR_4);
 }
}