#ifndef HEPTAGON196_TETRIS_BLOCK_H
#define HEPTAGON196_TETRIS_BLOCK_H
#include <vector>
#include <memory>
#include "ConsoleIO.h"
typedef int BlockMap[4][4];
typedef std::vector<std::vector<std::pair<int, int> > > GameMap;

int GetRandomBlockColor();

class Block {
    private:
        BlockMap element;
        BlockMap backup;
        GameMap* Map;
        int width;
        int x, y;
    public:
        int color;
        Block(BlockMap e, int width);
        Block();
        void Reset();
        void LinkToMap(GameMap& l);
        bool CheckCollision();
        void HideBlock();
        void ShowBlock();
        void PrintBlock(int y, int x, int c);
        bool VertivalMove(int d);
        void HorizontalMove(int d);
        void Rotate();
        void SetDown();
};
#endif
