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
#include "skill.h"
#include "particle.h"
#include "circle.h"
#include "sound.h"

//***************
// グローバル変数
//***************

//*********************
// モーションの更新処理
//*********************
void UpdateMotion(OBJECTINFO* Motion)
{
	if (Motion->bBlendMotion == false)
	{//ブレンドじゃないなら

	}
	else if (Motion->bBlendMotion == true)
	{//ブレンドなら

	}

	Motion->nCntMotion++;

	//ブレンドモーションがない時
	if (Motion->bFinish == false && Motion->bFirstBlend == false)
	{
		UpdateCurrentMotion(Motion);
	}
	//ブレンドモーションがある時
	else if(Motion->bFinish == true || Motion->bFirstBlend == true)
	{
		Motion->nCntMotionBlend++;
		UpdateBlendMotion(Motion);
	}
}
//*********************
// モーションの設定処理
//*********************
void SetMotion(MOTIONTYPE MotionType, OBJECTINFO* Motion, int BlendFlame)
{
	Motion->motionTypeBlend = MotionType;
	Motion->nKeyBlend = 0;
	Motion->nNextKeyBlend = 1;
	Motion->nCntMotionBlend = 0;
	Motion->nFrameBlend = BlendFlame;
	Motion->bFirstBlend = true;
	Motion->bFinish = false;
}
void UpdateCurrentMotion(OBJECTINFO* Motion)
{
	const bool bMotionCondision = Motion->aMotionInfo[Motion->motionType].nNumKey != NULL;
	const bool bGreaterMotionCount = Motion->nCntMotion >= Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].nFrame;
	const bool bFinishCondision = Motion->aMotionInfo[Motion->motionType].nNumKey - 1 <= Motion->nKey;
	const bool bLoopMotion = Motion->aMotionInfo[Motion->motionType].bLoop == false;

	if (bFinishCondision)
	{
		if (bLoopMotion)
		{
			Motion->bFinish = true;
			Motion->motionTypeBlend = MOTIONTYPE_NEUTRAL;
		}
	}

	if (bMotionCondision)
	{
		Motion->nNextKey = (Motion->nKey + 1) % Motion->aMotionInfo[Motion->motionType].nNumKey;
	}
	else
	{
		Motion->motionType = MOTIONTYPE_NEUTRAL;
	}

	if (bGreaterMotionCount)
	{// モーションカウンターが目標のフレーム以上だったら
		Motion->nCntMotion = 0;
		if (bMotionCondision)
		{
			Motion->nKey = (Motion->nKey + 1) % Motion->aMotionInfo[Motion->motionType].nNumKey;
		}
		else
		{
			Motion->motionType = MOTIONTYPE_NEUTRAL;
		}
	}
	for (int PartsCount = 0; PartsCount < Motion->nNumModel; PartsCount++)
	{// モデル分回す
		KEY KeyDef;
		KEY KeyDest;

		// 差分
		KeyDef.fPosX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nNextKey].aKey[PartsCount].fPosX - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosX;
		KeyDef.fPosY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nNextKey].aKey[PartsCount].fPosY - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosY;
		KeyDef.fPosZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nNextKey].aKey[PartsCount].fPosZ - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fPosZ;

		KeyDef.fRotX = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nNextKey].aKey[PartsCount].fRotX - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotX;
		KeyDef.fRotY = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nNextKey].aKey[PartsCount].fRotY - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotY;
		KeyDef.fRotZ = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nNextKey].aKey[PartsCount].fRotZ - Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nKey].aKey[PartsCount].fRotZ;

		// 角度の近道
		if (KeyDef.fRotX >= D3DX_PI)
		{
			KeyDef.fRotX -= D3DX_PI * 2.0f;
		}
		else if (KeyDef.fRotX <= -D3DX_PI)
		{
			KeyDef.fRotX += D3DX_PI * 2.0f;
		}

		// 角度の近道
		if (KeyDef.fRotY >= D3DX_PI)
		{
			KeyDef.fRotY -= D3DX_PI * 2.0f;
		}
		else if (KeyDef.fRotY <= -D3DX_PI)
		{
			KeyDef.fRotY += D3DX_PI * 2.0f;
		}

		// 角度の近道
		if (KeyDef.fRotZ >= D3DX_PI)
		{
			KeyDef.fRotZ -= D3DX_PI * 2.0f;
		}
		else if (KeyDef.fRotZ <= -D3DX_PI)
		{
			KeyDef.fRotZ += D3DX_PI * 2.0f;
		}

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
	CheckActionFlame(Motion);
}
void UpdateBlendMotion(OBJECTINFO* Motion)
{
	const bool nNumKeyCondision = Motion->aMotionInfo[Motion->motionTypeBlend].nNumKey != NULL;
	const bool GreaterMotionCount = Motion->nCntMotion >= Motion->aMotionInfo[Motion->motionTypeBlend].aKeyInfo[Motion->nKeyBlend].nFrame;

	if (nNumKeyCondision)
	{
		Motion->nNextKeyBlend = Motion->nKeyBlend + 1 % Motion->aMotionInfo[Motion->motionTypeBlend].nNumKey;
	}
	else
	{
		Motion->motionType = MOTIONTYPE_NEUTRAL;
	}

	if (GreaterMotionCount)
	{// モーションカウンターが目標のフレーム以上だったら
		Motion->nCntMotion = 0;
		if (nNumKeyCondision)
		{
			Motion->nKeyBlend = Motion->nKeyBlend + 1 % Motion->aMotionInfo[Motion->motionTypeBlend].nNumKey;
		}
		else
		{
			Motion->motionType = MOTIONTYPE_NEUTRAL;
		}
	}

	KEYINFO nKey = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nNextKey];
	KEYINFO nNextKey = Motion->aMotionInfo[Motion->motionType].aKeyInfo[Motion->nNextKey];

	KEYINFO nKeyBlend = Motion->aMotionInfo[Motion->motionTypeBlend].aKeyInfo[Motion->nKeyBlend];
	KEYINFO nNextKeyBlend = Motion->aMotionInfo[Motion->motionTypeBlend].aKeyInfo[Motion->nNextKeyBlend];

	float fRateMotion = (float)Motion->nCntMotion / (float)nKey.nFrame;
	float fRateMotionBlend = (float)Motion->nCntMotionBlend / (float)Motion->aMotionInfo[Motion->motionTypeBlend].aKeyInfo[Motion->nKeyBlend].nFrame;
	float fRateBlend = (float)Motion->nCntBlend / (float)Motion->nFrameBlend;

	for (int PartsCount = 0; PartsCount < Motion->nNumModel; PartsCount++)
	{
		D3DXVECTOR3 fDiffMotion;
		fDiffMotion.x = nNextKey.aKey[PartsCount].fRotX - nKey.aKey[PartsCount].fRotX;
		fDiffMotion.y = nNextKey.aKey[PartsCount].fRotY - nKey.aKey[PartsCount].fRotY;
		fDiffMotion.z = nNextKey.aKey[PartsCount].fRotZ - nKey.aKey[PartsCount].fRotZ;
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
		fDiffMotionPos.x = nNextKey.aKey[PartsCount].fPosX - nKey.aKey[PartsCount].fPosX;
		fDiffMotionPos.y = nNextKey.aKey[PartsCount].fPosY - nKey.aKey[PartsCount].fPosY;
		fDiffMotionPos.z = nNextKey.aKey[PartsCount].fPosZ - nKey.aKey[PartsCount].fPosZ;
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
	const bool bFinishBlend = Motion->nCntBlend >= Motion->nFrameBlend;

	if (bFinishBlend)
	{
		Motion->nCntBlend = 0;
		Motion->motionType = Motion->motionTypeBlend;
		Motion->bFirstBlend = false;
		Motion->bFinish = false;
		Motion->bBlendMotion = false;
	}
}
void CheckActionFlame(OBJECTINFO* Motion)
{
	for (int ActionFrameCount = 0; ActionFrameCount < MAX_ACTIONDIRECTION; ActionFrameCount++)
	{
		const bool bStartFlameCondision = Motion->nKey == Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].nStartKey 
			&& Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].bFirst == false;
		const bool bActionFlameCondision = Motion->nCntMotionBlend >= Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].nStartFrame 
			|| Motion->nCntMotion >= Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].nStartFrame;

		if (bStartFlameCondision)
		{
			if (bActionFlameCondision)
			{
				Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].bFirst = true;
				Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].bActionStart = true;
			}
		}
		if (Motion->nKey == Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].nEndKey &&
			Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].bFirst == true &&
			Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].bActionStart == true
			)
		{
			if (Motion->nCntMotionBlend >= Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].nEndFrame ||
				Motion->nCntMotion >= Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].nEndFrame)
			{
				Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].bActionStart = false;
			}
		}
		if (Motion->aMotionInfo[Motion->motionType].ActionFrameInfo[ActionFrameCount].bActionStart == true)
		{
			switch (ActionFrameCount)
			{
			case 0:
				CaceOneAction(Motion);
				break;
			case 1:
				CaceTwoAction(Motion);
				break;
			case 2:
				CaceThreeAction(Motion);
				break;
			default:
				break;
			}
		}
	}
}
void CaceOneAction(OBJECTINFO* Motion)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 Pos;
	Pos.x = pPlayer->mtxWand._41;
	Pos.y = pPlayer->mtxWand._42;
	Pos.z = pPlayer->mtxWand._43;


	switch (Motion->motionType)
	{
	case MOTIONTYPE_MOVE:
		// エフェクトの設定
		SetEffect(D3DXVECTOR3(pPlayer->PlayerMotion.aModel[7].mtxWorld._41, pPlayer->PlayerMotion.aModel[7].mtxWorld._42, pPlayer->PlayerMotion.aModel[7].mtxWorld._43),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			50,
			0,
			D3DXVECTOR3(1.0f, 1.0f, 1.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			EFFECT_SMOKE,
			0,
			0.0f,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		break;
	case MOTIONTYPE_ACTION:
		pPlayer->state = PLAYERSTATE_NORMAL;
		if (pPlayer->Status.nMP >= 50)
		{
			// MPを減らす
			SubMP(pPlayer->Skilltype);

			SetSkill(Pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					pPlayer->rot,
					SKILLTYPE_NONE,
					0.0f);
			PlaySound(SOUND_LABEL_MAGIC);
		}
		break;
	case MOTIONTYPE_ACTION_HORMING:
		pPlayer->state = PLAYERSTATE_NORMAL;
		if (pPlayer->Status.nMP >= 100)
		{
			for (int nCount = 0; nCount < 5; nCount++)
			{
				D3DXVECTOR3 fDistance;
				float fRatio = 0.29f + D3DX_PI / 5 * nCount;
				fDistance.x = cosf(fRatio) * sinf(pPlayer->rot.y + D3DX_PI * 0.5f) * 50.0f;
				fDistance.y = sinf(fRatio) * 50.0f;
				fDistance.z = cosf(fRatio) * cosf(pPlayer->rot.y + D3DX_PI * 0.5f) * 50.0f;

				SetSkill(D3DXVECTOR3(pPlayer->PlayerMotion.aModel[1].mtxWorld._41,
					pPlayer->PlayerMotion.aModel[1].mtxWorld._42,
					pPlayer->PlayerMotion.aModel[1].mtxWorld._43) + fDistance,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					pPlayer->rot,
					SKILLTYPE_HORMING,
					fRatio);
			}
			// MPを減らす
			SubMP(pPlayer->Skilltype);
		}
		break;
	case MOTIONTYPE_ACTION_EXPLOSION:
		pPlayer->state = PLAYERSTATE_NORMAL;

		if (pPlayer->Status.nMP >= 10)
		{
			SetParticle(Pos,
				D3DXVECTOR3(628.0f, 1.0f, 628.0f),
				D3DXCOLOR(1.0f, 0.65f, 0.0f, 1.0f),
				PARTICLE_NONE,
				D3DXVECTOR3(2.0f, 2.0f, 2.0f),
				100,
				3,
				1.0f,
				1.0f,
				0.0f,
				EFFECT_EXPROSION);

			// MPを減らす
			SubMP(pPlayer->Skilltype);
		}
		break;
	case MOTIONTYPE_LANDING:
		SetParticle(pPlayer->pos,
			D3DXVECTOR3(628.0f, 1.0f, 628.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			PARTICLE_NONE,
			D3DXVECTOR3(1.0f, 1.0f, 1.0f),
			100,
			10,
			50.0f,
			50.0f,
			0.0f,
			EFFECT_SMOKE);
		break;
	default:
		break;
	}
}
void CaceTwoAction(OBJECTINFO* Motion)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 Pos;
	Pos.x = pPlayer->mtxWand._41;
	Pos.y = pPlayer->mtxWand._42;
	Pos.z = pPlayer->mtxWand._43;
	
	switch (Motion->motionType)
	{
	case MOTIONTYPE_MOVE:
		// エフェクトの設定
		SetEffect(D3DXVECTOR3(pPlayer->PlayerMotion.aModel[9].mtxWorld._41, pPlayer->PlayerMotion.aModel[9].mtxWorld._42, pPlayer->PlayerMotion.aModel[9].mtxWorld._43),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			50,
			0,
			D3DXVECTOR3(1.0f, 1.0f, 1.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			EFFECT_SMOKE,
			0,
			0.0f,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		break;
	case MOTIONTYPE_ACTION:
		// エフェクトの設定
		SetEffect(Pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			50,
			0,
			D3DXVECTOR3(5.0f, 0.5f, 0.0f),
			D3DXCOLOR(0.25f, 0.45f, 1.0f, 0.5f),
			EFFECT_SKILLFLASH,
			0,
			0.0f,
			D3DXVECTOR3(0.0f, pPlayer->rotDest.y, 0.5f));

		// エフェクトの設定
		SetEffect(Pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			50,
			0,
			D3DXVECTOR3(5.0f, 0.5f, 0.0f),
			D3DXCOLOR(0.25f, 0.45f, 1.0f, 0.5f),
			EFFECT_SKILLFLASH,
			0,
			0.0f,
			D3DXVECTOR3(0.0f, pPlayer->rotDest.y, -0.5f));

		// エフェクトの設定
		SetEffect(Pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			50,
			0,
			D3DXVECTOR3(10.0f, 0.5f, 1.0f),
			D3DXCOLOR(0.25f, 0.45f, 1.0f, 0.5f),
			EFFECT_SKILLFLASH,
			0,
			0.0f,
			D3DXVECTOR3(0.0f, pPlayer->rotDest.y, 0.0f));
		break;
	case MOTIONTYPE_ACTION_HORMING:
		break;
	case MOTIONTYPE_ACTION_EXPLOSION:
		// エフェクトの設定
		SetEffect(Pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			50,
			0,
			D3DXVECTOR3(5.0f, 0.5f, 0.0f),
			D3DXCOLOR(0.25f, 0.45f, 1.0f, 0.5f),
			EFFECT_SKILLFLASH,
			0,
			0.0f,
			D3DXVECTOR3(0.0f, pPlayer->rotDest.y, 0.5f));

		// エフェクトの設定
		SetEffect(Pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			50,
			0,
			D3DXVECTOR3(5.0f, 0.5f, 0.0f),
			D3DXCOLOR(0.25f, 0.45f, 1.0f, 0.5f),
			EFFECT_SKILLFLASH,
			0,
			0.0f,
			D3DXVECTOR3(0.0f, pPlayer->rotDest.y, -0.5f));

		// エフェクトの設定
		SetEffect(Pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			50,
			0,
			D3DXVECTOR3(10.0f, 0.5f, 1.0f),
			D3DXCOLOR(0.25f, 0.45f, 1.0f, 0.5f),
			EFFECT_SKILLFLASH,
			0,
			0.0f,
			D3DXVECTOR3(0.0f, pPlayer->rotDest.y, 0.0f));
		break;
	}
}
void CaceThreeAction(OBJECTINFO* Motion)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 Pos;
	Pos.x = pPlayer->mtxWand._41;
	Pos.y = pPlayer->mtxWand._42;
	Pos.z = pPlayer->mtxWand._43;

	//サークルのインデックス
	int circleIndx = 0;

	switch (Motion->motionType)
	{
	case MOTIONTYPE_ACTION:
		// エフェクトの設定
		SetEffect(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 1.0f, pPlayer->pos.z),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			215,
			0,
			D3DXVECTOR3(5.0f, 5.0f, 1.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			EFFECT_MAGICCIRCLE,
			0,
			0.0f,
			D3DXVECTOR3(-D3DX_PI * 0.5f, pPlayer->rotDest.y, 0.0f));

		//サークルの設定
		circleIndx = SetCircle(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 1.0f, pPlayer->pos.z),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.05f, 1.0f, 1.0f, 1.0f),
			20,
			0,
			10.0f,
			36.0f,
			false,
			true,
			0);

		//サークルのアニメーションの設定
		SetAnime(circleIndx,
			ANIMETYPE_0,
			60);

		break;
	case MOTIONTYPE_ACTION_HORMING:
		// エフェクトの設定
		SetEffect(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 1.0f, pPlayer->pos.z),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			215,
			0,
			D3DXVECTOR3(5.0f, 5.0f, 1.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			EFFECT_MAGICCIRCLE,
			0,
			0.0f,
			D3DXVECTOR3(-D3DX_PI * 0.5f, pPlayer->rotDest.y, 0.0f));

		//サークルの設定
		circleIndx = SetCircle(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 1.0f, pPlayer->pos.z),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.05f, 1.0f, 1.0f, 1.0f),
			20,
			0,
			10.0f,
			36.0f,
			false,
			true,
			0);

		//サークルのアニメーションの設定
		SetAnime(circleIndx,
			ANIMETYPE_0,
			60);

		break;
	}
}