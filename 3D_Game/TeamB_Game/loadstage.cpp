#include "loadstage.h"

//*****************************
// スクリプト以前を読み込む処理
//*****************************
void LoadModelViewer()
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	FILE* pFile = fopen("data\\TEXT\\model.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			fgets(cData,2,pFile);
			if (*cData != '#')
			{
				strcat(cData1, cData);
				if (strcmp(&cData1[0],"SCRIPT") == 0)
				{
					cData1[0] = { NULL };
					SkipComment(pFile);
					break;
				}
			}
			else
			{
				cData1[0] = { NULL };
				SkipComment(pFile);
			}
		}
		LoadStart(pFile);
	}
}
//*****************************
// シャープ以降を読み飛ばす処理
//*****************************
void SkipComment(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a)
		{
			strcat(cData1, cData);
		}
		else
		{
			break;
		}
	}
}
//*****************************
// スクリプト以降を読み込む処理
//*****************************
void LoadStart(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	int nData;
	char *FilePath[5][32];

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ')
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "NUM_TEXTURE") == 0)
			{
				SkipEqual(pFile);
				nData = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "TEXTURE_FILENAME") == 0)
			{
				SkipEqual(pFile);
				FilePath[0][0] = LoadPath(pFile);
				int i = 0;
			}
		}
		else
		{
			cData1[0] = { NULL };
			SkipComment(pFile);
		}
	}
}
//*****************************
// 　＝　を読み飛ばす処理
//*****************************
void SkipEqual(FILE* pFile)
{
	int nData;
	nData = fgetc(pFile);
	nData = fgetc(pFile);
	nData = fgetc(pFile);
}
//*******************************
// テクスチャの種類を読み込む処理
//*******************************
void LoadTextureNum(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	int texturenum;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			texturenum = atoi(cData1);
			cData1[0] = { NULL };
			if (*cData != '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
}
//***********************************
// テクスチャのパスを読み込む処理処理
//***********************************
void LoadTexturePath(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char filepath[32] = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			strcpy(filepath,cData1);
			cData1[0] = { NULL };
			if (*cData != '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
}
//***************************
// モデルの種類を読み込む処理
//***************************
int LoadInt(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	int nData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			nData = atoi(cData1);
			cData1[0] = { NULL };
			if (*cData != '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return nData;
}
//******************************
// // モデルのパスを読み込む処理
//******************************
char *LoadPath(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char filepath[32] = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			strcpy(filepath, cData1);
			cData1[0] = { NULL };
			if (*cData != '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return &filepath[0];
}