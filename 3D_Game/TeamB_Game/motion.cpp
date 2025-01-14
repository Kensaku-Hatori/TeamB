////==============================
////
////  処理[edit.h]
////  Author:kaiti
////
////==============================
//#include "motion.h"
//#include "player.h"
//
//#include <stdio.h>
//#include <string.h>
//
//
//void LoadPlayer1(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	pDevice = GetDevice();
//
//	Player* pPlayer = GetPlayer();
//
//	char ModelFile[MAX_PARTS][MAX_WORD];//モデルのファイル名
//	int Index;
//
//	FILE* pFile;
//	pFile = fopen(MOTIONFILE_PLAYER, "r");
//	
//	if (pFile != NULL)
//	{
//		char aString[MAX_WORD];
//
//		while (1)
//		{
//			fscanf(pFile, "%s", &aString[0]);
//			if (strcmp(aString, "SCRIPT") == 0)
//			{
//				fscanf(pFile, "%s", &aString[0]);
//				//モデル数
//				if (strcmp(aString, "NUM_MODEL = ") == 0)
//				{
//					fscanf(pFile, "%d", &pPlayer->nNumModel);
//				}
//				//モデルファイル名
//				else if (strcmp(aString, "MODEL_FILENAME = ") == 0)
//				{
//					for (int nCnt = 0; nCnt < pPlayer->nNumModel; nCnt++)
//					{
//						fscanf(pFile, "%s", &ModelFile[nCnt][0]);
//						D3DXLoadMeshFromX(&ModelFile[nCnt][0],
//							D3DXMESH_SYSTEMMEM,
//							pDevice,
//							NULL,
//							&pPlayer->aModel[nCnt].pBuffMat,
//							NULL,
//							&pPlayer->aModel[nCnt].dwNumMat,
//							&pPlayer->aModel[nCnt].pMesh);
//					}
//				}
//				//キャラクター情報
//				else if (strcmp(aString, "CHARACTERSET") == 0)
//				{
//					fscanf(pFile, "%s", &aString[0]);
//					while (1)
//					{
//						//パーツ数
//						if (strcmp(aString, "NUM_PARTS = ") == 0)
//						{
//							fscanf(pFile, "%d", &pPlayer->nNumModel);
//						}
//						//パーツ設定
//						else if (strcmp(aString, "PARTSSET = ") == 0)
//						{
//							fscanf(pFile, "%s", &aString[0]);
//							while (1)
//							{
//								//インデックス
//								if (strcmp(aString, "INDEX = ") == 0)
//								{
//									fscanf(pFile, "%d", &Index);
//								}
//								//親モデルのインデックス
//								else if (strcmp(aString, "PARENT = ") == 0)
//								{
//									fscanf(pFile, "%d", &pPlayer->aModel[Index].nIdxModelParent);
//								}
//								//位置
//								else if (strcmp(aString, "POS = ") == 0)
//								{
//									fscanf(pFile, "%f", &pPlayer->aModel[Index].pos.x);
//									fscanf(pFile, " %f", &pPlayer->aModel[Index].pos.y);
//									fscanf(pFile, " %f", &pPlayer->aModel[Index].pos.z);
//								}
//								//向き
//								else if (strcmp(aString, "ROT = ") == 0)
//								{
//									fscanf(pFile, "%f", &pPlayer->aModel[Index].rot.x);
//									fscanf(pFile, " %f", &pPlayer->aModel[Index].rot.y);
//									fscanf(pFile, " %f", &pPlayer->aModel[Index].rot.z);
//								}
//								else if (strcmp(aString, "END_PARTSSET") == 0)
//								{
//									break;
//								}
//							}
//						}
//						else if (strcmp(aString, "END_CHARACTERSET") == 0)
//						{
//							break;
//						}
//					}
//				}
//				else if (strcmp(aString, "END_SCRIPT") == 0)
//				{
//					break;
//				}
//			}
//		}
//		fclose(pFile);
//	}
//	else
//	{
//		return;
//	}
//
//}
