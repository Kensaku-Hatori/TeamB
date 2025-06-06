//*********************************************************
// 
// カメラのアニメーション[cameraanim.cpp]
// Author:Hatori
// 
//*********************************************************

#include "cameraanim.h"

// 条件式の関数化
bool isMovieEffect(CameraAnim* Anim,int EffectIndx);

// 条件式の関数
void UpdateMovieEffect(CameraAnim* Anim);
void SetMovieEffect(CameraAnim* Anim, int Indx);

//*****************************
// カメラのアニメーションを更新
//*****************************
void UpdateCameraWork(CameraAnim* Anim, D3DXVECTOR3* PosV, D3DXVECTOR3* PosR, D3DXVECTOR3* Rot)
{
	Anim->nFrameCount++;
	Anim->AllFrame++;
	if(Anim->Anim[Anim->AnimType].nNumKey != NULL) Anim->nNexKey = (Anim->nKey + 1) % Anim->Anim[Anim->AnimType].nNumKey;
	if (Anim->nFrameCount >= Anim->Anim[Anim->AnimType].KeyInfo[Anim->nKey].nFrame)
	{
		Anim->nFrameCount = 0;
		if (Anim->Anim[Anim->AnimType].nNumKey != NULL) Anim->nKey = (Anim->nKey + 1) % Anim->Anim[Anim->AnimType].nNumKey;
		if (Anim->nKey >= Anim->Anim[Anim->AnimType].nNumKey - 1)
		{
			Anim->AllFrame = 0;
			if (Anim->Anim[Anim->AnimType].bLoop == false)
			{
				Anim->bFinish = true;
			}
		}
	}
	UpdateMovieEffect(Anim);
	CameraKey nKey = Anim->Anim[Anim->AnimType].KeyInfo[Anim->nKey];
	CameraKey nNexKey = Anim->Anim[Anim->AnimType].KeyInfo[Anim->nNexKey];

	CameraKey KeyDef;
	CameraKey KeyDest;

	// 差分
	KeyDef.PosR.x = nNexKey.PosR.x - nKey.PosR.x;
	KeyDef.PosR.y = nNexKey.PosR.y - nKey.PosR.y;
	KeyDef.PosR.z = nNexKey.PosR.z - nKey.PosR.z;

	KeyDef.PosV.x = nNexKey.PosV.x - nKey.PosV.x;
	KeyDef.PosV.y = nNexKey.PosV.y - nKey.PosV.y;
	KeyDef.PosV.z = nNexKey.PosV.z - nKey.PosV.z;

	KeyDef.Rot.x = nNexKey.Rot.x - nKey.Rot.x;
	KeyDef.Rot.y = nNexKey.Rot.y - nKey.Rot.y;
	KeyDef.Rot.z = nNexKey.Rot.z - nKey.Rot.z;

	// 角度の近道
	if (KeyDef.Rot.x >= D3DX_PI)
	{
		KeyDef.Rot.x -= D3DX_PI * 2.0f;
	}
	else if (KeyDef.Rot.x <= -D3DX_PI)
	{
		KeyDef.Rot.x += D3DX_PI * 2.0f;
	}

	// 角度の近道
	if (KeyDef.Rot.y >= D3DX_PI)
	{
		KeyDef.Rot.y -= D3DX_PI * 2.0f;
	}
	else if (KeyDef.Rot.y <= -D3DX_PI)
	{
		KeyDef.Rot.y += D3DX_PI * 2.0f;
	}

	// 角度の近道
	if (KeyDef.Rot.z >= D3DX_PI)
	{
		KeyDef.Rot.z -= D3DX_PI * 2.0f;
	}
	else if (KeyDef.Rot.z <= -D3DX_PI)
	{
		KeyDef.Rot.z += D3DX_PI * 2.0f;
	}

	// 希望の値
	KeyDest.PosV.x = nKey.PosV.x + KeyDef.PosV.x * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.PosV.y = nKey.PosV.y + KeyDef.PosV.y * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.PosV.z = nKey.PosV.z + KeyDef.PosV.z * ((float)Anim->nFrameCount / (float)nKey.nFrame);

	// 希望の値
	KeyDest.PosR.x = nKey.PosR.x + KeyDef.PosR.x * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.PosR.y = nKey.PosR.y + KeyDef.PosR.y * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.PosR.z = nKey.PosR.z + KeyDef.PosR.z * ((float)Anim->nFrameCount / (float)nKey.nFrame);

	// 希望の値
	KeyDest.Rot.x = nKey.Rot.x + KeyDef.Rot.x * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.Rot.y = nKey.Rot.y + KeyDef.Rot.y * ((float)Anim->nFrameCount / (float)nKey.nFrame);
	KeyDest.Rot.z = nKey.Rot.z + KeyDef.Rot.z * ((float)Anim->nFrameCount / (float)nKey.nFrame);

	// 足す
	PosV->x = KeyDest.PosV.x;
	PosV->y = KeyDest.PosV.y;
	PosV->z = KeyDest.PosV.z;

	// 足す
	PosR->x = KeyDest.PosR.x;
	PosR->y = KeyDest.PosR.y;
	PosR->z = KeyDest.PosR.z;

	// 足す
	Rot->x = KeyDest.Rot.x;
	Rot->y = KeyDest.Rot.y;
	Rot->z = KeyDest.Rot.z;
}

//*****************************
// カメラのアニメーションを設定
//*****************************
void SetCameraWork(CameraAnim *Anim, ANIMTYPE nType)
{
	Anim->AnimType = nType;
	Anim->nKey = 0;
	Anim->nNexKey = 0;
	Anim->nFrameCount = 0;
	Anim->bFinish = false;
}

//***************************
// ムービーエフェクトの条件式
//***************************
bool isMovieEffect(CameraAnim* Anim, int EffectIndx)
{
	return Anim->AllFrame >= Anim->Anim[Anim->AnimType].MovieEffect[EffectIndx].StartFrame && Anim->AllFrame <= Anim->Anim[Anim->AnimType].MovieEffect[EffectIndx].EndFrame;
}

//*****************************
// ムービーエフェクトの更新処理
//*****************************
void UpdateMovieEffect(CameraAnim* Anim)
{
	for (int MovieEffectCount = 0; MovieEffectCount < MAX_MOVIEEFFECTTYPE; MovieEffectCount++)
	{
		if (isMovieEffect(Anim, MovieEffectCount) == true)
		{
			SetMovieEffect(Anim, MovieEffectCount);
		}
	}
}

//*****************************
// ムービーエフェクトの設定処理
//*****************************
void SetMovieEffect(CameraAnim* Anim,int Indx)
{
	switch (Anim->Anim[Anim->AnimType].MovieEffect[Indx].EffectType)
	{
	case MOVIEEFFECT_NAME:
		SetBossNameEffect(Anim->Anim[Anim->AnimType].MovieEffect[Indx].SetNameEffect.Pos,
			Anim->Anim[Anim->AnimType].MovieEffect[Indx].SetNameEffect.Rot,
			Anim->Anim[Anim->AnimType].MovieEffect[Indx].SetNameEffect.Scale,
			Anim->Anim[Anim->AnimType].MovieEffect[Indx].SetNameEffect.Col,
			Anim->Anim[Anim->AnimType].MovieEffect[Indx].SetNameEffect.nLife);
		break;
	default:
		break;
	}
}