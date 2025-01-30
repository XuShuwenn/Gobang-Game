//本模块为棋盘模块，包含了棋盘的初始化，打印，判断输赢等函数
#include "Gobang.h"
#include"Board.h"
//判断输赢函数	
bool judge_result() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            // 如果当前位置的棋子为1或2，进行检查
            if (aRecordBoard[i][j] != NONE) {
                int color = aRecordBoard[i][j];
                // 水平检查
                if (j + 4 < SIZE && aRecordBoard[i][j + 1] == color && aRecordBoard[i][j + 2] == color && aRecordBoard[i][j + 3] == color && aRecordBoard[i][j + 4] == color) {
                    return true;
                }
                // 垂直检查
                if (i + 4 < SIZE && aRecordBoard[i + 1][j] == color && aRecordBoard[i + 2][j] == color && aRecordBoard[i + 3][j] == color && aRecordBoard[i + 4][j] == color) {
                    return true;
                }
                // 主对角线检查（从左上到右下）
                if (i + 4 < SIZE && j + 4 < SIZE && aRecordBoard[i + 1][j + 1] == color && aRecordBoard[i + 2][j + 2] == color && aRecordBoard[i + 3][j + 3] == color && aRecordBoard[i + 4][j + 4] == color) {
                    return true;
                }
                // 副对角线检查（从右上到左下）
                if (i + 4 < SIZE && j - 4 >= 0 && aRecordBoard[i + 1][j - 1] == color && aRecordBoard[i + 2][j - 2] == color && aRecordBoard[i + 3][j - 3] == color && aRecordBoard[i + 4][j - 4] == color) {
                    return true;
                }
            }
        }
    }
    return false;
}
//通过双重循环，将aRecordBoard清0
void initRecordBorard(void) {

    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            aRecordBoard[i][j] = 0;
        }
    }
}
//打印棋盘函数
void DrawChessBoard() {
    printf("\n  0 1 2 3 4 5 6 7 8 9 1011121314\n");
    for (int j = 0; j < SIZE; j++) {
        if (j <= 9)printf("%d ", j);
        else printf("%d", j);
        for (int i = 0; i < SIZE; i++) {
            if (ChessBoard[i][j] == 7)printf("┌-");
            if (ChessBoard[i][j] == 8)printf("┬-");
            if (ChessBoard[i][j] == 9)printf("┐");
            if (ChessBoard[i][j] == 4)printf("├-");
            if (ChessBoard[i][j] == 5)printf("┼-");
            if (ChessBoard[i][j] == 6)printf("┤");
            if (ChessBoard[i][j] == 1)printf("└-");
            if (ChessBoard[i][j] == 2)printf("┴-");
            if (ChessBoard[i][j] == 3)printf("┘");
            if (ChessBoard[i][j] == 10 && i < SIZE - 1)printf("○-");
            if (ChessBoard[i][j] == 10 && i == SIZE - 1)printf("○");
            if (ChessBoard[i][j] == 11 && i < SIZE - 1)printf("●-");
            if (ChessBoard[i][j] == 11 && i == SIZE - 1)printf("●");
        }
        printf("\n");
    }
}
//初始化显示棋盘函数
void RebuildChessBoard() {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            if (i == 0 && j == 0)ChessBoard[i][j] = 7;
            if (j == 0 && i < 14 && i >= 1)ChessBoard[i][j] = 8;
            if (i == 14 && j == 0)ChessBoard[i][j] = 9;
            if (i == 0 && j < 14 && j >= 1)ChessBoard[i][j] = 4;
            if (i < 14 && i >= 1 && j < 14 && j >= 1)ChessBoard[i][j] = 5;
            if (i == 14 && j < 14 && j >= 1)ChessBoard[i][j] = 6;
            if (i == 0 && j == 14)ChessBoard[i][j] = 1;
            if (j == 14 && i < 14 && i >= 1)ChessBoard[i][j] = 2;
            if (i == 14 && j == 14)ChessBoard[i][j] = 3;
        }
    }
}
//更新显示棋盘函数
void RecordToChessBoard() {
    RebuildChessBoard();
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            if (aRecordBoard[i][j] != 0)ChessBoard[i][j] = aRecordBoard[i][j] + 9;
        }
    }
}
//判断落子位置是否合法
bool IsValidPosition(int x, int y)
{
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)return true;
    else return false;
}
