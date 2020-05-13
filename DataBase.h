//#include <kipr/botball.h>
#include "Data.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

/*  Define numbers    */
#define left_wheel_number 2
#define right_wheel_number 3
#define arm_servo_number 3
#define arm_servo_part_1_number 0
#define arm_servo_part_2_number 0
#define camera_servo_number 0
#define hand_servo_number 2
/*  END   */

/*  Define positions  */
#define camera_forward_servo_position 0
#define arm_up_servo_position 700
#define arm_up_servo_part_1_position 0
#define arm_up_servo_part_2_position 0
#define arm_down_servo_part_1_position 0
#define arm_down_servo_part_2_position 0
#define arm_down_servo_positon 1265
#define hand_open_position 1175
#define hand_closed_position 470
/*  END   */

/*  define ratios  */
#define angle_ratio 50
/*  END   */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Initialize for C Programing DataBase~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef int DataType;
void set_arm(int);
void set_hand(int);
void catch_up_object();
void put_down_object();
void set_arm_position_with_two_parts(int percentage);
void initBot();
void catch_object(int object_number);
int Length_CharString(char *p);
void stop_running();
int Insert_to_end_of_LinkList_for_tracks_recording(int left_speed, int right_speed, int time_of_running);
void Clean_up_track_recording();
void go_back_as_records();
void motor_record(int left_speed, int right_speed, int time_of_running);
void move_forward(char speed, int time_of_running);
void set_motor(int left_wheel_speed, int right_wheel_speed, int time_of_running);
void change_direction(int degrees);
int move_from_file();
void follow_object(int object_number);

/* ----------------------------------LinkList---------------------------------------- */

typedef struct node
{
    DataType data;
    struct node *link;
} LinkNode, *LinkList;

int Length_CharString(char *p);
LinkList Locate(LinkList(*first), int i);
int Insert_LinkNode(LinkList(*first), int i, DataType x);
int Insert_to_end_of_LinkList(LinkList(*first), DataType x);
int Remove_LinkNode(LinkList(*first), int i);
LinkList String_to_LinkList(int *p, int length);
void Printf_LinkList(LinkList x);

/* ----------------------------------Stack---------------------------------------- */
#define initSize 20
typedef int SElemType;
typedef struct
{
    SElemType *elem;
    int maxSize, top;
} SeqStack;

void InitStack(SeqStack(*S));
int Push(SeqStack *S, DataType x);
int Pop(SeqStack(*S), SElemType *x);
int GetTop(SeqStack *S);
int StackEmpty(SeqStack(*S));
int StackFull(SeqStack(*S));

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DataBase for botball~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ----------------------------------Record tracks---------------------------------- */

/* int use_track_recording = 0;
typedef struct tracksRecording
{
    int speed_of_left, speed_of_right, time_of_running;
    struct tracksRecording(*link_to_next), (*link_to_last);
} LinkNode_for_tracks_recording, *LinkList_for_tracks_recording;

LinkList_for_tracks_recording track_recording;
LinkNode_for_tracks_recording *pointer_of_the_last_record;
int the_max_number_of_times_of_recording = 200;
int the_number_of_times_of_recording = 0;

void initLinkList_for_tracks_recording()
{
    track_recording = (LinkList_for_tracks_recording)malloc(sizeof(LinkList_for_tracks_recording));
    track_recording->link_to_last = 0;
    pointer_of_the_last_record = track_recording;
}

int Insert_to_end_of_LinkList_for_tracks_recording(int left_speed, int right_speed, int time_of_running)
{
    if (the_number_of_times_of_recording == the_max_number_of_times_of_recording) //Remove the first LinkNode.
    {
        LinkNode_for_tracks_recording *p;
        p = track_recording;
        track_recording = track_recording->link_to_next;
        //printf("----%d------\n", p->data);
        free(p);
        the_number_of_times_of_recording--;
    }

    LinkNode_for_tracks_recording *q, *p = track_recording;
    q = (LinkList_for_tracks_recording)malloc(sizeof(LinkList_for_tracks_recording));
    while (p->link_to_next != NULL)
    {
        p = p->link_to_next;
    }
    q->speed_of_left = left_speed;
    q->speed_of_right = right_speed;
    q->time_of_running = time_of_running;
    q->link_to_next = 0;
    q->link_to_last = p;
    p->link_to_next = q;
    the_number_of_times_of_recording++;
    pointer_of_the_last_record = q;

    return 1;
}

void Clean_up_track_recording()
{
    LinkList_for_tracks_recording p = track_recording->link_to_next;
    track_recording = 0;
    int i;
    for (i = 0; i < the_number_of_times_of_recording - 1; i++)
    {
        LinkList_for_tracks_recording q = p;
        p = p->link_to_next;
        free(q);
    }
}

void go_back_as_records()
{
    LinkNode_for_tracks_recording *p = pointer_of_the_last_record;
    int i;
    for (i = 0; i < the_number_of_times_of_recording; i++)
    {
        motor(left_wheel_number, -(p->speed_of_left));
        motor(right_wheel_number, -(p->speed_of_right));
        msleep(p->time_of_running);
        p = p->link_to_last;
    }
}

void motor_record(int left_speed, int right_speed, int time_of_running)
{
    set_motor(left_speed, right_speed, time_of_running);
    Insert_to_end_of_LinkList_for_tracks_recording(left_speed, right_speed, time_of_running);
} */

/* ----------------------------------Move forward---------------------------------- */
/*Speed is char from 1-100.                         */
/*If speed is greater than 0 is running forward.    */
/*If speed is less than 0 is running backward.      */
void move_forward(char speed, int time_of_running)
{
    motor(left_wheel_number, speed);
    motor(right_wheel_number, speed);
    msleep(time_of_running);
}

/* void move_forward(char speed, int time_of_running)
{
    if (use_track_recording)
    {
        motor_record(speed, speed, time_of_running);
    }
    else
    {
        motor(left_wheel_number, speed);
        motor(right_wheel_number, speed);
        msleep(time_of_running);
    }
} */

/*Set two motors' each speed and running time.*/
/*If time_of_running is 0, no running time.*/
void set_motor(int left_wheel_speed, int right_wheel_speed, int time_of_running)
{
    motor(left_wheel_number, left_wheel_speed);
    motor(right_wheel_number, right_wheel_speed);
    msleep(time_of_running);
}

/* ----------------------------------Stop the Wheels---------------------------------- */
void stop_running()
{
    set_motor(0, 0, 0);
}
/* ----------------------------------Change direction---------------------------------- */
/*If degrees greater than 0 is turning left. */
/*If degrees less than 0 is turning right.   */
void change_direction(int degrees)
{
    if (degrees >= 0)
    {
        motor_record(-100, 100, degrees * angle_ratio);
    }
    else
    {
        motor_record(100, -100, degrees * angle_ratio);
    }
}
/* void change_direction(int degrees)
{
    if (use_track_recording)
    {
        if (degrees >= 0)
        {
            set_motor(-100, 100, degrees * angle_ratio);
        }
        else
        {
            set_motor(100, -100, degrees * angle_ratio);
        }
    }
    else
    {
        if (degrees >= 0)
        {
            motor_record(-100, 100, degrees * angle_ratio);
        }
        else
        {
            motor_record(100, -100, degrees * angle_ratio);
        }
    }
} */
/* ----------------------------------Move from informations from files---------------------------------- */
/*Form of file per line: "number of direction(int degrees)" "running speed(char speed)" "time of running(int time)"\n. */
/*If degrees greater than 0 is turning left.        */
/*If degrees less than 0 is turning right.          */
/*Speed is char from 1-100.                         */
/*If speed is greater than 0 is running forward.    */
/*If speed is less than 0 is running backward.      */
int move_from_file()
{
    FILE *file_of_movements = fopen("Input_of_movements.text", "a+");
    if (!feof(file_of_movements))
    {
        return 0;
    }

    int degrees, time;
    char speed;
    do
    {
        fscanf(file_of_movements, "%d %c %d", &degrees, &speed, &time);
        change_direction(degrees);
        move_forward(speed, time);
    } while (feof(file_of_movements));

    return 1;
}
/* ----------------------------------Follow the Object---------------------------------- */
/*If lose object, wait until find the object agian. */
void follow_object(int object_number)
{
    camera_open_black();
    camera_update();
    printf("%d\n", get_object_center_y(0, object_number));
    while (get_object_center_y(0, object_number) < 110)
    {
        //printf("%d\n", get_object_center_y(0, object_number));
        camera_update();
        int object_center_x = get_object_center_x(0, object_number);
        if (get_object_center_y(0, object_number) < 60)
        {
            if (object_center_x > 80)
            {
                set_motor(100, 50, 0);
            }
            else if (object_center_x < 80 && object_center_x > 0)
            {
                set_motor(50, 100, 0);
            }
            else if (object_center_x == 80)
            {
                set_motor(100, 100, 0);
            }
            else
            {
                set_motor(0, 0, 0);
            }
        }
        else
        {
            if (object_center_x > 80)
            {
                set_motor(50, 10, 0);
            }
            else if (object_center_x < 80 && object_center_x > 0)
            {
                set_motor(10, 50, 0);
            }
            else
            {
                set_motor(30, 30, 0);
            }
        }
    }

    camera_close();
}
/* void follow_object(int object_number)
{
    camera_open_black();
    camera_update();
    printf("%d\n", get_object_center_y(0, object_number));
    if (use_track_recording)
    {
        while (get_object_center_y(0, object_number) < 110)
        {
            //printf("%d\n", get_object_center_y(0, object_number));
            camera_update();
            int object_center_x = get_object_center_x(0, object_number);
            if (get_object_center_y(0, object_number) < 60)
            {
                if (object_center_x > 80)
                {
                    motor_record(100, 50, 50);
                }
                else if (object_center_x < 80 && object_center_x > 0)
                {
                    motor_record(50, 100, 50);
                }
                else if (object_center_x == 80)
                {
                    motor_record(100, 100, 50);
                }
                else
                {
                    set_motor(0, 0, 0);
                }
            }
            else
            {
                if (object_center_x > 80)
                {
                    motor_record(50, 10, 50);
                }
                else if (object_center_x < 80 && object_center_x > 0)
                {
                    motor_record(10, 50, 50);
                }
                else
                {
                    motor_record(30, 30, 50);
                }
            }
        }
    }
    else
    {
        while (get_object_center_y(0, object_number) < 110)
        {
            //printf("%d\n", get_object_center_y(0, object_number));
            camera_update();
            int object_center_x = get_object_center_x(0, object_number);
            if (get_object_center_y(0, object_number) < 60)
            {
                if (object_center_x > 80)
                {
                    set_motor(100, 50, 0);
                }
                else if (object_center_x < 80 && object_center_x > 0)
                {
                    set_motor(50, 100, 0);
                }
                else if (object_center_x == 80)
                {
                    set_motor(100, 100, 0);
                }
                else
                {
                    set_motor(0, 0, 0);
                }
            }
            else
            {
                if (object_center_x > 80)
                {
                    set_motor(50, 10, 0);
                }
                else if (object_center_x < 80 && object_center_x > 0)
                {
                    set_motor(10, 50, 0);
                }
                else
                {
                    set_motor(30, 30, 0);
                }
            }
        }
    }
    camera_close();
} */

/* -----------------------------------Movement of servo----------------------------------- */
void set_arm(int degree)
{
    set_servo_position(arm_servo_number, degree);
}

void set_hand(int degree)
{
    set_servo_position(hand_servo_number, degree);
}

void catch_up_object()
{
    set_arm(arm_down_servo_positon);
    msleep(300);
    set_hand(hand_closed_position);
    msleep(300);
    set_arm(arm_up_servo_position);
}

void put_down_object()
{
    set_arm(arm_down_servo_positon);
    msleep(300);
    set_hand(hand_open_position);
    set_arm(arm_up_servo_position);
}

/*Percentage is from 0 to 100;  */
/*0 is lowest, 100 is highest;  */
void set_arm_position_with_two_parts(int percentage)
{
    int first_part_range = arm_up_servo_part_1_position - arm_down_servo_part_1_position;
    int second_part_range = arm_up_servo_part_2_position - arm_down_servo_part_2_position;
    set_servo_position(arm_servo_part_1_number, first_part_range * percentage / 100);
    set_servo_position(arm_servo_part_2_number, second_part_range * percentage / 100);
};
/* -----------------------------------Reset every part---------------------------------- */
/*Wheels stop.               */
/*Camera face forward.      */
/*Arm up.                   */
/*Hnad close.               */
void initBot()
{
    set_motor(0, 0, 0);
    //set_servo_position(camera_servo_number, camera_forward_servo_position);
    set_servo_position(arm_servo_number, arm_down_servo_positon);
    set_servo_position(hand_servo_number, hand_open_position);
}
/* -----------------------------------Inset Programs----------------------------------- */
void catch_object(int object_number)
{
    initBot();
    follow_object(object_number);
    catch_up_object();
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DataBase for C Programing~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* ----------------------------------String---------------------------------------- */
/*  --Length_CharString(char *) has been tested. In January 11, 2020-- */
int Length_CharString(char *p)
{
    int i = 0;
    while (p[i] != '\0')
    {
        i++;
    }
    return i;
}
/* ----------------------------------LinkList----------------------------------------*/

/*  --CreatLinkList(int) has been tested. In January 11, 2020-- */
LinkList CreatLinkList(int amount_of_LinkNodes)
{
    LinkList pNew = NULL, pTail = NULL;
    LinkList pHead = (LinkList)malloc(sizeof(LinkNode));
    if (pHead == NULL)
    {
        printf("Memory setting ERROR;\n");
        exit(1);
    }
    pHead->data = 0;
    pHead->link = NULL;
    pTail = pHead;
    int i;
    for (i = 1; i < amount_of_LinkNodes; i++)
    {
        pNew = (LinkList)malloc(sizeof(LinkNode));
        if (pNew == NULL)
        {
            printf("Memory setting ERROR;\n");
            exit(1);
        }
        pNew->data = 0;
        pNew->link = NULL;
        pTail->link = pNew;
        pTail = pNew;
    }
    return pHead;
}

/*  --LinkNode *Locate(LinkList, int) has been tested. In January 11, 2020--   */
LinkList Locate(LinkList(*first), int i)
{
    if (i < 0)
    {
        printf("The number is not available;     --From Locate(LinkList, int)\n");
        return NULL;
    }

    LinkNode *p = (*first);
    int k = 0;
    while (p != NULL && k < i)
    {
        p = p->link;
        k++;
    }
    if (p == NULL || k < i)
    {
        printf("The number is not available;    --From Locate(LinkList, int)\n");
        return NULL;
    }
    return p;
}

/*  "LinkList *first"   is the first_list_node's point.                                                       */
/*  "int i"     is the place that you want new_node to be among the link_list. before the link_list is "0".     */
/*  "DataType x"    is the int_number you want to put into the new_link_node.                                  */
/*  --Insert_LinkNode(LinkList, int, DataType) has been tested. In January 11, 2020--   */
int Insert_LinkNode(LinkList(*first), int i, DataType x)
{
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
    newNode->data = x;
    if (i == 0)
    {
        newNode->link = (*first);
        (*first) = newNode;
    }
    else
    {
        LinkNode *pHead;
        pHead = Locate(first, i - 1);
        newNode->link = pHead->link;
        pHead->link = newNode;
    }
    return 1;
}

/*  --Insert_to_end_LinkList(LinkList, DataType) has been tested. In January 11, 2020-- */
int Insert_to_end_of_LinkList(LinkList(*first), DataType x)
{
    LinkNode *q, *p = (*first);
    q = (LinkList)malloc(sizeof(LinkList));
    while (p->link != NULL)
    {
        p = p->link;
    }
    q->data = x;
    p->link = q;
    return 1;
}

/*  --Remove_LinkNode(LinkList, int) has been tested. In January 11, 2020-- */
int Remove_LinkNode(LinkList(*first), int i)
{
    LinkNode *p;
    if (i == 0)
    {
        p = (*first);
        (*first) = (*first)->link;
        //printf("----%d------\n", p->data);
        free(p);
        return 1;
    }

    LinkNode *q;
    p = Locate(first, i - 1);
    if (p == NULL)
    {
        printf("The number is not available;    --From Remove_linkNode(LinkList, int)\n");
        return 0;
    }
    q = p->link;
    p->link = q->link;
    free(q);
    return 1;
}

/*  --String_to_LinkList(int, int) has been tested. In January 11, 2020-- */
LinkList String_to_LinkList(int *p, int length)
{
    LinkList pHead;
    LinkNode *pTail, *pNew;
    pHead = (LinkNode *)malloc(sizeof(LinkNode));
    pHead->data = p[0];
    pTail = pHead;
    int i;
    for (i = 1; i < length; i++)
    {
        pNew = (LinkNode *)malloc(sizeof(LinkNode));
        pNew->data = p[i];
        pTail->link = pNew;
        pTail = pNew;
    }
    return pHead;
}

/*  --Printf_LinkList(LinkList) has been tested. In January 11, 2020-- */
void Printf_LinkList(LinkList x)
{
    int i = 0;
    while (x != NULL)
    {
        printf("%d", x->data);
        x = x->link;
    }
}

/* ----------------------------------END----------------------------------------*/

/* ----------------------------------Stack----------------------------------------*/

/*Initialize the SeqStack.*/
void InitStack(SeqStack(*S))
{
    (*S).elem = (SElemType *)malloc(initSize * sizeof(SElemType));
    if ((*S).elem == NULL)
    {
        printf("Memory setting ERROR;\n");
        exit(1);
    }
    (*S).maxSize = initSize;
    (*S).top = -1;
}

int Push(SeqStack *S, DataType x)
{
    if ((*S).top == (*S).maxSize - 1)
    {
        return 0;
    }
    (*S).elem[++(*S).top] = x;
    return 1;
}

int Pop(SeqStack(*S), SElemType *x)
{
    if ((*S).top == -1)
        return 0;
    (*x) = (*S).elem[(*S).top--];
    return 1;
}

int GetTop(SeqStack *S)
{
    if ((*S).top == -1)
        return 0;
    return (*S).elem[(*S).top];
}

/*Check if the stack is empty.                          */
/*If the stack is empty return 1; Otherwise return 0.   */
int StackEmpty(SeqStack(*S))
{
    return (*S).top == 1;
}

/*Check if the stack is full.*/
/*If the stack is full return 1; Otherwise return 0.    */
int StackFull(SeqStack(*S))
{
    return (*S).top == (*S).maxSize;
}

/*Return the size of the stack.     */
/*If the stack is empty return 0.   */
int StackSize(SeqStack(*S))
{
    return (*S).top + 1;
}

/*
FILE *fg = fopen("", "wr");
fscanf(fg, "%",&);
*/