//��ģ��ΪAIģ�飬��Minimax�㷨����Alpha-Beta��֦ʵ�����������AI����
#include"AI.h"
int DEPTH = 8;
int WIDTH = 15;
int ChessBoard[15][15] = { 0 };
int aRecordBoard[15][15] = { 0 };
struct Point_Score Value_Board[15][15] = { 0 };
//�ɼ���Ϣ����
void Collect_Information(int x, int y, int color)
{
    //�Ƚ�ԭ��Ϣ����
    Value_Board[x][y].score[color - 1] = 0;
    Value_Board[x][y].direction[color - 1].Right_5 = false;
    Value_Board[x][y].direction[color - 1].Living_4 = 0;
    Value_Board[x][y].direction[color - 1].Rush_4 = 0;
    Value_Board[x][y].direction[color - 1].Living_3 = 0;
    Value_Board[x][y].direction[color - 1].Rush_3 = 0;
    Value_Board[x][y].direction[color - 1].Living_2 = 0;
    Value_Board[x][y].direction[color - 1].Rush_2 = 0;
    //�������
    int s[8];       //s��ʾ������8���㶼���м����ͬ��same��0-7���δ����ϣ����ϣ��ң����£��£����£�������
    int s_e[8];     //��¼������ͬ��ɫ���Ӻ�Ŀ�λ
    int s_e_s[8];   //��¼��λ�����ͬ��ɫ��
    int s_e_s_e[8];
    int s_e_s_e_s[8];
    //��ʼ�����飬��ֵ��ȻȫΪ0
    for (int j = 0; j < 8; j++) {
        s[j] = s_e[j] = s_e_s[j] = s_e_s_e[j] = s_e_s_e_s[j] = 0;
    }
    //��������������Ϣ
    int i, j;
    // ����������j--;
    for (i = y, j = x - 1; j >= 0 && aRecordBoard[j][i] == color; j--, s[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == NONE; j--, s_e[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == color; j--, s_e_s[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == NONE; j--, s_e_s_e[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == color; j--, s_e_s_e_s[0]++);
    // ������������j--,i++;
    for (i = y + 1, j = x - 1; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == NONE; i++, j--, s_e[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s_e_s[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == NONE; i++, j--, s_e_s_e[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s_e_s_e_s[1]++);
    // ����������i++;
    for (i = y + 1, j = x; i < SIZE && aRecordBoard[j][i] == color; i++, s[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == NONE; i++, s_e[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == color; i++, s_e_s[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == NONE; i++, s_e_s_e[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == color; i++, s_e_s_e_s[2]++);
    // ������������j++,i++;
    for (i = y + 1, j = x + 1; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == NONE; i++, j++, s_e[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s_e_s[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == NONE; i++, j++, s_e_s_e[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s_e_s_e_s[3]++);
    // ����������j++;
    for (i = y, j = x + 1; j < SIZE && aRecordBoard[j][i] == color; j++, s[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == NONE; j++, s_e[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == color; j++, s_e_s[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == NONE; j++, s_e_s_e[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == color; j++, s_e_s_e_s[4]++);
    // ������������j++,i--;
    for (i = y - 1, j = x + 1; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == NONE; i--, j++, s_e[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s_e_s[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == NONE; i--, j++, s_e_s_e[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s_e_s_e_s[5]++);
    // ����������i--;
    for (i = y - 1, j = x; i >= 0 && aRecordBoard[j][i] == color; i--, s[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == NONE; i--, s_e[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == color; i--, s_e_s[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == NONE; i--, s_e_s_e[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == color; i--, s_e_s_e_s[6]++);
    // ������������j--,i--;
    for (i = y - 1, j = x - 1; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == NONE; i--, j--, s_e[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s_e_s[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == NONE; i--, j--, s_e_s_e[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s_e_s_e_s[7]++);
    //ͳ����ϣ�����Ӧ����ʼ����4�������3��4����Ŀ������
    //�����ж��Ƿ�����壬�������壬��Ȼ�����ɽ���
    for (int i = 0; i < 4; i++) {
        //�ж��Ƿ񹹳ɲ����ֵ�����,�����ȷ������ʵ�֣��������Ķ������ж��ˣ�ֱ��return
        if (s[i] + s[i + 4] == 4 || (s[i] == 4 && s[i + 4] == 4)) {   //���������ǽ��ֵ���������������¶���4������ʱ������4�м䲻���ɳ�������
            Value_Board[x][y].direction[color - 1].Right_5 = true;
            return;
        }
        //����ǰ��壬����Ҳ��Ӯ 
        if (s[i] + s[i + 4] >= 5 && color == WHITE) {    //ֻ�к����н���
            Value_Board[x][y].direction[color - 1].Right_5 = true;
            return;
        }
        //4��
        else if (s[i] + s[i + 4] == 3) {
            int flag = 0;
            if (s_e[i] > 0 && judge_next(x, y, s[i], i, color)) {
                flag++;
            }
            if (s_e[i + 4] > 0 && judge_next(x, y, s[i + 4], i + 4, color)) {
                flag++;
            }

            if (flag == 2) {    //����
                Value_Board[x][y].direction[color - 1].Living_4 += 1;
            }
            else if (flag == 1) {       //����
                Value_Board[x][y].direction[color - 1].Rush_4 += 1;
            }
            else {
                ;       //���߶������˻����²��ˣ�û��
            }
        }
        //3��
        else if (s[i] + s[i + 4] == 2) {
            //�������·���û�п��ܳ���,���߶��ǳ��ľ��ǻ���    ����  ��xxxox��
            int flag = 0;
            if (s_e[i] == 1 && s_e_s[i] == 1) {
                if (judge_next(x, y, s[i], i, color)) {      //���顰xxxox����o��
                    flag++;
                }
            }
            if (s_e[i + 4] == 1 && s_e_s[i + 4] == 1) {
                if (judge_next(x, y, s[i + 4], i + 4, color)) {     //���顰xoxxx������o��
                    flag++;
                }
            }
            if (flag == 2) {
                //����  "xoxxxox"������0�����������γɻ���
                Value_Board[x][y].direction[color - 1].Living_4 += 1;
            }
            else if (flag == 1) {
                //���� "xxxox"��0���������γɳ���
                Value_Board[x][y].direction[color - 1].Rush_4 += 1;
            }
            else {
                //����Ϸ��Ƿ��л���������һ���������Ϸ���һ����λ���ܷ��γɻ��ģ����û�л������ж��Ƿ��г�3
                bool flag1_1 = (s_e[i] > 2 || (s_e[i] == 2 && s_e_s[i] == 0)) ? true : false;
                bool flag1_2 = (s_e[i] == 1 && s_e_s[i] == 0) ? true : false;
                bool flag1_3 = (s_e[i + 4] > 1 || (s_e[i + 4] == 1 && s_e_s[i + 4] == 0)) ? true : false;
                bool flag2_1 = (s_e[i + 4] > 2 || (s_e[i + 4] == 2 && s_e_s[i + 4] == 0)) ? true : false;
                bool flag2_2 = (s_e[i + 4] == 1 && s_e_s[i + 4] == 0) ? true : false;
                bool flag2_3 = (s_e[i] > 1 || (s_e[i] == 1 && s_e_s[i] == 0)) ? true : false;
                if ((flag1_1 && flag1_3 && judge_next(x, y, s[i], i, color)) || (flag2_1 && flag2_3 && judge_next(x, y, s[i + 4], i + 4, color))) {
                    Value_Board[x][y].direction[color - 1].Living_3 += 1;
                }
                else if ((((flag1_2 && flag1_3) || (flag1_1 && !flag1_3)) && judge_next(x, y, s[i], i, color))
                    || (((flag2_2 && flag2_3) || (flag2_1 && !flag2_3)) && judge_next(x, y, s[i + 4], i + 4, color)))
                {
                    Value_Board[x][y].direction[color - 1].Rush_3 += 1;
                }
            }
        }
        //����
        else if (s[i] + s[i + 4] == 1) {
            int flag = 0;
            //���ĳ����ж�
            //�����ϻ���"oxxoxx" / "xxoxxo"Ϊ����
            //�����ϼ���"xxoxxoxx" Ϊ����
            if (s_e[i] == 1 && s_e_s[i] == 2) {
                if (judge_next(x, y, s[i], i, color)) {
                    flag++;      //���顰oxxoxx���ұ��Ǹ�o
                }
            }
            if (s_e[i + 4] == 1 && s_e_s[i + 4] == 2) {
                if (judge_next(x, y, s[i + 4], i + 4, color)) {
                    flag++;      //���顰xxoxxo������Ǹ�o
                }
            }
            if (flag == 2) {
                Value_Board[x][y].direction[color - 1].Living_4 += 1;
            }
            else if (flag == 1) {
                Value_Board[x][y].direction[color - 1].Rush_4 += 1;
            }
            else {
                //�����ж�
                bool flag1_1 = (s_e[i] == 1 && s_e_s[i] == 1) ? true : false;
                bool flag1_2 = (s_e_s_e[i] > 1 || (s_e_s_e[i] == 1 && s_e_s_e_s[i] == 0)) ? true : false;
                bool flag1_3 = (s_e[i + 4] > 1 || (s_e[i + 4] == 1 && s_e_s[i + 4] == 0)) ? true : false;
                bool flag2_1 = (s_e[i + 4] == 1 && s_e_s[i + 4] == 1) ? true : false;
                bool flag2_2 = (s_e_s_e[i + 4] > 1 || (s_e_s_e[i + 4] == 1 && s_e_s_e_s[i + 4] == 0)) ? true : false;
                bool flag2_3 = (s_e[i] > 1 || (s_e[i] == 1 && s_e_s[i] == 0)) ? true : false;
                if ((flag1_1 && flag1_2 && flag1_3 && judge_next(x, y, s[i], i, color)) || (flag2_1 && flag2_2 && flag2_3 && judge_next(x, y, s[i + 4], i + 4, color))) {
                    Value_Board[x][y].direction[color - 1].Living_3 += 1;
                }
                else if ((flag1_1 && (flag1_2 || flag1_3) && judge_next(x, y, s[i], i, color)) || (flag2_1 && (flag2_2 || flag2_3) && judge_next(x, y, s[i + 4], i + 4, color))) {
                    Value_Board[x][y].direction[color - 1].Rush_3 += 1;
                }
            }
            //�жϻ�2�������ֵ�ã�
            bool flag1_1 = (s_e[i] > 2 || (s_e[i] == 2 && s_e_s[i] == 0)) ? true : false;
            bool flag1_2 = (s_e[i] > 3 || (s_e[i] == 3 && s_e_s[i] == 0)) ? true : false;
            bool flag1_3 = (s_e[i + 4] > 2 || (s_e[i + 4] == 2 && s_e_s[i + 4] == 0)) ? true : false;
            bool flag2_1 = (s_e[i + 4] > 3 || (s_e[i + 4] == 3 && s_e_s[i + 4] == 0)) ? true : false;
            bool flag2_2 = (s_e[i] == 1 && s_e_s[i] == 0) ? true : false;
            if (flag1_1 && flag2_1) {
                if (flag1_2 || flag1_3 || flag2_2 || flag2_1) {
                    Value_Board[x][y].direction[color - 1].Rush_2 += 1;
                }
            }
        }
    }
    //��Ϣͳ�����
}
bool next_check_ban(int x, int y, int color)
{ //�����жϹؼ����Ƿ��ǽ���
    int s[8];       //s��ʾ������8���㶼���м����ͬ��same��0-7���δ����ϣ����ϣ��ң����£��£����£�������
    int s_e[8];     //��¼������ͬ��ɫ���Ӻ�Ŀ�λ
    int s_e_s[8];   //��¼��λ�����ͬ��ɫ��
    int s_e_s_e[8];
    int s_e_s_e_s[8];
    //��ʼ�����飬��ֵ��ȻȫΪ0
    for (int j = 0; j < 8; j++) {
        s[j] = s_e[j] = s_e_s[j] = s_e_s_e[j] = s_e_s_e_s[j] = 0;
    }
    //��������������Ϣ
    int i, j;
    // ����������j--;
    for (i = y, j = x - 1; j >= 0 && aRecordBoard[j][i] == color; j--, s[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == NONE; j--, s_e[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == color; j--, s_e_s[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == NONE; j--, s_e_s_e[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == color; j--, s_e_s_e_s[0]++);
    // ������������j--,i++;
    for (i = y + 1, j = x - 1; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == NONE; i++, j--, s_e[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s_e_s[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == NONE; i++, j--, s_e_s_e[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s_e_s_e_s[1]++);
    // ����������i++;
    for (i = y + 1, j = x; i < SIZE && aRecordBoard[j][i] == color; i++, s[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == NONE; i++, s_e[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == color; i++, s_e_s[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == NONE; i++, s_e_s_e[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == color; i++, s_e_s_e_s[2]++);
    // ������������j++,i++;
    for (i = y + 1, j = x + 1; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == NONE; i++, j++, s_e[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s_e_s[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == NONE; i++, j++, s_e_s_e[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s_e_s_e_s[3]++);
    // ����������j++;
    for (i = y, j = x + 1; j < SIZE && aRecordBoard[j][i] == color; j++, s[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == NONE; j++, s_e[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == color; j++, s_e_s[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == NONE; j++, s_e_s_e[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == color; j++, s_e_s_e_s[4]++);
    // ������������j++,i--;
    for (i = y - 1, j = x + 1; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == NONE; i--, j++, s_e[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s_e_s[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == NONE; i--, j++, s_e_s_e[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s_e_s_e_s[5]++);
    // ����������i--;
    for (i = y - 1, j = x; i >= 0 && aRecordBoard[j][i] == color; i--, s[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == NONE; i--, s_e[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == color; i--, s_e_s[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == NONE; i--, s_e_s_e[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == color; i--, s_e_s_e_s[6]++);
    // ������������j--,i--;
    for (i = y - 1, j = x - 1; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == NONE; i--, j--, s_e[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s_e_s[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == NONE; i--, j--, s_e_s_e[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s_e_s_e_s[7]++);
    //ͳ����ϣ�����Ӧ����ʼ����4�������3��4����Ŀ������
    int Living_4, Rush_4, Living_3;
    Living_4 = Rush_4 = Living_3 = 0;
    //�����ж��Ƿ�����壬�������壬��Ȼ�����ɽ���
    for (int i = 0; i < 4; i++) {
        if (s[i] + s[i + 4] == 4) {
            //��ȷ������˵���ùؼ��㲻�ǽ��֣�����true
            return true;
        }
        //4��
        else if (s[i] + s[i + 4] == 3) {
            int flag = 0;
            if (s_e[i] > 0 && judge_next(x, y, s[i], i, color)) {
                flag++;
            }
            if (s_e[i + 4] > 0 && judge_next(x, y, s[i + 4], i + 4, color)) {
                flag++;
            }

            if (flag == 2) {    //����
                Living_4 += 1;
            }
            else if (flag == 1) {       //����
                Rush_4 += 1;
            }
        }
        // 3��
        else if (s[i] + s[i + 4] == 2) {
            // �������·���û�п��ܳ��ģ����߶��ǳ��ľ��ǻ��ģ����硰xxxox��
            int flag = 0;
            if (s_e[i] == 1 && s_e_s[i] == 1) {
                if (judge_next(x, y, s[i], i, color)) { // ���顰xxxox����o��
                    flag++;
                }
            }
            if (s_e[i + 4] == 1 && s_e_s[i + 4] == 1) {
                if (judge_next(x, y, s[i + 4], i + 4, color)) { // ���顰xoxxx������o��
                    flag++;
                }
            }
            if (flag == 2) {
                // ���� "xoxxxox"������0�����������γɻ���
                Living_4 += 1;
            }
            else if (flag == 1) {
                // ���� "xxxox"��0���������γɳ���
                Rush_4 += 1;
            }
            else {
                // ����Ϸ��Ƿ��л���������һ���������Ϸ���һ����λ���ܷ��γɻ���
                bool flag_living_3 = false;

                if ((s_e[i] > 2 || (s_e[i] == 2 && s_e_s[i] == 0))
                    && (s_e[i + 4] > 1 || (s_e[i + 4] == 1 && s_e_s[i + 4] == 0))) {
                    if (judge_next(x, y, s[i], i, color)) {    // ����xxx�ϱߵĵ�һ��o��
                        flag_living_3 = true;
                    }
                }
                // ���Ϸ���ͬ�������ڼ���·�
                if ((s_e[i + 4] > 2 || (s_e[i + 4] == 2 && s_e_s[i + 4] == 0))
                    && (s_e[i] > 1 || (s_e[i] == 1 && s_e_s[i] == 0))) {
                    if (judge_next(x, y, s[i + 4], i + 4, color)) {    // ����xxx�±ߵĵ�һ��o��
                        flag_living_3 = true;
                    }
                }
                if (flag_living_3) {
                    Living_3 += 1;
                }
            }
        }
        // ����
        else if (s[i] + s[i + 4] == 1) {
            int flag = 0;
            // ���ĳ����ж�
            if (s_e[i] == 1 && s_e_s[i] == 2) {
                if (judge_next(x, y, s[i], i, color)) {
                    flag++; // ���顰oxxoxx���ұ��Ǹ�o
                }
            }
            if (s_e[i + 4] == 1 && s_e_s[i + 4] == 2) {
                if (judge_next(x, y, s[i + 4], i + 4, color)) {
                    flag++; // ���顰xxoxxo������Ǹ�o
                }
            }
            if (flag == 2) {
                Living_4 += 1;
            }
            else if (flag == 1) {
                Rush_4 += 1;
            }
            else {
                // �����ж�
                bool flag_living_3 = false;
                if (s_e[i] == 1 && s_e_s[i] == 1
                    && (s_e_s_e[i] > 1 || (s_e_s_e[i] == 1 && s_e_s_e_s[i] == 0))
                    && (s_e[i + 4] > 1 || (s_e[i + 4] == 1 && s_e_s[i + 4] == 0))) {
                    if (judge_next(x, y, s[i], i, color)) {   // ���顰ooxxoxoo"�м�Ŀ�λ
                        flag_living_3 = true;
                    }
                }
                if (s_e[i + 4] == 1 && s_e_s[i + 4] == 1
                    && (s_e_s_e[i + 4] > 1 || (s_e_s_e[i + 4] == 1 && s_e_s_e_s[i + 4] == 0))
                    && (s_e[i] > 1 || (s_e[i] == 1 && s_e_s[i] == 0))) {
                    if (judge_next(x, y, s[i + 4], i + 4, color)) {   // ���顰ooxoxxo"�м�Ŀ�λ
                        flag_living_3 = true;
                    }
                }
                if (flag_living_3) {
                    Living_3 += 1;
                }
            }
        }
        // ����һ��
        else if (s[i] + s[i + 4] == 0) {
            bool flag = false;
            // ���ĳ����ж�
            if (s_e[i] == 1 && s_e_s[i] == 3) {
                if (judge_next(x, y, s[i], i, color)) {   // ��Ҫ�жϵĵ��ǡ�oxoxxx���м��o
                    Rush_4 += 1;
                    flag = true;
                }
            }
            if (s_e[i + 4] == 1 && s_e_s[i + 4] == 3) {
                if (judge_next(x, y, s[i + 4], i + 4, color)) {
                    Rush_4 += 1;
                    flag = true;
                }
            }
            // �����ж�
            if (!flag) {
                bool flag_living_3 = false;
                if (s_e[i] == 1 && s_e_s[i] == 2
                    && (s_e_s_e[i] > 1 || (s_e_s_e[i] == 1 && s_e_s_e_s[i] == 0))
                    && (s_e[i + 4] > 1 || (s_e[i + 4] == 1 && s_e_s[i + 4] == 0))) {
                    if (judge_next(x, y, s[i], i, color)) {   // ��Ҫ�жϵĵ����м��o
                        flag_living_3 = true;
                    }
                }
                if (s_e[i + 4] == 1 && s_e_s[i + 4] == 2
                    && (s_e_s_e[i + 4] > 1 || (s_e_s_e[i + 4] == 1 && s_e_s_e_s[i + 4] == 0))
                    && (s_e[i] > 1 || (s_e[i] == 1 && s_e_s[i] == 0))) {
                    if (judge_next(x, y, s[i + 4], i + 4, color)) {   // ��Ҫ�жϵĵ����м��o
                        flag_living_3 = true;
                    }
                }
                if (flag_living_3) {
                    Living_3 += 1;
                }
            }
        }
    }
    if (Living_3 >= 2 && Living_4 + Rush_4 < 1) {             // ����һ����һ�������⣬���������ֻҪ�ʹ��ڵ���2��һ���ǽ��֡�
        return false;
    }
    else {
        return true;
    }
}
bool judge_next(int hang, int lie, int distance, int Direction, int color)
{
    if (color == WHITE)
    {
        return true;//����ǰ�����Ȼû�н�������
    }
    int next_hang, next_lie;
    distance++;    //��Ϊ���һ����������Ҫ++
    if (Direction >= 4)
    {
        distance = -distance;       //�����෴���Ӽ�Ӧ��֮�෴
    }
    //����ؼ�������
    switch (Direction % 4)
    {
    case 0:
        next_hang = hang - distance;
        next_lie = lie;
        break;
    case 1:
        next_hang = hang - distance;
        next_lie = lie + distance;
        break;
    case 2:
        next_hang = hang;
        next_lie = lie + distance;
        break;
    case 3:
        next_hang = hang + distance;
        next_lie = lie + distance;
        break;
    default:
        printf("����ķ�������");
        break;
    }
    bool if_just_evaluate = false;
    if (aRecordBoard[hang][lie] != NONE)
    {
        if_just_evaluate = true;
    }
    aRecordBoard[hang][lie] = color;        //���ղ��Ǹ�������
    bool flag = next_check_ban(next_hang, next_lie, color);
    if (!if_just_evaluate)
    {
        //��Ӧ�жϾ���ֵ���Ҫ�����жϾ����ʱ��ԭ����������ӣ����ܲ��� 
        aRecordBoard[hang][lie] = NONE;        //�ָ� 
    }
    if (flag) {
        return true;
    }
    else {
        return false;
    }
}
//�����ֺ�������Ϊ�������и���
bool judge_if_banhand(int x, int y, int color)
{
    if (Value_Board[x][y].direction[color - 1].Living_3 >= 2 && Value_Board[x][y].direction[color - 1].Living_4 == 0 && Value_Board[x][y].direction[color - 1].Rush_4 == 0) {
        return false;
    }
    return true;
}
//ĳ���ֵ�ۼӺ���
void evaluate_value(int x, int y)
{
    int value[2] = { 0, 0 };
    for (int i = 0; i <= 1; i++) {
        value[i] += Value_Board[x][y].direction[i].Right_5 * Value_Right_5;
        value[i] += Value_Board[x][y].direction[i].Living_4 * Value_Living_4;
        value[i] += Value_Board[x][y].direction[i].Rush_4 * Value_Rush_4;
        value[i] += Value_Board[x][y].direction[i].Living_3 * Value_Living_3;
        value[i] += Value_Board[x][y].direction[i].Rush_3 * Value_Rush_3;
        value[i] += Value_Board[x][y].direction[i].Living_2 * Value_Living_2;
        value[i] += Value_Board[x][y].direction[i].Rush_2 * Value_Rush_2;
        Value_Board[x][y].score[i] = value[i];
    }
    Value_Board[x][y].allscore = value[0] + value[1];
}
int Evaluate_Current_Situation_Value(int color) {
    //���ȼ��ǶԷ�����>��������>�Է���3
    int Sef_Value_Living_4 = 100000;
    int Sef_Value_Rush_4 = 720;
    int Rival_Value_Rush_4 = 1000000;
    int Sef_Value_Living_3 = 720;
    int Rival_Value_Living_3 = 50000;
    int Sef_Value_Rush_3 = 480;
    int Rival_Value_Rush_3 = 720;
    int Sef_Value_Living_2 = 480;
    int Rival_Value_Living_2 = 480;
    int Sef_Value_Rush_2 = 20;
    int Rival_Value_Rush_2 = 100;
    //���ڼ������������������ȵĸ�ֵ
    int i, j;
    int Living_4[2] = { 0, 0 };
    int Rush_4[2] = { 0, 0 };
    int Living_3[2] = { 0, 0 };
    int Rush_3[2] = { 0, 0 };
    int Living_2[2] = { 0, 0 };
    int Rush_2[2] = { 0, 0 };
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (aRecordBoard[i][j] == BLACK) {
                Collect_Information(i, j, BLACK);
                //Collect_Information(i, j, BLACK);
                Living_4[0] += Value_Board[i][j].direction[0].Living_4;
                Rush_4[0] += Value_Board[i][j].direction[0].Rush_4;
                Living_3[0] += Value_Board[i][j].direction[0].Living_3;
                Rush_3[0] += Value_Board[i][j].direction[0].Rush_3;
                Living_2[0] += Value_Board[i][j].direction[0].Living_2;
                Rush_2[0] += Value_Board[i][j].direction[0].Rush_2;
            }
            if (aRecordBoard[i][j] == WHITE) {
                Collect_Information(i, j, WHITE);
                //Collect_Information(i, j, WHITE);
                Living_4[1] += Value_Board[i][j].direction[1].Living_4;
                Rush_4[1] += Value_Board[i][j].direction[1].Rush_4;
                Living_3[1] += Value_Board[i][j].direction[1].Living_3;
                Rush_3[1] += Value_Board[i][j].direction[1].Rush_3;
                Living_2[1] += Value_Board[i][j].direction[1].Living_2;
                Rush_2[1] += Value_Board[i][j].direction[1].Rush_2;
            }
        }
    }
    int value = 0;
    if (color == BLACK) {
        value += Living_4[0] * Sef_Value_Living_4 / 4;
        value += Rush_4[0] * Sef_Value_Rush_4 / 4;
        value += Living_3[0] * Sef_Value_Living_3 / 3;
        value += Rush_3[0] * Sef_Value_Rush_3 / 3;
        value += Living_2[0] * Sef_Value_Living_2 / 2;
        value += Rush_2[0] * Sef_Value_Rush_2 / 2;

        value -= Living_4[1] * Rival_Value_Rush_4 / 4;
        value -= Rush_4[1] * Rival_Value_Rush_4 / 4;
        value -= Living_3[1] * Rival_Value_Living_3 / 3;
        value -= Rush_3[1] * Rival_Value_Rush_3 / 3;
        value -= Living_2[1] * Rival_Value_Living_2 / 2;
        value -= Rush_2[1] * Rival_Value_Rush_2 / 2;
    }
    else {
        value += Living_4[1] * Sef_Value_Living_4 / 4;
        value += Rush_4[1] * Sef_Value_Rush_4 / 4;
        value += Living_3[1] * Sef_Value_Living_3 / 3;
        value += Rush_3[1] * Sef_Value_Rush_3 / 3;
        value += Living_2[1] * Sef_Value_Living_2 / 2;
        value += Rush_2[1] * Sef_Value_Rush_2 / 2;

        value -= Living_4[0] * Rival_Value_Rush_4 / 4;
        value -= Rush_4[0] * Rival_Value_Rush_4 / 4;
        value -= Living_3[0] * Rival_Value_Living_3 / 3;
        value -= Rush_3[0] * Rival_Value_Rush_3 / 3;
        value -= Living_2[0] * Rival_Value_Living_2 / 2;
        value -= Rush_2[0] * Rival_Value_Rush_2 / 2;
    }
    return value;
}
//�ҵ㺯�����ҳ����п��ܵ����ӵ㣬����÷ֲ��ж��Ƿ�Ϊ�ؼ��㣨��ɱ��ص���
int Find_Points(PTR_To_Points All_Points, int color, bool flag, bool* flag_if_win, PTR_To_Point Bisha, bool* flag_will_lose, PTR_To_Point Bidang)
{
    int i, j;
    int index = 0;
    PTR_To_Point cunchu;  //ָ�����飬�洢���������ĵ�
    cunchu = (PTR_To_Point)malloc(sizeof(Point) * 225);//��cunchuָ�����225��Point�ṹ����ڴ�
    int cunchu_index = 0;//��¼���������ĵ������
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (aRecordBoard[i][j] != NONE) {         //���������
                int x1, y1, x2, y2;
                if (i > 0) {
                    x1 = i - 1;
                }
                else {
                    x1 = i;
                }
                if (i < SIZE - 1) {
                    x2 = i + 1;
                }
                else {
                    x2 = i;
                }
                if (j > 0) {
                    y1 = j - 1;
                }
                else {
                    y1 = j;
                }
                if (j < SIZE - 1) {
                    y2 = j + 1;
                }
                else {
                    y2 = j;
                }
                int m, n;
                for (m = x1; m <= x2; m++) {
                    for (n = y1; n <= y2; n++) {
                        if (aRecordBoard[m][n] == NONE) {
                            bool flag_cf = true;//����Ƿ��ظ��ж�
                            for (int t = 0; t < cunchu_index; t++) {
                                if (m == cunchu[t].hang && n == cunchu[t].lie) {
                                    flag_cf = false;//�ȼ���ڵ�ǰ�����Ѵ洢�����Ƿ����ظ���������±��������ѭ��
                                    break;
                                }
                            }
                            if (!flag_cf) {  //˵���õ��Ѿ��жϹ��ˣ�ֱ�ӵ���һ����ȥ
                                continue;
                            }
                            else {         //û�жϹ��������
                                cunchu[cunchu_index].hang = m;
                                cunchu[cunchu_index].lie = n;
                                cunchu_index++;
                            }
                            Collect_Information(m, n, BLACK);
                            Collect_Information(m, n, WHITE);
                            //������ְ��������жϣ�����ֺ��嵫�ⲽ�ǽ��֣���Ҳ������All_Points��
                            if (color == WHITE || judge_if_banhand(m, n, color)) {
                                if (Value_Board[m][n].direction[color - 1].Right_5) { //����������ս�����Ҫ��ǳ���
                                    Bisha->hang = m;
                                    Bisha->lie = n;//��¼������ɱ������
                                    *flag_if_win = true;
                                    return ++index;
                                }
                                int ag_color = (color == WHITE ? BLACK : WHITE);
                                if ((ag_color == WHITE || judge_if_banhand(m, n, ag_color)) && Value_Board[m][n].direction[ag_color - 1].Right_5) {
                                    Bidang->hang = m;
                                    Bidang->lie = n;//�Է���ɱ���������������ص��������
                                    *flag_will_lose = true;
                                }
                                All_Points[index].p.hang = m;
                                All_Points[index].p.lie = n;
                                if (flag) {
                                    evaluate_value(m, n);//�Ե�ǰ�ڵ���й�ֵ
                                    All_Points[index].score = Value_Board[m][n].allscore;
                                }
                                index++;
                            }
                        }
                    }
                }
            }
        }
    }
    return index;
}
//���չ�ֵ�Խڵ���п�������
void quicksort(PTR_To_Points s, int left, int right)
{
    int i, j;
    if (left < right)
    {
        i = left;
        j = right + 1;
        while (1)
        {
            do {
                i++;
            } while (i < right && s[i].score <= s[left].score);
            do {
                j--;
            } while (j > left && s[j].score >= s[left].score);
            if (i < j)
            {
                int temp;    //�м���������ڽ���s[i]��s[j]�ķ������С�������
                temp = s[i].score;
                s[i].score = s[j].score;
                s[j].score = temp;
                temp = s[i].p.hang;
                s[i].p.hang = s[j].p.hang;
                s[j].p.hang = temp;
                temp = s[i].p.lie;
                s[i].p.lie = s[j].p.lie;
                s[j].p.lie = temp;
            }
            else break;
        }
        int temp;
        temp = s[j].score;
        s[j].score = s[left].score;
        s[left].score = temp;
        temp = s[j].p.hang;
        s[j].p.hang = s[left].p.hang;
        s[left].p.hang = temp;
        temp = s[j].p.lie;
        s[j].p.lie = s[left].p.lie;
        s[left].p.lie = temp;
        quicksort(s, j + 1, right);
        quicksort(s, left, j - 1);
    }
}
//��������Ҷ�ӽڵ����color���Ĺ�ֵ
int Find_base_point(int color)
{
    PTR_To_Points All_Points;     //����ѡ��
    All_Points = (PTR_To_Points)malloc(sizeof(Points) * 225);//��ָ������All_Points�����ڴ�
    bool flag_if_win = false;
    bool flag_will_lose = false;
    Point Bisha, Bidang;//��ɱ���ص��Ĺؼ���
    int n = Find_Points(All_Points, color, NO_NEED_VALUE, &flag_if_win, &Bisha, &flag_will_lose, &Bidang);//�ؼ�������
    if (flag_if_win) {	//˵���ײ��ֵ�������ʱ���ս��֣�����һ������ֵ
        return 200000;
    }
    if (flag_will_lose) {//˵���ײ��ֵ�������ʱֻ��ȥ�¶���ģ�ֻ��һ��ѡ��
        aRecordBoard[Bidang.hang][Bidang.lie] = color;
        int only = Evaluate_Current_Situation_Value(color);
        aRecordBoard[Bidang.hang][Bidang.lie] = NONE;
        return only;
    }
    int value, max;
    max = -100000;
    for (int i = 0; i < n; i++)
    {
        aRecordBoard[All_Points[i].p.hang][All_Points[i].p.lie] = color;
        value = Evaluate_Current_Situation_Value(color);     //�����Ӳ���ֵ
        aRecordBoard[All_Points[i].p.hang][All_Points[i].p.lie] = NONE;//�������Ӳ��ж�
        if (value > max) {
            max = value;
        }
    }
    return max;
}
//ʵ��Minimax�ͼ�֦�㷨�ĵݹ麯������������ѡ���value
int Best_choice(int color, PTR_To_Point final, int depth, int a, int b) {
    switch (depth) {       //���ݲ����ѡ���������
    case 8:
        WIDTH = 12;
        break;
    case 7:
        WIDTH = 10;
        break;
    case 6:
        WIDTH = 10;
        break;
    case 5:
        WIDTH = 7;
        break;
    case 4:
        WIDTH = 7;
        break;
    case 3:
        WIDTH = 7;
        break;
    case 2:
        WIDTH = 7;
        break;
    case 1:
        WIDTH = 7;
        break;
    case 0:
        WIDTH = 14;
        break;
    default:
        printf("Error!");
        break;
    }
    //���ײ㡱����Ϊ�����б�ɱ�ֻ��ս���
    //AIΪż���㣬��Ϊ������
    //�ݹ���ֹ����Ϊ����ײ㣬��ʱҪ���ݾ���÷�ѡ��
    if (depth == 0) {
        int value = Find_base_point(color);
        return value;
    }
    //���ǵײ㣬��Ӧ�ø��ݵ��ѡ��
    int next_color = (color == BLACK ? WHITE : BLACK); //������һ����������ɫ
    PTR_To_Points All_Points;     //����ѡ��
    All_Points = (PTR_To_Points)malloc(sizeof(Points) * 225);//�����ڴ�
    if (All_Points == NULL) {
        printf("malloc error");
        exit(1); //�ڴ��������쳣�˳�
    }
    bool flag_if_win = false;
    bool flag_will_lose = false;
    Point Bisha, Bidang;
    int n = Find_Points(All_Points, color, NEED_VALUE, &flag_if_win, &Bisha, &flag_will_lose, &Bidang);
    //����ֵ�color�����˲����ս����
    if (flag_if_win) {
        if (depth % 2 == 1) {
            //���������Ӻ󣬷��ֶԷ���һ�����ս������˵�����������Ӳ����ʣ�Ӧ����һ����Сֵ
            return -200000;
        }
        else {
            //���Է�����(���ʼ����)ʱ���ҷ���һ�����ս������˵���Է������Ӳ����ʣ�Ӧ����һ������ֵ
            //ͬʱ�����ʱ�Ǹ��ڵ㼴��ʼ���棬��Ӧ�����ؼ����ս��ֵ�����
            if (depth == DEPTH) {
                final->hang = Bisha.hang;
                final->lie = Bisha.lie;
            }
            return 200000;
        }
    }
    if (n < WIDTH) {//�����ҵĵ�����14��
        WIDTH = n;
    }
    int temp_width = WIDTH;
    //���ݽڵ����ֶ����к�ѡ���ӽ���quicksort����Ŀ���ǽ����������ӵ��ŵ�ǰ�棬��С��������ģ
    quicksort(All_Points, 0, n - 1);
    int i, j;
    PTR_To_Points choice;       //���ŵ�WIDTH��ѡ��
    choice = (PTR_To_Points)malloc(sizeof(Points) * WIDTH);
    //��ALL_Points�е����ŵ�WIDTH���㸴�Ƶ�choice[]��ȥ
    for (i = 0, j = n - 1; i < WIDTH; i++, j--) {
        choice[i].p = All_Points[j].p;
        choice[i].score = All_Points[j].score;
        choice[i].min = a;  //�̳����Ը��ڵ�Ħ�
        choice[i].max = b;  //�̳����Ը��ڵ�Ħ�
    }
    int* value;  //��¼ÿ���ӽڵ�Ļ���ֵ
    value = (int*)malloc(sizeof(int) * WIDTH);
    //�ڵ�ǰ���к�������
    for (i = 0; i < temp_width; i++) {
        //step1:�Ȱ���������ȥ
        aRecordBoard[choice[i].p.hang][choice[i].p.lie] = color;
        //step2:���������ֵ���ƻ���
        value[i] = Best_choice(next_color, final, depth - 1, a, b);
        //step3:���ݻ���ֵ�ı���ͦ�
        //�����ż����(��������,ȡ�ӽڵ����ֵ�е����ֵ����˸ı�����min)
        if (depth % 2 == 0) {
            if (value[i] > a) {//�������޴���ı�����
                a = value[i];
                //������ڵ�ʱż���㣬��Ҫ֪�����λ��
                if (depth == DEPTH) {
                    final->hang = choice[i].p.hang;
                    final->lie = choice[i].p.lie;
                }
            }
            if (a >= b) {
                //����>=�£����������������ˣ�������ϲ㷵�ئ�
                aRecordBoard[choice[i].p.hang][choice[i].p.lie] = NONE;
                return a;
            }
        }
        //�����������(�Է����ӣ�ȡ�ӽڵ����ֵ�е���Сֵ����˸ı�����max)
        else {
            if (value[i] < b) {
                b = value[i];
            }
            if (a >= b) {
                //����>=�£�����������������������ϲ㷵�ئ�
                aRecordBoard[choice[i].p.hang][choice[i].p.lie] = NONE;
                return b;
            }
        }
        //step4:������Ӳ���
        aRecordBoard[choice[i].p.hang][choice[i].p.lie] = NONE;
    }
    if (depth % 2 == 0) {//AI��
        return a;
    }
    else {             //���ֲ�
        return b;
    }
}