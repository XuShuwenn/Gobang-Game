#pragma once
#include"Gobang.h"
//һ���������ú������������̡����ӡ��Ϸ����жϡ���Ӯ�жϵȻ�������
void initRecordBorard();						//����¼��������
void RebuildChessBoard();                       //�����ؽ�����
void RecordToChessBoard();      				//��aRecordBoard���̵�ǰ��ּ�¼����ʾ������
void DrawChessBoard();							//�����̺���
bool IsValidPosition(int x, int y);				//�ж�λ���Ƿ��ںϷ���Χ��
bool judge_result();                        	//�ж���Ӯ����
