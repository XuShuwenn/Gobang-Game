#pragma once
#include "Gobang.h"
//二、AI算法实现函数：
//1. 统计和估价函数
void Collect_Information(int hang, int lie, int color);         //统计某点棋型信息的函数
bool judge_next(int hang, int lie, int distance, int direction, int color);
bool next_check_ban(int hang, int lie, int color);
bool judge_if_banhand(int hang, int lie, int color);			//判断某点是否为禁手
void evaluate_value(int hang, int lie);							//给某点估值
int Evaluate_Current_Situation_Value(int color);				//给局面估值
//2.Minimax+αβ剪枝算法实现（AI核心函数）
int Best_choice(int color, PTR_To_Point final, int depth, int a, int b);
int Find_Points(PTR_To_Points All_Points, int color, bool flag, bool* flag_if_win, PTR_To_Point Bisha, bool* flag_will_lose, PTR_To_Point Bidang); //返回的是找到的点数
void quicksort(PTR_To_Points s, int left, int right);
int Find_base_point(int color);
