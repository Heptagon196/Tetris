#ifndef CONIOPLUS_H
#define CONIOPLUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#if defined(linux) || defined(__APPLE__)

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define LIGHT_GRAY 37
#define DARK_GRAY 90
#define LIGHT_RED 91
#define LIGHT_GREEN 92
#define LIGHT_YELLOW 93
#define LIGHT_BLUE 94
#define LIGHT_MAGENTA 95
#define LIGHT_CYAN 96
#define WHITE 97

bool kbhit(); // 检测是否有键按下
int getch(); // 获取用户按下的键

#else

#include <conio.h>
#include <windows.h>
#include <time.h>

#define BLACK 0
#define RED 4
#define GREEN 2
#define YELLOW 6
#define BLUE 1
#define MAGENTA 5
#define CYAN 3
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_RED 12
#define LIGHT_GREEN 10
#define LIGHT_YELLOW 14
#define LIGHT_BLUE 9
#define LIGHT_MAGENTA 13
#define LIGHT_CYAN 11
#define WHITE 15

#endif

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 20

void move_cursor_origin(int x, int y); // 移动至 x, y
void move_cursor(int x, int y); // 移动至 2 * x - 1, y。终端中字符高是宽的 2 倍，故用两个字符为一个单位。
void hide_cursor();
void show_cursor();
void set_color(int foreground_color, int background_color);
void clear_screen();
void clear_color();
double get_time(); // 获取程序已运行时间
int get_random_color();

#endif
