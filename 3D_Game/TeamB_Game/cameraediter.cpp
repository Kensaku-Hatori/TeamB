//*********************************************************
// 
// カメラエディター[cameraediter.cpp]
// Author:Hatori
// 
//*********************************************************

#include "cameraediter.h"
#include "input.h"
#include "mouse.h"
#include "camera.h"
#include "cameraanim.h"
#include "loadstage.h"

CameraAnim CameraEditer;
int KeyCount = 0,AnimCount = 0;
int g_LoadAnimCount, g_LoadKeyCount,EffectCount;

// 実作業の関数化
void LoadAnimInfo(FILE* pFile);
void LoadKeyNum(FILE* pFile);
void LoadKeyInfo(FILE* pFile);

//***********************
// カメラエディターを更新
//***********************
void UpdateCameraEditer()
{
	CameraMove();
	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetEditerInfo(&CameraEditer.Anim[AnimCount].KeyInfo[KeyCount], AnimCount, KeyCount, 100);
		if(KeyCount <= MAX_CAMERAKEY) KeyCount++;
	}
	if (KeyboardTrigger(DIK_RIGHT) == true)
	{
		if(AnimCount <= ANIMTYPE_MAX) AnimCount++;
	}
	if (KeyboardTrigger(DIK_F9) == true)
	{
		SaveCameraWork();
	}
}

//***********************
// カメラエディターを描画
//***********************
void DrawCameraEditer()
{

}

//*********************************
// カメラエディターのキー情報を保存
//*********************************
void SaveCameraWork()
{
	FILE* pFile = fopen("data\\TEXT\\CameraWork.txt", "w");
	fprintf(pFile, "#**********************#\n");
	fprintf(pFile, "#   カメラワーク情報   #\n");
	fprintf(pFile, "#       羽鳥健作       #\n");
	fprintf(pFile, "#**********************#\n");
	fprintf(pFile, "SCRIPT\n\n");

	for (int wCameraCount = 0; wCameraCount < AnimCount + 1; wCameraCount++)
	{
		fprintf(pFile, "SET_CAMERAWORK\n");
		fprintf(pFile, "	NUMKEY = %d\n",KeyCount);
		for (int wKeyCount = 0; wKeyCount < KeyCount; wKeyCount++)
		{
			fprintf(pFile, "	SET_KEY\n");
			fprintf(pFile, "		POSV = %3.2f %3.2f %3.2f\n",
				CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].PosV.x,
				CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].PosV.y,
				CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].PosV.z);
			fprintf(pFile, "		POSR = %3.2f %3.2f %3.2f\n",
				CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].PosR.x,
				CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].PosR.y,
				CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].PosR.z);
			fprintf(pFile, "		ROT = %3.2f % 3.2f %3.2f\n",
				CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].Rot.x,
				CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].Rot.y, 
				CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].Rot.z);
			fprintf(pFile, "		FRAME = %d\n", CameraEditer.Anim[wCameraCount].KeyInfo[wKeyCount].nFrame);
			fprintf(pFile, "	END_KEY\n");
		}
		fprintf(pFile, "END_CAMERAWORK\n");
	}
	fprintf(pFile, "END_SCRIPT\n");
	fclose(pFile);
}

//***************************
// カメラモーションの読み込み
//***************************
void LoadCameraWork()
{
	char cData[2] = { NULL };
	char cData1[64] = { NULL };
	FILE* pFile;

	pFile = fopen("data\\TEXT\\CameraWork.txt", "r");

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
		LoadAnimInfo(pFile);
	}
	fclose(pFile);
}

//*******************************************
// カメラのアニメーションの情報を読み込み
//*******************************************
void LoadAnimInfo(FILE* pFile)
{
	char cData[2] = {};
	char cData1[128] = {};

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "SET_CAMERAWORK") == 0)
			{
				LoadKeyNum(pFile);
			}
			else if (strcmp(&cData1[0], "END_SCRIPT") == 0)
			{
				g_LoadAnimCount = 0;
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

//*********************************************
// カメラのアニメーションのキーの総数を読み込み
//*********************************************
void LoadKeyNum(FILE* pFile)
{
	char cData[2] = {};
	char cData1[128] = {};
	char* cData2[32] = {};
	int nData = 0;
	char* FilePath[256] = {};
	NTYPE nType = {};
	int ModelPathCount = 0;
	int PolygonePathCount = 0;
	int StartFrame,EndFrame,nLife;
	BOSSNAMEEFFECT In;

	while (1)
	{
		fgets(cData, 2, pFile);
		if (cData[0] != 0x0a && cData[0] != '#' && cData[0] != ' ' && cData[0] != 0x09)
		{
			strcat(cData1, cData);
			if (strcmp(&cData1[0], "NUMKEY") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				SetNumKey(g_LoadAnimCount, LoadInt(pFile));
			}
			if (strcmp(&cData1[0], "SETNAMEEFFECT") == 0)
			{
				cData1[0] = { NULL };

				fgets(cData, 2, pFile);

				In.Pos.x = LoadFloat(pFile);
				In.Pos.y = LoadFloat(pFile);
				In.Pos.z = LoadFloat(pFile);

				In.Rot.x = LoadFloat(pFile);
				In.Rot.y = LoadFloat(pFile);
				In.Rot.z = LoadFloat(pFile);

				In.Scale.x = LoadFloat(pFile);
				In.Scale.y = LoadFloat(pFile);

				In.Col.r = LoadFloat(pFile);
				In.Col.g = LoadFloat(pFile);
				In.Col.b = LoadFloat(pFile);
				In.Col.a = LoadFloat(pFile);

				StartFrame = LoadInt(pFile);
				EndFrame = LoadInt(pFile);
				nLife = LoadInt(pFile);

				SetNameEffectInfo(In.Pos, In.Rot, In.Scale, In.Col, g_LoadAnimCount, EffectCount,StartFrame,EndFrame, nLife,MOVIEEFFECT_NAME);
			}
			if (strcmp(&cData1[0], "LOOP") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				SetLoop(g_LoadAnimCount, LoadInt(pFile));
			}
			if (strcmp(&cData1[0], "SET_KEY") == 0)
			{
				cData1[0] = { NULL };
				LoadKeyInfo(pFile);
			}
			else if (strcmp(&cData1[0], "END_CAMERAWORK") == 0)
			{
				EffectCount = 0;
				g_LoadKeyCount = 0;
				g_LoadAnimCount++;
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

//*******************************************
// カメラのアニメーションのキー情報を読み込み
//*******************************************
void LoadKeyInfo(FILE* pFile)
{
	D3DXVECTOR3 PosV,PosR,Rot;
	int Frame = 0;
	char cData[2] = {};
	char cData1[128] = {};
	char* cData2[32] = {};
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
			if (strcmp(&cData1[0], "POSV") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				PosV.x = LoadFloat(pFile);
				PosV.y = LoadFloat(pFile);
				PosV.z = LoadFloat(pFile);
			}
			if (strcmp(&cData1[0], "POSR") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				PosR.x = LoadFloat(pFile);
				PosR.y = LoadFloat(pFile);
				PosR.z = LoadFloat(pFile);
			}
			if (strcmp(&cData1[0], "ROT") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Rot.x = LoadFloat(pFile);
				Rot.y = LoadFloat(pFile);
				Rot.z = LoadFloat(pFile);
			}
			if (strcmp(&cData1[0], "FRAME") == 0)
			{
				cData1[0] = { NULL };
				SkipEqual(pFile);
				Frame = LoadInt(pFile);
			}
			else if (strcmp(&cData1[0], "END_KEY") == 0)
			{
				SetCameraWorkInfo(PosV, PosR, Rot, Frame, g_LoadAnimCount, g_LoadKeyCount);
				g_LoadKeyCount++;
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