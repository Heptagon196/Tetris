#include "ConsoleIO.h"

#if defined(linux) || defined(__APPLE__)
// 调用 linux api 实现 windows 下 conio.h 中部分函数

bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int getch() {
     struct termios tm, tm_old;
     int fd = 0, ch;
     if (tcgetattr(fd, &tm) < 0) {
          return -1;
     }
     tm_old = tm;
     cfmakeraw(&tm);
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
          return -1;
     }
     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
          return -1;
     }
     return ch;
}

// 使用终端控制码改变颜色、移动光标
void move_cursor_origin(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void move_cursor(int x, int y) {
    move_cursor_origin(2 * x - 1, y);
}

void hide_cursor() {
    printf("\033[?25l");
}

void show_cursor() {
    printf("\033[?25h");
}

void set_color(int foreground_color, int background_color) {
    printf("\033[%dm\033[%dm", background_color + 10, foreground_color);
}

void clear_screen() {
    system("clear");
}

void clear_color() {
    printf("\033[0m");
}

int get_random_color() {
    const int code[] = {30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96};
    return code[rand() % 16];
}

#else

#define color_calc(fg, bg) ((fg) + 16 * (bg))

// 调用 windows api
void move_cursor_origin(int x, int y) {
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void move_cursor(int x, int y) {
    move_cursor_origin(2 * x - 1, y);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void show_cursor() {
    CONSOLE_CURSOR_INFO cursor_info = {1, 25};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void set_color(int foreground_color, int background_color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_calc(foreground_color, background_color));
}

void clear_color() {
    set_color(WHITE, BLACK);
}

void clear_screen() {
    system("cls");
}

int get_random_color() {
    const int code[] = {0, 4, 2, 6, 1, 5, 3, 7, 8, 12, 10, 14, 9, 13, 11, 15};
    return code[rand() % 16];
}

#endif

double get_time() {
    return (double) clock() / CLOCKS_PER_SEC;
}

void sleep_for_milliseconds() {
}

