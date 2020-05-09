//#include <kipr/botball.h>
#include "Data.h"
/*Define numbers    */
#define left_wheel_number 2
#define right_wheel_number 3
#define arm_servo_number 3
#define camera_servo_number 0
#define hand_servo_number 2
/*END   */

/*Define positions  */
#define camera_forward_servo_position 0
#define arm_up_servo_position 700
#define arm_down_servo_positon 1265
#define hand_open_position 1175
#define hand_closed_position 470
/*END   */

/*Speed is char from 1-5                            */
/*If speed is greater than 0 is running forward.    */
/*If speed is less than 0 is running backward.      */
/*If time_of_running=-1, no msleep.                 */
void move_forward(int left_speed, int right_speed, int time_of_running)
{
    motor(left_wheel_number, left_speed);
    motor(right_wheel_number, right_speed);
    if (time_of_running != -1)
    {
        msleep(time_of_running);
    }
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
    printf("%d\n", get_object_center_y(0, object_number));
    while (get_object_center_y(0, object_number) < 105)
    {
        printf("%d\n", get_object_center_y(0, object_number));
        camera_update();
        int object_center_x = get_object_center_x(0, object_number);
        if (get_object_center_y(0, object_number) > 80)
        {
            if (object_center_x > 80)
            {
                motor(left_wheel_number, 100);
                motor(right_wheel_number, 50);
            }
            else if (object_center_x < 80 && object_center_x >= 0)
            {
                motor(left_wheel_number, 50);
                motor(right_wheel_number, 100);
            }
            else if (object_center_x == 80)
            {
                motor(left_wheel_number, 100);
                motor(right_wheel_number, 100);
            }
        }
        else
        {
            if (object_center_x > 80)
            {
                motor(left_wheel_number, 50);
                motor(right_wheel_number, 10);
            }
            else if (object_center_x < 80 && object_center_x >= 0)
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
                motor(left_wheel_number, 0);
                motor(right_wheel_number, 0);
            }
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
    //set_servo_position(camera_servo_number, camera_forward_servo_position);
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
    msleep(500);
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
/* #include <kipr/botball.h>

int left_wheel_number = 2;
int right_wheel_number = 3;
int arm_servo_number = 3;
int camera_servo_number = 0;
int hand_servo_number = 2;

int camera_forward_servo_position = 0;
int arm_up_servo_position = 700;
int arm_down_servo_positon = 1300;
int hand_open_position = 1160;
int hand_closed_position = 470;

int move_forward(int speed, int time_of_running)
{
    motor(left_wheel_number, speed);
    motor(right_wheel_number, speed);
    msleep(time_of_running);
    return 1;
}

int stop_running()
{
    motor(left_wheel_number, 0);
    motor(right_wheel_number, 0);
    return 1;
}

#define speed_ratio 50
int change_direction(int degrees)
{
    if (degrees >= 0)
    {
        motor(left_wheel_number, -100);
        motor(right_wheel_number, 100);
        msleep(degrees * speed_ratio);
    }
    else
    {
        motor(left_wheel_number, 100);
        motor(right_wheel_number, -100);
        msleep(degrees * speed_ratio);
    }
    return 1;
}

int follow_object(int object_number)
{
    camera_open_black();
    camera_update();
    printf("%d\n", get_object_center_y(0, object_number));
    while (get_object_center_y(0, object_number) < 105)
    {
        printf("%d\n", get_object_center_y(0, object_number));
        camera_update();
        int object_center_x = get_object_center_x(0, object_number);
        if (object_center_x > 80)
        {
            motor(left_wheel_number, 50);
            motor(right_wheel_number, 10);
        }
        else if (object_center_x < 80 && object_center_x > 0)
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
            motor(left_wheel_number, 0);
            motor(right_wheel_number, 0);
        }
    }
    camera_close();
    return 1;
}

int initBot()
{
    set_servo_position(arm_servo_number, arm_down_servo_positon);
    set_servo_position(hand_servo_number, hand_open_position);
    return 1;
}

int catch_object()
{
    set_servo_position(hand_servo_number, hand_closed_position);
    msleep(300);
    set_servo_position(arm_servo_number, arm_up_servo_position);
    return 1;
}

int put_object()
{
    set_servo_position(arm_servo_number, arm_down_servo_positon);
    msleep(300);
    set_servo_position(hand_servo_number, hand_open_position);
    return 1;
}

int main()
{
    enable_servos();
    initBot();
    follow_object(0);
    catch_object();
    move_forward(100, 1000);
    int i;
    for (i = 0; i < 10; i++)
    {
        set_servo_position(arm_servo_number, 600);
        motor(3, 100);
        motor(0, 100);
        msleep(200);
        ao();

        set_servo_position(arm_servo_number, 1300);
        motor(3, -100);
        motor(0, -100);
        msleep(200);
        ao();
    }
    put_object();
    move_forward(-100, 1000);
    initBot();
    return 1;
} */