#include "loadmotion.h"

//*****************************
// スクリプト以前を読み込む処理
//*****************************
void LoadMotionViewer(char* cMotionPath)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	FILE* pFile = fopen((const char*)cMotionPath, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			fgets(cData, 2, pFile);
			if (*cData != '#')
			{
				strcat(cData1, cData);
				if (strcmp(&cData1[0], "SCRIPT") == 0)
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
// スクリプト以降を読み込む処理
//*****************************
void LoadMotionStart(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char* cData2[32] = { NULL };
	int nData;
	char* ModelPath[32];
	int ModelPathCount = 0;
	int PolygonePathCount = 0;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "NUM_MODEL") == 0)
			{
				SkipEqual(pFile);
				nData = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "MODEL_FILENAME") == 0)
			{
				SkipEqual(pFile);
				ModelPath[0] = LoadPath(pFile);
			}
			else if (strcmp(&cData1[0], "CHARACTORSET") == 0)
			{
				while (1)
				{
					SkipEqual(pFile);
					cData2[0] = LoadCharactorInfo(pFile);
					if (strcmp(cData2[0], CHARACTOR) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "MOTIONSET") == 0)
			{
				while (1)
				{
					SkipEqual(pFile);
					cData2[0] = LoadMotionInfo(pFile);
					if (strcmp(cData2[0], MOTION) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		else
		{
			cData1[0] = { NULL };
			if (cData[0] == '#')
			{
				SkipComment(pFile);
			}
		}
	}
}
//*************************************
// 空白以外が読み込めるまで読み込む処理
//*************************************
char* LoadCharactorInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	char *cData3[64] = { NULL };
	float fData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] == 0x20 || cData[0] == 0x09 || cData[0] == 0x23 || cData[0] == 0x0a)
		{
			strcat(cData2, cData);
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
		}
		else
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "NUM_PARTS") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "MOVE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "JUMP") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "RADIUS") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "HEIGHT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "PARTSSET") == 0)
			{
				while (1)
				{
					cData3[0] = LoadPartsInfo(pFile);
					if (strcmp(cData3[0], PARTS) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "END_CHARACTORSET") == 0)
			{
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************
// カメラ情報を読み込む処理
//*************************
char* LoadPartsInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	float fData;
	int nData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] == 0x20 || cData[0] == 0x09 || cData[0] == 0x23 || cData[0] == 0x0a)
		{
			strcat(cData2, cData);
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
		}
		else
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "INDEX") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "PARENT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "POS") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "END_PARTSSET") == 0)
			{
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// 空白以外が読み込めるまで読み込む処理
//*************************************
char* LoadMotionInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	char *cData3[64] = { NULL };
	float fData;
	int nData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] == 0x20 || cData[0] == 0x09 || cData[0] == 0x23 || cData[0] == 0x0a)
		{
			strcat(cData2, cData);
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
		}
		else
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "LOOP") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "NUM_KEY") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "KEYSET") == 0)
			{
				while (1)
				{
					cData3[0] = LoadKeyInfo(pFile);
					if (strcmp(cData3[0], KEY) == 0)
					{
						break;
					}
				}
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				break;
			}
			else if (strcmp(&cData1[0], "END_MOTIONSET") == 0)
			{
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// 空白以外が読み込めるまで読み込む処理
//*************************************
char* LoadKeyInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	float fData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] == 0x20 || cData[0] == 0x09 || cData[0] == 0x23 || cData[0] == 0x0a)
		{
			strcat(cData2, cData);
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
		}
		else
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "POS") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "END_KEYSET") == 0)
			{
				break;
			}
		}
	}
	return &cData1[0];
}