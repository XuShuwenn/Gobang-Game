//��ģ��Ϊ���幦��ʵ�ֺ���
#include <iostream>
#include <string>
#include "AI.h"
#include "Gobang.h"
#include "Board.h"
#include "GoAChess.h"
//���˶�ս����
void Human_vs_Human() {
    DrawChessBoard();
    std::cout << "\n���˶�ս��ʼ���ɺ���������\n";
    int count = 1;
    while (true) {
        std::cout << "�ֵ������µ�" << count << "���壺\n";
        Human_Black_go();
        count++;
        if (judge_result()) {
            std::cout << "����ʤ������Ϸ����\n";
            break;
        }
        std::cout << "�ֵ������µ�" << count << "���壺\n";
        count++;
        Human_White_go();
        if (judge_result()) {
            std::cout << "����ʤ������Ϸ����\n";
            break;
        }
    }
}
//�˻���ս����
void Human_vs_AI() {
    DrawChessBoard();
    int choice;
    std::cout << "\n�˻���ս��ʼ�������ѡ���Ⱥ���:������1ѡ�����֣�����2ѡ�����)\n";
    std::cin >> choice;
    std::cin.ignore();  // ������ջ�����
    int count = 1;
    if (choice == 1) {
        while (true) {
            std::cout << "�ֵ������µ�" << count << "���壺\n";
            Human_Black_go();
            count++;
            if (judge_result()) {
                std::cout << "����ʤ������Ϸ����\n";
                break;
            }
            std::cout << "�ֵ������µ�" << count << "���壺\n";
            AI_White_go(count);
            count++;
            if (judge_result()) {
                std::cout << "����ʤ������Ϸ����\n";
                break;
            }
        }
    }
    else if (choice == 2) {
        while (true) {
            std::cout << "�ֵ������µ�" << count << "���壺\n";
            AI_Black_go(count);
            count++;
            if (judge_result()) {
                std::cout << "����ʤ������Ϸ����\n";
                break;
            }
            std::cout << "�ֵ������µ�" << count << "���壺\n";
            Human_White_go();
            count++;
            if (judge_result()) {
                std::cout << "����ʤ������Ϸ����\n";
                break;
            }
        }
    }
    else {
        std::cout << "������ʽ����";
    }
}
//��������庯��
void Human_Black_go() {
    int x, y;
    std::cout << "�������������������(_ _):";
    std::cin >> x >> y;
    std::cin.ignore();
    if (!IsValidPosition(x, y)) {
        std::cout << "������ʽ��������������\n";
        Human_Black_go();
        return;
    }
    if (aRecordBoard[x][y] != NONE) {
        std::cout << "��λ���������ӣ����������ӣ�\n";
        Human_Black_go();
        return;
    }
    Collect_Information(x, y, BLACK);
    if (!judge_if_banhand(x, y, BLACK)) {
        std::cout << "��������˫�������֣��ж�����ʤ����";
        system("pause");
    }
    aRecordBoard[x][y] = BLACK;   // ���Ӷ�Ӧֵ1
    RecordToChessBoard();         // ���������
    DrawChessBoard();
    // �ж��Ƿ����
    std::cout << "�Ƿ�ϣ�����壿(Y/N)";
    char l = std::cin.get();
    if (l == 'Y' || l == 'y') {
        aRecordBoard[x][y] = NONE;
        RecordToChessBoard();
        DrawChessBoard();
        std::cout << "���������ӣ�";
        Human_Black_go();
    }
}
//��������庯��
void Human_White_go() {
    int x, y;
    std::cout << "�����������������(_ _):";
    std::cin >> x >> y;
    std::cin.ignore();
    if (!IsValidPosition(x, y)) {
        std::cout << "������ʽ��������������\n";
        Human_White_go();
        return;
    }
    if (aRecordBoard[x][y] != NONE) {
        std::cout << "��λ���������ӣ����������ӣ�\n";
        Human_White_go();
        return;
    }
    Collect_Information(x, y, WHITE);
    aRecordBoard[x][y] = WHITE;     // ���Ӷ�Ӧֵ2
    RecordToChessBoard();           // ���������
    DrawChessBoard();
    // �ж��Ƿ����
    std::cout << "�Ƿ�ϣ�����壿(Y/N)";
    char l = std::cin.get();
    if (l == 'Y' || l == 'y') {
        aRecordBoard[x][y] = NONE;
        RecordToChessBoard();
        DrawChessBoard();
        std::cout << "���������ӣ�";
        Human_White_go();
    }
}
//AI����庯��
void AI_Black_go(int count) {
    if (count == 1) { // ��һ�����м�λ��
        aRecordBoard[7][7] = BLACK;
        RecordToChessBoard();
        DrawChessBoard();
        return;
    }
    PTR_To_Point final;
    final = (PTR_To_Point)malloc(sizeof(Point) * 1);
    int value = Best_choice(BLACK, final, DEPTH, N_Infinity, P_Infinity);
    std::cout << "\n��������λ��Ϊ(" << final->hang << "," << final->lie << ")\n";
    std::cout << "��ǰ����ڷ����֣�" << value << "��\n";
    aRecordBoard[final->hang][final->lie] = BLACK;
    RecordToChessBoard();
    DrawChessBoard();
    return;
}
//AI����庯��
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
    std::cout << "\n��������λ��Ϊ(" << final->hang << "," << final->lie << ")\n";
    std::cout << "��ǰ����׷����֣�" << value << "��\n";
    aRecordBoard[final->hang][final->lie] = WHITE;
    RecordToChessBoard();
    DrawChessBoard();
    return;
}