//#include <kipr/botball.h>
#include "DataBase.h"
//#include <stdio.h>
#define time_of_running 10
int main()
{
    enable_servos();
    int i;
    for (i = 0; i < 10; i++)
    {
        set_servo_position(2, 1000);

        set_servo_position(2, 1500);
    }
    return 0;
}