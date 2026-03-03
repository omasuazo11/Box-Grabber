/**
 * robot-nav.cpp is where you should put navigation routines.
 */

#include "robot.h"


void Robot::PrintState(void) {
    Serial.print(robotState);
    Serial.print("Current x: ");
    Serial.print(currPose.x);
    Serial.print(" Current y: ");
    Serial.print(currPose.y);
    Serial.print(" Current theta: ");
    Serial.println(currPose.theta);
    Serial.print("Destination x: ");
    Serial.print(destPose.x);
    Serial.print(" Destination y: ");
    Serial.print(destPose.y);
    Serial.print(" Destination theta: ");
    Serial.println(destPose.theta);
}

void Robot::UpdatePose(const Twist& twist)
{
    /*
    Update pose from given twist
    */
    float oldTheta = currPose.theta;
    currPose.theta += chassis.CONTROL_LOOP_PERIOD_MS * twist.omega;
    float theta_star = (float) (oldTheta + currPose.theta) / 2;
    currPose.x += chassis.CONTROL_LOOP_PERIOD_MS * twist.u * cos(theta_star);
    currPose.y += chassis.CONTROL_LOOP_PERIOD_MS * twist.u * sin(theta_star);
    // if (currPose.theta > PI) {
    //     currPose.theta -= 2*PI;
    // } else if (currPose.theta < PI * -1) {
    //     currPose.theta += 2*PI;
    // }
#ifdef __NAV_DEBUG__

#endif

}

/**
 * Sets a destination in the lab frame.
 */
void Robot::SetDestination(const Pose& dest)
{
    digitalWrite(13, HIGH);
    Serial.print("Setting dest to: ");
    Serial.print(dest.x);
    Serial.print(", ");
    Serial.print(dest.y);
    Serial.print('\n');
    destPose = dest;
    robotState = ROBOT_DRIVE_TO_POINT;
}

bool Robot::CheckReachedDestination(void)
{
    return ((destPose.x - 5 <= currPose.x && currPose.x <= destPose.x + 5) && 
        (destPose.y - 5 <= currPose.y && currPose.y <= destPose.y + 5));
}

void Robot::DriveToPoint(void)
{
    if(robotState == ROBOT_DRIVE_TO_POINT)
    {
        float distanceError = sqrt(sq(destPose.x - currPose.x) + sq(destPose.y - currPose.y));
        if (distanceError > 45) {
            distanceError = 45;
        }
        float thetaError = atan2(destPose.y - currPose.y, destPose.x - currPose.x) - currPose.theta;
        if (thetaError > PI ){
            thetaError -= 2*PI;
        } else if (thetaError < -1*PI) {
            thetaError += 2*PI;
        }
        float leftEffort = Kp_dist * distanceError - Kp_theta * thetaError;
        float rightEffort = Kp_dist * distanceError + Kp_theta * thetaError;

#ifdef __NAV_DEBUG__
        
#endif
        chassis.SetMotorEfforts(leftEffort, rightEffort);
    }
}

void Robot::HandleDestination(void)
{
    if (drivingNum == 0) {
        robotState = ROBOT_TURN_IN_PLACE;
        drivingNum++;
        turnAngle = 140;
        destPose = Pose(40, 25, 0);
        currPose = Pose(0, 0, 0);
    } else {
        EnterIdleState();
    }
    
}

void Robot::TurnInPlace(int degrees) {
    float rads = degrees * PI / 180;
    float thetaError = rads - currPose.theta; 
    if (thetaError > PI / 2) {
        thetaError = PI / 2;
    }
    float leftEffort = - Kp_theta * thetaError;
    float rightEffort = Kp_theta * thetaError;
    chassis.SetMotorEfforts(leftEffort, rightEffort);
    if (abs(thetaError) < 0.35 ) {
        turnFinished = true;
    }
}