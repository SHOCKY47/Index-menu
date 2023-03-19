/*****************************************************************/
// /* Menu.c
//  *
//  *  Created on: 2023/3/7
//  *  Author: SHOCKY
//  *
//  >>本菜单适用于较为简单的基本调参，存在部分情况未充分考量的情况
//  >>但是由于适用场景为智能车项目，提供显示的物理载体为IPS200,因
//  >>此部分可能导致数组越界的情况可以忽略。
/*****************************************************************/

#include "Menu.h"

typedef struct
{
    int menu_id;                                        // 菜单索引号
    char menu_name[30];                                 // 菜单显示名称
    void (*menu_action)(float32 *param, char name[30]); // 子菜单执行函数
    float32 *param;                                     // 需要传入处理的参数
} menu_item;
// 由于IPS200 屏幕大小为240X180，逐飞提供默认字库大小为8X16，因此屏幕横向无法显示超过30个字符

menu_item *current_menu_item;

void menu_11(void)
{
    ips200_clear();
    key_flag_clear();
    while (!key3_flag)
    {
        ips200_show_string(1, 150, "PRESS KEY3 TO QUIT");
        ips200_displayimage03x(mt9v03x_image[0], IMGW, IMGH); // 显示原图像
        DrawBoarder(&g_Border);                               // 原边线
    }
    return;
}

void menu_12(void)
{
    ips200_clear();
    key_flag_clear();
    while (!key3_flag)
    {
        // 添加图像调参函数
    }
    return;
}

void menu_13(void)
{
    ips200_clear();
    key_flag_clear();
    while (!key3_flag)
    {
        // 添加图像调参函数
    }
    return;
}

void menu_14(void)
{
    ips200_clear();
    key_flag_clear();
    while (!key3_flag)
    {
        // 添加图像调参函数
    }
    return;
}
void menu_15(void)
{
    ips200_clear();
    key_flag_clear();
    while (!key3_flag)
    {
        // 添加图像调参函数
    }
    return;
}

void menu_16(void)
{
    ips200_clear();
    key_flag_clear();
    while (!key3_flag)
    {
        // 添加图像调参函数
    }
    return;
}

void menu_tuning(float32 *tuning, char name[30]) // 调参界面菜单
{
    char buf[30]; // 由于IPS200 屏幕大小为240X180，逐飞提供默认字库大小为8X16，因此屏幕横向无法显示超过30个字符
    char *menu_name = name;
    float32 level[4] = {0.01, 0.1, 1, 10};
    int current_level = 0;
    SEGGER_RTT_printf(0, "\r\n%s: %5.2f", menu_name, *tuning); // 调节挡位开关
    ips200_clear();
    ips200_show_string(1, 0, "Change_level:");
    sprintf(buf, "X%5.2f: ", level[current_level]);
    ips200_show_string(1, 30, buf);
    key_flag_clear();

    while (1)
    {
        if (key_switch())
        {
            if (key1_flag && current_level < 4)
            {
                current_level += 1;
            }
            else if (key2_flag && current_level > 0)
            {
                current_level -= 1;
            }
            else if (key3_flag)
            {
                ips200_clear();
                sprintf(buf, "%s: ", menu_name);
                ips200_show_string(1, 0, buf);
                sprintf(buf, "%5.2f", *tuning);
                ips200_show_string(1, 30, buf);
                key_flag_clear();
                while (1)
                {
                    if (key_switch())
                    {
                        if (key1_flag)
                        {
                            *tuning += level[current_level];
                        }
                        else if (key2_flag)
                        {
                            *tuning -= level[current_level];
                        }
                        else if (key3_flag)
                        {
                            return;
                        }
                        ips200_clear();
                        sprintf(buf, "%s: ", menu_name);
                        ips200_show_string(1, 0, buf);
                        sprintf(buf, "%5.2f", *tuning);
                        ips200_show_string(1, 30, buf);
                        key_flag_clear();
                    }
                }
            }

            ips200_clear();
            ips200_show_string(1, 0, "Change_level:");
            sprintf(buf, "X %5.2f: ", level[current_level]);
            ips200_show_string(1, 30, buf);
            key_flag_clear();
        }
    }
}

menu_item menu[] = {
    {1, "Image Mode", NULL, NULL},                                         // 图像模式
    {11, "Image Tuning1", menu_11, NULL},                                  // 显示原边线
    {12, "Image Tuning2", menu_12, NULL},                                  // 图像菜单2
    {13, "Image Tuning3", menu_13, NULL},                                  // 图像菜单3
    {14, "Image Tuning4", menu_14, NULL},                                  // 图像菜单4
    {15, "Image Tuning5", menu_15, NULL},                                  // 图像菜单5
    {16, "Image Tuning6", menu_16, NULL},                                  // 图像菜单6
    {17, "Back to Main", NULL, NULL},                                      // 回到主菜单
    {2, "Tuning Mode", NULL, NULL},                                        // 调参模式
    {21, "Motor Parameter", NULL, NULL},                                   // 电机参数调整
    {211, "Variable Integral", NULL, NULL},                                // 电机参数调整——变积分
    {2111, "Left Wheel", NULL, NULL},                                      // 电机参数调整——变积分——左轮
    {21111, "Left Wheel MOTOR.L_Max_I", menu_tuning, &MOTOR.L_Max_I},      // 电机参数调整——变积分——左轮Max_I
    {21112, "Left Wheel MOTOR.L_Ci ", menu_tuning, &MOTOR.L_Ci},           // 电机参数调整——变积分——左轮CI
    {21113, "Back to Main", NULL, NULL},                                   // 回到主菜单
    {2112, "Right Wheel", NULL, NULL},                                     // 电机参数调整——变积分——右轮
    {21121, "Right Wheel MOTOR.R_Max_I", menu_tuning, &MOTOR.R_Max_I},     // 电机参数调整——变积分——右轮Max_I
    {21122, "Right Wheel MOTOR.R_Ci", menu_tuning, &MOTOR.R_Ci},           // 电机参数调整——变积分——右轮CI
    {2113, "Back to Main", NULL, NULL},                                    // 回到主菜单
    {21123, "Back to Main", NULL, NULL},                                   // 回到主菜单
    {212, "Variable Ratio", NULL, NULL},                                   // 电机参数调整——变比例
    {2121, "Left Wheel", NULL, NULL},                                      // 电机参数调整——变比例——左轮
    {21211, "Left Wheel MOTOR.L_Bas_KP", menu_tuning, &MOTOR.L_Bas_KP},    // 电机参数调整——变比例——左轮Bas_KP
    {21212, "Left Wheel MOTOR.L_Gain_KP", menu_tuning, &MOTOR.L_Gain_KP},  // 电机参数调整——变比例——左轮Gain_KP
    {21213, "Left Wheel MOTOR.L_Cp", menu_tuning, &MOTOR.L_Cp},            // 电机参数调整——变比例——左轮Cp
    {21214, "Back to Main", NULL, NULL},                                   // 回到主菜单
    {2122, "Right Wheel", NULL, NULL},                                     // 电机参数调整——变比例——右轮
    {21222, "Right Wheel MOTOR.R_Bas_KP", menu_tuning, &MOTOR.R_Bas_KP},   // 电机参数调整——变比例——右轮Bas_KP
    {21222, "Right Wheel MOTOR.R_Gain_KP", menu_tuning, &MOTOR.R_Gain_KP}, // 电机参数调整——变比例——右轮Gain_KP
    {21223, "Right Wheel MOTOR.R_Cp", menu_tuning, &MOTOR.R_Cp},           // 电机参数调整——变比例——右轮Cp
    {21224, "Back to Main", NULL, NULL},                                   // 回到主菜单
    {2123, "Back to Main", NULL, NULL},                                    // 回到主菜单
    {213, "Back to Main", NULL, NULL},                                     // 回到主菜单
    {22, "Duoji Parameter", NULL, NULL},                                   // 舵机参数调整
    {221, "Variable Integral", NULL, NULL},                                // 舵机参数调整——变积分
    {2211, "Serve.Kp_Gain", menu_tuning, &Serve.Kp_Gain},                  // 舵机参数调整——变积分Kp_Gain
    {2212, "Serve.Base", menu_tuning, &Serve.Base},                        // 舵机参数调整——变积分Base
    {2213, "Back to Main", NULL, NULL},                                    // 回到主菜单
    {222, "Variable Ratio", NULL, NULL},                                   // 舵机参数调整——变比例
    {2221, "Serve.Kd_Gain", menu_tuning, &Serve.Kd_Gain},                  // 舵机参数调整——变比例Kd_Gain
    {2222, "Back to Main", NULL, NULL},                                    // 回到主菜单
    {223, "Back to Main", NULL, NULL},                                     // 回到主菜单
    {23, "Back to Main", NULL, NULL},                                      // 回到主菜单
    {3, "Departure Mode", NULL, NULL}                                      // 发车模式

};

bool have_sub_menu(int menu_id) // 查看是否存在子菜单
{
    for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
    {
        if (menu[i].menu_id / 10 == menu_id)
        {
            return true;
        }
    }
    return false;
}

int show_sub_menu(int parent_id, int highlight_col) // 显示子菜单，以及当前高亮菜单
{
    ips200_clear();
    int item_idx = 0;
    for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
    {
        if (menu[i].menu_id / 10 == parent_id)
        {
            if (item_idx == highlight_col)
            {
                current_menu_item = &menu[i];
                ips200_set_color(RGB565_RED, RGB565_BLACK);
            }
            else
            {
                ips200_set_color(RGB565_GREEN, RGB565_BLACK);
            }
            ips200_show_string(1, 30 * item_idx, menu[i].menu_name);
            item_idx++;
        }
    }
    return item_idx;
}

void Menu_Switch(void)
{

    int parent_menu_id = 0;
    int highlight_col = 0; // 设定高亮行号
    int menu_item_count = show_sub_menu(parent_menu_id, highlight_col);
    while (1)
    {
        if (key_switch()) // 读取按键函数
        {
            if (key1_flag && highlight_col > 0) // 按下按键1减少当前行数
            {
                highlight_col--;
            }
            else if (key2_flag && highlight_col < menu_item_count - 1) // 按下按键2增加当前行数
            {
                highlight_col++;
            }
            else if (key3_flag)
            {
                if (have_sub_menu(current_menu_item->menu_id))
                {
                    highlight_col = 0;
                    parent_menu_id = current_menu_item->menu_id;
                }
                else if (strcmp(current_menu_item->menu_name, "Back to Main") == 0) // 如果当前菜单为“Back to Main”，则返回主界面
                {
                    highlight_col = 0;
                    parent_menu_id = 0;
                }
                else if (current_menu_item->menu_action)
                {
                    current_menu_item->menu_action(current_menu_item->param, current_menu_item->menu_name);
                }
            }

            menu_item_count = show_sub_menu(parent_menu_id, highlight_col);
            key_flag_clear();
        }
    }
}
