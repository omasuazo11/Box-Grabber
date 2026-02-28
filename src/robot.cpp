#include "robot.h"

Romi32U4ButtonA buttonA;
Romi32U4ButtonB buttonB;
Romi32U4ButtonC buttonC;
Claw claw;
FourBar fourbar;
// Slide slide;

void Robot::InitializeRobot(void)
{
    chassis.InititalizeChassis();
    claw.init();
    // fourbar.init();
    // slide.init();
}

void Robot::EnterIdleState(void)
{
    chassis.Stop();
    Serial.println("-> IDLE");
    robotState = ROBOT_IDLE;
}

/**
 * The main loop for your robot. Process both synchronous events (motor control),
 * and asynchronous events (distance readings, etc.).
*/
void Robot::RobotLoop(void) 
{
     /**
     * Run the chassis loop, which handles low-level control.
     */
    
    Twist velocity;
    if(chassis.ChassisLoop(velocity))
    {
        claw.open();
        // fourbar.changePos(0);
        // slide.moveDist(2000);
        if (fourbar.servo.isAttached) {
            Serial.println("ATTACHED IT");
        }

        // if (robotState == FOURBAR_MOVE) {
        //     fourbar.changePos(fourbar.positionIndex + 1);
        //     if (fourbar.posiitionReached) {
        //         robotState = SLIDE_MOVE;
        //         fourbar.positionIndex++;
        //     }
        // } else if (robotState == SLIDE_MOVE) {
        //     slide.moveDist(slide.currentIndex);
        //     if (slide.positionReached) {
        //         switch (slide.currentIndex) {
        //         case 0:
        //             robotState = CLAW_OPEN;
        //             break;
        //         case 1:
        //             robotState = FOURBAR_MOVE;
        //             break;
        //         case 2:
        //             robotState = CLAW_CLOSE;
        //         case 3:
        //             robotState = FOURBAR_MOVE;
        //         case 4:
        //             robotState = CLAW_OPEN;
        //         case 5:
        //             robotState = ROBOT_DRIVE_TO_POINT;
        //         default:
        //             break;
        //         }
        //         slide.currentIndex++;
        //     }
        // } else if (robotState == CLAW_OPEN) {
        //     claw.open();
        //     if (claw.opened) {
        //         robotState = SLIDE_MOVE;
        //     }
        // } else if (robotState == CLAW_CLOSE) {
        //     claw.close();
        //     if (!claw.opened) {
        //         if (fourbar.positionIndex == 0) {
        //             robotState = FOURBAR_MOVE;
        //         } else if (fourbar.positionIndex == 2) {
        //             robotState = SLIDE_MOVE;
        //         }
        //     }
        // }

        // // We do FK regardless of state
        // else if (robotState == ROBOT_DRIVE_TO_POINT) {
        //     PrintState();
        //     if (CheckReachedDestination()) {
        //         HandleDestination();
        //     } else {
        //         DriveToPoint();
        //     }
        // }
    }
}