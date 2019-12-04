#include <cstdio>
#include <iostream>
#include "Block.h"
using namespace std;

vector<Block> blocks = {
    Block((BlockMap){
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
    }, 4),
    Block((BlockMap){
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
    }, 3),
    Block((BlockMap){
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
    }, 3),
    Block((BlockMap){
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 1, 0, 0},
    }, 2),
    Block((BlockMap){
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
    }, 3),
    Block((BlockMap){
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
    }, 3),
    Block((BlockMap){
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
    }, 3),
};

vector<vector<int> > Map(24, vector<int>(14, 0));
int score = 0;

void ClearMap() {
    int l;
    bool clear;
    for (int i = Map.size() - 3; i >= 5; i --) {
        clear = true;
        l = i;
        for (int j = 2; j < Map[0].size() - 2; j ++) {
            if (!Map[i][j]) {
                clear = false;
                break;
            }
        }
        if (clear) {
            break;
        }
    }
    if (clear) {
        for (int i = l; i >= 5; i --) {
            for (int j = 2; j < Map[0].size() - 2; j ++) {
                Map[i][j] = Map[i - 1][j];
            }
        }
        score ++;
        ClearMap();
    }
}

void PrintMap() {
    for (int i = 1; i < Map.size() - 1; i ++) {
        for (int j = 1; j < Map[0].size() - 1; j ++) {
            gotoxy(j, i);
            if (Map[i][j]) {
                if (i == 1 || j == 1 || i == Map.size() - 2 || j == Map[0].size() - 2) {
                    color(WHITE, GREEN);
                } else {
                    color(WHITE, RED);
                }
            } else {
                color(WHITE, WHITE);
            }
            printf("  ");
        }
    }
}

Block* NewBlock() {
    return &blocks[rand() % blocks.size()];
}

int main() {
    srand(time(NULL));
    hidecursor();
#if defined(linux) || defined(__APPLE__)
#else
    system("mode con lines=30");
    system("mode con cols=30");
#endif
    for (int i = 0; i < Map.size(); i ++) {
        Map[i][1] = Map[i][Map[0].size() - 2] = 1;
    }
    for (int j = 0; j < Map[0].size(); j ++) {
        Map[1][j] = Map[Map.size() - 2][j] = 1;
    }
    int L = Map[0].size() - 2;
    for (int i = 1; i < Map.size() - 1; i ++) {
        for (int j = L; j <= L + 7; j ++) {
            gotoxy(j, i);
            if (i == 1 || i == Map.size() - 2 || j == Map[0].size() + 5) {
                color(WHITE, GREEN);
            } else {
                color(WHITE, WHITE);
            }
            printf("  ");
        }
    }
    PrintMap();
    gotoxy(L + 3, Map.size() / 2 - 8);
    color(BLACK, WHITE);
    puts("Next");
    gotoxy(L + 2, Map.size() / 2 - 1);
    color(BLACK, WHITE);
    puts(" Points");
    gotoxy(L + 3, Map.size() / 2 + 1);
    color(BLACK, WHITE);
    printf(" %d  ", score);
    Block* block = NewBlock();
    Block* next_block = NewBlock();
    next_block->PrintBlock(L + 2, Map.size() / 2 - 7);
    block->LinkToMap(Map);
    block->ShowBlock();
    int ch;
    int cnt = 0;
    while ((ch = readkey(0.1)) != 'q') {
        if (ch == 'a') {
            block->HorizontalMove(-1);
        }
        if (ch == 'd') {
            block->HorizontalMove(1);
        }
        if (ch == 's') {
            cnt = 2;
        }
        if (ch == ' ') {
            block->Rotate();
        }
        cnt ++;
        cnt %= 3;
        if (cnt && ch != '\n') {
            continue;
        }
        LOOP:;
        if (block->VertivalMove(1)) {
            block->SetDown();
            block->Reset();
            ClearMap();
            PrintMap();
            gotoxy(L + 3, Map.size() / 2 + 1);
            color(BLACK, WHITE);
            printf(" %d  ", score);
            block = next_block;
            next_block = NewBlock();
            next_block->PrintBlock(L + 2, Map.size() / 2 - 7);
            block->LinkToMap(Map);
            block->ShowBlock();
            if (block->CheckCollision()) {
                color(BLACK, WHITE);
                puts("Game over!");
                break;
            }
        } else if (ch == '\n') {
            goto LOOP;
        }
    }
    gotoxy(1, Map.size());
    showcursor();
    return 0;
}
