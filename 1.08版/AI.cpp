//本模块为AI模块，以Minimax算法辅以Alpha-Beta剪枝实现了五子棋的AI功能
#include"AI.h"
int DEPTH = 10;
int WIDTH = 15;
int ChessBoard[15][15] = { 0 };
int aRecordBoard[15][15] = { 0 };
struct Point_Score Value_Board[15][15] = { 0 };
//采集信息函数
void Collect_Information(int x, int y, int color)
{
    //先将原信息清零
    Value_Board[x][y].score[color - 1] = 0;
    Value_Board[x][y].direction[color - 1].Right_5 = false;
    Value_Board[x][y].direction[color - 1].Living_4 = 0;
    Value_Board[x][y].direction[color - 1].Rush_4 = 0;
    Value_Board[x][y].direction[color - 1].Living_3 = 0;
    Value_Board[x][y].direction[color - 1].Rush_3 = 0;
    Value_Board[x][y].direction[color - 1].Living_2 = 0;
    Value_Board[x][y].direction[color - 1].Rush_2 = 0;
    //清零完毕
    int s[8];       //s表示附近的8个点都与中间点相同（same）0-7依次代表上，右上，右，右下，下，左下，左，左上
    int s_e[8];     //记录连续相同颜色棋子后的空位
    int s_e_s[8];   //记录空位后的相同颜色数
    int s_e_s_e[8];
    int s_e_s_e_s[8];
    //初始化数组，赋值当然全为0
    for (int j = 0; j < 8; j++) {
        s[j] = s_e[j] = s_e_s[j] = s_e_s_e[j] = s_e_s_e_s[j] = 0;
    }
    //计算各个方向的信息
    int i, j;
    // 向上搜索即j--;
    for (i = y, j = x - 1; j >= 0 && aRecordBoard[j][i] == color; j--, s[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == NONE; j--, s_e[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == color; j--, s_e_s[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == NONE; j--, s_e_s_e[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == color; j--, s_e_s_e_s[0]++);
    // 向右上搜索即j--,i++;
    for (i = y + 1, j = x - 1; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == NONE; i++, j--, s_e[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s_e_s[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == NONE; i++, j--, s_e_s_e[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s_e_s_e_s[1]++);
    // 向右搜索即i++;
    for (i = y + 1, j = x; i < SIZE && aRecordBoard[j][i] == color; i++, s[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == NONE; i++, s_e[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == color; i++, s_e_s[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == NONE; i++, s_e_s_e[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == color; i++, s_e_s_e_s[2]++);
    // 向右下搜索即j++,i++;
    for (i = y + 1, j = x + 1; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == NONE; i++, j++, s_e[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s_e_s[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == NONE; i++, j++, s_e_s_e[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s_e_s_e_s[3]++);
    // 向下搜索即j++;
    for (i = y, j = x + 1; j < SIZE && aRecordBoard[j][i] == color; j++, s[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == NONE; j++, s_e[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == color; j++, s_e_s[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == NONE; j++, s_e_s_e[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == color; j++, s_e_s_e_s[4]++);
    // 向左下搜索即j++,i--;
    for (i = y - 1, j = x + 1; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == NONE; i--, j++, s_e[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s_e_s[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == NONE; i--, j++, s_e_s_e[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s_e_s_e_s[5]++);
    // 向左搜索即i--;
    for (i = y - 1, j = x; i >= 0 && aRecordBoard[j][i] == color; i--, s[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == NONE; i--, s_e[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == color; i--, s_e_s[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == NONE; i--, s_e_s_e[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == color; i--, s_e_s_e_s[6]++);
    // 向左上搜索即j--,i--;
    for (i = y - 1, j = x - 1; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == NONE; i--, j--, s_e[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s_e_s[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == NONE; i--, j--, s_e_s_e[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s_e_s_e_s[7]++);
    //统计完毕，下面应当开始计算4个方向活3活4的数目及禁手
    //首先判断是否成连五，若成连五，显然不构成禁手
    for (int i = 0; i < 4; i++) {
        //判断是否构成不禁手的五连,如果正确的五连实现，那其他的都不用判断了，直接return
        if (s[i] + s[i + 4] == 4 || (s[i] == 4 && s[i + 4] == 4)) {   //后者条件是禁手的特殊情况，即上下都是4个，此时下两个4中间不构成长连禁手
            Value_Board[x][y].direction[color - 1].Right_5 = true;
            return;
        }
        //如果是白棋，则长连也算赢 
        if (s[i] + s[i + 4] >= 5 && color == WHITE) {    //只有黑棋有禁手
            Value_Board[x][y].direction[color - 1].Right_5 = true;
            return;
        }
        //4连
        else if (s[i] + s[i + 4] == 3) {
            int flag = 0;
            if (s_e[i] > 0 && judge_next(x, y, s[i], i, color)) {
                flag++;
            }
            if (s_e[i + 4] > 0 && judge_next(x, y, s[i + 4], i + 4, color)) {
                flag++;
            }

            if (flag == 2) {    //活四
                Value_Board[x][y].direction[color - 1].Living_4 += 1;
            }
            else if (flag == 1) {       //冲四
                Value_Board[x][y].direction[color - 1].Rush_4 += 1;
            }
            else {
                ;       //两边都被堵了或者下不了，没用
            }
        }
        //3连
        else if (s[i] + s[i + 4] == 2) {
            //检验上下方有没有可能冲四,两边都是冲四就是活四    形如  “xxxox”
            int flag = 0;
            if (s_e[i] == 1 && s_e_s[i] == 1) {
                if (judge_next(x, y, s[i], i, color)) {      //检验“xxxox”的o处
                    flag++;
                }
            }
            if (s_e[i + 4] == 1 && s_e_s[i + 4] == 1) {
                if (judge_next(x, y, s[i + 4], i + 4, color)) {     //检验“xoxxx”处的o处
                    flag++;
                }
            }
            if (flag == 2) {
                //形如  "xoxxxox"且两个0处均能落子形成活四
                Value_Board[x][y].direction[color - 1].Living_4 += 1;
            }
            else if (flag == 1) {
                //形如 "xxxox"且0处能落子形成冲四
                Value_Board[x][y].direction[color - 1].Rush_4 += 1;
            }
            else {
                //检查上方是否有活三，即下一步落子在上方第一个空位上能否形成活四；如果没有活三，判断是否有冲3
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
        //二连
        else if (s[i] + s[i + 4] == 1) {
            int flag = 0;
            //活四冲四判断
            //形如上或下"oxxoxx" / "xxoxxo"为冲四
            //形如上加下"xxoxxoxx" 为活四
            if (s_e[i] == 1 && s_e_s[i] == 2) {
                if (judge_next(x, y, s[i], i, color)) {
                    flag++;      //检验“oxxoxx”右边那个o
                }
            }
            if (s_e[i + 4] == 1 && s_e_s[i + 4] == 2) {
                if (judge_next(x, y, s[i + 4], i + 4, color)) {
                    flag++;      //检验“xxoxxo”左边那个o
                }
            }
            if (flag == 2) {
                Value_Board[x][y].direction[color - 1].Living_4 += 1;
            }
            else if (flag == 1) {
                Value_Board[x][y].direction[color - 1].Rush_4 += 1;
            }
            else {
                //活三判断
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
            //判断活2（计算价值用）
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
    //信息统计完毕
}
bool next_check_ban(int x, int y, int color)
{ //用于判断关键点是否是禁手
    int s[8];       //s表示附近的8个点都与中间点相同（same）0-7依次代表上，右上，右，右下，下，左下，左，左上
    int s_e[8];     //记录连续相同颜色棋子后的空位
    int s_e_s[8];   //记录空位后的相同颜色数
    int s_e_s_e[8];
    int s_e_s_e_s[8];
    //初始化数组，赋值当然全为0
    for (int j = 0; j < 8; j++) {
        s[j] = s_e[j] = s_e_s[j] = s_e_s_e[j] = s_e_s_e_s[j] = 0;
    }
    //计算各个方向的信息
    int i, j;
    // 向上搜索即j--;
    for (i = y, j = x - 1; j >= 0 && aRecordBoard[j][i] == color; j--, s[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == NONE; j--, s_e[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == color; j--, s_e_s[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == NONE; j--, s_e_s_e[0]++);
    for (; j >= 0 && aRecordBoard[j][i] == color; j--, s_e_s_e_s[0]++);
    // 向右上搜索即j--,i++;
    for (i = y + 1, j = x - 1; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == NONE; i++, j--, s_e[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s_e_s[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == NONE; i++, j--, s_e_s_e[1]++);
    for (; i < SIZE && j >= 0 && aRecordBoard[j][i] == color; i++, j--, s_e_s_e_s[1]++);
    // 向右搜索即i++;
    for (i = y + 1, j = x; i < SIZE && aRecordBoard[j][i] == color; i++, s[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == NONE; i++, s_e[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == color; i++, s_e_s[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == NONE; i++, s_e_s_e[2]++);
    for (; i < SIZE && aRecordBoard[j][i] == color; i++, s_e_s_e_s[2]++);
    // 向右下搜索即j++,i++;
    for (i = y + 1, j = x + 1; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == NONE; i++, j++, s_e[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s_e_s[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == NONE; i++, j++, s_e_s_e[3]++);
    for (; i < SIZE && j < SIZE && aRecordBoard[j][i] == color; i++, j++, s_e_s_e_s[3]++);
    // 向下搜索即j++;
    for (i = y, j = x + 1; j < SIZE && aRecordBoard[j][i] == color; j++, s[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == NONE; j++, s_e[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == color; j++, s_e_s[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == NONE; j++, s_e_s_e[4]++);
    for (; j < SIZE && aRecordBoard[j][i] == color; j++, s_e_s_e_s[4]++);
    // 向左下搜索即j++,i--;
    for (i = y - 1, j = x + 1; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == NONE; i--, j++, s_e[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s_e_s[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == NONE; i--, j++, s_e_s_e[5]++);
    for (; i >= 0 && j < SIZE && aRecordBoard[j][i] == color; i--, j++, s_e_s_e_s[5]++);
    // 向左搜索即i--;
    for (i = y - 1, j = x; i >= 0 && aRecordBoard[j][i] == color; i--, s[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == NONE; i--, s_e[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == color; i--, s_e_s[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == NONE; i--, s_e_s_e[6]++);
    for (; i >= 0 && aRecordBoard[j][i] == color; i--, s_e_s_e_s[6]++);
    // 向左上搜索即j--,i--;
    for (i = y - 1, j = x - 1; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == NONE; i--, j--, s_e[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s_e_s[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == NONE; i--, j--, s_e_s_e[7]++);
    for (; i >= 0 && j >= 0 && aRecordBoard[j][i] == color; i--, j--, s_e_s_e_s[7]++);
    //统计完毕，下面应当开始计算4个方向活3活4的数目及禁手
    int Living_4, Rush_4, Living_3;
    Living_4 = Rush_4 = Living_3 = 0;
    //首先判断是否成连五，若成连五，显然不构成禁手
    for (int i = 0; i < 4; i++) {
        if (s[i] + s[i + 4] == 4) {
            //正确五连，说明该关键点不是禁手，返回true
            return true;
        }
        //4连
        else if (s[i] + s[i + 4] == 3) {
            int flag = 0;
            if (s_e[i] > 0 && judge_next(x, y, s[i], i, color)) {
                flag++;
            }
            if (s_e[i + 4] > 0 && judge_next(x, y, s[i + 4], i + 4, color)) {
                flag++;
            }

            if (flag == 2) {    //活四
                Living_4 += 1;
            }
            else if (flag == 1) {       //冲四
                Rush_4 += 1;
            }
        }
        // 3连
        else if (s[i] + s[i + 4] == 2) {
            // 检验上下方有没有可能冲四，两边都是冲四就是活四，形如“xxxox”
            int flag = 0;
            if (s_e[i] == 1 && s_e_s[i] == 1) {
                if (judge_next(x, y, s[i], i, color)) { // 检验“xxxox”的o处
                    flag++;
                }
            }
            if (s_e[i + 4] == 1 && s_e_s[i + 4] == 1) {
                if (judge_next(x, y, s[i + 4], i + 4, color)) { // 检验“xoxxx”处的o处
                    flag++;
                }
            }
            if (flag == 2) {
                // 形如 "xoxxxox"且两个0处均能落子形成活四
                Living_4 += 1;
            }
            else if (flag == 1) {
                // 形如 "xxxox"且0处能落子形成冲四
                Rush_4 += 1;
            }
            else {
                // 检查上方是否有活三，即下一步落子在上方第一个空位上能否形成活四
                bool flag_living_3 = false;

                if ((s_e[i] > 2 || (s_e[i] == 2 && s_e_s[i] == 0))
                    && (s_e[i + 4] > 1 || (s_e[i + 4] == 1 && s_e_s[i + 4] == 0))) {
                    if (judge_next(x, y, s[i], i, color)) {    // 检验xxx上边的第一个o处
                        flag_living_3 = true;
                    }
                }
                // 与上方相同道理，现在检测下方
                if ((s_e[i + 4] > 2 || (s_e[i + 4] == 2 && s_e_s[i + 4] == 0))
                    && (s_e[i] > 1 || (s_e[i] == 1 && s_e_s[i] == 0))) {
                    if (judge_next(x, y, s[i + 4], i + 4, color)) {    // 检验xxx下边的第一个o处
                        flag_living_3 = true;
                    }
                }
                if (flag_living_3) {
                    Living_3 += 1;
                }
            }
        }
        // 二连
        else if (s[i] + s[i + 4] == 1) {
            int flag = 0;
            // 活四冲四判断
            if (s_e[i] == 1 && s_e_s[i] == 2) {
                if (judge_next(x, y, s[i], i, color)) {
                    flag++; // 检验“oxxoxx”右边那个o
                }
            }
            if (s_e[i + 4] == 1 && s_e_s[i + 4] == 2) {
                if (judge_next(x, y, s[i + 4], i + 4, color)) {
                    flag++; // 检验“xxoxxo”左边那个o
                }
            }
            if (flag == 2) {
                Living_4 += 1;
            }
            else if (flag == 1) {
                Rush_4 += 1;
            }
            else {
                // 活三判断
                bool flag_living_3 = false;
                if (s_e[i] == 1 && s_e_s[i] == 1
                    && (s_e_s_e[i] > 1 || (s_e_s_e[i] == 1 && s_e_s_e_s[i] == 0))
                    && (s_e[i + 4] > 1 || (s_e[i + 4] == 1 && s_e_s[i + 4] == 0))) {
                    if (judge_next(x, y, s[i], i, color)) {   // 检验“ooxxoxoo"中间的空位
                        flag_living_3 = true;
                    }
                }
                if (s_e[i + 4] == 1 && s_e_s[i + 4] == 1
                    && (s_e_s_e[i + 4] > 1 || (s_e_s_e[i + 4] == 1 && s_e_s_e_s[i + 4] == 0))
                    && (s_e[i] > 1 || (s_e[i] == 1 && s_e_s[i] == 0))) {
                    if (judge_next(x, y, s[i + 4], i + 4, color)) {   // 检验“ooxoxxo"中间的空位
                        flag_living_3 = true;
                    }
                }
                if (flag_living_3) {
                    Living_3 += 1;
                }
            }
        }
        // 单独一子
        else if (s[i] + s[i + 4] == 0) {
            bool flag = false;
            // 活四冲四判断
            if (s_e[i] == 1 && s_e_s[i] == 3) {
                if (judge_next(x, y, s[i], i, color)) {   // 需要判断的点是“oxoxxx”中间的o
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
            // 活三判断
            if (!flag) {
                bool flag_living_3 = false;
                if (s_e[i] == 1 && s_e_s[i] == 2
                    && (s_e_s_e[i] > 1 || (s_e_s_e[i] == 1 && s_e_s_e_s[i] == 0))
                    && (s_e[i + 4] > 1 || (s_e[i + 4] == 1 && s_e_s[i + 4] == 0))) {
                    if (judge_next(x, y, s[i], i, color)) {   // 需要判断的点是中间的o
                        flag_living_3 = true;
                    }
                }
                if (s_e[i + 4] == 1 && s_e_s[i + 4] == 2
                    && (s_e_s_e[i + 4] > 1 || (s_e_s_e[i + 4] == 1 && s_e_s_e_s[i + 4] == 0))
                    && (s_e[i] > 1 || (s_e[i] == 1 && s_e_s[i] == 0))) {
                    if (judge_next(x, y, s[i + 4], i + 4, color)) {   // 需要判断的点是中间的o
                        flag_living_3 = true;
                    }
                }
                if (flag_living_3) {
                    Living_3 += 1;
                }
            }
        }
    }
    if (Living_3 >= 2 && Living_4 + Rush_4 < 1) {             // 除了一个四一个三以外，其余情况下只要和大于等于2，一定是禁手。
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
        return true;//如果是白棋显然没有禁手问题
    }
    int next_hang, next_lie;
    distance++;    //因为相隔一个，坐标数要++
    if (Direction >= 4)
    {
        distance = -distance;       //方向相反，加减应随之相反
    }
    //计算关键点坐标
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
        printf("传入的方向有误");
        break;
    }
    bool if_just_evaluate = false;
    if (aRecordBoard[hang][lie] != NONE)
    {
        if_just_evaluate = true;
    }
    aRecordBoard[hang][lie] = color;        //将刚才那个子落下
    bool flag = next_check_ban(next_hang, next_lie, color);
    if (!if_just_evaluate)
    {
        //适应判断局面分的需要，在判断局面分时，原本这里就有子，不能擦除 
        aRecordBoard[hang][lie] = NONE;        //恢复 
    }
    if (flag) {
        return true;
    }
    else {
        return false;
    }
}
//检查禁手函数（若为禁手则判负）
bool judge_if_banhand(int x, int y, int color)
{
    if (Value_Board[x][y].direction[color - 1].Living_3 >= 2 && Value_Board[x][y].direction[color - 1].Living_4 == 0 && Value_Board[x][y].direction[color - 1].Rush_4 == 0) {
        return false;
    }
    return true;
}
//某点估值累加函数
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
    //优先级是对方冲四>己方活四>对方活3
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
    //关于己方活三活二对面冲三等的赋值
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
//找点函数：找出所有可能的落子点，计算得分并判断是否为关键点（必杀或必挡）
int Find_Points(PTR_To_Points All_Points, int color, bool flag, bool* flag_if_win, PTR_To_Point Bisha, bool* flag_will_lose, PTR_To_Point Bidang)
{
    int i, j;
    int index = 0;
    PTR_To_Point cunchu;  //指针数组，存储已搜索过的点
    cunchu = (PTR_To_Point)malloc(sizeof(Point) * 225);//给cunchu指针分配225个Point结构体的内存
    int cunchu_index = 0;//记录已搜索过的点的数量
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (aRecordBoard[i][j] != NONE) {         //如果有棋子
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
                            bool flag_cf = true;//标记是否重复判断
                            for (int t = 0; t < cunchu_index; t++) {
                                if (m == cunchu[t].hang && n == cunchu[t].lie) {
                                    flag_cf = false;//先检查在当前所有已存储点中是否有重复，有则更新标记且跳出循环
                                    break;
                                }
                            }
                            if (!flag_cf) {  //说明该点已经判断过了，直接到下一个点去
                                continue;
                            }
                            else {         //没判断过，存进来
                                cunchu[cunchu_index].hang = m;
                                cunchu[cunchu_index].lie = n;
                                cunchu_index++;
                            }
                            Collect_Information(m, n, BLACK);
                            Collect_Information(m, n, WHITE);
                            //如果是轮白棋则不用判断，如果轮黑棋但这步是禁手，则也不放入All_Points中
                            if (color == WHITE || judge_if_banhand(m, n, color)) {
                                if (Value_Board[m][n].direction[color - 1].Right_5) { //如果己方有终结手需要标记出来
                                    Bisha->hang = m;
                                    Bisha->lie = n;//记录下来必杀点坐标
                                    *flag_if_win = true;
                                    return ++index;
                                }
                                int ag_color = (color == WHITE ? BLACK : WHITE);
                                if ((ag_color == WHITE || judge_if_banhand(m, n, ag_color)) && Value_Board[m][n].direction[ag_color - 1].Right_5) {
                                    Bidang->hang = m;
                                    Bidang->lie = n;//对方有杀棋的情况，记下来必挡点的坐标
                                    *flag_will_lose = true;
                                }
                                All_Points[index].p.hang = m;
                                All_Points[index].p.lie = n;
                                if (flag) {
                                    evaluate_value(m, n);//对当前节点进行估值
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
//依照估值对节点进行快速排序
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
                int temp;    //中间变量：用于交换s[i]和s[j]的分数、行、列坐标
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
//查找所有叶子节点对于color方的估值
int Find_base_point(int color)
{
    PTR_To_Points All_Points;     //所有选点
    All_Points = (PTR_To_Points)malloc(sizeof(Points) * 225);//给指针数组All_Points分配内存
    bool flag_if_win = false;
    bool flag_will_lose = false;
    Point Bisha, Bidang;//必杀、必挡的关键点
    int n = Find_Points(All_Points, color, NO_NEED_VALUE, &flag_if_win, &Bisha, &flag_will_lose, &Bidang);//关键点数量
    if (flag_if_win) {	//说明底层轮到己方下时有终结手，返回一个极大值
        return 200000;
    }
    if (flag_will_lose) {//说明底层轮到己方下时只能去堵对面的，只有一种选择
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
        value = Evaluate_Current_Situation_Value(color);     //拟落子并估值
        aRecordBoard[All_Points[i].p.hang][All_Points[i].p.lie] = NONE;//撤销落子并判断
        if (value > max) {
            max = value;
        }
    }
    return max;
}
//实现Minimax和剪枝算法的递归函数，返回最优选择的value
int Best_choice(int color, PTR_To_Point final, int depth, int a, int b) {
    switch (depth) {       //根据层深度选定搜索宽度
    case 10:
        WIDTH = 14;
        break;
    case 9:
        WIDTH = 14;
        break;
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
    //“底层”定义为己方有必杀手或终结手
    //AI为偶数层，人为奇数层
    //递归终止条件为到达底层，此时要根据局面得分选点
    if (depth == 0) {
        int value = Find_base_point(color);
        return value;
    }
    //若非底层，则应该根据点分选点
    int next_color = (color == BLACK ? WHITE : BLACK); //定义下一步的棋子颜色
    PTR_To_Points All_Points;     //所有选点
    All_Points = (PTR_To_Points)malloc(sizeof(Points) * 225);//分配内存
    if (All_Points == NULL) {
        printf("malloc error");
        exit(1); //内存分配出错异常退出
    }
    bool flag_if_win = false;
    bool flag_will_lose = false;
    Point Bisha, Bidang;
    int n = Find_Points(All_Points, color, NEED_VALUE, &flag_if_win, &Bisha, &flag_will_lose, &Bidang);
    //如果轮到color方，此步能终结比赛
    if (flag_if_win) {
        if (depth % 2 == 1) {
            //即己方落子后，发现对方下一步能终结比赛，说明己方该落子不合适，应返回一个极小值
            return -200000;
        }
        else {
            //即对方落子(或初始局面)时，我方下一步能终结比赛，说明对方该落子不合适，应返回一个极大值
            //同时如果此时是根节点即初始局面，则应当返回己方终结手的坐标
            if (depth == DEPTH) {
                final->hang = Bisha.hang;
                final->lie = Bisha.lie;
            }
            return 200000;
        }
    }
    if (n < WIDTH) {//即可找的点少于14个
        WIDTH = n;
    }
    int temp_width = WIDTH;
    //根据节点评分对所有候选落子进行quicksort排序，目的是将高评分落子点排到前面，减小搜索树规模
    quicksort(All_Points, 0, n - 1);
    int i, j;
    PTR_To_Points choice;       //最优的WIDTH个选点
    choice = (PTR_To_Points)malloc(sizeof(Points) * WIDTH);
    //将ALL_Points中的最优的WIDTH个点复制到choice[]中去
    for (i = 0, j = n - 1; i < WIDTH; i++, j--) {
        choice[i].p = All_Points[j].p;
        choice[i].score = All_Points[j].score;
        choice[i].min = a;  //继承来自父节点的α
        choice[i].max = b;  //继承来自父节点的β
    }
    int* value;  //记录每个子节点的回推值
    value = (int*)malloc(sizeof(int) * WIDTH);
    //在当前层中横向搜索
    for (i = 0; i < temp_width; i++) {
        //step1:先把棋子落上去
        aRecordBoard[choice[i].p.hang][choice[i].p.lie] = color;
        //step2:根据下面的值回推回来
        value[i] = Best_choice(next_color, final, depth - 1, a, b);
        //step3:根据回推值改变α和β
        //如果是偶数层(己方落子,取子节点回推值中的最大值，因此改变下限min)
        if (depth % 2 == 0) {
            if (value[i] > a) {//若比下限大，则改变下限
                a = value[i];
                //顶层根节点时偶数层，需要知道落点位置
                if (depth == DEPTH) {
                    final->hang = choice[i].p.hang;
                    final->lie = choice[i].p.lie;
                }
            }
            if (a >= b) {
                //即α>=β，不用再往下搜索了，本层给上层返回α
                aRecordBoard[choice[i].p.hang][choice[i].p.lie] = NONE;
                return a;
            }
        }
        //如果是奇数层(对方落子，取子节点回推值中的最小值，因此改变上限max)
        else {
            if (value[i] < b) {
                b = value[i];
            }
            if (a >= b) {
                //即α>=β，不用往下搜索栏，本层给上层返回β
                aRecordBoard[choice[i].p.hang][choice[i].p.lie] = NONE;
                return b;
            }
        }
        //step4:把落的子擦除
        aRecordBoard[choice[i].p.hang][choice[i].p.lie] = NONE;
    }
    if (depth % 2 == 0) {//AI层
        return a;
    }
    else {             //对手层
        return b;
    }
}
