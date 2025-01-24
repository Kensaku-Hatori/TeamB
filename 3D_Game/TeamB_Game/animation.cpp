//************************************
// 
// Author: HATORI
// モーションを管理する[animation.cpp]
// 
//************************************


//*************
// インクルード
//*************
#include "animation.h"
#include "effect.h"
#include "impact.h"

//***************
// グローバル変数
//***************
bool g_bMotion;

//*********************
// モーションの更新処理
//*********************
void UpdateMotion(OBJECTINFO* Motion)
{
	Motion->nCntMotion++;

	//if (pMotion[pPlayer->pMotion].StartKey == pPlayer->nKey)
	//{// 今のキーが開始するキーだったら
	//	if (pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].StartFlame <= pPlayer->nCounterMotion
	//		&& pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].EndFlame >= pPlayer->nCounterMotion)
	//	{// 開始フレーム以上で終了フレーム以内なら
	//		collisionEnemy(pPlayer->WeponRadius[pPlayer->Pfolm]);
	//	}
	//}
	//if (pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aStartKey == pPlayer->nKey)
	//{// 今のキーが二種類目の開始するキーだったら
	//	if (pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aStartFlame <= pPlayer->nCounterMotion
	//		&& pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aEndFlame >= pPlayer->nCounterMotion)
	//	{// 二種類目の開始フレーム以上で二種類目の終了フレーム以内なら
	//		if (pPlayer->pMotion == MOTIONTYPE_ACTION)
	//		{
	//			switch (pPlayer->Pfolm)
	//			{
	//			case PLAYERFOLM_ATACK:
	//				SetImpact(IMPACTTYPE_NORMAL, D3DXVECTOR3(pPlayer->mtxWepon[pPlayer->Pfolm]._41,
	//					0.0f,
	//					pPlayer->mtxWepon[pPlayer->Pfolm]._43),
	//					D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
	//					100,
	//					10.0f,
	//					30.0f,
	//					2,
	//					50,
	//					2.0f);
	//				break;
	//			case PLAYERFOLM_SPEED:
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//}

	if (Motion->nCntMotion >= Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame)
	{// モーションカウンターが目標のフレーム以上だったら
		Motion->nCntMotion = 0;
		Motion->nKey++;
		Motion->NextKey++;
		if (Motion->nKey == Motion->aMotionInfo[Motion->motionType].nNumKey - 1)
		{// 今のキーがキーの最大数だったら
			if (Motion->aMotionInfo[Motion->motionType].bLoop == true)
			{// ループするタイプだったら
				Motion->NextKey = 0;
			}
			else
			{// ループしないタイプだったら
				g_bMotion = false;
				if (Motion->motionType != MOTIONTYPE_JUMP)
				{
					SetMotion(MOTIONTYPE_NEUTRAL,Motion);
				}
				else
				{
					Motion->NextKey = Motion->nKey;
				}
			}
		}
		else if (Motion->nKey > Motion->NextKey)
		{// 今のキーが次のキー以上だったら
			if (Motion->aMotionInfo[Motion->motionType].bLoop == true)
			{// ループするタイプだったら
				Motion->nKey = 0;
			}
		}
	}

	for (int PartsCount = 0; PartsCount < Motion->nNumModel; PartsCount++)
	{// モデル分回す
		KEY KeyDef;
		KEY KeyDest;

		// 差分
		KeyDef.fPosX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fPosX - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosX;
		KeyDef.fPosY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fPosY - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosY;
		KeyDef.fPosZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fPosZ - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosZ;

		KeyDef.fRotX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fRotX - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotX;
		KeyDef.fRotY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fRotY - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotY;
		KeyDef.fRotZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fRotZ - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotZ;

		// 希望の値
		KeyDest.fPosX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosX + KeyDef.fPosX * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
		KeyDest.fPosY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosY + KeyDef.fPosY * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
		KeyDest.fPosZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosZ + KeyDef.fPosZ * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);

		KeyDest.fRotX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotX + KeyDef.fRotX * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
		KeyDest.fRotY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotY + KeyDef.fRotY * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
		KeyDest.fRotZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotZ + KeyDef.fRotZ * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);

		// 足す
		Motion->aModel[PartsCount].pos.x = Motion->aModel[PartsCount].OffSet.x + KeyDest.fPosX;
		Motion->aModel[PartsCount].pos.y = Motion->aModel[PartsCount].OffSet.y + KeyDest.fPosY;
		Motion->aModel[PartsCount].pos.z = Motion->aModel[PartsCount].OffSet.z + KeyDest.fPosZ;

		Motion->aModel[PartsCount].rot.x = KeyDest.fRotX;
		Motion->aModel[PartsCount].rot.y = KeyDest.fRotY;
		Motion->aModel[PartsCount].rot.z = KeyDest.fRotZ;
	}
}
//*********************
// モーションの設定処理
//*********************
void SetMotion(MOTIONTYPE MotionType, OBJECTINFO* Motion)
{
	Motion->nKey = 0;
	Motion->NextKey = 1;
	Motion->nCntMotion = 0;
	g_bMotion = true;
	Motion->motionType = MotionType;
}