#pragma once
#include "Gobang.h"
//����AI�㷨ʵ�ֺ�����
//1. ͳ�ƺ͹��ۺ���
void Collect_Information(int hang, int lie, int color);         //ͳ��ĳ��������Ϣ�ĺ���
bool judge_next(int hang, int lie, int distance, int direction, int color);
bool next_check_ban(int hang, int lie, int color);
bool judge_if_banhand(int hang, int lie, int color);			//�ж�ĳ���Ƿ�Ϊ����
void evaluate_value(int hang, int lie);							//��ĳ���ֵ
int Evaluate_Current_Situation_Value(int color);				//�������ֵ
//2.Minimax+���¼�֦�㷨ʵ�֣�AI���ĺ�����
int Best_choice(int color, PTR_To_Point final, int depth, int a, int b);
int Find_Points(PTR_To_Points All_Points, int color, bool flag, bool* flag_if_win, PTR_To_Point Bisha, bool* flag_will_lose, PTR_To_Point Bidang); //���ص����ҵ��ĵ���
void quicksort(PTR_To_Points s, int left, int right);
int Find_base_point(int color);

