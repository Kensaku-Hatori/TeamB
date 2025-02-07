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

//*********************
// モーションの更新処理
//*********************
void UpdateMotion(OBJECTINFO* Motion)
{
	MotionBlend(Motion);
	
	//Motion->nCntMotion++;
	//
	//if (Motion->nCntMotion >= Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame)
	//{// モーションカウンターが目標のフレーム以上だったら
	//	Motion->nCntMotion = 0;
	//	Motion->nKey++;
	//	Motion->NextKey++;
	//	if (Motion->nKey == Motion->aMotionInfo[Motion->motionType].nNumKey - 1)
	//	{// 今のキーがキーの最大数だったら
	//		if (Motion->aMotionInfo[Motion->motionType].bLoop == true)
	//		{// ループするタイプだったら
	//			Motion->NextKey = 0;
	//		}
	//		else
	//		{// ループしないタイプだったら
	//			g_bMotion = false;
	//			if (Motion->motionType != MOTIONTYPE_JUMP)
	//			{
	//				SetMotion(MOTIONTYPE_NEUTRAL,Motion);
	//			}
	//			else
	//			{
	//				Motion->NextKey = Motion->nKey;
	//			}
	//		}
	//	}
	//	else if (Motion->nKey > Motion->NextKey)
	//	{// 今のキーが次のキー以上だったら
	//		if (Motion->aMotionInfo[Motion->motionType].bLoop == true)
	//		{// ループするタイプだったら
	//			Motion->nKey = 0;
	//		}
	//	}
	//}
	//
	//for (int PartsCount = 0; PartsCount < Motion->nNumModel; PartsCount++)
	//{// モデル分回す
	//	KEY KeyDef;
	//	KEY KeyDest;
	//
	//	// 差分
	//	KeyDef.fPosX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fPosX - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosX;
	//	KeyDef.fPosY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fPosY - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosY;
	//	KeyDef.fPosZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fPosZ - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosZ;
	//
	//	KeyDef.fRotX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fRotX - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotX;
	//	KeyDef.fRotY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fRotY - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotY;
	//	KeyDef.fRotZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey].aKey[PartsCount].fRotZ - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotZ;
	//
	//	// 希望の値
	//	KeyDest.fPosX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosX + KeyDef.fPosX * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
	//	KeyDest.fPosY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosY + KeyDef.fPosY * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
	//	KeyDest.fPosZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosZ + KeyDef.fPosZ * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
	//
	//	KeyDest.fRotX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotX + KeyDef.fRotX * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
	//	KeyDest.fRotY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotY + KeyDef.fRotY * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
	//	KeyDest.fRotZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotZ + KeyDef.fRotZ * ((float)Motion->nCntMotion / (float)Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame);
	//
	//	// 足す
	//	Motion->aModel[PartsCount].pos.x = Motion->aModel[PartsCount].OffSetPos.x + KeyDest.fPosX;
	//	Motion->aModel[PartsCount].pos.y = Motion->aModel[PartsCount].OffSetPos.y + KeyDest.fPosY;
	//	Motion->aModel[PartsCount].pos.z = Motion->aModel[PartsCount].OffSetPos.z + KeyDest.fPosZ;
	//
	//	Motion->aModel[PartsCount].rot.x = KeyDest.fRotX;
	//	Motion->aModel[PartsCount].rot.y = KeyDest.fRotY;
	//	Motion->aModel[PartsCount].rot.z = KeyDest.fRotZ;
	//}
}
//*********************
// モーションの設定処理
//*********************
void SetMotion(MOTIONTYPE MotionType, OBJECTINFO* Motion)
{
	Motion->nKey = 0;
	Motion->NextKey = 1;
	Motion->nCntMotion = 0;
	Motion->motionType = MotionType;

	Motion->nKeyBlend = 0;
	Motion->nNextKeyBlend = 1;
	Motion->nCntMotionBlend = 0;
}
//=====================
// モーションブレンド
//=====================
void MotionBlend(OBJECTINFO* Motion)
{
	if (Motion->bBlendMotion == false)
	{
		Motion->nCntMotion++;
	}
	else if (Motion->bBlendMotion == true)
	{
		Motion->nCntMotionBlend++;
	}

	//if (Motion->aMotionInfo[Motion->motionType].StartKey == Motion->nKey)
	//{// 今のキーが開始するキーだったら
	//	if (Motion->aMotionInfo[Motion->motionType].StartFlame <= Motion->nCntMotion
	//		&& Motion->aMotionInfo[Motion->motionType].EndFlame >= Motion->nCntMotion)
	//	{// 開始フレーム以上で終了フレーム以内なら
	//		Motion->bBlendMotion = false;
	//	}
	//}
	//if (Motion->aMotionInfo[Motion->motionType].aStartKey == Motion->nKey)
	//{// 今のキーが二種類目の開始するキーだったら
	//	if (Motion->aMotionInfo[Motion->motionType].aStartFlame <= Motion->nCntMotion
	//		&& Motion->aMotionInfo[Motion->motionType].aEndFlame >= Motion->nCntMotion)
	//	{// 二種類目の開始フレーム以上で二種類目の終了フレーム以内なら
	//		Motion->bBlendMotion = true;
	//
	//		if (Motion->motionType == MOTIONTYPE_ACTION)
	//		{
	//
	//		}
	//	}
	//}

	if (Motion->nCntMotion >= Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame)
	{// モーションカウンターが目標のフレーム以上だったら
		Motion->nCntMotion = 0;
		if (Motion->bFinish == false)
		{
			Motion->nKey++;
			Motion->NextKey++;
		}
		if (Motion->aMotionInfo[Motion->motionType].bLoop == true)
		{//ループする場合
			if (Motion->nKey >= Motion->aMotionInfo[Motion->motionType].nNumKey - 1)
			{// 今のキーがキーの最大数だったら
				if (Motion->nKey > Motion->NextKey)
				{// 今のキーが次のキー以上だったら
					Motion->nKey = 0;
				}
				else
				{
					Motion->NextKey = 0;
				}
			}
		}
		else
		{
			if (Motion->nKey >= Motion->aMotionInfo[Motion->motionType].nNumKey - 1)
			{// 今のキーがキーの最大数だったら
				Motion->bFinish = true;
				Motion->NextKey = Motion->nKey;
				Motion->bBlendMotion = true;
				Motion->motionTypeBlend = MOTIONTYPE_NEUTRAL;
				Motion->nFrameBlend = 30;
				Motion->bLoopBlend = Motion->aMotionInfo[Motion->motionTypeBlend].bLoop;
				Motion->nNumKeyBlend = Motion->aMotionInfo[Motion->motionTypeBlend].nNumKey;
			}
			else if (Motion->nKey > Motion->NextKey)
			{// 今のキーが次のキー以上だったら
				Motion->nKey = 0;
			}
		}
	}
	if (Motion->nCntMotionBlend >= Motion->aMotionInfo[Motion->motionTypeBlend].aKeyInfo[Motion->nKeyBlend].nFrame)
	{// ブレンドモーションカウンターが目標のフレーム以上だったら
		Motion->nCntMotionBlend = 0;
		Motion->nKeyBlend++;
		Motion->nNextKeyBlend++;

		if (Motion->nKeyBlend == Motion->nNumKeyBlend - 1)
		{// 今のキーがキーの最大数だったら
			if (Motion->bLoopBlend == true)
			{// ループするタイプだったら
				Motion->nNextKeyBlend = 0;
			}
			else
			{// ループしないタイプだったら
				Motion->bBlendMotion = false;
				Motion->nNextKeyBlend = Motion->nKeyBlend;
			}
		}
		else if (Motion->nKeyBlend > Motion->nNextKeyBlend)
		{// 今のキーが次のキー以上だったら
			if (Motion->bLoopBlend == true)
			{// ループするタイプだったら
				Motion->nKeyBlend = 0;
			}
		}
	}

	KEYINFO nKey = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey];
	KEYINFO nNexKey = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->NextKey];

	float fRateMotion = (float)Motion->nCntMotion / (float)nKey.nFrame;

	//ブレンドモーションがない時
	if (Motion->bBlendMotion == false)
	{
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
			Motion->aModel[PartsCount].pos.x = Motion->aModel[PartsCount].OffSetPos.x + KeyDest.fPosX;
			Motion->aModel[PartsCount].pos.y = Motion->aModel[PartsCount].OffSetPos.y + KeyDest.fPosY;
			Motion->aModel[PartsCount].pos.z = Motion->aModel[PartsCount].OffSetPos.z + KeyDest.fPosZ;

			Motion->aModel[PartsCount].rot.x = Motion->aModel[PartsCount].OffSetRot.x + KeyDest.fRotX;
			Motion->aModel[PartsCount].rot.y = Motion->aModel[PartsCount].OffSetRot.y + KeyDest.fRotY;
			Motion->aModel[PartsCount].rot.z = Motion->aModel[PartsCount].OffSetRot.z + KeyDest.fRotZ;
		}
	}
	//ブレンドモーションがある時
	else
	{
		KEYINFO nKeyBlend = Motion->aMotionInfo[Motion->motionTypeBlend].aKeyInfo[Motion->nKeyBlend];
		KEYINFO nNextKeyBlend = Motion->aMotionInfo[Motion->motionTypeBlend].aKeyInfo[Motion->nNextKeyBlend];

		float fRateMotionBlend = (float)Motion->nCntMotionBlend / (float)Motion->aMotionInfo[Motion->motionTypeBlend].aKeyInfo[Motion->nKeyBlend].nFrame;
		float fRateBlend = (float)Motion->nCntBlend / (float)Motion->nFrameBlend;

		for (int PartsCount = 0; PartsCount < Motion->nNumModel; PartsCount++)
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
			fDiffMotionBlend.x = nNextKeyBlend.aKey[PartsCount].fRotX - nKeyBlend.aKey[PartsCount].fRotX;
			fDiffMotionBlend.y = nNextKeyBlend.aKey[PartsCount].fRotY - nKeyBlend.aKey[PartsCount].fRotY;
			fDiffMotionBlend.z = nNextKeyBlend.aKey[PartsCount].fRotZ - nKeyBlend.aKey[PartsCount].fRotZ;
			D3DXVECTOR3 fRotBlend;
			fRotBlend.x = nKeyBlend.aKey[PartsCount].fRotX + (fDiffMotionBlend.x * fRateMotionBlend);
			fRotBlend.y = nKeyBlend.aKey[PartsCount].fRotY + (fDiffMotionBlend.y * fRateMotionBlend);
			fRotBlend.z = nKeyBlend.aKey[PartsCount].fRotZ + (fDiffMotionBlend.z * fRateMotionBlend);

			D3DXVECTOR3 fDiffBlendRot = fRotBlend - fRotCurrent;

			D3DXVECTOR3 fDiffMotionPos;
			fDiffMotionPos.x = nNexKey.aKey[PartsCount].fPosX - nKey.aKey[PartsCount].fPosX;
			fDiffMotionPos.y = nNexKey.aKey[PartsCount].fPosY - nKey.aKey[PartsCount].fPosY;
			fDiffMotionPos.z = nNexKey.aKey[PartsCount].fPosZ - nKey.aKey[PartsCount].fPosZ;
			D3DXVECTOR3 fPosCurrent;
			fPosCurrent.x = nKey.aKey[PartsCount].fPosX + (fDiffMotion.x * fRateMotion);
			fPosCurrent.y = nKey.aKey[PartsCount].fPosY + (fDiffMotion.y * fRateMotion);
			fPosCurrent.z = nKey.aKey[PartsCount].fPosZ + (fDiffMotion.z * fRateMotion);

			D3DXVECTOR3 fDiffMotionBlendPos;
			fDiffMotionBlendPos.x = nNextKeyBlend.aKey[PartsCount].fPosX - nKeyBlend.aKey[PartsCount].fPosX;
			fDiffMotionBlendPos.y = nNextKeyBlend.aKey[PartsCount].fPosY - nKeyBlend.aKey[PartsCount].fPosY;
			fDiffMotionBlendPos.z = nNextKeyBlend.aKey[PartsCount].fPosZ - nKeyBlend.aKey[PartsCount].fPosZ;
			D3DXVECTOR3 fPosBlend;
			fPosBlend.x = nKeyBlend.aKey[PartsCount].fPosX + (fDiffMotionBlendPos.x * fRateMotionBlend);
			fPosBlend.y = nKeyBlend.aKey[PartsCount].fPosY + (fDiffMotionBlendPos.y * fRateMotionBlend);
			fPosBlend.z = nKeyBlend.aKey[PartsCount].fPosZ + (fDiffMotionBlendPos.z * fRateMotionBlend);

			D3DXVECTOR3 fDiffBlendPos = fPosBlend - fPosCurrent;
			D3DXVECTOR3 fPos, fRot;

			fPos.x = fPosCurrent.x + (fDiffBlendPos.x * fRateBlend);
			fPos.y = fPosCurrent.y + (fDiffBlendPos.y * fRateBlend);
			fPos.z = fPosCurrent.z + (fDiffBlendPos.z * fRateBlend);

			fRot.x = fRotCurrent.x + (fDiffBlendRot.x * fRateBlend);
			fRot.y = fRotCurrent.y + (fDiffBlendRot.y * fRateBlend);
			fRot.z = fRotCurrent.z + (fDiffBlendRot.z * fRateBlend);

			Motion->aModel[PartsCount].pos = Motion->aModel[PartsCount].OffSetPos + fPos;
			Motion->aModel[PartsCount].rot = Motion->aModel[PartsCount].OffSetRot + fRot;
		}
		Motion->nCntBlend++;
		if (Motion->nCntBlend >= Motion->nFrameBlend)
		{
			Motion->nCntBlend = 0;
			SetMotion(Motion->motionTypeBlend, Motion);
			Motion->bFinish = false;
			Motion->bBlendMotion = false;
		}
	}
}