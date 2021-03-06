#include "Block.h"

int GetRandomBlockColor() {
    int c = WHITE;
    while (c == WHITE || c == BLACK || c == GREEN) {
        c = get_random_color();
    }
    return c;
}

Block::Block() {
    x = 0;
    y = 4;
    color = GetRandomBlockColor();
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
    color = GetRandomBlockColor();
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
            if (x + i >= 0 && y + j >= 0 && x + i < Map->size() && y + j < (*Map)[0].size() && element[i][j] && (*Map)[i + x][j + y].first) {
                set_color(BLACK, WHITE);
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
                move_cursor(j + y, i + x);
                set_color(WHITE, WHITE);
                printf("  ");
            }
        }
    }
}

void Block::ShowBlock() {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            if (element[i][j]) {
                move_cursor(j + y, i + x);
                set_color(WHITE, color);
                printf("  ");
            }
        }
    }
}

void Block::PrintBlock(int y, int x, int c) {
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            move_cursor(j + y, i + x);
            if (element[i][j]) {
                set_color(WHITE, c);
            } else {
                set_color(WHITE, WHITE);
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
                (*Map)[i + x][j + y].first = 1;
                (*Map)[i + x][j + y].second = color;
            }
        }
    }
}
