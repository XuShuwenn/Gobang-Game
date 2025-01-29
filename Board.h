#pragma once
#include"Gobang.h"
//一、基础设置函数：关于棋盘、落子、合法性判断、输赢判断等基础函数
void initRecordBorard();						//将记录棋盘置零
void RebuildChessBoard();                       //用于重建棋盘
void RecordToChessBoard();      				//将aRecordBoard棋盘当前格局记录到显示棋盘中
void DrawChessBoard();							//画棋盘函数
bool IsValidPosition(int x, int y);				//判断位置是否在合法范围内
bool judge_result();                        	//判断输赢函数
