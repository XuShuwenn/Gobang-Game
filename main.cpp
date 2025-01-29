//��ģ��Ϊ������ģ�飬��Ҫʵ����Ϸ�ĳ�ʼ����ѡ��ģʽ�ȹ���
#include <iostream>
#include <string>
#include "Gobang.h"
#include "Board.h"
#include "GoAChess.h"
#include "AI.h"
//��ʼ����Ϸ
void InitializeGame() {
    std::cout << "*************************************************\n";
    std::cout << "**************Welcome To Gobang Game*************\n";
    std::cout << "*************************************************\n";
    std::cout << "This is a Gobang Game designed by XuShuwen, UCAS. \n";
    std::cout << "\n\tMy Email: xushuwen23@mails.ucas.ac.cn\n";
    std::cout << "\n\tMy Github: https://github.com/XuShuwenn\n";
    std::cout << "\nFeel free to visit my personal profile and give your suggestion!\n";
    initRecordBorard();                           	 	// ��ʼ����¼����
    RebuildChessBoard();				           		// ��ʼ����ʾ����
    DrawChessBoard();
}
// ѡ����Ϸģʽ
void ChooseMode() {
    std::cout << "��ѡ��ģʽ--���˶�ս(��P����) / �˻���ս(��E����)\n";
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
// ������
int main() {
    InitializeGame();
    ChooseMode();
    return 0;
}