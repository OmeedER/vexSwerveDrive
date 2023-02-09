#include "main.h"
 
float target_dist = 30;
int distanceLeft;
int distanceRight;
float sonar_speed;
float speedLeft;
float speedRight;
float sonar_kp = 8;
int counts1_M;
int counts2_M;
int counts3_M;
int counts4_M;
float kp_M = 1.4;

void follow1D(int Distance){
	sonar_speed =  (Distance - target_dist) * sonar_kp;
	motorSet(2, sonar_speed);
	motorSet(3, sonar_speed);
	motorSet(4, sonar_speed);
	motorSet(5, sonar_speed);
}

void follow2D(int DistanceLeft, int DistanceRight){
	speedLeft = (DistanceLeft - target_dist) * sonar_kp;
	speedRight = (DistanceRight - target_dist) * sonar_kp;
    motorSet(2, speedLeft);
	motorSet(3, speedLeft);
	motorSet(4, speedRight);
	motorSet(5, speedRight);
}

void holdTurn(){
  imeGet(IME_MOTOR_1, &counts1_M);
  imeGet(IME_MOTOR_2, &counts2_M);
  imeGet(IME_MOTOR_3, &counts3_M);
  imeGet(IME_MOTOR_4, &counts4_M);

  motorSet(6, kp_M*(0 - (counts1_M * 27/79)));
  motorSet(7, kp_M*(0 - (counts2_M * 27/79)));
  motorSet(8, kp_M*(0 - (counts3_M * 27/79)));
  motorSet(9, kp_M*(0 - (counts4_M * 27/79)));
}

void operatorControl() {
 Ultrasonic sonarLeft;
 Ultrasonic sonarRight;
 sonarRight = ultrasonicInit(2,1);
 sonarLeft = ultrasonicInit(4,3);
 while(true){
 distanceLeft = ultrasonicGet(sonarLeft);
 distanceRight = ultrasonicGet(sonarRight);
 printf("SonarLeft:%d   SonarRight:%d \n", distanceLeft, distanceRight);
 holdTurn();
 follow2D(distanceLeft, distanceRight);
 delay(50);
}}