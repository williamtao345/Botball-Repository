#include "Data.h"

/*Define numbers    */
#define left_wheel_number 1
#define right_wheel_number 3
#define arm_servo_number 100
#define camera_servo_number 2
#define hand_servo_number 4
/*END   */

/*Define positions  */
#define camera_forward_servo_position 50
#define arm_up_servo_position 500
#define arm_down_servo_positon 10
#define hand_open_position 1000
#define hand_closed_position 0
/*END   */

/*Speed is char from 1-5*/
/*If speed is greater than 0 is running forward.    */
/*If speed is less than 0 is running backward.      */
void move_forward(char speed, int time_of_running)
{
    motor(left_wheel_number, (int)speed * 20);
    motor(right_wheel_number, (int)speed * 20);
    msleep(time_of_running);
}

/*--Stop the Wheels--   */
void stop_running()
{
    motor(left_wheel_number, 0);
    motor(right_wheel_number, 0);
}

/*If degrees greater than 0 is turning left. */
/*If degrees less than 0 is turning right.   */
#define angle_ratio 50
void change_direction(int degrees)
{
    if (degrees >= 0)
    {
        motor(left_wheel_number, -100);
        motor(right_wheel_number, 100);
        msleep(degrees * angle_ratio);
    }
    else
    {
        motor(left_wheel_number, 100);
        motor(right_wheel_number, -100);
        msleep(degrees * angle_ratio);
    }
}

/*--Follow the Object--                             */
/*If lose object, wait until find the object agian. */
void follow_object(int object_number)
{
    camera_open_black();
    camera_update();
    while (get_object_center_y(1, object_number) < 110)
    {
        camera_update();
        int object_center_x = get_object_center_x(1, object_number);
        if (object_center_x > 80)
        {
            motor(left_wheel_number, 50);
            motor(right_wheel_number, 10);
        }
        else if (object_center_x < 80)
        {
            motor(left_wheel_number, 10);
            motor(right_wheel_number, 50);
        }
        else if (object_center_x == 80)
        {
            motor(left_wheel_number, 30);
            motor(right_wheel_number, 30);
        }
        else
        {
            motor(3, 0);
            motor(1, 0);
        }
    }
    camera_close();
}

/*--Reset every part--      */
/*Wheels stop               */
/*Camera face forward.      */
/*Arm up.                   */
/*Hnad close.               */
void initBot()
{
    motor(left_wheel_number, 0);
    motor(right_wheel_number, 0);
    set_servo_position(camera_servo_number, camera_forward_servo_position);
    set_servo_position(arm_servo_number, arm_down_servo_positon);
    set_servo_position(hand_servo_number, hand_open_position);
}

void catch_object()
{
    set_servo_position(hand_servo_number, hand_closed_position);
    set_servo_position(arm_servo_number, arm_up_servo_position);
}

void put_object()
{
    set_servo_position(arm_servo_number, arm_down_servo_positon);
    msleep(300);
    set_servo_position(hand_servo_number, hand_open_position);
}

int main()
{
    //enable_servos();
    initBot();
    follow_object(0);
    catch_object();
    return 1;
}