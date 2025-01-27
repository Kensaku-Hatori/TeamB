#include "loadstage.h"
#include "loadmotion.h"
#include "meshfield.h"
#include "meshwall.h"

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
	fclose(pFile);
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
	char *cData2[32] = { NULL };
	int nData;
	char *FilePath[32];
	char FilePathPoly[MAX_FILEPATH][64];
	char FilePathModel[MAX_FILEPATH][64];
	NTYPE nType = { NULL };
	int ModelPathCount = 0;
	int PolygonePathCount = 0;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "NUM_TEXTURE") == 0)
			{
				SkipEqual(pFile);
				nData = LoadInt(pFile);
				nType.nPolygoneType = nData;
			}
			else if (strcmp(&cData1[0], "TEXTURE_FILENAME") == 0)
			{
				SkipEqual(pFile);
				FilePath[0] = LoadPath(pFile);
				strcpy(&FilePathPoly[PolygonePathCount][0],FilePath[0]);
				SetfieldTexture(&FilePathPoly[PolygonePathCount][0], PolygonePathCount);
				if (PolygonePathCount < nType.nPolygoneType)
				{
					PolygonePathCount++;
				}
			}
			else if (strcmp(&cData1[0], "NUM_MODEL") == 0)
			{
				SkipEqual(pFile);
				nData = LoadInt(pFile);
				nType.nModelType = nData;
			}
			else if (strcmp(&cData1[0], "MODEL_FILENAME") == 0)
			{
				SkipEqual(pFile);
				FilePath[0] = LoadPath(pFile);
				strcpy(&FilePathModel[ModelPathCount][0], FilePath[0]);
				SetStageModelInfo(&FilePathModel[ModelPathCount][0], ModelPathCount);
				if (ModelPathCount < nType.nModelType)
				{
					ModelPathCount++;
				}
			}
			else if (strcmp(&cData1[0], "CAMERASET") == 0)
			{
				while (1)
				{
					cData2[0] = LoadCameraInfo(pFile);
					if (strcmp(cData2[0], CAMERA) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "LIGHTSET") == 0)
			{
				while (1)
				{
					cData2[0] = LoadLightInfo(pFile);
					if (strcmp(cData2[0], LIGHT) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "SKYSET") == 0)
			{
				while (1)
				{
					cData2[0] = LoadSkyInfo(pFile);
					if (strcmp(cData2[0], SKY) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "MOUNTAINSET") == 0)
			{
				while (1)
				{
					cData2[0] = LoadMountInfo(pFile);
					if (strcmp(cData2[0], MOUNTAIN) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "FIELDSET") == 0)
			{
				while (1)
				{
					cData2[0] = LoadFieldInfo(pFile);
					if (strcmp(cData2[0], FIELD) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "WALLSET") == 0)
			{
				while (1)
				{
					cData2[0] = LoadWallInfo(pFile);
					if (strcmp(cData2[0], WALL) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "MODELSET") == 0)
			{
				while (1)
				{
					cData2[0] = LoadModelInfo(pFile);
					if (strcmp(cData2[0], MODEL) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "BILLBOARDSET") == 0)
			{
				while (1)
				{
					cData2[0] = LoadBillBoardInfo(pFile);
					if (strcmp(cData2[0], BILLBOARD) == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(&cData1[0], "PLAYERSET") == 0)
			{
				while (1)
				{
					cData2[0] = LoadPlayerInfo(pFile);
					if (strcmp(cData2[0], PLAYER) == 0)
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
			if (cData[0] != 0x0a && cData[0] != '#')
			{
				SkipComment(pFile);
			}
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
//***************************
// 整数を読み込む処理
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
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return nData;
}
//*********************
// 小数点を読み込む処理
//*********************
float LoadFloat(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	float fData;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			fData = (float)atof(cData1);
			cData1[0] = { NULL };
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return fData;
}
//******************************
// // 文字列を読み込む処理
//******************************
char *LoadPath(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char filepath[32] = { NULL };

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != 0x23 && cData[0] != 0x20 && cData[0] != 0x09)
		{
			strcat(cData1, cData);
		}
		else
		{
			strcpy(filepath, cData1);
			cData1[0] = { NULL };
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return &filepath[0];
}
//*************************************
// カメラ情報を読み込む処理
//*************************************
char* LoadCameraInfo(FILE* pFile)
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
			else if (strcmp(&cData1[0], "REF") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "END_CAMERASET") == 0)
			{
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// ライト情報を読み込む処理
//*************************************
char* LoadLightInfo(FILE* pFile)
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
			if (strcmp(&cData1[0], "DIRECTION") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "DIFFUSE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
				fData = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "END_LIGHTSET") == 0)
			{
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// 空情報を読み込む処理
//*************************************
char* LoadSkyInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	int nData;
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
			if (strcmp(&cData1[0], "TEXTYPE") == 0)
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
			else if (strcmp(&cData1[0], "END_SKYSET") == 0)
			{
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// 山情報を読み込む処理
//*************************************
char* LoadMountInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
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
			if (strcmp(&cData1[0], "TEXTYPE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nData = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "END_MOUNTAINSET") == 0)
			{
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// 地面情報を読み込む処理
//*************************************
char* LoadFieldInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	D3DXVECTOR3 Pos,Rot;
	D3DXVECTOR2 Block, Size;
	int nType;

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
				Pos.x = LoadFloat(pFile);
				Pos.y = LoadFloat(pFile);
				Pos.z = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Rot.x = LoadFloat(pFile);
				Rot.y = LoadFloat(pFile);
				Rot.z = LoadFloat(pFile);
				PitoRadian(&Rot);
			}
			else if (strcmp(&cData1[0], "BLOCK") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Block.x = (float)LoadInt(pFile);
				Block.y = (float)LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "SIZE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Size.x = (float)LoadInt(pFile);
				Size.y = (float)LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "TEXTYPE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nType = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "END_FIELDSET") == 0)
			{
				SetMeshfield(Pos, Rot, nType, (int)Block.x, 0, (int)Block.y, (int)Size.x, (int)Size.y);
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// 壁情報を読み込む処理
//*************************************
char* LoadWallInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	D3DXVECTOR3 Pos, Rot;
	D3DXVECTOR2 Block, Size;
	int nType = 0;

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
				Pos.x = LoadFloat(pFile);
				Pos.y = LoadFloat(pFile);
				Pos.z = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Rot.x = LoadFloat(pFile);
				Rot.y = LoadFloat(pFile);
				Rot.z = LoadFloat(pFile);
				PitoRadian(&Rot);
				int i = 0;
			}
			else if (strcmp(&cData1[0], "BLOCK") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Block.x = (float)LoadInt(pFile);
				Block.y = (float)LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "SIZE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Size.x = (float)LoadInt(pFile);
				Size.y = (float)LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "TEXTYPE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nType = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "END_WALLSET") == 0)
			{
				//SetMeshWall(Pos, Rot, nType, (int)Block.x, 0, (int)Block.y, (int)Size.x, (int)Size.y);
				int i = 0;
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// モデル情報を読み込む処理
//*************************************
char* LoadModelInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	D3DXVECTOR3 Pos, Rot;
	bool bShadow;
	int nType;

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
				Pos.x = LoadFloat(pFile);
				Pos.y = LoadFloat(pFile);
				Pos.z = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Rot.x = LoadFloat(pFile);
				Rot.y = LoadFloat(pFile);
				Rot.z = LoadFloat(pFile);
				PitoRadian(&Rot);
			}
			else if (strcmp(&cData1[0], "TYPE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nType = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "SHADOW") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				bShadow = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "END_MODELSET") == 0)
			{
				SetStageModel(Pos, Rot, (MODELTYPE)nType);
				break;
			}
		}
	}
	return &cData1[0];
}
//*************************************
// ビルボード情報を読み込む処理
//*************************************
char* LoadBillBoardInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Size, Origin;
	int nType;
	bool bShadow;

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
				Pos.x = LoadFloat(pFile);
				Pos.y = LoadFloat(pFile);
				Pos.z = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "SIZE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Size.x = (float)LoadInt(pFile);
				Size.y = (float)LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "TEXTYPE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				nType = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "ORIGIN") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Origin.x = (float)LoadInt(pFile);
				Origin.y = (float)LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "SHADOW") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				bShadow = (bool)LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "END_BILLBOARDSET") == 0)
			{
				break;
			}
		}
	}
	return &cData1[0];
}
//*****************************
// プレイヤー情報を読み込む処理
//*****************************
char* LoadPlayerInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	char *cData3[64] = { NULL };
	D3DXVECTOR3 Pos,Rot;
	char cFileName[32];

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
				Pos.x = LoadFloat(pFile);
				Pos.y = LoadFloat(pFile);
				Pos.z = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "ROT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Rot.x = LoadFloat(pFile);
				Rot.y = LoadFloat(pFile);
				Rot.z = LoadFloat(pFile);
				PitoRadian(&Rot);
			}
			else if (strcmp(&cData1[0], "MOTION_FILENAME") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				cData3[0] = LoadPath(pFile);
				strcpy(cFileName, cData3[0]);
			}
			else if (strcmp(&cData1[0], "END_PLAYERSET") == 0)
			{
				LoadMotionViewer(cFileName);
				break;
			}
		}
	}
	return &cData1[0];
}