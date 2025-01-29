#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//��Ӧ���̳ߴ�
#define SIZE 15
//��Ӧ������ɫ
#define NONE 0
#define BLACK 1
#define WHITE 2
//��Ӧÿ����״�ļ�ֵ
#define Value_Right_5 50000
#define Value_Living_4 5000
#define Value_Rush_4 1000
#define Value_Living_3 1000
#define Value_Rush_3 300
#define Value_Living_2 300
#define Value_Rush_2 100
//�������ҵ������ʱ�費��Ҫ��ֵ
#define NEED_VALUE 1
#define NO_NEED_VALUE 0
//�����������
extern int DEPTH;
//����ѡ����
#define Base_Width 15
extern int WIDTH;
#define N_Infinity -10000000          //���ĳ�ֵΪ������
#define P_Infinity 10000000           //�µĳ�ֵΪ������
//�ĸ�structure���͵Ķ���
typedef struct {                      //��¼���λ��
    int hang;
    int lie;
} Point, * PTR_To_Point; 			  //�ڵ��ָ��ڵ��ָ��
typedef struct {
    Point p;
    int score;
    int min;
    int max;
} Points, * PTR_To_Points;
struct Point_Inf {                     //�ýṹ���ڼ�¼ĳ��ĳһ�����ϵ�������Ϣ
    bool Right_5;
    int Living_4;
    int Rush_4;
    int Living_3;
    int Rush_3;
    int Living_2;
    int Rush_2;
};
struct Point_Score {
    struct Point_Inf direction[2];      //direction[0]��ʾ����   direction[1]��ʾ����
    int score[2];                       //score[0]��ʾ����÷�     score[1]��ʾ����÷�
    int allscore;
};
//������������(extern ֻ���������壬��ֹ�����ڶ��Դ�ļ����ظ�����)��
extern int ChessBoard[SIZE][SIZE];                          //������������ʾ����
extern int aRecordBoard[SIZE][SIZE];                        //���������ڼ�¼���̵�ǰ���
extern struct Point_Score Value_Board[SIZE][SIZE];          //������������¼ÿ����ĸ�����Ϣ