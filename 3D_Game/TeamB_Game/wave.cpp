//============================================================
//
//ウェーブ処理[wave.cpp]
//Author:Rio Ohno
//
//============================================================

#include"wave.h"
#include"enemy.h"
#include "boss.h"
#include<stdio.h>

//マクロ定義
#define WAVE_0 "data\\TEXT\\wave\\wave00.txt"						// ウェーブ0
#define WAVE_1 "data\\TEXT\\wave\\wave01.txt"						// ウェーブ1
#define WAVE_2 "data\\TEXT\\wave\\wave02.txt"						// ウェーブ2
#define WAVE_3 "data\\TEXT\\wave\\wave03.txt"						// ウェーブ3


//グローバル変数宣言
//LoadInfo g_Info[MAX_ENEMY];
MODE g_gamemode;
int g_nCntEnemy;
int g_nWave;												// ウェーブのカウント
bool g_bFinish;												// ウェーブの終了判定

//============================================================
// ウェーブの初期化処理
//============================================================
void InitWave(MODE mode)
{
	g_gamemode = mode;
	g_nCntEnemy = 0;
	g_nWave = 0;
	g_bFinish = false;
}

//============================================================
// ウェーブの読込処理
//============================================================
void LoadWave()
{
	FILE* pFile;											// 外部ファイルへのポインタ

	int type = 0;
	int Return = 0;
	D3DXVECTOR3 pos = {}, rot = {};

	//敵の数を取得
	int *pNumEnemy = GetNumEnemy();
	g_nCntEnemy = (int)pNumEnemy;

	//各ウェーブのファイルを開く
	switch (g_gamemode)
	{
	case MODE_STAGEONE://Wave1

		pFile = fopen(WAVE_0, "r");

		break;

	case MODE_STAGETWO://Wave2

		pFile = fopen(WAVE_1, "r");

		break;

	case MODE_STAGETHREE:

		pFile = fopen(WAVE_2, "r");

		break;

	case MODE_STAGEFOUR:

		pFile = fopen(WAVE_3, "r");

		break;

	default://例外

		pFile = NULL;

		g_bFinish = true;//ウェーブ終了

		break;
	}

	if (pFile != NULL)
	{
		while (1)
		{
			char aString[MAX_WORD];

			//ファイルを読みこむ
			Return = fscanf(pFile, "%s", &aString[0]);
			if (strcmp(aString, "ENEMYSET") == 0)//ENEMYSETを読込んだなら
			{
				while (1)
				{
					Return = fscanf(pFile, "%s", &aString[0]);//TYPEを読み込んだら

					if (strcmp(aString, "TYPE") == 0)
					{
						//種類の取得
						Return = fscanf(pFile, "%d", &type);
					}
					else if (strcmp(aString, "POS") == 0)//POSを読込んだなら
					{
						//位置の取得
						Return = fscanf(pFile, "%f", &pos.x);
						Return = fscanf(pFile, "%f", &pos.y);
						Return = fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(aString, "ROT") == 0)//LIFEを読込んだなら
					{
						//向きの取得
						Return = fscanf(pFile, "%f", &rot.x);
						Return = fscanf(pFile, "%f", &rot.y);
						Return = fscanf(pFile, "%f", &rot.z);
					}
					else if (strcmp(aString, "END_ENEMYSET") == 0)//END_ENEMYSETを読込んだなら
					{
						if (type == 3)
						{
							SetBoss(pos, rot);
						}
						else
						{
							//敵の設定
							SetEnemy(pos, type, rot);
						}

						break;
					}
				}
			}
			if (Return == EOF)
			{
				break;
			}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				break;
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		return;
	}
}

//============================================================
// ウェーブ数の取得
//============================================================
int GetWave()
{
	return g_nWave;
}

//============================================================
// ウェーブ終了の取得
//============================================================
bool GetFinish()
{
	return g_bFinish;
}