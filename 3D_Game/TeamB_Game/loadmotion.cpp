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
		LoadMotionStart(pFile);
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
	int CharactorCount, PartsCount;
	CharactorCount = 0;
	PartsCount = 0;
	int MotionCount, KeyCount, KeyPartsCount;
	MotionCount = 0;
	KeyCount = 0;
	KeyPartsCount = 0;
	MODELINFO ModelInfo[MAX_PARTS];
	MOTIONINFO MotionInfo[MAX_MOTION];

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "NUM_MODEL") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
				int i = 0;
			}
			else if (strcmp(&cData1[0], "MODEL_FILENAME") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				ModelPath[0] = LoadPath(pFile);
				int i = 0;
			}
			else if (strcmp(&cData1[0], "CHARACTERSET") == 0)
			{
				cData1[0] = { NULL };
				while (1)
				{
					cData2[0] = LoadCharactorInfo(pFile,&CharactorCount,&PartsCount,ModelInfo);
					if (strcmp(cData2[0], CHARACTOR) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "MOTIONSET") == 0)
			{
				cData1[0] = { NULL };
				while (1)
				{
					cData2[0] = LoadMotionInfo(pFile,&MotionCount,&KeyCount,&KeyPartsCount,&MotionInfo[MotionCount]);
					int i = 0;
					if (strcmp(cData2[0], MOTION) == 0)
					{
						MotionCount++;
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "END_SCRIPT") == 0)
			{
				MotionCount = 0;
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
// キャラクター情報を読み込む処理
//*************************************
char* LoadCharactorInfo(FILE* pFile,int *nCharactor,int *nParts,MODELINFO *ModelInfo)
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
			if (strcmp(&cData1[0], "NUM_PARTS") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "MOVE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "JUMP") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "RADIUS") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "HEIGHT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "PARTSSET") == 0)
			{
				cData1[0] = { NULL };
				while (1)
				{
					cData3[0] = LoadPartsInfo(pFile,nParts,ModelInfo);
					if (strcmp(cData3[0], PARTS) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "END_CHARACTERSET") == 0)
			{
				*nCharactor+=1;
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************
// パーツ情報を読み込む処理
//*************************
char* LoadPartsInfo(FILE* pFile,int *Parts,MODELINFO *ModelInfo)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };

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
				ModelInfo->nIndx = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "PARENT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				ModelInfo->Parent = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "POS") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				ModelInfo->pos.x = LoadFloat(pFile);
				ModelInfo->pos.y = LoadFloat(pFile);
				ModelInfo->pos.z = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				ModelInfo->rot.x = LoadFloat(pFile);
				ModelInfo->rot.y = LoadFloat(pFile);
				ModelInfo->rot.z = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "END_PARTSSET") == 0)
			{
				*Parts+=1;
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// モーション情報を読み込む処理
//*************************************
char* LoadMotionInfo(FILE* pFile,int *Motion,int *Key, int* nKeyParts,MOTIONINFO *MotionInfo)
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
				MotionInfo->bLoop = (bool)LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "NUM_KEY") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				MotionInfo->nNumKey = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "FOOTSTEP") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
				nData = LoadInt(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				nData = LoadInt(pFile);
				nData = LoadInt(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "SHOT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				nData = LoadInt(pFile);
				nData = LoadInt(pFile);
				nData = LoadInt(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "SMOKE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				nData = LoadInt(pFile);
				nData = LoadInt(pFile);
				nData = LoadInt(pFile);
				nData = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "KEYSET") == 0)
			{
				cData1[0] = { NULL };
				while (1)
				{
					cData3[0] = LoadKeyInfo(pFile,Key, nKeyParts, MotionInfo);
					int i = 0;
					if (strcmp(cData3[0], KEY) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "END_MOTIONSET") == 0)
			{
				*Key = 0;
				break;
			}
		}
	}
	return &cData1[0];
}
//*****************************
// キー情報を読み込む処理
//*****************************
char* LoadKeyInfo(FILE* pFile, int* nKey, int* nKeyParts, MOTIONINFO* Motion)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	char *cData3[64] = { NULL };

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
			if (strcmp(&cData1[0], "FRAME") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Motion->aKeyInfo[*nKey].nFrame = LoadInt(pFile);
				int i = 0;
			}
			else if (strcmp(&cData1[0], "KEY") == 0)
			{
				cData1[0] = { NULL };
				while (1)
				{
					cData3[0] = LoadKeyPartsInfo(pFile,nKey, nKeyParts, Motion);
					int i = 0;
					if (strcmp(cData3[0], KEYPARTS) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "END_KEYSET") == 0)
			{
				*nKeyParts = 0;
				*nKey+=1;
				break;
			}
		}
	}
	return &cData1[0];
}
//***********************************
// パーツごとのキー情報を読み込む処理
//***********************************
char* LoadKeyPartsInfo(FILE* pFile,int *nKey,int* nKeyParts,MOTIONINFO *MotionInfo)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };

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
				MotionInfo->aKeyInfo[*nKey].aKey[*nKeyParts].fPosX = LoadFloat(pFile);
				MotionInfo->aKeyInfo[*nKey].aKey[*nKeyParts].fPosY = LoadFloat(pFile);
				MotionInfo->aKeyInfo[*nKey].aKey[*nKeyParts].fPosZ = LoadFloat(pFile);
				int i = 0;
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				MotionInfo->aKeyInfo[*nKey].aKey[*nKeyParts].fRotX = LoadFloat(pFile);
				MotionInfo->aKeyInfo[*nKey].aKey[*nKeyParts].fRotY = LoadFloat(pFile);
				MotionInfo->aKeyInfo[*nKey].aKey[*nKeyParts].fRotZ = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "END_KEY") == 0)
			{
				*nKeyParts+=1;
				break;
			}
		}
	}
	return &cData1[0];
}