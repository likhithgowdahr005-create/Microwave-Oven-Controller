#include <xc.h>
#include "clcd.h"
#include "micro_oven.h"
#include "matrix_keypad.h"

unsigned char min, sec;
unsigned int temp;
extern unsigned char screen_flag;
unsigned char reset_flag;
unsigned char pre_heat;

void display_power_screen(void)
{
    for (unsigned char i = 0; i < 16; i++)
    {
        clcd_putch(BAR, LINE1(i));
        __delay_ms(100);
    }
    clcd_print("Powering ON", LINE2(3));
    clcd_print("Microwave Oven", LINE3(2));
    for (unsigned char i = 0; i < 16; i++)
    {
        clcd_putch(BAR, LINE4(i));
        __delay_ms(100);
    }
    __delay_ms(1000);
}

void display_modes(void)
{
    clcd_print("1. Micro", LINE1(3));
    clcd_print("2. Grill", LINE2(3));
    clcd_print("3. Convection", LINE3(3));
    clcd_print("4. Start", LINE4(3));
}

void set_time(unsigned char key, unsigned char reset_flag)
{
    static unsigned char sec_digits = 0;
    static unsigned char min_digits = 0;
    static unsigned char edit_field = 0;   // 0 = seconds, 1 = minutes
    static unsigned char delay = 0, display_blank = 0;

    TMR2ON = 0;   // timer OFF while setting time

    /* RESET WHEN ENTERING TIME SET */
    if (reset_flag == RESET_FLAG)
    {
        sec = 0;
        min = 0;
        sec_digits = 0;
        min_digits = 0;
        edit_field = 0;   // start with seconds
    }

    /* DISPLAY */
    clcd_print("SET TIME (MM:SS)", LINE1(0));
    clcd_print("TIME:", LINE2(0));
    clcd_putch(':', LINE2(7));
    clcd_print("*:CLEAR  #:START", LINE4(0));

    /* HANDLE KEY */
    if (key != ALL_RELEASED)
    {
        /* DIGIT */
        if (key <= 9)
        {
            if (edit_field == 0)          // seconds
            {
                sec = (sec % 10) * 10 + key;
                sec_digits++;

                if (sec_digits == 2)      // AUTO MOVE to minutes
                    edit_field = 1;
            }
            else if (edit_field == 1)     // minutes
            {
                if (min_digits < 2)
                {
                    min = (min % 10) * 10 + key;
                    min_digits++;
                }
            }
        }

        /* CLEAR */
        else if (key == '*')
        {
            sec = 0;
            min = 0;
            sec_digits = 0;
            min_digits = 0;
            edit_field = 0;
        }

        /* CONFIRM */
        else if (key == '#')
        {
            FAN = ON;
            TMR2ON = 1;
            clear_screen();
            screen_flag = DISPLAY_TIME;
            return;
        }
    }

    /* BLINK EFFECT */
    if (++delay == 10)
    {
        delay = 0;
        display_blank = !display_blank;
    }

    /* DISPLAY TIME */
    if (display_blank)
    {
        if (edit_field == 0)
        {
            clcd_putch(' ', LINE2(8));
            clcd_putch(' ', LINE2(9));
        }
        else
        {
            clcd_putch(' ', LINE2(5));
            clcd_putch(' ', LINE2(6));
        }
    }
    else
    {
        clcd_putch(min / 10 + '0', LINE2(5));
        clcd_putch(min % 10 + '0', LINE2(6));
        clcd_putch(sec / 10 + '0', LINE2(8));
        clcd_putch(sec % 10 + '0', LINE2(9));
    }
}

void set_temp(unsigned char key, unsigned char reset_flag)
{
    static unsigned char key_count = 0;
    static unsigned char delay = 0;
    static unsigned char display_blank = 0;

    if (reset_flag == RESET_FLAG)
    {
        temp = 0;
        key_count = 0;
        clear_screen();
    }

    /* Display format */
    clcd_print("SET TEMP <*C>", LINE1(0));
    clcd_print("TEMP=", LINE2(0));
    clcd_print("*:CLEAR #:ENTER", LINE4(0));

    /* ---- READ KEYPAD (FIX) ---- */
    if (key != '*' && key != '#' && key != ALL_RELEASED)
    {
        if (key_count < 3)   // max 180
        {
            temp = temp * 10 + key;
            key_count++;
        }
    }
    else if (key == '*')
    {
        temp = 0;
        key_count = 0;
    }
    else if (key == '#')
    {
        if (temp > 180)
            temp = 180;

        pre_heat = 60;
        TMR2ON = 1;
        clear_screen();
        screen_flag = PRE_HEAT_SCREEN;  // go to preheat screen
        return;
    }

    /* Blink temperature */
    if (++delay == 10)
    {
        delay = 0;
        display_blank = !display_blank;
    }

    if (display_blank)
    {
        clcd_putch(' ', LINE2(7));
        clcd_putch(' ', LINE2(8));
        clcd_putch(' ', LINE2(9));
    }
    else
    {
        clcd_putch((temp / 100) + '0', LINE2(7));
        clcd_putch((temp / 10) % 10 + '0', LINE2(8));
        clcd_putch((temp % 10) + '0', LINE2(9));
    }
}


void display_time(void)
{
    clcd_print("TIME = ", LINE1(1));
    clcd_putch(min / 10 + '0', LINE1(9));
    clcd_putch(min % 10 + '0', LINE1(10));
    clcd_putch(':', LINE1(11));
    clcd_putch(sec / 10 + '0', LINE1(12));
    clcd_putch(sec % 10 + '0', LINE1(13));

    clcd_print("4.START/RESUME", LINE2(2));
    clcd_print("5.PAUSE", LINE3(2));
    clcd_print("6.STOP", LINE4(2));

    if (min == 0 && sec == 0)
    {
        clear_screen();
        TMR2ON = 0;
        FAN = 0;
        clcd_print("TIME UP!!!", LINE2(4));
        clcd_print("Enjoy your Meal", LINE3(0));
        __delay_ms(2000);
        clear_screen();
        screen_flag = MENU_SCREEN;
    }
}

void heat_food(void)
{
    sec = 30;
    min = 0;
    TMR2ON = 1;
    FAN = 1;
    screen_flag = DISPLAY_TIME;
}
void display_preheat(void)
{
    clcd_print("PRE-HEATING", LINE1(2));
    clcd_print("TIME Rem :", LINE3(0));

    clcd_putch(pre_heat / 10 + '0', LINE3(10));
    clcd_putch(pre_heat % 10 + '0', LINE3(11));
    clcd_putch('s', LINE3(12));

   if (pre_heat == 0)
{
    TMR2ON = 0;
    TMR2IF = 0;          // stop pending timer interrupt

    sec = 0;
    min = 0;
    clear_screen();
    screen_flag = MICRO_MODE;
    reset_flag = RESET_FLAG;
}
}
