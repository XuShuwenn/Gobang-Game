//本模块为下棋功能实现函数
#include <iostream>
#include <string>
#include "AI.h"
#include "Gobang.h"
#include "Board.h"
#include "GoAChess.h"
//人人对战函数
void Human_vs_Human() {
    DrawChessBoard();
    std::cout << "\n人人对战开始，由黑棋先落子\n";
    int count = 1;
    while (true) {
        std::cout << "轮到黑棋下第" << count << "手棋：\n";
        Human_Black_go();
        count++;
        if (judge_result()) {
            std::cout << "黑棋胜利，游戏结束\n";
            break;
        }
        std::cout << "轮到白棋下第" << count << "手棋：\n";
        count++;
        Human_White_go();
        if (judge_result()) {
            std::cout << "白棋胜利，游戏结束\n";
            break;
        }
    }
}
//人机对战函数
void Human_vs_AI() {
    DrawChessBoard();
    int choice;
    std::cout << "\n人机对战开始，请玩家选择先后手:（输入1选择先手，输入2选择后手)\n";
    std::cin >> choice;
    std::cin.ignore();  // 用于清空缓冲区
    int count = 1;
    if (choice == 1) {
        while (true) {
            std::cout << "轮到黑棋下第" << count << "手棋：\n";
            Human_Black_go();
            count++;
            if (judge_result()) {
                std::cout << "黑棋胜利，游戏结束\n";
                break;
            }
            std::cout << "轮到白棋下第" << count << "手棋：\n";
            AI_White_go(count);
            count++;
            if (judge_result()) {
                std::cout << "白棋胜利，游戏结束\n";
                break;
            }
        }
    }
    else if (choice == 2) {
        while (true) {
            std::cout << "轮到黑棋下第" << count << "手棋：\n";
            AI_Black_go(count);
            count++;
            if (judge_result()) {
                std::cout << "黑棋胜利，游戏结束\n";
                break;
            }
            std::cout << "轮到白棋下第" << count << "手棋：\n";
            Human_White_go();
            count++;
            if (judge_result()) {
                std::cout << "白棋胜利，游戏结束\n";
                break;
            }
        }
    }
    else {
        std::cout << "输入形式有误！";
    }
}
//人类落黑棋函数
void Human_Black_go() {
    int x, y;
    std::cout << "请输入欲落黑子子坐标(_ _):";
    std::cin >> x >> y;
    std::cin.ignore();
    if (!IsValidPosition(x, y)) {
        std::cout << "输入形式错误，请重新输入\n";
        Human_Black_go();
        return;
    }
    if (aRecordBoard[x][y] != NONE) {
        std::cout << "该位置已有棋子，请重新落子！\n";
        Human_Black_go();
        return;
    }
    Collect_Information(x, y, BLACK);
    if (!judge_if_banhand(x, y, BLACK)) {
        std::cout << "黑棋走了双活三禁手，判定白棋胜利！";
        system("pause");
    }
    aRecordBoard[x][y] = BLACK;   // 黑子对应值1
    RecordToChessBoard();         // 标记新落子
    DrawChessBoard();
    // 判断是否悔棋
    std::cout << "是否希望悔棋？(Y/N)";
    char l = std::cin.get();
    if (l == 'Y' || l == 'y') {
        aRecordBoard[x][y] = NONE;
        RecordToChessBoard();
        DrawChessBoard();
        std::cout << "请慎重落子！";
        Human_Black_go();
    }
}
//人类落白棋函数
void Human_White_go() {
    int x, y;
    std::cout << "请输入欲落白子坐标(_ _):";
    std::cin >> x >> y;
    std::cin.ignore();
    if (!IsValidPosition(x, y)) {
        std::cout << "输入形式错误，请重新输入\n";
        Human_White_go();
        return;
    }
    if (aRecordBoard[x][y] != NONE) {
        std::cout << "该位置已有棋子，请重新落子！\n";
        Human_White_go();
        return;
    }
    Collect_Information(x, y, WHITE);
    aRecordBoard[x][y] = WHITE;     // 白子对应值2
    RecordToChessBoard();           // 标记新落子
    DrawChessBoard();
    // 判断是否悔棋
    std::cout << "是否希望悔棋？(Y/N)";
    char l = std::cin.get();
    if (l == 'Y' || l == 'y') {
        aRecordBoard[x][y] = NONE;
        RecordToChessBoard();
        DrawChessBoard();
        std::cout << "请慎重落子！";
        Human_White_go();
    }
}
//AI落黑棋函数
void AI_Black_go(int count) {
    if (count == 1) { // 第一步下中间位置
        aRecordBoard[7][7] = BLACK;
        RecordToChessBoard();
        DrawChessBoard();
        return;
    }
    PTR_To_Point final;
    final = (PTR_To_Point)malloc(sizeof(Point) * 1);
    int value = Best_choice(BLACK, final, DEPTH, N_Infinity, P_Infinity);
    std::cout << "\n黑子落子位置为(" << final->hang << "," << final->lie << ")\n";
    std::cout << "当前局面黑方评分：" << value << "分\n";
    aRecordBoard[final->hang][final->lie] = BLACK;
    RecordToChessBoard();
    DrawChessBoard();
    return;
}
//AI落白棋函数
void AI_White_go(int count) {
    PTR_To_Point final;
    final = (PTR_To_Point)malloc(sizeof(Point) * 1);
    if (count == 2) {
        if (aRecordBoard[7][7] == BLACK) {
            aRecordBoard[8][8] = WHITE;
            RecordToChessBoard();
            DrawChessBoard();
            return;
        }
    }
    int value = Best_choice(WHITE, final, DEPTH, N_Infinity, P_Infinity);
    std::cout << "\n白子落子位置为(" << final->hang << "," << final->lie << ")\n";
    std::cout << "当前局面白方评分：" << value << "分\n";
    aRecordBoard[final->hang][final->lie] = WHITE;
    RecordToChessBoard();
    DrawChessBoard();
    return;
}
