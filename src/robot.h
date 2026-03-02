#pragma once

#include "chassis.h"
#include "claw.h"
#include "slide.h"
#include "fourbar.h"

class Robot
{
protected:
    /**
     * robotState is used to track the current task of the robot. You will add new states as 
     * the term progresses.
     */
    enum ROBOT_STATE 
    {
        ROBOT_DRIVE_TO_POINT,
        ROBOT_IDLE,
        CLAW_OPEN,
        CLAW_CLOSE,
        FOURBAR_MOVE,
        SLIDE_MOVE,
        ROBOT_TURN_IN_PLACE
    };
    ROBOT_STATE robotState = ROBOT_IDLE;

    /* Define the chassis*/
    Chassis chassis;

    // For managing key presses
    String keyString;

    /**
     * For tracking current pose and the destination.
     */
    // Pose destPose = Pose(35, -10, 0);
    Pose destPose = Pose(42, 33, 0);
    
public:
    Pose currPose;
    Robot(void) {keyString.reserve(10);}
    void InitializeRobot(void);
    void RobotLoop(void);
    void PrintState(void);
    const float Kp_dist = 2.75;
    const float Kp_theta = 90;
    bool turnFinished = false;

protected:
    int currentPoint = 0;
    /* State changes */    
    void EnterIdleState(void);

    // /* Navigation methods.*/
    void UpdatePose(const Twist& u);
    void SetDestination(const Pose& destination);
    void DriveToPoint(void);
    void TurnInPlace(int degrees);
    bool CheckReachedDestination(void);
    void HandleDestination(void);
};
