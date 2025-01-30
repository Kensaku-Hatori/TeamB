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
#include "player.h"

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
//
//
//
void MotionBlend(void)
{
	Player* pPlayer = GetPlayer();

	pPlayer->nCounterMotion++;
	pPlayer->nCounterBlendMotion++;

	if (pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].StartKey == pPlayer->nKey)
	{// 今のキーが開始するキーだったら
		if (pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].StartFlame <= pPlayer->nCounterMotion
			&& pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].EndFlame >= pPlayer->nCounterMotion)
		{// 開始フレーム以上で終了フレーム以内なら
			collisionEnemy(pPlayer->WeponRadius[pPlayer->Pfolm]);
		}
	}
	if (pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aStartKey == pPlayer->nKey)
	{// 今のキーが二種類目の開始するキーだったら
		if (pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aStartFlame <= pPlayer->nCounterMotion
			&& pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aEndFlame >= pPlayer->nCounterMotion)
		{// 二種類目の開始フレーム以上で二種類目の終了フレーム以内なら
			if (pPlayer->pMotion == MOTIONTYPE_ACTION)
			{
				switch (pPlayer->Pfolm)
				{
				case PLAYERFOLM_ATACK:
					SetImpact(IMPACTTYPE_NORMAL, D3DXVECTOR3(pPlayer->mtxWepon[pPlayer->Pfolm]._41,
						0.0f,
						pPlayer->mtxWepon[pPlayer->Pfolm]._43),
						D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
						100,
						10.0f,
						30.0f,
						2,
						50,
						2.0f);
					break;
				case PLAYERFOLM_SPEED:
					break;
				default:
					break;
				}
			}
		}
	}

	if (pPlayer->nCounterMotion >= pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].nFrame)
	{// モーションカウンターが目標のフレーム以上だったら
		pPlayer->nCounterMotion = 0;
		if (pPlayer->bFinish == false)
		{
			pPlayer->nKey++;
			pPlayer->nNextKey++;
		}
		if (pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].bLoop == true)
		{
			if (pPlayer->nKey >= pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].nNumKey - 1)
			{// 今のキーがキーの最大数だったら
				if (pPlayer->nKey > pPlayer->nNextKey)
				{// 今のキーが次のキー以上だったら
					pPlayer->nKey = 0;
				}
				else
				{
					pPlayer->nNextKey = 0;
				}
			}
		}
		else
		{
			if (pPlayer->nKey >= pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].nNumKey - 1)
			{// 今のキーがキーの最大数だったら
				g_bMotion = false;
				pPlayer->bFinish = true;
				pPlayer->nNextKey = pPlayer->nKey;
				if (pPlayer->pMotion != MOTIONTYPE_JUMP)
				{
					if (pPlayer->pMotion == MOTIONTYPE_ACTION)
					{
						pPlayer->bBlendMotion = true;
						pPlayer->pMotionBlend = MOTIONTYPE_NUTORAL;
					}
					//SetMotion(MOTIONTYPE_NUTORAL);w
				}
				else
				{
					pPlayer->nNextKey = pPlayer->nKey;
				}
			}
			else if (pPlayer->nKey > pPlayer->nNextKey)
			{// 今のキーが次のキー以上だったら
				pPlayer->nKey = 0;
			}
		}
	}
	if (pPlayer->nCounterBlendMotion >= pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotionBlend].aKeyInfo[pPlayer->nKeyBlend].nFrame)
	{// モーションカウンターが目標のフレーム以上だったら
		pPlayer->nCounterBlendMotion = 0;
		pPlayer->nKeyBlend++;
		pPlayer->nNexKeyBlend++;
		if (pPlayer->nKeyBlend == pPlayer->nNumKeyBlend - 1)
		{// 今のキーがキーの最大数だったら
			if (pPlayer->bLoopBlend == true)
			{// ループするタイプだったら
				pPlayer->nNexKeyBlend = 0;
			}
			else
			{// ループしないタイプだったら
				g_bMotion = false;
				pPlayer->bBlendMotion = false;
				pPlayer->nNexKeyBlend = pPlayer->nKeyBlend;
			}
		}
		else if (pPlayer->nKeyBlend > pPlayer->nNexKeyBlend)
		{// 今のキーが次のキー以上だったら
			if (pPlayer->bLoopBlend == true)
			{// ループするタイプだったら
				pPlayer->nKeyBlend = 0;
			}
		}
	}

	KEYINFO nKey = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey];
	KEYINFO nNexKey = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nNextKey];

	float fRateMotion = (float)pPlayer->nCounterMotion / (float)nKey.nFrame;

	if (pPlayer->bBlendMotion == false)
	{
		for (int PartsCount = 0; PartsCount < pPlayer->nNumModel[pPlayer->Pfolm]; PartsCount++)
		{// モデル分回す
			KEY KeyDef;
			KEY KeyDest;

			// 差分
			KeyDef.fPosX = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nNextKey].aKey[PartsCount].fPosX - pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosX;
			KeyDef.fPosY = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nNextKey].aKey[PartsCount].fPosY - pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosY;
			KeyDef.fPosZ = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nNextKey].aKey[PartsCount].fPosZ - pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosZ;

			KeyDef.fRotX = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nNextKey].aKey[PartsCount].fRotX - pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotX;
			KeyDef.fRotY = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nNextKey].aKey[PartsCount].fRotY - pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotY;
			KeyDef.fRotZ = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nNextKey].aKey[PartsCount].fRotZ - pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotZ;

			// 希望の値
			KeyDest.fPosX = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosX + KeyDef.fPosX * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].nFrame);
			KeyDest.fPosY = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosY + KeyDef.fPosY * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].nFrame);
			KeyDest.fPosZ = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fPosZ + KeyDef.fPosZ * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].nFrame);

			KeyDest.fRotX = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotX + KeyDef.fRotX * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].nFrame);
			KeyDest.fRotY = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotY + KeyDef.fRotY * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].nFrame);
			KeyDest.fRotZ = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].aKey[PartsCount].fRotZ + KeyDef.fRotZ * ((float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotion].aKeyInfo[pPlayer->nKey].nFrame);

			// 足す
			pPlayer->aModel[pPlayer->Pfolm][PartsCount].Partspos.x = pPlayer->aModel[pPlayer->Pfolm][PartsCount].OffSet.x + KeyDest.fPosX;
			pPlayer->aModel[pPlayer->Pfolm][PartsCount].Partspos.y = pPlayer->aModel[pPlayer->Pfolm][PartsCount].OffSet.y + KeyDest.fPosY;
			pPlayer->aModel[pPlayer->Pfolm][PartsCount].Partspos.z = pPlayer->aModel[pPlayer->Pfolm][PartsCount].OffSet.z + KeyDest.fPosZ;

			pPlayer->aModel[pPlayer->Pfolm][PartsCount].Partsrot.x = pPlayer->aModel[pPlayer->Pfolm][PartsCount].OffSetRot.x + KeyDest.fRotX;
			pPlayer->aModel[pPlayer->Pfolm][PartsCount].Partsrot.y = pPlayer->aModel[pPlayer->Pfolm][PartsCount].OffSetRot.y + KeyDest.fRotY;
			pPlayer->aModel[pPlayer->Pfolm][PartsCount].Partsrot.z = pPlayer->aModel[pPlayer->Pfolm][PartsCount].OffSetRot.z + KeyDest.fRotZ;
		}
	}
	else
	{
		KEYINFO nKeyBlend = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotionBlend].aKeyInfo[pPlayer->nKeyBlend];
		KEYINFO nNexKeyBlend = pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotionBlend].aKeyInfo[pPlayer->nNexKeyBlend];

		float fRateMotionBlend = (float)pPlayer->nCounterBlendMotion / (float)pPlayer->aMotionInfo[pPlayer->Pfolm][pPlayer->pMotionBlend].aKeyInfo[pPlayer->nKeyBlend].nFrame;
		float fRateBlend = (float)pPlayer->nCountBlend / (float)pPlayer->nFlameBlend;

		for (int PartsCount = 0; PartsCount < pPlayer->nNumModel[pPlayer->Pfolm]; PartsCount++)
		{
			D3DXVECTOR3 fDiffMotion;
			fDiffMotion.x = nNexKey.aKey[PartsCount].fRotX - nKey.aKey[PartsCount].fRotX;
			fDiffMotion.y = nNexKey.aKey[PartsCount].fRotY - nKey.aKey[PartsCount].fRotY;
			fDiffMotion.z = nNexKey.aKey[PartsCount].fRotZ - nKey.aKey[PartsCount].fRotZ;
			D3DXVECTOR3 fRotCurrent;
			fRotCurrent.x = nKey.aKey[PartsCount].fRotX + (fDiffMotion.x * fRateMotion);
			fRotCurrent.y = nKey.aKey[PartsCount].fRotY + (fDiffMotion.y * fRateMotion);
			fRotCurrent.z = nKey.aKey[PartsCount].fRotZ + (fDiffMotion.z * fRateMotion);

			D3DXVECTOR3 fDiffMotionBlend;
			fDiffMotionBlend.x = nNexKeyBlend.aKey[PartsCount].fRotX - nKeyBlend.aKey[PartsCount].fRotX;
			fDiffMotionBlend.y = nNexKeyBlend.aKey[PartsCount].fRotY - nKeyBlend.aKey[PartsCount].fRotY;
			fDiffMotionBlend.z = nNexKeyBlend.aKey[PartsCount].fRotZ - nKeyBlend.aKey[PartsCount].fRotZ;
			D3DXVECTOR3 fRotBlend;
			fRotBlend.x = nKeyBlend.aKey[PartsCount].fRotX + (fDiffMotionBlend.x * fRateMotionBlend);
			fRotBlend.y = nKeyBlend.aKey[PartsCount].fRotY + (fDiffMotionBlend.y * fRateMotionBlend);
			fRotBlend.z = nKeyBlend.aKey[PartsCount].fRotZ + (fDiffMotionBlend.z * fRateMotionBlend);

			D3DXVECTOR3 fDiffBlendRot = fRotBlend - fRotCurrent;
			D3DXVECTOR3 fRot;

			D3DXVECTOR3 fDiffMotionPos;
			fDiffMotionPos.x = nNexKey.aKey[PartsCount].fPosX - nKey.aKey[PartsCount].fPosX;
			fDiffMotionPos.y = nNexKey.aKey[PartsCount].fPosY - nKey.aKey[PartsCount].fPosY;
			fDiffMotionPos.z = nNexKey.aKey[PartsCount].fPosZ - nKey.aKey[PartsCount].fPosZ;
			D3DXVECTOR3 fRotCurrentPos;
			fRotCurrentPos.x = nKey.aKey[PartsCount].fPosX + (fDiffMotion.x * fRateMotion);
			fRotCurrentPos.y = nKey.aKey[PartsCount].fPosY + (fDiffMotion.y * fRateMotion);
			fRotCurrentPos.z = nKey.aKey[PartsCount].fPosZ + (fDiffMotion.z * fRateMotion);

			D3DXVECTOR3 fDiffMotionBlendPos;
			fDiffMotionBlendPos.x = nNexKeyBlend.aKey[PartsCount].fPosX - nKeyBlend.aKey[PartsCount].fPosX;
			fDiffMotionBlendPos.y = nNexKeyBlend.aKey[PartsCount].fPosY - nKeyBlend.aKey[PartsCount].fPosY;
			fDiffMotionBlendPos.z = nNexKeyBlend.aKey[PartsCount].fPosZ - nKeyBlend.aKey[PartsCount].fPosZ;
			D3DXVECTOR3 fRotBlendPos;
			fRotBlendPos.x = nKeyBlend.aKey[PartsCount].fPosX + (fDiffMotionBlendPos.x * fRateMotionBlend);
			fRotBlendPos.y = nKeyBlend.aKey[PartsCount].fPosY + (fDiffMotionBlendPos.y * fRateMotionBlend);
			fRotBlendPos.z = nKeyBlend.aKey[PartsCount].fPosZ + (fDiffMotionBlendPos.z * fRateMotionBlend);

			D3DXVECTOR3 fDiffBlendPos = fRotBlendPos - fRotCurrentPos;
			D3DXVECTOR3 fPos;

			fPos.x = fRotCurrentPos.x + (fDiffBlendPos.x * fRateBlend);
			fPos.y = fRotCurrentPos.y + (fDiffBlendPos.y * fRateBlend);
			fPos.z = fRotCurrentPos.z + (fDiffBlendPos.z * fRateBlend);

			fRot.x = fRotCurrent.x + (fDiffBlendRot.x * fRateBlend);
			fRot.y = fRotCurrent.y + (fDiffBlendRot.y * fRateBlend);
			fRot.z = fRotCurrent.z + (fDiffBlendRot.z * fRateBlend);

			pPlayer->aModel[pPlayer->Pfolm][PartsCount].Partspos = pPlayer->aModel[pPlayer->Pfolm][PartsCount].OffSet + fPos;
			pPlayer->aModel[pPlayer->Pfolm][PartsCount].Partsrot = pPlayer->aModel[pPlayer->Pfolm][PartsCount].OffSetRot + fRot;
			int i = 0;
		}
		pPlayer->nCountBlend++;
		if (pPlayer->nCountBlend >= pPlayer->nFlameBlend)
		{
			pPlayer->nCountBlend = 0;
			SetMotion(pPlayer->pMotionBlend);
			pPlayer->bFinish = false;
			pPlayer->bBlendMotion = false;
		}
	}

}