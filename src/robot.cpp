#include "robot.h"

Romi32U4ButtonA buttonA;
Romi32U4ButtonB buttonB;
Romi32U4ButtonC buttonC;
Claw claw;
FourBar fourbar;
Slide slide;

void Robot::InitializeRobot(void)
{
    chassis.InititalizeChassis();
    claw.init();
    // slide.init();
    // fourbar.init();
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
    if(chassis.ChassisLoop(velocity)) {
        if (buttonC.isPressed()) {
            robotState = ROBOT_TURN_IN_PLACE;
        } else if (robotState == FOURBAR_MOVE) {
            // fourbar.changePos(fourbar.positionIndex + 1);
            fourbar.changePos(3);
            if (fourbar.posiitionReached) {
                robotState = SLIDE_MOVE;
                fourbar.posiitionReached = false;
                fourbar.positionIndex++;
            }
        } else if (robotState == SLIDE_MOVE) {
            // slide.moveDist(slide.currentIndex);
            if (slide.positionReached) {
                slide.positionReached = false;
                slide.currentIndex++;
                switch (slide.currentIndex) {
                case 0:
                    robotState = CLAW_OPEN;
                    break;
                case 1:
                    robotState = FOURBAR_MOVE;
                    break;
                case 2:
                    robotState = CLAW_CLOSE;
                    break;
                case 3:
                    robotState = FOURBAR_MOVE;
                    break;
                case 4:
                    robotState = CLAW_OPEN;
                    break;
                case 5:
                    robotState = ROBOT_TURN_IN_PLACE;
                    claw.detach();
                    fourbar.detach();
                    break;
                default:
                    break;
                }
            }
        } else if (robotState == CLAW_OPEN) {
            claw.open();
            if (claw.opened) {
                robotState = SLIDE_MOVE;
            }
        } else if (robotState == CLAW_CLOSE) {
            claw.close();
            if (!claw.opened) {
                if (fourbar.positionIndex == 0) {
                    robotState = FOURBAR_MOVE;
                    fourbar.init();
                } else if (fourbar.positionIndex == 2) {
                    robotState = SLIDE_MOVE;
                }
            }
        }

        else if (robotState == ROBOT_TURN_IN_PLACE) {
            UpdatePose(velocity);
            // 250
            TurnInPlace(180);
            if (turnFinished) {
                chassis.Stop();
                // Reset Current Pose for simplicity 
                currPose = Pose(0, 0, 0);
                robotState = ROBOT_DRIVE_TO_POINT;
            }
        }
        // We do FK regardless of state
        else if (robotState == ROBOT_DRIVE_TO_POINT) {
            UpdatePose(velocity);
            if (CheckReachedDestination()) {
                HandleDestination();
            } else {
                DriveToPoint();
            }
        } else if (robotState == ROBOT_IDLE) {
            chassis.Stop();
        }
    }
}