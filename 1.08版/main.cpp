//本模块为主函数模块，主要实现游戏的初始化、选择模式等功能
#include <iostream>
#include <string>
#include "Gobang.h"
#include "Board.h"
#include "GoAChess.h"
#include "AI.h"
//初始化游戏
void InitializeGame() {
    std::cout << "*************************************************\n";
    std::cout << "**************Welcome To Gobang Game*************\n";
    std::cout << "*************************************************\n";
    std::cout << "This is a Gobang Game designed by XuShuwen, UCAS. \n";
    std::cout << "\n\tMy Email: xushuwen23@mails.ucas.ac.cn\n";
    std::cout << "\n\tMy Github: https://github.com/XuShuwenn\n";
    std::cout << "\nFeel free to visit my personal profile and give your suggestion!\n";
    initRecordBorard();                           	 	// 初始化记录棋盘
    RebuildChessBoard();				           		// 初始化显示棋盘
    DrawChessBoard();
}
// 选择游戏模式
void ChooseMode() {
    std::cout << "请选择模式--人人对战(按P进入) / 人机对战(按E进入)\n";
    char choice;
    std::cin >> choice;
    if (choice == 'P') {
        Human_vs_Human();
    }
    else if (choice == 'E') {
        Human_vs_AI();
    }
    else {
        std::cout << "Illegal input!\n";
    }
}
// 主函数
int main() {
    InitializeGame();
    ChooseMode();
    return 0;
}
