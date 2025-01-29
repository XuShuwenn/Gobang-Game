#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//对应棋盘尺寸
#define SIZE 15
//对应棋子颜色
#define NONE 0
#define BLACK 1
#define WHITE 2
//对应每种形状的价值
#define Value_Right_5 50000
#define Value_Living_4 5000
#define Value_Rush_4 1000
#define Value_Living_3 1000
#define Value_Rush_3 300
#define Value_Living_2 300
#define Value_Rush_2 100
//决定在找点的数组时需不需要点值
#define NEED_VALUE 1
#define NO_NEED_VALUE 0
//定义搜索深度
extern int DEPTH;
//定义选点宽度
#define Base_Width 15
extern int WIDTH;
#define N_Infinity -10000000          //α的初值为负无穷
#define P_Infinity 10000000           //β的初值为正无穷
//四个structure类型的定义
typedef struct {                      //记录点的位置
    int hang;
    int lie;
} Point, * PTR_To_Point; 			  //节点和指向节点的指针
typedef struct {
    Point p;
    int score;
    int min;
    int max;
} Points, * PTR_To_Points;
struct Point_Inf {                     //该结构用于记录某点某一方向上的连子信息
    bool Right_5;
    int Living_4;
    int Rush_4;
    int Living_3;
    int Rush_3;
    int Living_2;
    int Rush_2;
};
struct Point_Score {
    struct Point_Inf direction[2];      //direction[0]表示黑棋   direction[1]表示白棋
    int score[2];                       //score[0]表示黑棋得分     score[1]表示白棋得分
    int allscore;
};
//三个基本数组(extern 只声明不定义，防止变量在多个源文件中重复定义)：
extern int ChessBoard[SIZE][SIZE];                          //此数组用来显示棋盘
extern int aRecordBoard[SIZE][SIZE];                        //此数组用于记录棋盘当前格局
extern struct Point_Score Value_Board[SIZE][SIZE];          //此数组用来记录每个点的各种信息