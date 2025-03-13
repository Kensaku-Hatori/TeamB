//****************************************
//
// モデル情報を読み込む処理[loadstage.cpp]
// Hatori Kensaku
//
//****************************************
#include "loadstage.h"
#include "loadmotion.h"
#include "meshfield.h"
#include "meshwall.h"
#include "camera.h"
#include "light.h"
#include "billboard.h"

// グローバル変数
char FilePathPoly[MAX_FILEPATH][256] = { {} };
char FilePathModel[MAX_FILEPATH][256] = { {} };

//*****************************
// スクリプト以前を読み込む処理
//*****************************
void LoadModelViewer(MODE Mode)
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	FILE* pFile;

	switch (Mode)
	{
	case MODE_STAGEONE:
		pFile = fopen("data\\TEXT\\tutorialstage.txt", "r");
		break;
	case MODE_STAGETWO:
		pFile = fopen("data\\TEXT\\model.txt", "r");
		break;
	case MODE_STAGETHREE:
		pFile = fopen("data\\TEXT\\middle bossstage.txt", "r");
		break;
	case MODE_STAGEFOUR:
		pFile = fopen("data\\TEXT\\lastbossstage.txt", "r");
		break;
	default:
		return;
		break;
	}

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
	char cData[2] = {};
	char cData1[128] = {};

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
	char cData[2] = {};
	char cData1[128] = {};
	char *cData2[32] = {};
	int nData = 0;
	char* FilePath[256] = {};
	NTYPE nType = {};
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
				FilePath[0] = LoadPath(pFile,FilePath[0]);
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
				FilePath[0] = LoadPath(pFile,FilePath[0]);
				strcpy(&FilePathModel[ModelPathCount][0], FilePath[0]);
				SetStageModelInfo(&FilePath[0], ModelPathCount);
				if (ModelPathCount < nType.nModelType)
				{
					ModelPathCount++;
				}
			}
			else if (strcmp(&cData1[0], "CAMERASET") == 0)
			{
				LoadCameraInfo(pFile);
			}
			else if (strcmp(&cData1[0], "LIGHTSET") == 0)
			{
				LoadLightInfo(pFile);
			}
			else if (strcmp(&cData1[0], "SKYSET") == 0)
			{
				LoadSkyInfo(pFile);
			}
			else if (strcmp(&cData1[0], "MOUNTAINSET") == 0)
			{
				LoadMountInfo(pFile);
			}
			else if (strcmp(&cData1[0], "FIELDSET") == 0)
			{
				LoadFieldInfo(pFile);
			}
			else if (strcmp(&cData1[0], "WALLSET") == 0)
			{
				LoadWallInfo(pFile);
			}
			else if (strcmp(&cData1[0], "MODELSET") == 0)
			{
				LoadModelInfo(pFile);
			}
			else if (strcmp(&cData1[0], "BILLBOARDSET") == 0)
			{
				LoadBillBoardInfo(pFile);
			}
			else if (strcmp(&cData1[0], "PLAYERSET") == 0)
			{
				LoadPlayerInfo(pFile);
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
char *LoadPath(FILE* pFile,char *cData2)
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
			cData2 = cData1;
			if (*cData == '#')
			{
				SkipComment(pFile);
			}
			break;
		}
	}
	return cData2;
}
//*************************************
// カメラ情報を読み込む処理
//*************************************
void LoadCameraInfo(FILE* pFile)
{
	Camera* pCamera = GetCamera();

	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	D3DXVECTOR3 PosV, PosR;


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
				PosV.x = LoadFloat(pFile);
				PosV.y = LoadFloat(pFile);
				PosV.z = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "REF") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				PosR.x = LoadFloat(pFile);
				PosR.y = LoadFloat(pFile);
				PosR.z = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "END_CAMERASET") == 0)
			{
				pCamera->posR = PosR;
				pCamera->posV = PosV;
				break;
			}
		}
	}
}
//*************************************
// ライト情報を読み込む処理
//*************************************
void LoadLightInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	float fData[3] = { NULL };
	float fData1[3] = { NULL };

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
				fData[0] = LoadFloat(pFile);
				fData[1] = LoadFloat(pFile);
				fData[2] = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "DIFFUSE") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				fData1[0] = LoadFloat(pFile);
				fData1[1] = LoadFloat(pFile);
				fData1[2] = LoadFloat(pFile);
			}
			else if (strcmp(&cData1[0], "END_LIGHTSET") == 0)
			{
				SetLight(D3DXVECTOR3(fData[0], fData[1], fData[2]), D3DXCOLOR(fData1[0], fData1[1], fData1[2], 1.0f));

				break;
			}
		}
	}
}
//*************************************
// 空情報を読み込む処理
//*************************************
void LoadSkyInfo(FILE* pFile)
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
}
//*************************************
// 山情報を読み込む処理
//*************************************
void LoadMountInfo(FILE* pFile)
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
}
//*************************************
// 地面情報を読み込む処理
//*************************************
void LoadFieldInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	D3DXVECTOR3 Pos,Rot;
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
}
//*************************************
// 壁情報を読み込む処理
//*************************************
void LoadWallInfo(FILE* pFile)
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
				SetMeshWall(Pos, Rot, nType, (int)Block.x, 0, (int)Block.y, (int)Size.x, (int)Size.y);
				int i = 0;
				break;
			}
		}
	}
}
//*************************************
// モデル情報を読み込む処理
//*************************************
void LoadModelInfo(FILE* pFile)
{
	char cData[2] = {};
	char cData1[128] = {};
	char cData2[64] = { NULL };
	D3DXVECTOR3 Pos, Rot;
	bool bShadow = false;
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
}
//*************************************
// ビルボード情報を読み込む処理
//*************************************
void LoadBillBoardInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Size, Origin;
	int nType;
	bool bShadow;
	int Vertical, Horizon,AnimSpeed;

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
			else if (strcmp(&cData1[0], "ANIM") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Vertical = (bool)LoadInt(pFile);
				Horizon = (bool)LoadInt(pFile);
				AnimSpeed = (bool)LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "END_BILLBOARDSET") == 0)
			{
				//SetBiillboard(Pos, (int)Size.x, (int)Size.y, nType, D3DXVECTOR2(Origin.x, Origin.y), bShadow);
				break;
			}
		}
	}
}
//*****************************
// プレイヤー情報を読み込む処理
//*****************************
void LoadPlayerInfo(FILE* pFile)
{
	char cData[2] = { NULL };
	char cData1[128] = { NULL };
	char cData2[64] = { NULL };
	char *cData3[64] = { NULL };
	D3DXVECTOR3 Pos,Rot;
	char cFileName[256] = {};

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
				cData3[0] = LoadPath(pFile,cData3[0]);
				strcpy(cFileName, cData3[0]);
			}
			else if (strcmp(&cData1[0], "END_PLAYERSET") == 0)
			{
				LoadMotionViewer(cFileName);
				break;
			}
		}
	}
}