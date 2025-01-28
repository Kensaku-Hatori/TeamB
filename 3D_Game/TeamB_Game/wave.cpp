//============================================================
//
//ウェーブ処理[wave.cpp]
//Author:Rio Ohno
//
//============================================================

#include"wave.h"
#include"enemy.h"
#include<stdio.h>

//マクロ定義
#define MAXX_CHAR (256)										//最大文字数

//.txt
static const char* WAVE_TXT[MAX_WAVE] =
{
	"data\\TEXT\\wave\\wave00.txt",
	"data\\TEXT\\wave\\wave01.txt",
	"data\\TEXT\\wave\\wave02.txt",
	"data\\TEXT\\wave\\wave03.txt",
};

//グローバル変数宣言
int g_nWave;												//ウェーブのカウント
bool g_bFinish;												//ウェーブの終了判定

//============================================================
// ウェーブの初期化処理
//============================================================
void InitWave()
{
	g_nWave = 0;
	g_bFinish = false;
}

//============================================================
// ウェーブの読込処理
//============================================================
void LoadWave()
{
	int type = 0/*, nLife = 0*/;
	D3DXVECTOR3 pos = {}, rot = {};

	//外部ファイルへのポインタ
	FILE* pFile;

	//waveが全て終了しているなら
	if (g_nWave >= MAX_WAVE)
	{
		pFile = NULL;

		g_bFinish = true;									//ウェーブ終了

	}
	else
	{	//各ウェーブのファイルを開く

		pFile = fopen(WAVE_TXT[g_nWave], "r");
	}

	if (pFile != NULL)
	{
		while (1)
		{
			char aString[MAXX_CHAR];

			//ファイルを読みこむ
			fscanf(pFile, "%s", &aString[0]);
			if (strcmp(aString, "ENEMYSET") == 0)//ENEMYSETを読込んだなら
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);//TYPEを読み込んだら

					if (strcmp(aString, "TYPE") == 0)
					{
						//種類の取得
						fscanf(pFile, "%d", &type);
					}
					else if (strcmp(aString, "POS") == 0)//POSを読込んだなら
					{
						//位置の取得
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(aString, "ROT") == 0)//LIFEを読込んだなら
					{
						//向きの取得
						fscanf(pFile, "%f", &rot.x);
						fscanf(pFile, "%f", &rot.y);
						fscanf(pFile, "%f", &rot.z);
					}
					else if (strcmp(aString, "END_ENEMYSET") == 0)//END_ENEMYSETを読込んだなら
					{
						//敵の設定
						SetEnemy(pos,type, rot);

						break;
					}
				}
			}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				break;
			}
		}

		//ファイルを閉じる
		fclose(pFile);

		//ウェーブのカウントアップ
		g_nWave++;
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