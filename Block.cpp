#include "Block.h"

Block::Block() {
    x = 0;
    y = 4;
}

Block::Block(BlockMap e, int width) : width(width) {
    x = 0;
    y = 4;
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            element[i][j] = e[i][j];
            backup[i][j] = e[i][j];
        }
    }
}

void Block::Reset() {
    x = 0;
    y = 4;
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            element[i][j] = backup[i][j];
        }
    }
}

void Block::LinkToMap(GameMap& l) {
    Map = &l;
}

bool Block::CheckCollision() {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            if (x + i >= 0 && y + j >= 0 && x + i < Map->size() && y + j < (*Map)[0].size() && element[i][j] && (*Map)[i + x][j + y]) {
                color(BLACK, WHITE);
                return true;
            }
        }
    }
    return false;
}

void Block::HideBlock() {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            if (element[i][j]) {
                gotoxy(j + y, i + x);
                color(WHITE, WHITE);
                printf("  ");
            }
        }
    }
}

void Block::ShowBlock() {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            if (element[i][j]) {
                gotoxy(j + y, i + x);
                color(WHITE, RED);
                printf("  ");
            }
        }
    }
}

void Block::PrintBlock(int y, int x) {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            gotoxy(j + y, i + x);
            if (element[i][j]) {
                color(WHITE, RED);
            } else {
                color(WHITE, WHITE);
            }
            printf("  ");
        }
    }
}

bool Block::VertivalMove(int d) {
    HideBlock();
    x += d;
    if (CheckCollision()) {
        x -= d;
        ShowBlock();
        return true;
    }
    ShowBlock();
    return false;
}

void Block::HorizontalMove(int d) {
    HideBlock();
    y += d;
    if (CheckCollision()) {
        y -= d;
    }
    ShowBlock();
}

void Block::Rotate() {
    HideBlock();
    BlockMap cur;
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            cur[i][j] = element[i][j];
        }
    }
    for (int i = 4 - width; i < 4; i ++) {
        for (int j = 0; j < width; j ++) {
            element[3 - j][width - 4 + i] = cur[i][j];
        }
    }
    if (CheckCollision()) {
        for (int i = 0; i < 4; i ++) {
            for (int j = 0; j < 4; j ++) {
                element[i][j] = cur[i][j];
            }
        }
    }
    ShowBlock();
}

void Block::SetDown() {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            if (element[i][j]) {
                (*Map)[i + x][j + y] = 1;
            }
        }
    }
}
