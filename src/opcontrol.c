#include "main.h"
 
//Define all variables
int distanceLeft;
int distanceRight;
int deadRange = 5;
int counts1_M;
int counts2_M;
int counts3_M;
int counts4_M;
float targetDist = 30;
float avgDist;
float sonar_speed;
float turn_speed;
float sonar_kp = 8;
float turn_kp = 1.4;

//1D Following
void follow1D(int Distance){
//Calculate speed
	sonar_speed = (Distance - targetDist) * sonar_kp;
//Run drive motors
	motorSet(2, sonar_speed);
	motorSet(3, sonar_speed);
	motorSet(4, sonar_speed);
	motorSet(5, sonar_speed);
}

//2D Following
void follow2D(int DistanceLeft, int DistanceRight){
    int sonarDif = abs(DistanceLeft - DistanceRight);
    printf("Sonar Dif: %d \n", sonarDif);
//Rotate robot if the left and right distances are close
   if(sonarDif < deadRange){
    //Calculate avarage distance and speed
        avgDist = (DistanceLeft + DistanceRight)/2;
        sonar_speed = (avgDist - targetDist) * sonar_kp;
    //Turn modules to be at 0 degrees
        motorSet(6, turn_kp*(-counts1_M * 27/79));
        motorSet(7, turn_kp*(-counts2_M * 27/79));
        motorSet(8, turn_kp*(-counts3_M * 27/79));
        motorSet(9, turn_kp*(-counts4_M * 27/79));
    //Run drive motors
	    motorSet(2, sonar_speed);
	    motorSet(3, sonar_speed);
	    motorSet(4, sonar_speed);
	    motorSet(5, sonar_speed);
    }
//Turn the robot to achieve equal distances
   else{
    //Turn modules to be at 45 degrees (Rotating position)
        motorSet(6, turn_kp*(-45 - (counts1_M * 27/79)));
        motorSet(7, turn_kp*(45 - (counts2_M * 27/79)));
        motorSet(8, turn_kp*(45 - (counts3_M * 27/79)));
        motorSet(9, turn_kp*(-45 - (counts4_M * 27/79)));
    //Drive motors based on the differnece of the sonar
        turn_speed = (DistanceLeft - DistanceRight) * sonar_kp;
	    motorSet(2, turn_speed);
	    motorSet(3, turn_speed);
	    motorSet(4, -turn_speed);
	    motorSet(5, -turn_speed); 
    }

}

void operatorControl() {
//Initialize sonar sensors and reset IMEs
Ultrasonic sonarLeft;
Ultrasonic sonarRight;
sonarRight = ultrasonicInit(2,1);
sonarLeft = ultrasonicInit(4,3);
 imeReset(IME_MOTOR_1);
 imeReset(IME_MOTOR_2);
 imeReset(IME_MOTOR_3);
 imeReset(IME_MOTOR_4);
while(true){
//Get the IME values
    imeGet(IME_MOTOR_1, &counts1_M);
    imeGet(IME_MOTOR_2, &counts2_M);
    imeGet(IME_MOTOR_3, &counts3_M);
    imeGet(IME_MOTOR_4, &counts4_M);
//Get the Sonar values
    distanceLeft = ultrasonicGet(sonarLeft);
    distanceRight = ultrasonicGet(sonarRight);
//Print sensor values for debugging
    printf("SonarLeft:%d   SonarRight:%d \n", distanceLeft, distanceRight);
//Run the sonar following code
    follow2D(distanceLeft, distanceRight);
    delay(40);
    motorStopAll();
    }
}